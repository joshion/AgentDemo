/***************************************************
 * 2016-01-09 20:31:18
 * tableview中表格的每一个单元的代理
 * 输入范围为0~100的整型数,spin一次为1
 * *************************************************/
#ifndef CINTDELEGATE_H
#define CNITDELEGATE_H

#include <QStyledItemDelegate>

class CIntDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    CIntDelegate(int max = 100, int min = 0, QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    int m_max;  //可输入的最大值
    int m_min;  //可输入的最小值
};

#endif
