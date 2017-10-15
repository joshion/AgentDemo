#include "CFloatDelegate.h"
#include <QDoubleSpinBox>

CFloatDelegate::CFloatDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *CFloatDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setSingleStep(0.01);
    editor->setMinimum(0);
    editor->setMaximum(1);

    return editor;
}

void CFloatDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    float value = index.model()->data(index, Qt::EditRole).toFloat();

    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setValue(value);
}

void CFloatDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->interpretText();
    float value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
}

void CFloatDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
