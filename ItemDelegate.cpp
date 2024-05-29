#include "ItemDelegate.h"

#include <QLineEdit>
#include <QIntValidator>

ItemDelegate::ItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *ItemDelegate::createEditor(QWidget* parent,
                                    const QStyleOptionViewItem&,
                                    const QModelIndex& index) const
{
    if(index.column() == 0 || 3 || 5 || 6 || 7 || 8 || 9 || 10)
    {
        QLineEdit* editor = new QLineEdit(parent);
        editor->setValidator(new QIntValidator);
        return editor;
    }

    return new QLineEdit(parent);
}


void ItemDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        line->setText(value);
}


void ItemDelegate::setModelData(QWidget *editor,
                                QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    QString value = line->text();
    model->setData(index, value);
}


void ItemDelegate::updateEditorGeometry(QWidget* editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex&) const
{
    editor->setGeometry(option.rect);
}
