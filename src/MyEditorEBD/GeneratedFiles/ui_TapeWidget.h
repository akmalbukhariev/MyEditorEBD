/********************************************************************************
** Form generated from reading UI file 'TapeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAPEWIDGET_H
#define UI_TAPEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TapeWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *pBNormal;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QPushButton *pB_Z1;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pB_R_Frill;
    QPushButton *pB_Z6;
    QPushButton *pB_Z4;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_8;
    QPushButton *pB_R_Coil;
    QPushButton *pB_F_Coil;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_9;
    QPushButton *pB_Z5;
    QPushButton *pB_Z2;
    QPushButton *pB_Z3;
    QPushButton *pB_R_Tape;
    QPushButton *pB_F_Frill;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_7;
    QPushButton *pB_F_Tape;

    void setupUi(QWidget *TapeWidget)
    {
        if (TapeWidget->objectName().isEmpty())
            TapeWidget->setObjectName(QStringLiteral("TapeWidget"));
        TapeWidget->resize(741, 427);
        gridLayout = new QGridLayout(TapeWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pBNormal = new QPushButton(TapeWidget);
        pBNormal->setObjectName(QStringLiteral("pBNormal"));
        pBNormal->setMinimumSize(QSize(80, 51));
        pBNormal->setMaximumSize(QSize(75, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(16);
        font.setBold(false);
        font.setWeight(50);
        pBNormal->setFont(font);

        gridLayout->addWidget(pBNormal, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 198, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 2, 7, 1, 1);

        pB_Z1 = new QPushButton(TapeWidget);
        pB_Z1->setObjectName(QStringLiteral("pB_Z1"));
        pB_Z1->setMinimumSize(QSize(60, 60));
        pB_Z1->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_z1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_Z1->setIcon(icon);
        pB_Z1->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_Z1, 1, 3, 1, 3);

        horizontalSpacer_4 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 22, 1, 1);

        pB_R_Frill = new QPushButton(TapeWidget);
        pB_R_Frill->setObjectName(QStringLiteral("pB_R_Frill"));
        pB_R_Frill->setMinimumSize(QSize(60, 60));
        pB_R_Frill->setFont(font);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_r_frill.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_R_Frill->setIcon(icon1);
        pB_R_Frill->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_R_Frill, 0, 19, 1, 3);

        pB_Z6 = new QPushButton(TapeWidget);
        pB_Z6->setObjectName(QStringLiteral("pB_Z6"));
        pB_Z6->setMinimumSize(QSize(60, 60));
        pB_Z6->setFont(font);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_z6.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_Z6->setIcon(icon2);
        pB_Z6->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_Z6, 1, 19, 1, 3);

        pB_Z4 = new QPushButton(TapeWidget);
        pB_Z4->setObjectName(QStringLiteral("pB_Z4"));
        pB_Z4->setMinimumSize(QSize(60, 60));
        pB_Z4->setFont(font);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_z4.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_Z4->setIcon(icon3);
        pB_Z4->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_Z4, 1, 13, 1, 3);

        verticalSpacer_10 = new QSpacerItem(20, 255, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_10, 1, 1, 2, 1);

        verticalSpacer_5 = new QSpacerItem(20, 198, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 2, 10, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 22, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 198, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_8, 2, 20, 1, 1);

        pB_R_Coil = new QPushButton(TapeWidget);
        pB_R_Coil->setObjectName(QStringLiteral("pB_R_Coil"));
        pB_R_Coil->setMinimumSize(QSize(60, 60));
        pB_R_Coil->setFont(font);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_r_coil.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_R_Coil->setIcon(icon4);
        pB_R_Coil->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_R_Coil, 0, 16, 1, 3);

        pB_F_Coil = new QPushButton(TapeWidget);
        pB_F_Coil->setObjectName(QStringLiteral("pB_F_Coil"));
        pB_F_Coil->setMinimumSize(QSize(60, 60));
        pB_F_Coil->setFont(font);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_f_coil.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_F_Coil->setIcon(icon5);
        pB_F_Coil->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_F_Coil, 0, 6, 1, 3);

        horizontalSpacer = new QSpacerItem(74, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 12, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 198, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 2, 4, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 198, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_9, 2, 17, 1, 1);

        pB_Z5 = new QPushButton(TapeWidget);
        pB_Z5->setObjectName(QStringLiteral("pB_Z5"));
        pB_Z5->setMinimumSize(QSize(60, 60));
        pB_Z5->setFont(font);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_z5.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_Z5->setIcon(icon6);
        pB_Z5->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_Z5, 1, 16, 1, 3);

        pB_Z2 = new QPushButton(TapeWidget);
        pB_Z2->setObjectName(QStringLiteral("pB_Z2"));
        pB_Z2->setMinimumSize(QSize(60, 60));
        pB_Z2->setFont(font);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_z2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_Z2->setIcon(icon7);
        pB_Z2->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_Z2, 1, 6, 1, 3);

        pB_Z3 = new QPushButton(TapeWidget);
        pB_Z3->setObjectName(QStringLiteral("pB_Z3"));
        pB_Z3->setMinimumSize(QSize(60, 60));
        pB_Z3->setFont(font);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_z3.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_Z3->setIcon(icon8);
        pB_Z3->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_Z3, 1, 9, 1, 3);

        pB_R_Tape = new QPushButton(TapeWidget);
        pB_R_Tape->setObjectName(QStringLiteral("pB_R_Tape"));
        pB_R_Tape->setMinimumSize(QSize(60, 60));
        pB_R_Tape->setFont(font);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_r_tape.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_R_Tape->setIcon(icon9);
        pB_R_Tape->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_R_Tape, 0, 13, 1, 3);

        pB_F_Frill = new QPushButton(TapeWidget);
        pB_F_Frill->setObjectName(QStringLiteral("pB_F_Frill"));
        pB_F_Frill->setMinimumSize(QSize(60, 60));
        pB_F_Frill->setFont(font);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_f_frill.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_F_Frill->setIcon(icon10);
        pB_F_Frill->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_F_Frill, 0, 9, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(74, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 12, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 198, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_7, 2, 14, 1, 1);

        pB_F_Tape = new QPushButton(TapeWidget);
        pB_F_Tape->setObjectName(QStringLiteral("pB_F_Tape"));
        pB_F_Tape->setMinimumSize(QSize(60, 60));
        pB_F_Tape->setFont(font);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/MyEditorEBD/Resources/icon_f_tape.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_F_Tape->setIcon(icon11);
        pB_F_Tape->setIconSize(QSize(45, 45));

        gridLayout->addWidget(pB_F_Tape, 0, 3, 1, 3);


        retranslateUi(TapeWidget);

        QMetaObject::connectSlotsByName(TapeWidget);
    } // setupUi

    void retranslateUi(QWidget *TapeWidget)
    {
        TapeWidget->setWindowTitle(QApplication::translate("TapeWidget", "TapeWidget", nullptr));
        pBNormal->setText(QApplication::translate("TapeWidget", "Normal", nullptr));
        pB_Z1->setText(QString());
#ifndef QT_NO_TOOLTIP
        pB_R_Frill->setToolTip(QApplication::translate("TapeWidget", "Frill", nullptr));
#endif // QT_NO_TOOLTIP
        pB_R_Frill->setText(QString());
        pB_Z6->setText(QString());
        pB_Z4->setText(QString());
#ifndef QT_NO_TOOLTIP
        pB_R_Coil->setToolTip(QApplication::translate("TapeWidget", "Coil", nullptr));
#endif // QT_NO_TOOLTIP
        pB_R_Coil->setText(QString());
#ifndef QT_NO_TOOLTIP
        pB_F_Coil->setToolTip(QApplication::translate("TapeWidget", "Coil", nullptr));
#endif // QT_NO_TOOLTIP
        pB_F_Coil->setText(QString());
        pB_Z5->setText(QString());
        pB_Z2->setText(QString());
        pB_Z3->setText(QString());
#ifndef QT_NO_TOOLTIP
        pB_R_Tape->setToolTip(QApplication::translate("TapeWidget", "Tape", nullptr));
#endif // QT_NO_TOOLTIP
        pB_R_Tape->setText(QString());
#ifndef QT_NO_TOOLTIP
        pB_F_Frill->setToolTip(QApplication::translate("TapeWidget", "Frill", nullptr));
#endif // QT_NO_TOOLTIP
        pB_F_Frill->setText(QString());
#ifndef QT_NO_TOOLTIP
        pB_F_Tape->setToolTip(QApplication::translate("TapeWidget", "Tape", nullptr));
#endif // QT_NO_TOOLTIP
        pB_F_Tape->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TapeWidget: public Ui_TapeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAPEWIDGET_H
