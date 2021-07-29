/********************************************************************************
** Form generated from reading UI file 'WidgetHeaderInfo.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETHEADERINFO_H
#define UI_WIDGETHEADERINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetHeaderInfo
{
public:
    QGridLayout *gridLayout;
    QTableView *tView;

    void setupUi(QWidget *WidgetHeaderInfo)
    {
        if (WidgetHeaderInfo->objectName().isEmpty())
            WidgetHeaderInfo->setObjectName(QStringLiteral("WidgetHeaderInfo"));
        WidgetHeaderInfo->resize(400, 300);
        gridLayout = new QGridLayout(WidgetHeaderInfo);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tView = new QTableView(WidgetHeaderInfo);
        tView->setObjectName(QStringLiteral("tView"));

        gridLayout->addWidget(tView, 0, 0, 1, 1);


        retranslateUi(WidgetHeaderInfo);

        QMetaObject::connectSlotsByName(WidgetHeaderInfo);
    } // setupUi

    void retranslateUi(QWidget *WidgetHeaderInfo)
    {
        WidgetHeaderInfo->setWindowTitle(QApplication::translate("WidgetHeaderInfo", "WidgetHeaderInfo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetHeaderInfo: public Ui_WidgetHeaderInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETHEADERINFO_H
