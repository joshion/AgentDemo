#include "CScene.h"
#include <QPainter>

CScene::CScene(QObject *parent):
    QGraphicsScene(parent)
{
    this->setSceneRect(0 , 0, BASEWIDTH, BASEHEIGHT);
    m_pSceneXml = new CSceneXml;
    m_vAgent.clear();
}

CScene::~CScene()
{
    delete m_pSceneXml;
    clearvAgent();
}

void CScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if(m_Map.isNull())  //没有加载成攻,设置默认空白图片
    {
        m_Map = QPixmap(":/images/white.png");
    }

    if(!m_Map.isNull()) //如果加载地图图片成功,则进行绘制
    {
        painter->drawPixmap(QRect(QPoint(0, 0), QSize(this->width(), this->height())), m_Map );
    }
}

void CScene::clearvAgent()  //清空scene里的所有agent,并清空vector
{
    this->clear();
    m_vAgent.clear();
}

void CScene::readXml(const QString &filename)   //读取Xml文件,并依据Xml文件显示agent
{
    m_pSceneXml->readFile(filename);
    this->setByXml(m_pSceneXml);
}

void CScene::setByXml(const CSceneXml *sceneXml)
{
    if (!sceneXml)
        return;
    this->setMap(QPixmap(sceneXml->m_strFileName), sceneXml->m_uMapWidth, sceneXml->m_uMapHeight);
    this->setAgentLocation(sceneXml->m_vLocation);
}


void CScene::setMap(QPixmap pm, qreal width, qreal height)
{
    if(width == 0 || height == 0)   //如果加载图片的尺寸为0,则给予scene一个初始大小
    {
        width = BASEWIDTH;
        height = BASEHEIGHT;
    }
    this->setSceneRect(0 , 0, width, height);
    m_Map = pm;
    update();
}

void CScene::setAgentLocation(vector<CAgentLocation> vLocation)
{
    clearvAgent();  //设置新的地图的agent之前,先清空已有的agent

    if (vLocation.empty())
        return;

    for (unsigned int i = 0; i < vLocation.size(); ++i)
    {
        CAgent *item = new CAgent(Qt::green, vLocation[i].m_number, vLocation[i].m_size, "");
        m_vAgent.push_back(item);
        this->addItem(item);
        item->setPos(QPointF(vLocation[i].m_x, vLocation[i].m_y));
    }
}

void CScene::setAgentRole(int m, int n , vector<vector<int>> T, vector<QString> roleName)
{
    for (int i = 0; i < m; ++i)
    {
        QString str;
        for (int j = 0; j < n; ++j)
        {
            if(T[i][j] == 1)
            {
                str +=  "\r" + roleName[j];
            }
        }
        if (i < int(m_vAgent.size()))
            m_vAgent[i]->upDateShowText(str);
    }
}

void CScene::setAgentRole(const CKm *km)
{
    this->setAgentRole(km->m_m, km->m_n, km->m_mT, km->m_vRoleName);
}
