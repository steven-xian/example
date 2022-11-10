#include "treeitem.h"

TreeItem::TreeItem(const QVector<QVariant> &data, bool readOnly, ItemType itemType, ItemDataType itemDataType, TreeItem* parent) :
    m_itemData(data), m_readOnly(readOnly), m_itemType(itemType), m_itemDataType(itemDataType),m_parentItem(parent)
{
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *child)
{
    m_childItems.append(child);
}

TreeItem* TreeItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;

    return m_childItems.at(row);
}

TreeItem::ItemType TreeItem::type() const
{
    return m_itemType;
}

TreeItem::ItemDataType TreeItem::dataType() const
{
    return m_itemDataType;
}

TreeItem* TreeItem::child(ItemDataType itemDataType)
{
    for (QVector<TreeItem*>::iterator it = m_childItems.begin(); it != m_childItems.end(); it++)
    {
        if ((*it)->dataType() == itemDataType)
            return *it;
    }

    return nullptr;
}


int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return 1;//m_itemData.count();
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.count())
        return QVariant();

    return m_itemData.at(column);
}

bool TreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= m_itemData.count())
        return false;

    m_itemData[column] = value;
    return true;
}

void TreeItem::addProperty(const QString &key, const QVariant &value)
{
    m_itemProperties.insert(key, value);
}

void TreeItem::addAllProperties(QVariantMap&& map)
{
    m_itemProperties.swap(map);
}

QVariantMap TreeItem::properties() const
{
    return m_itemProperties;
}

TreeItem* TreeItem::parentItem()
{
    return m_parentItem;
}

bool TreeItem::readOnly() const
{
    return m_readOnly;
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem *>(this));

    return 0;
}
