#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include "CScene.h"
#include "CKm.h"
#include "CKmInfoWidget.h"
#include "CKmMatrixTWidget.h"
#include "CView.h"
#include "CProcessWidget.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QStandardItemModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

//    QStandardItemModel *m_pModel;

private:
    QMenuBar *m_pMenuBar;
    QToolBar *m_pViewControl;
    QToolBar *m_pArithmeticChoice;
    QMenu *m_pFileMenu;
    QMenu *m_pSet;
    QMenu *m_pModelMenu;
    QMenu *m_pHelpMenu;

    CView *m_pView;
    CProcessWidget *m_pProcessWidget;
    CScene *m_pScene;
    CKm *m_pKm;

    CKmInfoWidget *m_pKmInfoWidget; //显示Q,L,La的窗口
    CKmMatrixTWidget *m_pKmMatrixTWidget;  //显示矩阵T的窗口


private:
    void initWidget();
    void initConnect();

public:
    void updateModel(int m, int n , vector<vector<int>> T);
    void updateModel(const CKm *km);

    void updateSceneByRmKm(CKm *km);    //用RmKm算法生成T矩阵,更新model和scene
    void updateSceneByMsKm(CKm *km);    //用MsKm算法生成T矩阵,更新model和scene
    void updateSceneByJwKm(CKm *km);    //用JwKm算法生成T矩阵,更新model和scene

signals:
    void kmInfoisChanged(const CKm *km);    //当km的发生改变时,发出该信号
    void kmMatrixTisChanged(const CKm *km); //当km的T矩阵发生改变时,发出该信号

private slots:
    void setMenuTriggered(QAction *action);
    void fileMenuTriggered(QAction *action);
    void namMenuTriggered(QAction *action);
    void helpMenuTriggered(QAction *action);

    void ArithmeticToolTriggered(QAction *action);
    void setMatrix();
};

#endif // MAINWINDOW_H
