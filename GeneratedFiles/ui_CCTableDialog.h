/********************************************************************************
** Form generated from reading UI file 'CCTableDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCTABLEDIALOG_H
#define UI_CCTABLEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "CCTableView.h"
#include "ChenileWidget.h"
#include "NormalWidget.h"
#include "TapeWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CCTableDialog
{
public:
    QGridLayout *gridLayout;
    CCTableView *tWCCTableView;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_9;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pBInit;
    QPushButton *pBSave;
    QTabWidget *tabWidgets;
    QWidget *tabNormal;
    QGridLayout *gridLayout_8;
    NormalWidget *wDNormal;
    QWidget *tabChenile;
    QGridLayout *gridLayout_5;
    ChenileWidget *wDChenile;
    QWidget *tabTape;
    QGridLayout *gridLayout_6;
    TapeWidget *wDTape;
    QGridLayout *gridLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QPushButton *pBAdd;
    QPushButton *pBRemove;

    void setupUi(QDialog *CCTableDialog)
    {
        if (CCTableDialog->objectName().isEmpty())
            CCTableDialog->setObjectName(QStringLiteral("CCTableDialog"));
        CCTableDialog->resize(1236, 833);
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/cctable.png"), QSize(), QIcon::Normal, QIcon::Off);
        CCTableDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(CCTableDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tWCCTableView = new CCTableView(CCTableDialog);
        tWCCTableView->setObjectName(QStringLiteral("tWCCTableView"));
        tWCCTableView->setMinimumSize(QSize(300, 0));
        tWCCTableView->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(tWCCTableView, 0, 0, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        horizontalSpacer_3 = new QSpacerItem(438, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        pBInit = new QPushButton(CCTableDialog);
        pBInit->setObjectName(QStringLiteral("pBInit"));
        pBInit->setMinimumSize(QSize(35, 35));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MyEditorEBD/Resources/btn_refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        pBInit->setIcon(icon1);
        pBInit->setIconSize(QSize(32, 32));

        gridLayout_9->addWidget(pBInit, 0, 1, 1, 1);

        pBSave = new QPushButton(CCTableDialog);
        pBSave->setObjectName(QStringLiteral("pBSave"));
        pBSave->setMinimumSize(QSize(35, 35));

        gridLayout_9->addWidget(pBSave, 0, 2, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 0, 0, 1, 1);

        tabWidgets = new QTabWidget(CCTableDialog);
        tabWidgets->setObjectName(QStringLiteral("tabWidgets"));
        tabWidgets->setCursor(QCursor(Qt::ArrowCursor));
        tabWidgets->setStyleSheet(QLatin1String("/* Style the tab using the tab sub-control. Note that\n"
"    it reads QTabBar _not_ QTabWidget */\n"
"QTabBar::tab { \n"
"  background: lightgray;\n"
"  color: black;\n"
"    padding: 20px;\n"
"}\n"
"QTabBar::tab:selected {\n"
"  background: white;\n"
" }"));
        tabNormal = new QWidget();
        tabNormal->setObjectName(QStringLiteral("tabNormal"));
        gridLayout_8 = new QGridLayout(tabNormal);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        wDNormal = new NormalWidget(tabNormal);
        wDNormal->setObjectName(QStringLiteral("wDNormal"));
        wDNormal->setAutoFillBackground(true);

        gridLayout_8->addWidget(wDNormal, 0, 0, 1, 1);

        tabWidgets->addTab(tabNormal, QString());
        tabChenile = new QWidget();
        tabChenile->setObjectName(QStringLiteral("tabChenile"));
        gridLayout_5 = new QGridLayout(tabChenile);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        wDChenile = new ChenileWidget(tabChenile);
        wDChenile->setObjectName(QStringLiteral("wDChenile"));
        wDChenile->setAutoFillBackground(true);

        gridLayout_5->addWidget(wDChenile, 0, 0, 1, 1);

        tabWidgets->addTab(tabChenile, QString());
        tabTape = new QWidget();
        tabTape->setObjectName(QStringLiteral("tabTape"));
        gridLayout_6 = new QGridLayout(tabTape);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        wDTape = new TapeWidget(tabTape);
        wDTape->setObjectName(QStringLiteral("wDTape"));
        wDTape->setAutoFillBackground(true);

        gridLayout_6->addWidget(wDTape, 0, 0, 1, 1);

        tabWidgets->addTab(tabTape, QString());

        gridLayout_10->addWidget(tabWidgets, 1, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(CCTableDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pBAdd = new QPushButton(groupBox_3);
        pBAdd->setObjectName(QStringLiteral("pBAdd"));
        pBAdd->setMinimumSize(QSize(51, 51));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MyEditorEBD/Resources/btn_needle_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pBAdd->setIcon(icon2);
        pBAdd->setIconSize(QSize(40, 40));

        gridLayout_3->addWidget(pBAdd, 0, 0, 1, 1);

        pBRemove = new QPushButton(groupBox_3);
        pBRemove->setObjectName(QStringLiteral("pBRemove"));
        pBRemove->setMinimumSize(QSize(51, 51));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MyEditorEBD/Resources/btn_needle_del.png"), QSize(), QIcon::Normal, QIcon::Off);
        pBRemove->setIcon(icon3);
        pBRemove->setIconSize(QSize(40, 40));

        gridLayout_3->addWidget(pBRemove, 0, 1, 1, 1);


        gridLayout_7->addWidget(groupBox_3, 0, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_7, 2, 0, 1, 1);


        gridLayout->addLayout(gridLayout_10, 0, 1, 1, 1);


        retranslateUi(CCTableDialog);

        tabWidgets->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(CCTableDialog);
    } // setupUi

    void retranslateUi(QDialog *CCTableDialog)
    {
        CCTableDialog->setWindowTitle(QApplication::translate("CCTableDialog", "CCTableDialog", nullptr));
#ifndef QT_NO_TOOLTIP
        pBInit->setToolTip(QApplication::translate("CCTableDialog", "Initialize cc dialog", nullptr));
#endif // QT_NO_TOOLTIP
        pBInit->setText(QString());
        pBSave->setText(QApplication::translate("CCTableDialog", "Save", nullptr));
        tabWidgets->setTabText(tabWidgets->indexOf(tabNormal), QApplication::translate("CCTableDialog", "Normal", nullptr));
        tabWidgets->setTabText(tabWidgets->indexOf(tabChenile), QApplication::translate("CCTableDialog", "Chenile", nullptr));
        tabWidgets->setTabText(tabWidgets->indexOf(tabTape), QApplication::translate("CCTableDialog", "Tape", nullptr));
        groupBox_3->setTitle(QApplication::translate("CCTableDialog", "Add and Remove", nullptr));
        pBAdd->setText(QString());
        pBRemove->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CCTableDialog: public Ui_CCTableDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CCTABLEDIALOG_H
