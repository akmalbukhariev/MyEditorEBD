/********************************************************************************
** Form generated from reading UI file 'WidgetCCTable.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETCCTABLE_H
#define UI_WIDGETCCTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetCCTable
{
public:
    QGridLayout *gridLayout;
    QTableView *tView;

    void setupUi(QWidget *WidgetCCTable)
    {
        if (WidgetCCTable->objectName().isEmpty())
            WidgetCCTable->setObjectName(QStringLiteral("WidgetCCTable"));
        WidgetCCTable->resize(400, 300);
        gridLayout = new QGridLayout(WidgetCCTable);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tView = new QTableView(WidgetCCTable);
        tView->setObjectName(QStringLiteral("tView"));

        gridLayout->addWidget(tView, 0, 0, 1, 1);


        retranslateUi(WidgetCCTable);

        QMetaObject::connectSlotsByName(WidgetCCTable);
    } // setupUi

    void retranslateUi(QWidget *WidgetCCTable)
    {
        WidgetCCTable->setWindowTitle(QApplication::translate("WidgetCCTable", "WidgetCCTable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetCCTable: public Ui_WidgetCCTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETCCTABLE_H
