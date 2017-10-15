/**********************************************
 * 2015-12-29 13:05:11
 * author:魏永倬
 * tel:15626234799
 * e-mail:jobshionway@qq.com
 * *******************************************/
#ifndef CAGENT_H
#define CAGENT_H

#include <QColor>
#include <QString>
#include <QGraphicsItem>

class CAgent : public QGraphicsItem
{
public:
    CAgent(const QColor &color,int number, int size, QString info);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QVector<QPointF> m_stuff;

/***********************************************************
 * agnet的信息
 * *********************************************************/
private:
    QColor m_color; //agent的颜色
    int m_number;   //agent的编号
    int m_size; //agent显示在scene上的大小
    QString m_info; //信息
    QString m_showText; //tips和控件上显示的文本
public:
    //void AddAgentInfo(const QString info);  //添加anget信息
    void upDateShowText(const QString info);    //更新显示信息
};

#endif // CAGENT_H
