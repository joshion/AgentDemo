/**********************************************
 * time:2016-01-14 11:28:20
 * author:魏永倬
 * tel:15626234799
 * e-mail:jobshionway@qq.com
 *
 * km的输入信息显示窗口,通过获取CKm的const指针对窗口进行更新
 * 显示的内容不可修改
 * Q,L,La分别在三个tableview中居中显示
 * Q表的列头名为role编号+名字,行头名为agent编号
 * L只有一行(隐藏行头名),列头名为role编号+名字
 * La只有一行(隐藏行头名),列头名为agent编号
 * *******************************************/
#ifndef CKMINFOWIDGET_H
#define CKMINFOWIDGET_H

#include "CKm.h"
#include <QWidget>
#include <QStandardItemModel>

class CKmInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CKmInfoWidget(QWidget *parent = 0);
    ~CKmInfoWidget();

private:
    QStandardItemModel *m_pModelL;
    QStandardItemModel *m_pModelQ;
    QStandardItemModel *m_pModelLa;
//    QStandardItemModel *m_pModelRoleName;

private:
    void initWidget();
    void initConnect();

    void updateModels(const CKm *km);
//    void updateModelRoleName(vector<QString> vectorRoleName);
    void updateModelQ(const vector<vector<float>> matrixQ, vector<QString> vectorRoleName);
    void updateModelL(const vector<int> vectorL, vector<QString> vectorRoleName);
    void updateModelLa(const vector<int> vectorLa);

public:
    void clearModels();

signals:

public slots:
    void updateWidget(const CKm *km);
};

#endif // CKMINFOWIDGET_H
