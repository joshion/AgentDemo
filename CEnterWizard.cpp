#include "CEnterWizard.h"
#include "CIntDelegate.h"
#include "CFloatDelegate.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QLabel>

CEnterWizard::CEnterWizard(QWidget *parent)
    : QWizard(parent)
{
    m_pFirst = new QWizardPage;
    m_pSecond = new QWizardPage;
    m_pThird = new QWizardPage;
    m_pFinal = new QWizardPage;
    m_pModelQ = new QStandardItemModel;
    m_pModelL = new QStandardItemModel;
    m_pModelRoleName = new QStandardItemModel;
    m_pModelBA = new QStandardItemModel;
    m_pSpinM = new QSpinBox;
    m_pSpinN = new QSpinBox;
    m_pKm = new CKm(0,0);
    m_uColumn = 0;
    m_uRow = 0;
    initWizard();
}

CEnterWizard::~CEnterWizard()
{

}

void CEnterWizard::initWizard()
{
    this->createFirstPage();
    this->createSecondPage();
    this->createThirdPage();
    this->createFinalPage();

    this->setPage(PageMN, m_pFirst);
    this->setPage(PageQ, m_pSecond);
    this->setPage(PageL, m_pThird);
    this->setPage(PageBA, m_pFinal);
}

void CEnterWizard::createFirstPage()
{
    //M(agent个数/矩阵行数)输入框
    m_pSpinM->setValue(1);
    m_pSpinM->setMinimum(1);    //设置最小输入值为1
    QLabel *pLabelM = new QLabel("M:");
    QHBoxLayout *pTopLayout= new QHBoxLayout;
    pTopLayout->addSpacing(150);
    pTopLayout->addWidget(pLabelM);
    pTopLayout->addWidget(m_pSpinM);
    pTopLayout->addSpacing(150);

    //N(role种类个数/矩阵列数)输入框
    m_pSpinN->setValue(1);
    m_pSpinN->setMinimum(1);    //设置最小输入值为1
    QLabel *pLabelN = new QLabel("N:");
    QHBoxLayout *pButtomLayout= new QHBoxLayout;
    pButtomLayout->addSpacing(150);
    pButtomLayout->addWidget(pLabelN);
    pButtomLayout->addWidget(m_pSpinN);
    pButtomLayout->addSpacing(150);

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addLayout(pTopLayout);
    pLayout->addLayout(pButtomLayout);
    m_pFirst->setLayout(pLayout);
}

void CEnterWizard::createSecondPage()
{
    //Q矩阵输入表格
    QLabel *pLabelQ = new QLabel("Q:");
    QTableView *pTableView = new QTableView;
    pTableView->setModel(m_pModelQ);
    pTableView->setItemDelegate(new CFloatDelegate);
    pTableView->horizontalHeader()->setStretchLastSection(false);    //设置最后一行不填满整个窗口
    pTableView->horizontalHeader()->setSectionsMovable(false);   //设置列不能拖动
    pTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //依据窗口空间调节列宽

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(pLabelQ);
    pLayout->addWidget(pTableView);
    m_pSecond->setLayout(pLayout);
}

void CEnterWizard::createThirdPage()
{
    //L数组输入表格
    QLabel *pLabelL = new QLabel("L:");
    QTableView *pTableViewL = new QTableView;
    pTableViewL->setModel(m_pModelL);
    pTableViewL->setItemDelegate(new CIntDelegate);
    pTableViewL->horizontalHeader()->setStretchLastSection(false);    //设置最后一行不填满整个窗口
    pTableViewL->horizontalHeader()->setSectionsMovable(false);   //设置列不能拖动
    pTableViewL->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //依据窗口空间调节列宽

    //roleName数组输入表格
    QLabel *pLabelRoleName = new QLabel("RoleName:");
    QTableView *pTableViewRoleName = new QTableView;
    pTableViewRoleName->setModel(m_pModelRoleName);
    pTableViewRoleName->horizontalHeader()->setStretchLastSection(false);    //设置最后一行不填满整个窗口
    pTableViewRoleName->horizontalHeader()->setSectionsMovable(false);   //设置列不能拖动
    pTableViewRoleName->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //依据窗口空间调节列宽

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(pLabelL);
    pLayout->addWidget(pTableViewL);
    pLayout->addWidget(pLabelRoleName);
    pLayout->addWidget(pTableViewRoleName);
    m_pThird->setLayout(pLayout);
}

void CEnterWizard::createFinalPage()
{

    QLabel *pLabelBA = new QLabel("La:");

    QTableView *pTableView = new QTableView;
    pTableView->setModel(m_pModelBA);
    pTableView->setItemDelegate(new CIntDelegate);
    pTableView->horizontalHeader()->setStretchLastSection(false);    //设置最后一行不填满整个窗口
    pTableView->horizontalHeader()->setSectionsMovable(false);   //设置列不能拖动
    pTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //依据窗口空间调节列宽

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(pLabelBA);
    pLayout->addWidget(pTableView);
    m_pFinal->setLayout(pLayout);
}

bool CEnterWizard::validateCurrentPage()    //重载next和finish按钮事件
{
    switch (this->currentId())
    {
    case PageMN:
        m_uRow = m_pSpinM->value();
        m_uColumn = m_pSpinN->value();

        if(m_uColumn != 0 && m_uRow != 0)   //行和列数都不为0时,显示表格
        {
            //更新model的大小
            m_pModelQ->setColumnCount(m_uColumn);
            m_pModelQ->setRowCount(m_uRow);
            m_pModelBA->setColumnCount(m_uRow); //m
            m_pModelL->setColumnCount(m_uColumn);   //n
            m_pModelRoleName->setColumnCount(m_uColumn);

            m_pModelL->setRowCount(1);
            m_pModelRoleName->setRowCount(1);
            m_pModelBA->setRowCount(1);
        }
        else    //如果列数为0,则不再添加行显示
        {
            m_pModelQ->setRowCount(0);
            m_pModelL->setRowCount(0);
            m_pModelRoleName->setRowCount(0);
            m_pModelBA->setRowCount(0);
        }
        break;
    default:
        break;
    }
    if(-1 == this->currentPage()->nextId()) //点击finish/cancel按钮事件
    {
        this->setKm();
        this->close();
    };
    return true;
}

void CEnterWizard::setKm()
{
    m_pKm = new CKm(m_uRow, m_uColumn); //设置km的m和n
    for(int i = 0; i < m_uRow; ++i) //设置km的Q
    {
        for(int j = 0; j < m_uColumn; ++j)
        {
            m_pKm->m_mQ[i][j] = m_pModelQ->index(i, j).data().toFloat();
        }
    }
    for(int i = 0; i < m_uRow; ++i)  //设置km的BA,长度为m
    {
        m_pKm->m_vLa[i] = m_pModelBA->index(0, i).data().toInt();
    }
    for(int i = 0; i < m_uColumn; ++i) //设置km的L和roleName,长度为n
    {
        m_pKm->m_vL[i] = m_pModelL->index(0, i).data().toInt();
        m_pKm->m_vRoleName[i] = m_pModelRoleName->index(0, i).data().toString();
    }
}
