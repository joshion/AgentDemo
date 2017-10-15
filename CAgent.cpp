#include "CAgent.h"
#include <QtWidgets>

CAgent::CAgent(const QColor &color = Qt::green, int number = 0, int size = 30, QString info = "")
    :m_color(color), m_number(number), m_size(size), m_info(info)
{
    setZValue(number);
    setFlags(ItemIsSelectable | ItemIsMovable); //可选择、可移动
    setAcceptHoverEvents(true); //接收鼠标停留事件,为了显示tips

    m_info += QString("Agent:%1\nRole:").arg(number);

    //设置初始显示信息
    m_showText = m_info;
    setToolTip(m_showText);
}

//void CAgent::AddAgentInfo(const QString info)   //添加agent显示信息
//{
//    m_info += info;
//    this->setToolTip(m_showText);
//}

void CAgent::upDateShowText(const QString info)   //更新agent显示信息
{
    m_showText = m_info + info;
    this->setToolTip(m_showText);
}


QRectF CAgent::boundingRect() const //返回控件刷新区域,刷新区域要比绘制的图形大
{
    return QRectF(-2, -2, m_size+4, m_size+4);
}

QPainterPath CAgent::shape() const  //返回控件选择区域
{
    QPainterPath path;
//    path.addRect(0, 0, m_size, m_size);
    path.addEllipse(QRect(0, 0, m_size, m_size));
    return path;
}

void CAgent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

    QPen pen = painter->pen();
    QColor fillColor = (option->state & QStyle::State_Selected) ? m_color.dark(150) : m_color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    pen.setColor(fillColor);
    painter->setPen(pen);
    painter->drawEllipse(QRect(0, 0, m_size, m_size));

    //Draw text
    if (lod >= 3)   //zommIn时,agent显示详细信息
    {   
        QFont font("Times", m_size * 0.1);
        font.setStyleStrategy(QFont::ForceOutline);
        pen.setColor(Qt::black);
        painter->setFont(font);
        painter->setPen(pen);
        painter->save();
        painter->drawText(QRect(0, 0, m_size, m_size), Qt::AlignCenter, this->m_showText);
        painter->restore();
    }
    else    //zoomOut时,agent显示编号
    {
        QFont font("Times", m_size * 0.6);
        font.setStyleStrategy(QFont::ForceOutline);
        pen.setColor(Qt::black);
        painter->setFont(font);
        painter->setPen(pen);
        painter->save();
        painter->drawText(QRect(0, 0, m_size, m_size), Qt::AlignCenter, QString::number(this->m_number));
        painter->restore();
    }
}

void CAgent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void CAgent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier)
    {
        m_stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void CAgent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

