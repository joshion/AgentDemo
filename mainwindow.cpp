#include "mainwindow.h"
#include "CEnterWizard.h"
#include "CRmKm.h"
#include "CMsKm.h"
#include "CJwKm.h"
#include "CKmXml.h"

#include <QDockWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    m_vColor.push_back(Qt::blue);
//    m_vColor.push_back(Qt::red);
//    m_vColor.push_back(Qt::gray);
//    m_vColor.push_back(Qt::green);
    this->setWindowTitle(tr("基于E-CARGO的无线传感器网络仿真软件"));

    m_pViewControl = new QToolBar("ViewControl");
    m_pArithmeticChoice = new QToolBar("ArithmeticChoice");
    m_pMenuBar = new QMenuBar;
    m_pFileMenu = new QMenu(tr("打开(&O)"), NULL);
    m_pSet = new QMenu(tr("设置(&S)"), NULL);
    m_pModelMenu = new QMenu("模式(&M)", NULL);

    m_pHelpMenu = new QMenu("帮助(&H)", NULL) ;

    m_pKmInfoWidget = new CKmInfoWidget;
    m_pKmMatrixTWidget = new CKmMatrixTWidget;

    m_pView = new CView();
    m_pScene = new CScene;
    m_pProcessWidget = new CProcessWidget;
    m_pKm = new CKm(0, 0);

    initWidget();
    initConnect();
//    updateModel(0, 0, {{}});
}

MainWindow::~MainWindow()
{
    delete m_pKm;

    delete m_pView;
    delete m_pProcessWidget;
}

void MainWindow::initWidget()
{
    m_pFileMenu->addAction(tr("加载地图配置文件(&M)"));
    m_pFileMenu->addAction(tr("加载参数文件(&K)"));
//    m_pSet->addAction("loadFile");
    m_pSet->addAction(tr("设置km参数"));
    m_pModelMenu->addAction(tr("地图视图"));
    m_pModelMenu->addAction("Leach");
    m_pModelMenu->addAction("ZigeBee");

    m_pHelpMenu->addAction(tr("使用说明"));
    m_pHelpMenu->addAction(tr("关于"));

    m_pMenuBar->addMenu(m_pFileMenu);
    m_pMenuBar->addMenu(m_pSet);
    m_pMenuBar->addMenu(m_pModelMenu);
    m_pMenuBar->addMenu(m_pHelpMenu);

    m_pViewControl->addAction(QIcon(QPixmap(":/images/select.png")), QString("Select"));
    m_pViewControl->addAction(QIcon(QPixmap(":/images/drag.png")), QString("Drag"));
//    m_pArithmeticChoice->addAction(QIcon(QPixmap(":/images/M.png")), QString("MsKm"));
    m_pArithmeticChoice->addAction(QIcon(QPixmap(":/images/W.png")), QString("JwKm"));
    m_pArithmeticChoice->addAction(QIcon(QPixmap(":/images/R.png")), QString("RmKm"));

    m_pView->view()->setScene(m_pScene);

    QDockWidget *pDockKmInfo = new QDockWidget(tr("Km输入信息"), this);
    pDockKmInfo->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);    //可移动、可关闭
    pDockKmInfo->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);    //dock只可在左右两侧
    pDockKmInfo->setWidget(m_pKmInfoWidget);

    QDockWidget *pDockT = new QDockWidget(tr("Km输出信息"), this);
    pDockT->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);    //可移动、可关闭
    pDockT->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);    //dock只可在左右两侧
    pDockT->setWidget(m_pKmMatrixTWidget);


    this->setMenuBar(m_pMenuBar);
//    this->addToolBar(Qt::TopToolBarArea, m_pViewControl);   //添加视图控制工具到窗口
    this->addToolBar(Qt::TopToolBarArea, m_pArithmeticChoice);  //添加算法选择工具到窗口
    this->addDockWidget(Qt::LeftDockWidgetArea, pDockKmInfo, Qt::Vertical);
    this->addDockWidget(Qt::LeftDockWidgetArea, pDockT, Qt::Vertical);
    this->setCentralWidget(m_pView);
}

void MainWindow::initConnect()
{
    connect(m_pSet, SIGNAL(triggered(QAction*)), this, SLOT(setMenuTriggered(QAction*)));
    connect(m_pFileMenu, SIGNAL(triggered(QAction*)), this, SLOT(fileMenuTriggered(QAction*)));
    connect(m_pModelMenu, SIGNAL(triggered(QAction*)), this, SLOT(namMenuTriggered(QAction*)));
    connect(m_pHelpMenu, SIGNAL(triggered(QAction*)), this, SLOT(helpMenuTriggered(QAction*)));

    connect(m_pArithmeticChoice, SIGNAL(actionTriggered(QAction*)), this, SLOT(ArithmeticToolTriggered(QAction*)));
    connect(this, SIGNAL(kmInfoisChanged(const CKm*)), m_pKmInfoWidget, SLOT(updateWidget(const CKm*)));
    connect(this, SIGNAL(kmMatrixTisChanged(const CKm*)), m_pKmMatrixTWidget, SLOT(updateWidget(const CKm*)));
}

void  MainWindow::fileMenuTriggered(QAction *action)    //open菜单点击事件
{
    if(action->text() == "加载地图配置文件(&M)")
    {
        QString path = QFileDialog::getOpenFileName(this, tr("Open Map Xml"), ".", tr("Xml Files(*.xml)"));
        if(path.size() > 0)
        {
            m_pKmMatrixTWidget->clearModels();  //加载新图片,清空T矩阵的显示
            m_pKmInfoWidget->clearModels(); //清空Q、L、La的显示
            m_pScene->readXml(path);
        }
    }
    if (action->text() == "加载参数文件(&K)")
    {
        m_pKmMatrixTWidget->clearModels();  //选择新的算法时,清空T矩阵的显示

        //updateModel(0, 0, {{}});    //加载新的信息文件,清空model
        QString path = QFileDialog::getOpenFileName(this, tr("Open Km Xml"), ".", tr("Xml Files(*.xml)"));
        if(path.size() > 0)
        {
            CKmXml *pKmXml = new CKmXml(0, 0);
            pKmXml->readFile(path);
            //updateScene(pKmXml);
            this->m_pKm = pKmXml;
            emit kmInfoisChanged(m_pKm);
            //delete pKmXml;
        }
    }
}

void MainWindow::setMenuTriggered(QAction *action)  //set菜单点击事件
{
    if (action->text() == "设置km参数")
    {
        setMatrix();
    }
}

void MainWindow::namMenuTriggered(QAction *action)
{
    if(action->text() == "地图视图")
    {
        this->centralWidget()->setParent(NULL);
        this->setCentralWidget(m_pView);
    }
    else if(action->text() == "Leach")
    {
        this->centralWidget()->setParent(NULL);
        this->setCentralWidget(m_pProcessWidget);
        m_pProcessWidget->startLeach();
    }
    else if(action->text() == "ZigeBee")
    {
        this->centralWidget()->setParent(NULL);
        this->setCentralWidget(m_pProcessWidget);
        m_pProcessWidget->startZigeBee();
    }
}

void MainWindow::helpMenuTriggered(QAction *action)
{
    if (action->text() == "使用说明")
    {
        QMessageBox::question(0 ,
        "使用说明" ,"一、模式切换\n"
                "1.点击\"模式\"菜单的\"地图视图\"按钮选择km算法演示\n"
                "2.点击\"模式\"菜单的\"Leach\"按钮选择Leach协议演示\n"
                "3.点击\"模式\"菜单的\"ZigeBee\"按钮选择B协议演示\n"
                "\n"
                "二、Km算法的演示\n"
                "1.点击\"打开\"菜单的\"加载地图配置文件\"按钮加载地图文件\n"
                "2.点击\"打开\"菜单的\"加载参数文件\"按钮加载km参数\n"
                "    或者点击\"设置\"菜单的\"设置km参数\"按钮自己输入km参数\n"
                "3.点击工具栏的\"W\"按钮或者\"R\"按钮选择不同算法计算T矩阵\n",
        QMessageBox::Ok | QMessageBox::Default , 0 );
    }
    else if (action->text() == "关于")
    {
        QMessageBox::information(0 ,
        "关于" , "基于E-CARGO的无线传感器网络仿真软件1.0",
        QMessageBox::Ok | QMessageBox::Default, 0 );
    }

}

void MainWindow::ArithmeticToolTriggered(QAction *action)
{
    m_pKmMatrixTWidget->clearModels();  //选择新的算法时,清空T矩阵的显示
    if (!m_pKm->isKmLegal())
        return;
    if(action->text() == "RmKm")
    {
        this->updateSceneByRmKm(m_pKm);
        emit kmMatrixTisChanged(m_pKm);
    }
//    else if(action->text() == "MsKm")
//    {
//        this->updateSceneByMsKm(m_pKm);
//        emit kmMatrixTisChanged(m_pKm);
//    }
    else if(action->text() == "JwKm")
    {
        this->updateSceneByJwKm(m_pKm);
        emit kmMatrixTisChanged(m_pKm);
    }
}

void MainWindow::setMatrix()
{
    CEnterWizard *wizard = new CEnterWizard(this);
    wizard->show();
    if(wizard->exec() == wizard->Accepted)
    {
        this->m_pKm = wizard->m_pKm;
        emit kmInfoisChanged(m_pKm);
    }
}

void MainWindow::updateSceneByRmKm(CKm *km) //用RmKm算法生成T矩阵,更新model和scene
{
    //km中的存在空的vector或matrix会报错
    CRmKm::RatedAssign(km->m_vL, km->m_vLa, km->m_mQ, km->m_mT, km->m_m, km->m_n);
    m_pScene->setAgentRole(km);
}

void MainWindow::updateSceneByMsKm(CKm *km) //用MsKm算法生成T矩阵,更新model和scene
{
    CMsKm::RatedAssign(km->m_mQ, km->m_vL, km->m_mT);
    m_pScene->setAgentRole(km);
}

void MainWindow::updateSceneByJwKm(CKm *km) //用JwKm算法生成T矩阵,更新model和scene
{
    CJwKm::RatedAssign(km->m_mQ, km->m_vL, km->m_mT);
    m_pScene->setAgentRole(km);
}
