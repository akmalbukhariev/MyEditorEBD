/********************************************************************************
** Form generated from reading UI file 'MyEditorEBD.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYEDITOREBD_H
#define UI_MYEDITOREBD_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "WidgetCCTable.h"
#include "WidgetColorFilm.h"
#include "WidgetDesignNavigator.h"
#include "WidgetHeaderInfo.h"
#include "WidgetNavigator.h"
#include "WidgetPointInfo.h"
#include "designcontainer.h"

QT_BEGIN_NAMESPACE

class Ui_MyEditorEBDClass
{
public:
    QAction *actionOpen_File;
    QAction *actionSave_File;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionTransform;
    QAction *actionEditStitches;
    QAction *actionRotate;
    QAction *actionScale;
    QAction *actionDesignGrid;
    QAction *actionAxis;
    QAction *actionPointing;
    QAction *actionTile_Window;
    QAction *actionCascade_Window;
    QAction *actionCCTable;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    DesignContainer *designContainer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuWindows;
    QMenu *menuHelp_2;
    QToolBar *mainToolBar;
    QToolBar *colorToolBar;
    QToolBar *cursorToolBar;
    QStatusBar *statusBar;
    QDockWidget *dkImageMap;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    WidgetNavigator *wdNavigator;
    QDockWidget *dkSequenceViewer;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout_3;
    QWidget *wdSequenceViewer;
    QDockWidget *dkHeader;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_4;
    WidgetHeaderInfo *wdHeaderInfo;
    QDockWidget *dkPoint;
    QWidget *dockWidgetContents_4;
    QGridLayout *gridLayout_5;
    WidgetPointInfo *wdPoint;
    QDockWidget *dkCCTable;
    QWidget *dockWidgetContents_5;
    QGridLayout *gridLayout_6;
    WidgetCCTable *wdCCTable;
    QDockWidget *dkColorFilm;
    QWidget *dockWidgetContents_6;
    QGridLayout *gridLayout_7;
    WidgetColorFilm *wdColorFilm;
    QDockWidget *dkDesign;
    QWidget *dockWidgetContents_7;
    QGridLayout *gridLayout_8;
    WidgetDesignNavigator *wdDesign;

    void setupUi(QMainWindow *MyEditorEBDClass)
    {
        if (MyEditorEBDClass->objectName().isEmpty())
            MyEditorEBDClass->setObjectName(QStringLiteral("MyEditorEBDClass"));
        MyEditorEBDClass->resize(1357, 910);
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/needle.png"), QSize(), QIcon::Normal, QIcon::Off);
        MyEditorEBDClass->setWindowIcon(icon);
        actionOpen_File = new QAction(MyEditorEBDClass);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MyEditorEBD/Resources/open_dir.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_File->setIcon(icon1);
        actionSave_File = new QAction(MyEditorEBDClass);
        actionSave_File->setObjectName(QStringLiteral("actionSave_File"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MyEditorEBD/Resources/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_File->setIcon(icon2);
        actionExit = new QAction(MyEditorEBDClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MyEditorEBD/Resources/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionAbout = new QAction(MyEditorEBDClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionTransform = new QAction(MyEditorEBDClass);
        actionTransform->setObjectName(QStringLiteral("actionTransform"));
        actionTransform->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/MyEditorEBD/Resources/cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTransform->setIcon(icon4);
        actionEditStitches = new QAction(MyEditorEBDClass);
        actionEditStitches->setObjectName(QStringLiteral("actionEditStitches"));
        actionEditStitches->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/MyEditorEBD/Resources/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditStitches->setIcon(icon5);
        actionRotate = new QAction(MyEditorEBDClass);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/MyEditorEBD/Resources/rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotate->setIcon(icon6);
        actionScale = new QAction(MyEditorEBDClass);
        actionScale->setObjectName(QStringLiteral("actionScale"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/MyEditorEBD/Resources/scale.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScale->setIcon(icon7);
        actionDesignGrid = new QAction(MyEditorEBDClass);
        actionDesignGrid->setObjectName(QStringLiteral("actionDesignGrid"));
        actionDesignGrid->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/MyEditorEBD/Resources/grid.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDesignGrid->setIcon(icon8);
        actionAxis = new QAction(MyEditorEBDClass);
        actionAxis->setObjectName(QStringLiteral("actionAxis"));
        actionAxis->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/MyEditorEBD/Resources/coordinate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAxis->setIcon(icon9);
        actionPointing = new QAction(MyEditorEBDClass);
        actionPointing->setObjectName(QStringLiteral("actionPointing"));
        actionPointing->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/MyEditorEBD/Resources/pointing.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPointing->setIcon(icon10);
        actionTile_Window = new QAction(MyEditorEBDClass);
        actionTile_Window->setObjectName(QStringLiteral("actionTile_Window"));
        actionCascade_Window = new QAction(MyEditorEBDClass);
        actionCascade_Window->setObjectName(QStringLiteral("actionCascade_Window"));
        actionCCTable = new QAction(MyEditorEBDClass);
        actionCCTable->setObjectName(QStringLiteral("actionCCTable"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/MyEditorEBD/Resources/cctable.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCCTable->setIcon(icon11);
        centralWidget = new QWidget(MyEditorEBDClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 9, 0);
        designContainer = new DesignContainer(centralWidget);
        designContainer->setObjectName(QStringLiteral("designContainer"));
        designContainer->setAutoFillBackground(false);

        gridLayout_2->addWidget(designContainer, 0, 0, 1, 1);

        MyEditorEBDClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyEditorEBDClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1357, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QStringLiteral("menuWindows"));
        menuHelp_2 = new QMenu(menuBar);
        menuHelp_2->setObjectName(QStringLiteral("menuHelp_2"));
        MyEditorEBDClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyEditorEBDClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setCursor(QCursor(Qt::PointingHandCursor));
        MyEditorEBDClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        colorToolBar = new QToolBar(MyEditorEBDClass);
        colorToolBar->setObjectName(QStringLiteral("colorToolBar"));
        colorToolBar->setCursor(QCursor(Qt::PointingHandCursor));
        MyEditorEBDClass->addToolBar(Qt::TopToolBarArea, colorToolBar);
        MyEditorEBDClass->insertToolBarBreak(colorToolBar);
        cursorToolBar = new QToolBar(MyEditorEBDClass);
        cursorToolBar->setObjectName(QStringLiteral("cursorToolBar"));
        cursorToolBar->setCursor(QCursor(Qt::PointingHandCursor));
        MyEditorEBDClass->addToolBar(Qt::TopToolBarArea, cursorToolBar);
        MyEditorEBDClass->insertToolBarBreak(cursorToolBar);
        statusBar = new QStatusBar(MyEditorEBDClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyEditorEBDClass->setStatusBar(statusBar);
        dkImageMap = new QDockWidget(MyEditorEBDClass);
        dkImageMap->setObjectName(QStringLiteral("dkImageMap"));
        dkImageMap->setMinimumSize(QSize(241, 38));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        wdNavigator = new WidgetNavigator(dockWidgetContents);
        wdNavigator->setObjectName(QStringLiteral("wdNavigator"));
        wdNavigator->setAutoFillBackground(true);

        gridLayout->addWidget(wdNavigator, 0, 0, 1, 1);

        dkImageMap->setWidget(dockWidgetContents);
        MyEditorEBDClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dkImageMap);
        dkSequenceViewer = new QDockWidget(MyEditorEBDClass);
        dkSequenceViewer->setObjectName(QStringLiteral("dkSequenceViewer"));
        dkSequenceViewer->setMinimumSize(QSize(241, 38));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        gridLayout_3 = new QGridLayout(dockWidgetContents_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        wdSequenceViewer = new QWidget(dockWidgetContents_2);
        wdSequenceViewer->setObjectName(QStringLiteral("wdSequenceViewer"));
        wdSequenceViewer->setAutoFillBackground(true);

        gridLayout_3->addWidget(wdSequenceViewer, 0, 0, 1, 1);

        dkSequenceViewer->setWidget(dockWidgetContents_2);
        MyEditorEBDClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dkSequenceViewer);
        dkHeader = new QDockWidget(MyEditorEBDClass);
        dkHeader->setObjectName(QStringLiteral("dkHeader"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        gridLayout_4 = new QGridLayout(dockWidgetContents_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        wdHeaderInfo = new WidgetHeaderInfo(dockWidgetContents_3);
        wdHeaderInfo->setObjectName(QStringLiteral("wdHeaderInfo"));
        wdHeaderInfo->setAutoFillBackground(true);

        gridLayout_4->addWidget(wdHeaderInfo, 0, 0, 1, 1);

        dkHeader->setWidget(dockWidgetContents_3);
        MyEditorEBDClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dkHeader);
        dkPoint = new QDockWidget(MyEditorEBDClass);
        dkPoint->setObjectName(QStringLiteral("dkPoint"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        gridLayout_5 = new QGridLayout(dockWidgetContents_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        wdPoint = new WidgetPointInfo(dockWidgetContents_4);
        wdPoint->setObjectName(QStringLiteral("wdPoint"));
        wdPoint->setAutoFillBackground(true);

        gridLayout_5->addWidget(wdPoint, 0, 0, 1, 1);

        dkPoint->setWidget(dockWidgetContents_4);
        MyEditorEBDClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dkPoint);
        dkCCTable = new QDockWidget(MyEditorEBDClass);
        dkCCTable->setObjectName(QStringLiteral("dkCCTable"));
        dkCCTable->setLayoutDirection(Qt::LeftToRight);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QStringLiteral("dockWidgetContents_5"));
        gridLayout_6 = new QGridLayout(dockWidgetContents_5);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        wdCCTable = new WidgetCCTable(dockWidgetContents_5);
        wdCCTable->setObjectName(QStringLiteral("wdCCTable"));
        wdCCTable->setAutoFillBackground(true);

        gridLayout_6->addWidget(wdCCTable, 0, 0, 1, 1);

        dkCCTable->setWidget(dockWidgetContents_5);
        MyEditorEBDClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dkCCTable);
        dkColorFilm = new QDockWidget(MyEditorEBDClass);
        dkColorFilm->setObjectName(QStringLiteral("dkColorFilm"));
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QStringLiteral("dockWidgetContents_6"));
        gridLayout_7 = new QGridLayout(dockWidgetContents_6);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        wdColorFilm = new WidgetColorFilm(dockWidgetContents_6);
        wdColorFilm->setObjectName(QStringLiteral("wdColorFilm"));
        wdColorFilm->setAutoFillBackground(true);

        gridLayout_7->addWidget(wdColorFilm, 0, 0, 1, 1);

        dkColorFilm->setWidget(dockWidgetContents_6);
        MyEditorEBDClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dkColorFilm);
        dkDesign = new QDockWidget(MyEditorEBDClass);
        dkDesign->setObjectName(QStringLiteral("dkDesign"));
        dockWidgetContents_7 = new QWidget();
        dockWidgetContents_7->setObjectName(QStringLiteral("dockWidgetContents_7"));
        gridLayout_8 = new QGridLayout(dockWidgetContents_7);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        wdDesign = new WidgetDesignNavigator(dockWidgetContents_7);
        wdDesign->setObjectName(QStringLiteral("wdDesign"));
        wdDesign->setAutoFillBackground(true);

        gridLayout_8->addWidget(wdDesign, 0, 0, 1, 1);

        dkDesign->setWidget(dockWidgetContents_7);
        MyEditorEBDClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dkDesign);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuWindows->menuAction());
        menuBar->addAction(menuHelp_2->menuAction());
        menuFile->addAction(actionOpen_File);
        menuFile->addAction(actionSave_File);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuWindows->addAction(actionTile_Window);
        menuWindows->addAction(actionCascade_Window);
        menuHelp_2->addAction(actionAbout);
        mainToolBar->addAction(actionExit);
        mainToolBar->addAction(actionSave_File);
        mainToolBar->addAction(actionOpen_File);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCCTable);
        cursorToolBar->addAction(actionTransform);
        cursorToolBar->addAction(actionEditStitches);
        cursorToolBar->addSeparator();
        cursorToolBar->addAction(actionRotate);
        cursorToolBar->addAction(actionScale);
        cursorToolBar->addSeparator();
        cursorToolBar->addAction(actionPointing);
        cursorToolBar->addAction(actionDesignGrid);
        cursorToolBar->addAction(actionAxis);

        retranslateUi(MyEditorEBDClass);

        QMetaObject::connectSlotsByName(MyEditorEBDClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyEditorEBDClass)
    {
        MyEditorEBDClass->setWindowTitle(QApplication::translate("MyEditorEBDClass", "MyEditorEBD", nullptr));
        actionOpen_File->setText(QApplication::translate("MyEditorEBDClass", "Open File", nullptr));
        actionSave_File->setText(QApplication::translate("MyEditorEBDClass", "Save File", nullptr));
        actionExit->setText(QApplication::translate("MyEditorEBDClass", "Exit", nullptr));
        actionAbout->setText(QApplication::translate("MyEditorEBDClass", "About", nullptr));
        actionTransform->setText(QApplication::translate("MyEditorEBDClass", "actionTransform", nullptr));
#ifndef QT_NO_TOOLTIP
        actionTransform->setToolTip(QApplication::translate("MyEditorEBDClass", "Re-arrange objects", nullptr));
#endif // QT_NO_TOOLTIP
        actionEditStitches->setText(QApplication::translate("MyEditorEBDClass", "actionEditStitches", nullptr));
#ifndef QT_NO_TOOLTIP
        actionEditStitches->setToolTip(QApplication::translate("MyEditorEBDClass", "Edit stitches of objects", nullptr));
#endif // QT_NO_TOOLTIP
        actionRotate->setText(QApplication::translate("MyEditorEBDClass", "Rotate", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRotate->setToolTip(QApplication::translate("MyEditorEBDClass", "Rotate design", nullptr));
#endif // QT_NO_TOOLTIP
        actionScale->setText(QApplication::translate("MyEditorEBDClass", "Scale", nullptr));
#ifndef QT_NO_TOOLTIP
        actionScale->setToolTip(QApplication::translate("MyEditorEBDClass", "Scale design", nullptr));
#endif // QT_NO_TOOLTIP
        actionDesignGrid->setText(QApplication::translate("MyEditorEBDClass", "DesignGrid", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDesignGrid->setToolTip(QApplication::translate("MyEditorEBDClass", "Design grid is visible", nullptr));
#endif // QT_NO_TOOLTIP
        actionAxis->setText(QApplication::translate("MyEditorEBDClass", "Axis", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAxis->setToolTip(QApplication::translate("MyEditorEBDClass", "Axis is visble", nullptr));
#endif // QT_NO_TOOLTIP
        actionPointing->setText(QApplication::translate("MyEditorEBDClass", "Pointing", nullptr));
        actionTile_Window->setText(QApplication::translate("MyEditorEBDClass", "Tile Window", nullptr));
        actionCascade_Window->setText(QApplication::translate("MyEditorEBDClass", "Cascade Window", nullptr));
        actionCCTable->setText(QApplication::translate("MyEditorEBDClass", "CCTable", nullptr));
#ifndef QT_NO_TOOLTIP
        actionCCTable->setToolTip(QApplication::translate("MyEditorEBDClass", "CCTable", nullptr));
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("MyEditorEBDClass", "File", nullptr));
        menuWindows->setTitle(QApplication::translate("MyEditorEBDClass", "Windows", nullptr));
        menuHelp_2->setTitle(QApplication::translate("MyEditorEBDClass", "Help", nullptr));
        mainToolBar->setWindowTitle(QApplication::translate("MyEditorEBDClass", "File", nullptr));
        colorToolBar->setWindowTitle(QApplication::translate("MyEditorEBDClass", "Color palette", nullptr));
        cursorToolBar->setWindowTitle(QApplication::translate("MyEditorEBDClass", "Design modify", nullptr));
        dkImageMap->setWindowTitle(QApplication::translate("MyEditorEBDClass", "Image Map", nullptr));
        dkSequenceViewer->setWindowTitle(QApplication::translate("MyEditorEBDClass", "Sequence Viewer", nullptr));
        dkHeader->setWindowTitle(QApplication::translate("MyEditorEBDClass", "Header Info", nullptr));
        dkPoint->setWindowTitle(QApplication::translate("MyEditorEBDClass", "Points", nullptr));
        dkCCTable->setWindowTitle(QApplication::translate("MyEditorEBDClass", "C/C Table", nullptr));
        dkColorFilm->setWindowTitle(QApplication::translate("MyEditorEBDClass", "Color Film Table", nullptr));
        dkDesign->setWindowTitle(QApplication::translate("MyEditorEBDClass", "Design Navigator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyEditorEBDClass: public Ui_MyEditorEBDClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYEDITOREBD_H
