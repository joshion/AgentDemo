#include "CKmMatrixTWidget.h"
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLabel>

CKmMatrixTWidget::CKmMatrixTWidget(QWidget *parent)
    : QWidget(parent)
{
    for(int i = 0; i < 10; ++i)
    {
        if(i % 3 == 0)
            m_vColor.push_back(QColor(i*20, 0, 100, 255));
        if(i % 3 == 1)
            m_vColor.push_back(QColor(100, i*20, 0, 255));
        if(i % 3 == 2)
            m_vColor.push_back(QColor(0, 100, i*20, 255));
    }
    m_pModelT = new QStandardItemModel;

    initWidget();
}

CKmMatrixTWidget::~CKmMatrixTWidget()
{

}

void CKmMatrixTWidget::initWidget()
{
    QLabel *pLabelT = new QLabel(tr("分配矩阵(T):"));
    QTableView *pTableViewT = new QTableView();
    pTableViewT->setModel(m_pModelT);
    pTableViewT->horizontalHeader()->setStretchLastSection(false);    //设置最后一行不填满整个窗口
    pTableViewT->horizontalHeader()->setSectionsMovable(false);   //设置列不能拖动
    pTableViewT->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //依据窗口空间调节列宽
    pTableViewT->resizeRowsToContents();   //依据内容调节行高
    pTableViewT->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(pLabelT);
    pLayout->addWidget(pTableViewT);
    this->setLayout(pLayout);

}

void CKmMatrixTWidget::updateModels(const CKm *km)
{
//    if (km->isKmLegal())
//    {
        m_pModelT->setColumnCount(km->m_vRoleName.size());
        m_pModelT->setRowCount(km->m_mT.size());
        for (int i = 0; i < static_cast<int>(km->m_mT.size()); ++i)
        {
            m_pModelT->setHeaderData(i, Qt::Orientation::Vertical,
                                      QString("A%1").arg(QString::number(i+1)));
        }

        for (int i = 0; i < static_cast<int>(km->m_vRoleName.size()); ++i)
        {
            m_pModelT->setHeaderData(i, Qt::Orientation::Horizontal,
                                     QString("R%1(%2)").arg(QString::number(i+1)).arg(km->m_vRoleName[i]));
            for(int j = 0; j < static_cast<int>(km->m_mT.size()); ++j)
            {
                QModelIndex index = m_pModelT->index(j, i, QModelIndex());
                m_pModelT->setData(index, QVariant(km->m_mT[j][i]));
                m_pModelT->item(j, i)->setTextAlignment(Qt::AlignCenter);   //设置表格文本居中显示
                if(km->m_mT[j][i] == 1)
                    m_pModelT->item(j, i)->setBackground(m_vColor[i]);
                else
                    m_pModelT->item(j, i)->setBackground(QBrush(Qt::white));
            }
        }
//    }
}

void  CKmMatrixTWidget::clearModels()
{
    m_pModelT->clear();
}

void CKmMatrixTWidget::updateWidget(const CKm *km)
{
    this->updateModels(km);
}
