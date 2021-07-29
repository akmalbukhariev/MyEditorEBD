/********************************************************************************
** Form generated from reading UI file 'WidgetSequenceViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETSEQUENCEVIEWER_H
#define UI_WIDGETSEQUENCEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetSequenceViewer
{
public:

    void setupUi(QWidget *WidgetSequenceViewer)
    {
        if (WidgetSequenceViewer->objectName().isEmpty())
            WidgetSequenceViewer->setObjectName(QStringLiteral("WidgetSequenceViewer"));
        WidgetSequenceViewer->resize(400, 300);

        retranslateUi(WidgetSequenceViewer);

        QMetaObject::connectSlotsByName(WidgetSequenceViewer);
    } // setupUi

    void retranslateUi(QWidget *WidgetSequenceViewer)
    {
        WidgetSequenceViewer->setWindowTitle(QApplication::translate("WidgetSequenceViewer", "WidgetSequenceViewer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetSequenceViewer: public Ui_WidgetSequenceViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETSEQUENCEVIEWER_H
