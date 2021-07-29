/********************************************************************************
** Form generated from reading UI file 'WidgetWokrDesign.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETWOKRDESIGN_H
#define UI_WIDGETWOKRDESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "SewingGraphicsView.h"

QT_BEGIN_NAMESPACE

class Ui_WidgetWokrDesign
{
public:
    QGridLayout *gridLayout;
    SewingGraphicsView *grViewSewing;

    void setupUi(QWidget *WidgetWokrDesign)
    {
        if (WidgetWokrDesign->objectName().isEmpty())
            WidgetWokrDesign->setObjectName(QStringLiteral("WidgetWokrDesign"));
        WidgetWokrDesign->resize(749, 561);
        gridLayout = new QGridLayout(WidgetWokrDesign);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        grViewSewing = new SewingGraphicsView(WidgetWokrDesign);
        grViewSewing->setObjectName(QStringLiteral("grViewSewing"));

        gridLayout->addWidget(grViewSewing, 0, 0, 1, 1);


        retranslateUi(WidgetWokrDesign);

        QMetaObject::connectSlotsByName(WidgetWokrDesign);
    } // setupUi

    void retranslateUi(QWidget *WidgetWokrDesign)
    {
        WidgetWokrDesign->setWindowTitle(QApplication::translate("WidgetWokrDesign", "WidgetWokrDesign", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetWokrDesign: public Ui_WidgetWokrDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETWOKRDESIGN_H
