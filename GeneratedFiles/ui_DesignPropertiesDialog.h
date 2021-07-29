/********************************************************************************
** Form generated from reading UI file 'DesignPropertiesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESIGNPROPERTIESDIALOG_H
#define UI_DESIGNPROPERTIESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DesignPropertiesDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *lbImage;
    QLabel *label_2;
    QLabel *lbFileName;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLabel *lbDesign;
    QLabel *label_4;
    QLabel *lbSize;
    QLabel *label_5;
    QLabel *lbTotalStitch;
    QLabel *label_6;
    QLabel *lbColor;
    QLabel *label_7;
    QLabel *lbJump;

    void setupUi(QDialog *DesignPropertiesDialog)
    {
        if (DesignPropertiesDialog->objectName().isEmpty())
            DesignPropertiesDialog->setObjectName(QStringLiteral("DesignPropertiesDialog"));
        DesignPropertiesDialog->resize(550, 448);
        DesignPropertiesDialog->setMinimumSize(QSize(550, 448));
        DesignPropertiesDialog->setMaximumSize(QSize(550, 448));
        gridLayout = new QGridLayout(DesignPropertiesDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(448, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        btnOk = new QPushButton(DesignPropertiesDialog);
        btnOk->setObjectName(QStringLiteral("btnOk"));

        gridLayout->addWidget(btnOk, 1, 1, 1, 1);

        tabWidget = new QTabWidget(DesignPropertiesDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 50, 161, 161));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lbImage = new QLabel(groupBox);
        lbImage->setObjectName(QStringLiteral("lbImage"));
        lbImage->setScaledContents(true);

        gridLayout_2->addWidget(lbImage, 0, 0, 1, 1);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 99, 12));
        lbFileName = new QLabel(tab);
        lbFileName->setObjectName(QStringLiteral("lbFileName"));
        lbFileName->setGeometry(QRect(10, 30, 56, 12));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(200, 50, 321, 151));
        gridLayout_3 = new QGridLayout(layoutWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(43, 16777215));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        lbDesign = new QLabel(layoutWidget);
        lbDesign->setObjectName(QStringLiteral("lbDesign"));

        gridLayout_3->addWidget(lbDesign, 0, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(29, 16777215));

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        lbSize = new QLabel(layoutWidget);
        lbSize->setObjectName(QStringLiteral("lbSize"));

        gridLayout_3->addWidget(lbSize, 1, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(67, 16777215));

        gridLayout_3->addWidget(label_5, 2, 0, 1, 1);

        lbTotalStitch = new QLabel(layoutWidget);
        lbTotalStitch->setObjectName(QStringLiteral("lbTotalStitch"));

        gridLayout_3->addWidget(lbTotalStitch, 2, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMaximumSize(QSize(34, 16777215));

        gridLayout_3->addWidget(label_6, 3, 0, 1, 1);

        lbColor = new QLabel(layoutWidget);
        lbColor->setObjectName(QStringLiteral("lbColor"));

        gridLayout_3->addWidget(lbColor, 3, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(35, 16777215));

        gridLayout_3->addWidget(label_7, 4, 0, 1, 1);

        lbJump = new QLabel(layoutWidget);
        lbJump->setObjectName(QStringLiteral("lbJump"));

        gridLayout_3->addWidget(lbJump, 4, 1, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 2);


        retranslateUi(DesignPropertiesDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DesignPropertiesDialog);
    } // setupUi

    void retranslateUi(QDialog *DesignPropertiesDialog)
    {
        DesignPropertiesDialog->setWindowTitle(QApplication::translate("DesignPropertiesDialog", "DesignPropertiesDialog", nullptr));
        btnOk->setText(QApplication::translate("DesignPropertiesDialog", "Ok", nullptr));
        groupBox->setTitle(QString());
        lbImage->setText(QString());
        label_2->setText(QApplication::translate("DesignPropertiesDialog", "Design file name:", nullptr));
        lbFileName->setText(QApplication::translate("DesignPropertiesDialog", "file", nullptr));
        label_3->setText(QApplication::translate("DesignPropertiesDialog", "Design:", nullptr));
        lbDesign->setText(QApplication::translate("DesignPropertiesDialog", ".", nullptr));
        label_4->setText(QApplication::translate("DesignPropertiesDialog", "Size:", nullptr));
        lbSize->setText(QApplication::translate("DesignPropertiesDialog", ".", nullptr));
        label_5->setText(QApplication::translate("DesignPropertiesDialog", "Total Stitch:", nullptr));
        lbTotalStitch->setText(QApplication::translate("DesignPropertiesDialog", ".", nullptr));
        label_6->setText(QApplication::translate("DesignPropertiesDialog", "Color:", nullptr));
        lbColor->setText(QApplication::translate("DesignPropertiesDialog", ".", nullptr));
        label_7->setText(QApplication::translate("DesignPropertiesDialog", "Jump:", nullptr));
        lbJump->setText(QApplication::translate("DesignPropertiesDialog", ".", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
    } // retranslateUi

};

namespace Ui {
    class DesignPropertiesDialog: public Ui_DesignPropertiesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESIGNPROPERTIESDIALOG_H
