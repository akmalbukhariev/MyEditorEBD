/********************************************************************************
** Form generated from reading UI file 'WidgetNavigator.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETNAVIGATOR_H
#define UI_WIDGETNAVIGATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "DesignGraphicsView.h"

QT_BEGIN_NAMESPACE

class Ui_WidgetNavigator
{
public:
    QGridLayout *gridLayout;
    DesignGraphicsView *designView;

    void setupUi(QWidget *WidgetNavigator)
    {
        if (WidgetNavigator->objectName().isEmpty())
            WidgetNavigator->setObjectName(QStringLiteral("WidgetNavigator"));
        WidgetNavigator->resize(384, 289);
        gridLayout = new QGridLayout(WidgetNavigator);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        designView = new DesignGraphicsView(WidgetNavigator);
        designView->setObjectName(QStringLiteral("designView"));
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        designView->setBackgroundBrush(brush);

        gridLayout->addWidget(designView, 0, 0, 1, 1);


        retranslateUi(WidgetNavigator);

        QMetaObject::connectSlotsByName(WidgetNavigator);
    } // setupUi

    void retranslateUi(QWidget *WidgetNavigator)
    {
        WidgetNavigator->setWindowTitle(QApplication::translate("WidgetNavigator", "WidgetNavigator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetNavigator: public Ui_WidgetNavigator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETNAVIGATOR_H
