#include "CKmInfoWidget.h"
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLabel>

CKmInfoWidget::CKmInfoWidget(QWidget *parent) : QWidget(parent)
{
    m_pModelL = new QStandardItemModel;
    m_pModelQ = new QStandardItemModel;
    m_pModelLa = new QStandardItemModel;
//    m_pModelRoleName = new QStandardItemModel;
    initWidget();
}

CKmInfoWidget::~CKmInfoWidget()
{

}
void CKmInfoWidget::initWidget()
{
//    QLabel *pLabelRoleName = new QLabel("RoleName:");
//    QTableView *pTableViewRoleName = new QTableView();
//    pTableViewRoleName->setModel(m_pModelRoleName);
//    pTableViewRoleName->horizontalHeader()->setStretchLastSection(false);    //设置最后一行不填满整个窗口
//    pTableViewRoleName->horizontalHeader()->setSectionsMovable(false);   //设置列不能拖动
//    pTableViewRoleName->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //依据窗口空间调节列宽
//    pTableViewRoleName->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑

    QLabel *pLabelQ = new QLabel(tr("能力矩阵(Q):"));
    QTableView *pTableViewQ = new QTableView();
    pTableViewQ->setModel(m_pModelQ);
    pTableViewQ->horizontalHeader()->setStretchLastSection(false);    //设置最后一行不填满整个窗口
    pTableViewQ->horizontalHeader()->setSectionsMovable(false);   //设置列不能拖动
    pTableViewQ->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  //依据窗口空间调节列宽
    //pTableViewQ->resizeRowsToContents();   //依据内容调节行高
    pTableViewQ->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑

    QLabel *pLabelL = new QLabel(tr("需求向量(L):"));
    QTableView *pTableViewL = new QTableView();
    pTableViewL->horizontalHeader()->setStretchLastSection(false);    //设置最后一行不填满整个窗口
    pTableViewL->horizontalHeader()->setSectionsMovable(false);   //设置列不能拖动
    pTableViewL->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  //依据窗口空间调节列宽
    pTableViewL->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    pTableViewL->verticalHeader()->setVisible(false);   //隐藏行头
    pTableViewL->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    pTableViewL->setModel(m_pModelL);

    QLabel *pLabelLa = new QLabel(tr("能力限制矩阵(La):"));
    QTableView *pTableViewLa = new QTableView();
    pTableViewLa->horizontalHeader()->setStretchLastSection(false);    //设置最后一行不填满整个窗口
    pTableViewLa->horizontalHeader()->setSectionsMovable(false);   //设置列不能拖动
    pTableViewLa->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  //依据窗口空间调节列宽
    pTableViewLa->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    pTableViewLa->verticalHeader()->setVisible(false);   //隐藏行头
    pTableViewLa->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    pTableViewLa->setModel(m_pModelLa);

    QVBoxLayout *pLayout = new QVBoxLayout;
//    pLayout->addWidget(pLabelRoleName);
//    pLayout->addWidget(pTableViewRoleName);
    pLayout->addWidget(pLabelQ);
    pLayout->addWidget(pTableViewQ, 1080);
    pLayout->addWidget(pLabelL);
    pLayout->addWidget(pTableViewL, 80);
    pLayout->addWidget(pLabelLa);
    pLayout->addWidget(pTableViewLa, 80);
    this->setLayout(pLayout);
}

void CKmInfoWidget::CKmInfoWidget::initConnect()
{

}

void CKmInfoWidget::updateModels(const CKm *km)
{
    clearModels();
    if(km->isKmLegal())
    {
        //updateModelRoleName(km->m_vRoleName);
        updateModelQ(km->m_mQ, km->m_vRoleName);
        updateModelL(km->m_vL, km->m_vRoleName);
        updateModelLa(km->m_vLa);
    }
}

//void CKmInfoWidget::updateModelRoleName(vector<QString> vectorRoleName)
//{
//    if  (vectorRoleName.size() > 0)
//    {
//        m_pModelRoleName->setColumnCount(vectorRoleName.size);
//    }
//}

void CKmInfoWidget::updateModelQ(const vector<vector<float>> matrixQ, vector<QString> vectorRoleName)
{
//    m_pModelRoleName->setColumnCount(vectorRoleName.size);
    m_pModelQ->setColumnCount(vectorRoleName.size());
    m_pModelQ->setRowCount(matrixQ.size());

    for (int i = 0; i < static_cast<int>(matrixQ.size()); ++i)
    {
        m_pModelQ->setHeaderData(i, Qt::Orientation::Vertical,
                                  QString("A%1").arg(QString::number(i+1)));
    }

    for (int i = 0; i < static_cast<int>(vectorRoleName.size()); ++i)
    {
        m_pModelQ->setHeaderData(i, Qt::Orientation::Horizontal,
                                 QString("R%1(%2)").arg(QString::number(i+1)).arg(vectorRoleName[i]));
        for(int j = 0; j < static_cast<int>(matrixQ.size()); ++j)
        {
            QModelIndex index = m_pModelQ->index(j, i, QModelIndex());
            m_pModelQ->setData(index, QVariant(matrixQ[j][i]));
            m_pModelQ->item(j, i)->setTextAlignment(Qt::AlignCenter);   //设置表格文本居中显示
        }
    }
}

void CKmInfoWidget::updateModelL(const vector<int> vectorL, vector<QString> vectorRoleName)
{
    m_pModelL->setColumnCount(vectorL.size());
    m_pModelL->setRowCount(1);
    for (int i = 0; i < static_cast<int>(vectorL.size()); ++i)
    {
        m_pModelL->setHeaderData(i, Qt::Orientation::Horizontal,
                                 QString("R%1(%2)").arg(QString::number(i+1)).arg(vectorRoleName[i]));
        QModelIndex index = m_pModelL->index(0, i, QModelIndex());
        m_pModelL->setData(index, QVariant(vectorL[i]));
        m_pModelL->item(0, i)->setTextAlignment(Qt::AlignCenter);   //设置表格文本居中显示
    }

}

void CKmInfoWidget::updateModelLa(const vector<int> vectorLa)
{
    m_pModelLa->setColumnCount(vectorLa.size());
    m_pModelLa->setRowCount(1);
    for (int i = 0; i < static_cast<int>(vectorLa.size()); ++i)
    {
        m_pModelLa->setHeaderData(i, Qt::Orientation::Horizontal,
                                  QString("A%1").arg(QString::number(i+1)));
        QModelIndex index = m_pModelLa->index(0, i, QModelIndex());
        m_pModelLa->setData(index, QVariant(vectorLa[i]));
        m_pModelLa->item(0, i)->setTextAlignment(Qt::AlignCenter);   //设置表格文本居中显示
    }
}

void CKmInfoWidget::clearModels()
{
    m_pModelQ->clear();
    m_pModelL->clear();
    m_pModelLa->clear();
}

void CKmInfoWidget::updateWidget(const CKm *km)
{
    this->updateModels(km);
}
