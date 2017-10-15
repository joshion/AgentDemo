#include "CKmXml.h"
#include <QFile>

CKmXml::CKmXml(const int m =0, const int n = 0)
    :CKm(m, n)
{
    m_pReader = new QXmlStreamReader;
}

CKmXml::~CKmXml()
{
    delete m_pReader;
}


void CKmXml::readFile(const QString &fileName)
{
    //读取文件前,先将原有信息清空
    this->m_m = 0;
    this->m_n = 0;
    this->update();
    this->readXmlFile(fileName);
}

bool CKmXml::readXmlFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_pReader->setDevice(&file);
        while (!m_pReader->atEnd())
        {
            m_pReader->readNext();
            if(m_pReader->isStartElement())
            {
                if(m_pReader->name() == "kmData")
                    this->readKmData();
            }
        }
        return !m_pReader->error();
    }
    return false;
}

void CKmXml::readKmData()
{
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "size")
                this->readSize();
            if(m_pReader->name() == "roleName")
                this->readRoleName();
            if(m_pReader->name() == "vectorL")
                this->readVectorL();
            if(m_pReader->name() == "vectorLa")
                this->readVectorLa();
            if(m_pReader->name() == "matrixQ")
                this->readMatrixQ();
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "kmData")
                break;
        }
    }
}



void CKmXml::readSize()
{
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "row")
                this->readM();
            if(m_pReader->name() == "column")
                this->readN();
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "size")
                break;
        }
    }
}

void CKmXml::readRoleName()
{
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "column")
                this->readRoleNameColumn();
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "roleName")
                break;
        }
    }
}

void CKmXml::readVectorL()
{
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "column")
                this->readVectorLColumn();
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "vectorL")
                break;
        }
    }
}

void CKmXml::readVectorLa()
{
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "column")
                this->readVectorLaColumn();
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "vectorLa")
                break;
        }
    }
}

void CKmXml::readMatrixQ()
{
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "row")
                this->readMatrixQRow();
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "matrixQ")
                break;
        }
    }
}

void CKmXml::readM()
{
    this->m_m = m_pReader->attributes().value("m").toInt();
    this->update(); //更新矩阵大小
}

void CKmXml::readN()
{
    this->m_n = m_pReader->attributes().value("n").toInt();
    this->update(); //更新矩阵大小
}

void CKmXml::readRoleNameColumn()
{
    int i = m_pReader->attributes().value("number").toInt();
    if (i < this->m_n && i < int(m_vRoleName.size()))    //确保不越界
        this->m_vRoleName[i] = m_pReader->attributes().value("value").toString();
}

void CKmXml::readVectorLColumn()
{
    int i = m_pReader->attributes().value("number").toInt();
    if (i < this->m_n && i < int(m_vL.size()))   //确保不越界
        this->m_vL[i] = m_pReader->attributes().value("value").toInt();
}

void CKmXml::readVectorLaColumn()
{
    int i = m_pReader->attributes().value("number").toInt();
    if (i < this->m_m && i < int(m_vLa.size()))  //确保不越界
        this->m_vLa[i] = m_pReader->attributes().value("value").toInt();
}

void CKmXml::readMatrixQRow()
{
    int rowNumber = m_pReader->attributes().value("number").toInt();
    if(rowNumber >= this->m_m || rowNumber >= int(this->m_mQ.size()))  //如果行号大于矩阵大小或m值,则不再读取该行
        return;
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "column")
                this->readMatrixQColumn(rowNumber);
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "row")
                break;
        }
    }
}

void CKmXml::readMatrixQColumn(const int rowNumber)
{
    int columnNumber = m_pReader->attributes().value("number").toInt();
    if (this->m_mQ.size() > 0)
    {   //在列号小于n值和矩阵大小,才读取
        if (columnNumber < this->m_n  && columnNumber < int(this->m_mQ[0].size()))
            this->m_mQ[rowNumber][columnNumber] = m_pReader->attributes().value("value").toFloat();
    }
}
