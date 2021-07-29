/********************************************************************************
** Form generated from reading UI file 'AboutDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnOk;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QStringLiteral("AboutDialog"));
        AboutDialog->resize(295, 230);
        AboutDialog->setMinimumSize(QSize(295, 230));
        AboutDialog->setMaximumSize(QSize(295, 230));
        QIcon icon;
        icon.addFile(QStringLiteral(":/MyEditorEBD/Resources/needle.png"), QSize(), QIcon::Normal, QIcon::Off);
        AboutDialog->setWindowIcon(icon);
        label = new QLabel(AboutDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 80, 271, 90));
        label_2 = new QLabel(AboutDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 231, 41));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(18);
        label_2->setFont(font);
        btnOk = new QPushButton(AboutDialog);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        btnOk->setGeometry(QRect(210, 200, 75, 23));

        retranslateUi(AboutDialog);

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "Ebd Editor", nullptr));
        label->setText(QApplication::translate("AboutDialog", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Version 1.0.0</span></p><p><span style=\" font-size:14pt; font-weight:600;\">2020 SunStar Company.</span></p><p><span style=\" font-size:14pt; font-weight:600;\">All rights reserved.</span></p></body></html>", nullptr));
        label_2->setText(QApplication::translate("AboutDialog", "<html><head/><body><p><span style=\" color:#0000ff;\">About Ebd Editor</span></p></body></html>", nullptr));
        btnOk->setText(QApplication::translate("AboutDialog", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
