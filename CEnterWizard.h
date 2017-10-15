/***************************************************
 * 2016-01-08 19:00:24
 * 已知bug：按cancel出错
 * L/BA的各元素之和没有控制
 *
 * 2016-01-09 20:27:37
 * 需要将m_pKm修改为const返回传递给mainwindow
 * *************************************************/
#ifndef CWIZARD_H
#define CWIZARD_H

#include "CKm.h"
#include<QWizard>
#include<QWizardPage>
#include <QStandardItemModel>
#include <QSpinBox>

class CEnterWizard : public QWizard
{
public:
    CEnterWizard(QWidget *parent = 0);
    ~CEnterWizard();
    enum {PageMN, PageQ, PageL, PageBA};

private:
    QWizardPage *m_pFirst;
    QWizardPage *m_pSecond;
    QWizardPage *m_pThird;
    QWizardPage *m_pFinal;
    QSpinBox *m_pSpinM;
    QSpinBox *m_pSpinN;
    QStandardItemModel *m_pModelQ;
    QStandardItemModel *m_pModelL;
    QStandardItemModel *m_pModelRoleName;
    QStandardItemModel *m_pModelBA;
    int m_uColumn;  //model的列数
    int m_uRow; //model的行数(ModelBA的列数)

private:
    void initWizard();
    void createFirstPage();
    void createSecondPage();
    void createThirdPage();
    void createFinalPage();
    void initConnect();
    virtual bool validateCurrentPage();    //重载next和finish按钮事件

public:
    CKm *m_pKm; //用于将wizard里获取的信息传递给mainwindow

private slots:
    void setKm();
};

#endif // CWIZARD_H
