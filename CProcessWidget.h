#ifndef CPROCESSWIDGET_H
#define CPROCESSWIDGET_H

#include <windows.h>
#include <QWidget>
#include <QProcess>

class CProcessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CProcessWidget(QWidget *parent = 0);
    ~CProcessWidget();

private:
    QWidget *m_pCmd;
    QWidget *m_pNam;
    QWidget *m_pNamChild;
    QProcess *m_pProcess;

private:
    void initWidget();
    void initConnect();
    void processError(QProcess::ProcessError error);    //打开exe文件的出错提示

signals:

public slots:
    void startZigeBee();
    void startLeach();

protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void hideEvent(QHideEvent *event);
};

#endif // CPROCESSWIDGET_H
