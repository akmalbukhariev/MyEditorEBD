/********************************************************************************
** Form generated from reading UI file 'WidgetPointInfo.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETPOINTINFO_H
#define UI_WIDGETPOINTINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "PointTableView.h"

QT_BEGIN_NAMESPACE

class Ui_WidgetPointInfo
{
public:
    QGridLayout *gridLayout;
    PointTableView *tView;

    void setupUi(QWidget *WidgetPointInfo)
    {
        if (WidgetPointInfo->objectName().isEmpty())
            WidgetPointInfo->setObjectName(QStringLiteral("WidgetPointInfo"));
        WidgetPointInfo->resize(400, 300);
        gridLayout = new QGridLayout(WidgetPointInfo);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tView = new PointTableView(WidgetPointInfo);
        tView->setObjectName(QStringLiteral("tView"));

        gridLayout->addWidget(tView, 0, 0, 1, 1);


        retranslateUi(WidgetPointInfo);

        QMetaObject::connectSlotsByName(WidgetPointInfo);
    } // setupUi

    void retranslateUi(QWidget *WidgetPointInfo)
    {
        WidgetPointInfo->setWindowTitle(QApplication::translate("WidgetPointInfo", "WidgetPointInfo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetPointInfo: public Ui_WidgetPointInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETPOINTINFO_H
