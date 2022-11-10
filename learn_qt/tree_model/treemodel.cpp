#include "treemodel.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QBrush>
#include <QIcon>

TreeModel::TreeModel(const QString& data, QObject *parent)
    : QAbstractItemModel(parent)
{
    loadModelData(data);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem* parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();

    return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant result;
    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

    switch(role)
    {
    case Qt::DisplayRole:
        result = item->data(index.column());
        break;

    case Qt::DecorationRole :
        switch(item->type())
        {
        case TreeItem::Project:
            result = QVariant( QIcon("://icon/project.png") );
            break;

        case TreeItem::Folder:
            switch(item->dataType())
            {
            case TreeItem::DataStream:
                result = QVariant( QIcon("://icon/data_stream.png") );
                break;

            case TreeItem::DataFile:
                result = QVariant( QIcon("://icon/data_file.png") );
                break;

            case TreeItem::Solution:
                result = QVariant( QIcon("://icon/cal_res.png") );
                break;
            }
            break;

        case TreeItem::Node:
            result = QVariant( QIcon("://icon/menu_undo.png") );
            break;
        }

        break;

    default:
        result = QVariant();
    }

    return result;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, QVariantMap& variantMap, int role)
{
    if (!index.isValid())
        return false;

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    item->setData(index.column(), value);
    item->addAllProperties(std::move(variantMap));

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    return item->readOnly() ? Qt::ItemIsSelectable : Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

QModelIndex TreeModel::childIndex(TreeItem::ItemDataType type)
{
    TreeItem* childItem = rootItem->child(0)->child(type);
    if (childItem)
        return createIndex(childItem->row(), 0, childItem);

    return QModelIndex();
}

int TreeModel::childCount(const QModelIndex &index) const
{
    if (!index.isValid())
        return -1;

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

    return item->childCount();
}

QString TreeModel::toJson() const
{
    TreeItem* prjItem = rootItem->child(0);

    QJsonDocument jsonDoc;
    QJsonObject rootObj;

    rootObj.insert("name", prjItem->data(0).toString());
    toJsonValue(rootObj, prjItem);

    jsonDoc.setObject(rootObj);

    QString jsonStr = jsonDoc.toJson();
    return jsonStr;
}

void TreeModel::toJsonValue(QJsonObject& jsonObject, TreeItem* parentItem) const
{
    for(int i = 0; i < parentItem->childCount(); i++)
    {
        TreeItem* item = parentItem->child(i);
        QJsonArray childArray;

        switch(item->type())
        {
        case TreeItem::DataStream:
            {
                toJsonArray(childArray, item);
                jsonObject.insert("connection", childArray);
            }
            break;

        case TreeItem::DataFile:
            {
                toJsonArray(childArray, item);
                jsonObject.insert("file", childArray);
            }
            break;

        case TreeItem::Solution:
            {
                toJsonArray(childArray, item);
                jsonObject.insert("solution", childArray);
            }
            break;
        }
    }
}

void TreeModel::toJsonArray(QJsonArray& childArray, TreeItem* parentItem) const
{
    for(int i = 0; i < parentItem->childCount(); i++)
    {
        QJsonObject childObj;
        TreeItem* item = parentItem->child(i);

        childObj.insert("name", item->data(0).toString());
        childArray.append(childObj.fromVariantMap(item->properties()));
    }
}

bool TreeModel::appendChild(const QModelIndex &index, const QVariant &value, QVariantMap &variantMap)
{
    if (!index.isValid())
        return false;

    this->beginInsertRows(index, 0, index.row() + 1);
    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* child = new TreeItem({value}, false, TreeItem::Node, TreeItem::DataStream, item);
    item->appendChild(child);
    child->addAllProperties(std::move(variantMap));

    this->endInsertRows();
    return true;
}

TreeItem* TreeModel::root() const
{
    TreeItem* prjItem = rootItem->child(0);

    return  prjItem;
}

bool TreeModel::loadModelData(const QString& data)
{
    QJsonParseError errRpt;

    QJsonDocument rootDoc = QJsonDocument::fromJson(data.toUtf8(), &errRpt);
    if (errRpt.error != QJsonParseError::NoError && !rootDoc.isNull())
        return false;

    QJsonObject rootObj = rootDoc.object();
    QString prjName = rootObj.find("name")->toString();
    rootItem = new TreeItem({QStringLiteral("root")}, true, TreeItem::Root);

    TreeItem* prjItem = new TreeItem({prjName}, true, TreeItem::Project, TreeItem::None, rootItem);
    TreeItem* dataTreeItem = new TreeItem({QStringLiteral("数据流")}, true, TreeItem::Folder, TreeItem::DataStream, prjItem);
    TreeItem* fileTreeItem = new TreeItem({QStringLiteral("数据文件")}, true, TreeItem::Folder, TreeItem::DataFile, prjItem);
    TreeItem* solItem = new TreeItem({QStringLiteral("解算结果")}, true, TreeItem::Folder,  TreeItem::Solution, prjItem);

    rootItem->appendChild(prjItem);
    prjItem->appendChild(dataTreeItem);
    prjItem->appendChild(fileTreeItem);
    prjItem->appendChild(solItem);

    //数据流
    QJsonArray connArray = rootObj.find("connection").value().toArray();
    for (int i = 0; i < connArray.count(); i++)
    {
        QJsonObject connObj = connArray.at(i).toObject();

        QString name = connObj.find("name")->toString();

        TreeItem* item = new TreeItem({name}, false, TreeItem::Node, TreeItem::DataStream, dataTreeItem);
        item->addAllProperties(connObj.toVariantMap());
        dataTreeItem->appendChild(item);
    }

    //回放文件
    QJsonArray fileArray = rootObj.find("file").value().toArray();
    for (int i = 0; i < fileArray.count(); i++)
    {
        QJsonObject fileObj = fileArray.at(i).toObject();

        QString name = fileObj.find("name")->toString();

        TreeItem* item = new TreeItem({name}, false, TreeItem::Node, TreeItem::DataFile, fileTreeItem);
        item->addAllProperties(fileObj.toVariantMap());
        fileTreeItem->appendChild(item);
    }

    //解算结果
    QJsonArray solArray = rootObj.find("solution").value().toArray();
    for (int i = 0; i < fileArray.count(); i++)
    {
        QJsonObject solObj = solArray.at(i).toObject();

        QString name = solObj.find("name")->toString();
        TreeItem* item = new TreeItem({name}, false, TreeItem::Node, TreeItem::Solution, solItem);
        item->addAllProperties(solObj.toVariantMap());
        solItem->appendChild(item);
    }
}
