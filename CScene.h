#ifndef CSCENE_H
#define CSCENE_H

#include <vector>
#include <QGraphicsScene>
#include <QPixmap>
#include "CAgent.h"
#include "CSceneXml.h"
#include "CKm.h"

using namespace std;

const int BASEWIDTH = 1024;
const int BASEHEIGHT = 768;

class CScene : public QGraphicsScene
{
    Q_OBJECT

private:
    QPixmap m_Map;
    vector<CAgent *> m_vAgent;  //记录插入的agent,方便修改agent的信息
    CSceneXml *m_pSceneXml; //用于处理xml文件,将agent转为显示在scene

public:
    explicit CScene(QObject *parent = 0);
    ~CScene();

private:
    void clearvAgent();

public:
    void setMap(QPixmap pm, qreal width, qreal height);
    void setAgentLocation(vector<CAgentLocation> vLocation);    //设置anget的分布
    void setAgentRole(int m, int n , vector<vector<int>> T, vector<QString> roleName); //设置anget的role
    void setAgentRole(const CKm *km);
    void readXml(const QString &filename);
    void setByXml(const CSceneXml *sceneXml);

protected:
    void drawBackground(QPainter * painter, const QRectF & rect);
};

#endif // CSCENE_H
