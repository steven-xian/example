#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVector>
#include <QMap>
#include <QVariant>

class TreeItem
{
public:
    enum ItemType {Root, Folder, Node, Project};
    enum ItemDataType {None, DataStream, DataFile, Solution};

    explicit TreeItem(const QVector<QVariant> &data, bool readOnly = false, ItemType itemType = Node,
                      ItemDataType itemDataType = DataStream, TreeItem* parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem* child(int row);
    TreeItem* child(ItemDataType itemDataType);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool setData(int column, const QVariant& value);
    int row() const;
    TreeItem* parentItem();
    QVariantMap properties() const;
    void addProperty(const QString& key, const QVariant& value);
    void addAllProperties(QVariantMap&& map);
    bool readOnly() const;
    ItemType type() const;
    ItemDataType dataType() const;

private:
    QVector<TreeItem*> m_childItems;
    QVector<QVariant> m_itemData;
    QVariantMap m_itemProperties;
    bool m_readOnly;
    ItemType m_itemType;
    ItemDataType m_itemDataType;
    TreeItem* m_parentItem = nullptr;
};

#endif // TREEITEM_H
