/********************************************************************************
** Form generated from reading UI file 'PreviewDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWDIALOG_H
#define UI_PREVIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSplitter>
#include "DesignListWidget.h"
#include "FileDirTreeView.h"

QT_BEGIN_NAMESPACE

class Ui_PreviewDialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lEPath;
    QComboBox *cBSort;
    QLabel *label;
    QLabel *lBFileCount;
    QSplitter *splitter;
    FileDirTreeView *tVDir;
    DesignListWidget *lWImages;

    void setupUi(QDialog *PreviewDialog)
    {
        if (PreviewDialog->objectName().isEmpty())
            PreviewDialog->setObjectName(QStringLiteral("PreviewDialog"));
        PreviewDialog->resize(970, 723);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MyEditorEBD/Resources/preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        PreviewDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(PreviewDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lEPath = new QLineEdit(PreviewDialog);
        lEPath->setObjectName(QStringLiteral("lEPath"));

        gridLayout->addWidget(lEPath, 0, 0, 1, 1);

        cBSort = new QComboBox(PreviewDialog);
        cBSort->setObjectName(QStringLiteral("cBSort"));
        cBSort->setMinimumSize(QSize(161, 0));

        gridLayout->addWidget(cBSort, 0, 1, 1, 1);

        label = new QLabel(PreviewDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        lBFileCount = new QLabel(PreviewDialog);
        lBFileCount->setObjectName(QStringLiteral("lBFileCount"));
        lBFileCount->setMinimumSize(QSize(30, 0));

        gridLayout->addWidget(lBFileCount, 0, 3, 1, 1);

        splitter = new QSplitter(PreviewDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tVDir = new FileDirTreeView(splitter);
        tVDir->setObjectName(QStringLiteral("tVDir"));
        tVDir->setMaximumSize(QSize(250, 16777215));
        splitter->addWidget(tVDir);
        lWImages = new DesignListWidget(splitter);
        lWImages->setObjectName(QStringLiteral("lWImages"));
        splitter->addWidget(lWImages);

        gridLayout->addWidget(splitter, 1, 0, 1, 4);


        retranslateUi(PreviewDialog);

        QMetaObject::connectSlotsByName(PreviewDialog);
    } // setupUi

    void retranslateUi(QDialog *PreviewDialog)
    {
        PreviewDialog->setWindowTitle(QApplication::translate("PreviewDialog", "PreviewDialog", nullptr));
        label->setText(QApplication::translate("PreviewDialog", "Files: ", nullptr));
        lBFileCount->setText(QApplication::translate("PreviewDialog", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PreviewDialog: public Ui_PreviewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWDIALOG_H
