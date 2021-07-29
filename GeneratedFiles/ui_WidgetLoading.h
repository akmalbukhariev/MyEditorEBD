/********************************************************************************
** Form generated from reading UI file 'WidgetLoading.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETLOADING_H
#define UI_WIDGETLOADING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetLoading
{
public:
    QGridLayout *gridLayout;
    QLabel *lbLoadingGif;

    void setupUi(QWidget *WidgetLoading)
    {
        if (WidgetLoading->objectName().isEmpty())
            WidgetLoading->setObjectName(QStringLiteral("WidgetLoading"));
        WidgetLoading->resize(94, 16);
        WidgetLoading->setMaximumSize(QSize(94, 16));
        gridLayout = new QGridLayout(WidgetLoading);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lbLoadingGif = new QLabel(WidgetLoading);
        lbLoadingGif->setObjectName(QStringLiteral("lbLoadingGif"));
        lbLoadingGif->setScaledContents(true);

        gridLayout->addWidget(lbLoadingGif, 0, 0, 1, 1);


        retranslateUi(WidgetLoading);

        QMetaObject::connectSlotsByName(WidgetLoading);
    } // setupUi

    void retranslateUi(QWidget *WidgetLoading)
    {
        WidgetLoading->setWindowTitle(QApplication::translate("WidgetLoading", "WidgetLoading", nullptr));
        lbLoadingGif->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WidgetLoading: public Ui_WidgetLoading {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETLOADING_H
