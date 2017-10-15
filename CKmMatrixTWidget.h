/**********************************************
 * time:2016-01-14 11:35:14
 * author:魏永倬
 * tel:15626234799
 * e-mail:jobshionway@qq.com
 *
 * km的输出信息matrixT显示窗口,通过获取CKm的const指针对窗口进行更新
 * 显示的内容不可修改
 * 表的列头名为role编号+名字,行头名为agent编号
 * *******************************************/
#ifndef CKMMATRIXTWIDGET_H
#define CKMMATRIXTWIDGET_H

#include "CKm.h"
#include <QWidget>
#include <QStandardItemModel>

class CKmMatrixTWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CKmMatrixTWidget(QWidget *parent = 0);
    ~CKmMatrixTWidget();

    vector<QColor> m_vColor;
    QStandardItemModel *m_pModelT;

private:
    void initWidget();
    void updateModels(const CKm *km);
public:
    void clearModels();

signals:

public slots:
    void updateWidget(const CKm *km);
};

#endif // CKMMATRIXTWIDGET_H
