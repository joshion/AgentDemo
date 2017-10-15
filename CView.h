#ifndef CVIEW_H
#define CVIEW_H

#include <QFrame>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class CView;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(CView *v) : QGraphicsView(), CView(v) {}

protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
#endif

private:
    CView *CView;
};

class CView : public QFrame
{
    Q_OBJECT
public:
    explicit CView(QWidget *parent = 0);

    QGraphicsView *view() const;

private:
    GraphicsView *graphicsView;
    QToolButton *resetButton;
    QSlider *zoomSlider;
    QSlider *rotateSlider;

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
    void togglePointerMode(bool tag);

private slots:
    void resetView();
    void setResetButtonEnabled();
    void setupMatrix();
    void rotateLeft();
    void rotateRight();
};

#endif // CVIEW_H
