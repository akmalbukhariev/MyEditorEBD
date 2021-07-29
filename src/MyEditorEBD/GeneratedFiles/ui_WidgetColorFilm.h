/********************************************************************************
** Form generated from reading UI file 'WidgetColorFilm.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETCOLORFILM_H
#define UI_WIDGETCOLORFILM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetColorFilm
{
public:
    QGridLayout *gridLayout;
    QTableView *tbView;

    void setupUi(QWidget *WidgetColorFilm)
    {
        if (WidgetColorFilm->objectName().isEmpty())
            WidgetColorFilm->setObjectName(QStringLiteral("WidgetColorFilm"));
        WidgetColorFilm->resize(400, 300);
        gridLayout = new QGridLayout(WidgetColorFilm);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tbView = new QTableView(WidgetColorFilm);
        tbView->setObjectName(QStringLiteral("tbView"));

        gridLayout->addWidget(tbView, 0, 0, 1, 1);


        retranslateUi(WidgetColorFilm);

        QMetaObject::connectSlotsByName(WidgetColorFilm);
    } // setupUi

    void retranslateUi(QWidget *WidgetColorFilm)
    {
        WidgetColorFilm->setWindowTitle(QApplication::translate("WidgetColorFilm", "WidgetColorFilm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetColorFilm: public Ui_WidgetColorFilm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETCOLORFILM_H
