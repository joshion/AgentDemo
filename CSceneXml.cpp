#include "CSceneXml.h"
#include <QFile>
#include <QStringList>

CSceneXml::CSceneXml()
{
    m_pReader = new QXmlStreamReader;
    m_strFileName = "";
    m_uMapWidth = 0;
    m_uMapHeight = 0;
    m_uAgentCount = 0;
    m_vLocation = {};
}

CSceneXml::~CSceneXml()
{
    delete m_pReader;
}

void CSceneXml::readFile(const QString &fileName)
{
    //读取文件前,先将原有信息清空
    m_strFileName = "";
    m_uMapWidth = 0;
    m_uMapHeight = 0;
    m_uAgentCount = 0;
    m_vLocation.clear();

    //提取当前文件夹路径
    QStringList strList = fileName.split("/");
    strList.pop_back();
    for(auto str: strList)
    {
        m_strFileName += str +"/";
    }
    this->readXmlFile(fileName);
}

bool CSceneXml::readXmlFile(const QString &fileName)
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
                if(m_pReader->name() == "data")
                    this->readData();
            }
        }
        return !m_pReader->error();
    }
    return false;
}

void CSceneXml::readData()
{
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "map")
                this->readMap();
            if(m_pReader->name() == "agent")
                this->readAgent();
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "data")
                break;
        }
    }
}

void CSceneXml::readMap()
{
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "filename")
            {
                this->readFileName();
            }
            if(m_pReader->name() == "size")
            {
                this->readMapSize();
            }
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "map")
                break;
        }
    }
}

void CSceneXml::readAgent()
{
    while (!m_pReader->atEnd())
    {
        m_pReader->readNext();
        if (m_pReader->isStartElement())
        {
            if(m_pReader->name() == "count")
            {
                this->readAgentCount();
            }
            if(m_pReader->name() == "number")
            {
                this->readAgentNumber();
            }
        }
        if (m_pReader->isEndElement())
        {
            if(m_pReader->name() == "agent")
                break;
        }
    }
}

void CSceneXml::readFileName()
{
   this->m_strFileName += m_pReader->attributes().value("filename").toString();
}

void CSceneXml::readMapSize()
{
    this->m_uMapWidth = m_pReader->attributes().value("width").toInt();
    this->m_uMapHeight = m_pReader->attributes().value("height").toInt();
}

void CSceneXml::readAgentCount()
{
    this->m_uAgentCount = m_pReader->attributes().value("count").toInt();
}

void CSceneXml::readAgentNumber()
{
    int number= m_pReader->attributes().value("number").toInt();
    int x = m_pReader->attributes().value("x").toInt();
    int y = m_pReader->attributes().value("y").toInt();
    int size= m_pReader->attributes().value("size").toInt();
    this->m_vLocation.push_back(CAgentLocation(number, x, y, size));
}
