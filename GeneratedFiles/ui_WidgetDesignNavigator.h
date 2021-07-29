/********************************************************************************
** Form generated from reading UI file 'WidgetDesignNavigator.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETDESIGNNAVIGATOR_H
#define UI_WIDGETDESIGNNAVIGATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "DesignListNavigator.h"

QT_BEGIN_NAMESPACE

class Ui_WidgetDesignNavigator
{
public:
    QGridLayout *gridLayout;
    DesignListNavigator *lsWidgetDesign;

    void setupUi(QWidget *WidgetDesignNavigator)
    {
        if (WidgetDesignNavigator->objectName().isEmpty())
            WidgetDesignNavigator->setObjectName(QStringLiteral("WidgetDesignNavigator"));
        WidgetDesignNavigator->resize(400, 300);
        gridLayout = new QGridLayout(WidgetDesignNavigator);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lsWidgetDesign = new DesignListNavigator(WidgetDesignNavigator);
        lsWidgetDesign->setObjectName(QStringLiteral("lsWidgetDesign"));

        gridLayout->addWidget(lsWidgetDesign, 0, 0, 1, 1);


        retranslateUi(WidgetDesignNavigator);

        QMetaObject::connectSlotsByName(WidgetDesignNavigator);
    } // setupUi

    void retranslateUi(QWidget *WidgetDesignNavigator)
    {
        WidgetDesignNavigator->setWindowTitle(QApplication::translate("WidgetDesignNavigator", "WidgetDesignNavigator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetDesignNavigator: public Ui_WidgetDesignNavigator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETDESIGNNAVIGATOR_H
