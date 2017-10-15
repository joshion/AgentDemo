#include "CProcessWidget.h"
#include <QMessageBox>
#include <QWindow>

CProcessWidget::CProcessWidget(QWidget *parent)
    : QWidget(parent)
{
    m_pCmd = new QWidget;
    m_pNam = new QWidget;
    m_pNamChild = new QWidget;
    m_pProcess = new QProcess(this);

    initWidget();
}

CProcessWidget::~CProcessWidget()
{
    m_pProcess->close();
    delete m_pProcess;
}

void  CProcessWidget::initWidget()
{
}

void CProcessWidget::initConnect()
{
    connect(m_pProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));
}

void CProcessWidget::startZigeBee()
{
    if(m_pProcess->isOpen())
    {
        m_pProcess->close();
    }

    m_pProcess->start("nam/nam.exe nam/ZigeBee.nam");

    if (!m_pProcess->waitForFinished(2000))
    {
        WId wid = 0;
        QWindow *pCmdWindow;
        wid = (WId)FindWindow(L"ConsoleWindowClass", NULL);
        pCmdWindow = QWindow::fromWinId(wid);
        m_pCmd = QWidget::createWindowContainer(pCmdWindow, this);

        QWindow *pNamWindow;
        wid = (WId)FindWindow(L"TkTopLevel", L"Nam Console v1.0a11a");   //TkTopLevel
        pNamWindow = QWindow::fromWinId(wid);
        m_pNam = QWidget::createWindowContainer(pNamWindow, this);

        QWindow *pNamChildWindow;
        wid = (WId)FindWindow(L"TkTopLevel", L"Nam: nam/ZigeBee.nam" );   //TkTopLevel
        pNamChildWindow = QWindow::fromWinId(wid);
        m_pNamChild = QWidget::createWindowContainer(pNamChildWindow, this);

        m_pNamChild->resize(this->width(), this->height());
    }
}

void CProcessWidget::startLeach()
{

    if(m_pProcess->isOpen())
    {
        m_pProcess->close();
    }

    m_pProcess->start("nam/nam.exe nam/leach.nam");

    if (!m_pProcess->waitForFinished(2000))
    {
        WId wid = 0;
        QWindow *pCmdWindow;
        wid = (WId)FindWindow(L"ConsoleWindowClass", NULL);
        pCmdWindow = QWindow::fromWinId(wid);
        m_pCmd = QWidget::createWindowContainer(pCmdWindow, this);

        QWindow *pNamWindow;
        wid = (WId)FindWindow(L"TkTopLevel", L"Nam Console v1.0a11a");   //TkTopLevel
        pNamWindow = QWindow::fromWinId(wid);
        m_pNam = QWidget::createWindowContainer(pNamWindow, this);

        QWindow *pNamChildWindow;
        wid = (WId)FindWindow(L"TkTopLevel", L"Nam: nam/leach.nam" );   //TkTopLevel
        pNamChildWindow = QWindow::fromWinId(wid);
        m_pNamChild = QWidget::createWindowContainer(pNamChildWindow, this);

        m_pNamChild->resize(this->width(), this->height());
    }
}

void CProcessWidget::processError(QProcess::ProcessError error)
{
    switch(error)
    {
    case QProcess::FailedToStart:
        QMessageBox::information(0,"FailedToStart","FailedToStart");
        break;
    case QProcess::Crashed:
        QMessageBox::information(0,"Crashed","Crashed");
        break;
    case QProcess::Timedout:
        QMessageBox::information(0,"FailedToStart","FailedToStart");
        break;
    case QProcess::WriteError:
        QMessageBox::information(0,"Timedout","Timedout");
        break;
    case QProcess::ReadError:
        QMessageBox::information(0,"ReadError","ReadError");
        break;
    case QProcess::UnknownError:
        QMessageBox::information(0,"UnknownError","UnknownError");
        break;
    default:
        QMessageBox::information(0,"default","default");
    break;
    }
}

void CProcessWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    m_pCmd->setVisible(false);
    m_pNam->setVisible(false);
}

void CProcessWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    m_pNamChild->close();
    m_pNam->close();
    m_pCmd->close();
    m_pProcess->close();
}

void CProcessWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    m_pNamChild->resize(this->width(), this->height());
}

void CProcessWidget::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    m_pCmd->setVisible(false);
    m_pNam->setVisible(false);
    m_pNamChild->setVisible(false);
}

