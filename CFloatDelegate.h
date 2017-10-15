/***************************************************
 * 2016-01-09 20:31:18
 * tableview中表格的每一个单元的代理
 * 输入范围为0~1的浮点数,spin一次为0.01
 * *************************************************/

#ifndef CFLOATDELEGATE_H
#define CFLOATDELEGATE_H

#include <QStyledItemDelegate>

class CFloatDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    CFloatDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif
