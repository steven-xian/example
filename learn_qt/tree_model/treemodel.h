#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "treeitem.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(const QString& data, QObject *parent = nullptr);
    ~TreeModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, QVariantMap& variantMap,
                 int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QModelIndex childIndex(TreeItem::ItemDataType type);

    bool appendChild(const QModelIndex &index, const QVariant &value, QVariantMap& variantMap);

    int childCount(const QModelIndex &index) const;

    QString toJson() const;

    void toJsonValue(QJsonObject& jsonObject, TreeItem* parentItem) const;

    void toJsonArray(QJsonArray& childArray, TreeItem* parentItem) const;

    TreeItem* root() const;

private:
    TreeItem *rootItem;

    bool loadModelData(const QString& data);
};

#endif // TREEMODEL_H
