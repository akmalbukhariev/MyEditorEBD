/********************************************************************************
** Form generated from reading UI file 'WidgetColorTable.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETCOLORTABLE_H
#define UI_WIDGETCOLORTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetColorTable
{
public:

    void setupUi(QWidget *WidgetColorTable)
    {
        if (WidgetColorTable->objectName().isEmpty())
            WidgetColorTable->setObjectName(QStringLiteral("WidgetColorTable"));
        WidgetColorTable->resize(400, 300);

        retranslateUi(WidgetColorTable);

        QMetaObject::connectSlotsByName(WidgetColorTable);
    } // setupUi

    void retranslateUi(QWidget *WidgetColorTable)
    {
        WidgetColorTable->setWindowTitle(QApplication::translate("WidgetColorTable", "WidgetColorTable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetColorTable: public Ui_WidgetColorTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETCOLORTABLE_H
