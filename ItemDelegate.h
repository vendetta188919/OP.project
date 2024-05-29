#pragma once

#include <QItemDelegate>

enum class validTypes
{
    validInt,
    validString,
    end
};

class ItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ItemDelegate(QObject *parent = 0);

protected:
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& = QStyleOptionViewItem(), const QModelIndex& = QModelIndex()) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex&) const;
};

