/********************************************************************************
** Form generated from reading UI file 'turingmachine.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TURINGMACHINE_H
#define UI_TURINGMACHINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TuringMachineClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableWidget *tape;
    QHBoxLayout *horizontalLayout;
    QPushButton *step;
    QPushButton *begin;
    QPushButton *stop;
    QSpacerItem *horizontalSpacer;
    QPushButton *exportTape;
    QPushButton *importTape;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QTableWidget *controller;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *nextCommand;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *currentState;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *exportController;
    QPushButton *importController;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TuringMachineClass)
    {
        if (TuringMachineClass->objectName().isEmpty())
            TuringMachineClass->setObjectName(QStringLiteral("TuringMachineClass"));
        TuringMachineClass->resize(1159, 649);
        TuringMachineClass->setMinimumSize(QSize(1159, 649));
        TuringMachineClass->setMaximumSize(QSize(1159, 649));
        centralWidget = new QWidget(TuringMachineClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(1141, 131));
        groupBox->setMaximumSize(QSize(1141, 131));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tape = new QTableWidget(groupBox);
        tape->setObjectName(QStringLiteral("tape"));
        tape->setMinimumSize(QSize(0, 60));
        tape->setMaximumSize(QSize(16777215, 60));
        QFont font;
        font.setFamily(QStringLiteral("Cooper Black"));
        font.setPointSize(13);
        font.setBold(false);
        font.setWeight(50);
        tape->setFont(font);
        tape->setTextElideMode(Qt::ElideMiddle);
        tape->horizontalHeader()->setVisible(false);
        tape->horizontalHeader()->setCascadingSectionResizes(true);
        tape->horizontalHeader()->setDefaultSectionSize(50);
        tape->verticalHeader()->setVisible(false);
        tape->verticalHeader()->setCascadingSectionResizes(false);
        tape->verticalHeader()->setDefaultSectionSize(50);

        gridLayout_2->addWidget(tape, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        step = new QPushButton(groupBox);
        step->setObjectName(QStringLiteral("step"));
        step->setMinimumSize(QSize(75, 23));
        step->setMaximumSize(QSize(75, 23));
        QFont font1;
        font1.setPointSize(9);
        step->setFont(font1);

        horizontalLayout->addWidget(step);

        begin = new QPushButton(groupBox);
        begin->setObjectName(QStringLiteral("begin"));
        begin->setMinimumSize(QSize(75, 23));
        begin->setMaximumSize(QSize(75, 23));
        begin->setFont(font1);

        horizontalLayout->addWidget(begin);

        stop = new QPushButton(groupBox);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setMinimumSize(QSize(75, 23));
        stop->setMaximumSize(QSize(75, 23));
        stop->setFont(font1);

        horizontalLayout->addWidget(stop);

        horizontalSpacer = new QSpacerItem(718, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        exportTape = new QPushButton(groupBox);
        exportTape->setObjectName(QStringLiteral("exportTape"));
        exportTape->setMinimumSize(QSize(75, 23));
        exportTape->setMaximumSize(QSize(75, 23));
        exportTape->setFont(font1);

        horizontalLayout->addWidget(exportTape);

        importTape = new QPushButton(groupBox);
        importTape->setObjectName(QStringLiteral("importTape"));
        importTape->setMinimumSize(QSize(75, 23));
        importTape->setMaximumSize(QSize(75, 23));
        importTape->setFont(font1);

        horizontalLayout->addWidget(importTape);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(1141, 451));
        groupBox_2->setMaximumSize(QSize(1141, 451));
        groupBox_2->setFont(font1);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        controller = new QTableWidget(groupBox_2);
        controller->setObjectName(QStringLiteral("controller"));
        controller->setMinimumSize(QSize(581, 371));
        controller->setMaximumSize(QSize(581, 371));
        controller->horizontalHeader()->setCascadingSectionResizes(false);
        controller->horizontalHeader()->setStretchLastSection(true);
        controller->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(controller, 0, 0, 3, 2);

        frame_2 = new QFrame(groupBox_2);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMinimumSize(QSize(529, 46));
        frame_2->setMaximumSize(QSize(529, 46));
        frame_2->setFrameShape(QFrame::WinPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        nextCommand = new QLabel(frame_2);
        nextCommand->setObjectName(QStringLiteral("nextCommand"));
        QFont font2;
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setWeight(75);
        nextCommand->setFont(font2);
        nextCommand->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(nextCommand);


        gridLayout->addWidget(frame_2, 0, 2, 1, 1);

        frame = new QFrame(groupBox_2);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(529, 46));
        frame->setMaximumSize(QSize(529, 46));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        horizontalLayout_2->addWidget(label);

        currentState = new QLabel(frame);
        currentState->setObjectName(QStringLiteral("currentState"));
        currentState->setFont(font2);
        currentState->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(currentState);


        gridLayout->addWidget(frame, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(17, 295, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 2, 2, 2, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        exportController = new QPushButton(groupBox_2);
        exportController->setObjectName(QStringLiteral("exportController"));
        exportController->setMinimumSize(QSize(75, 23));
        exportController->setMaximumSize(QSize(75, 23));

        horizontalLayout_4->addWidget(exportController);

        importController = new QPushButton(groupBox_2);
        importController->setObjectName(QStringLiteral("importController"));
        importController->setMinimumSize(QSize(75, 23));
        importController->setMaximumSize(QSize(75, 23));

        horizontalLayout_4->addWidget(importController);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(398, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        TuringMachineClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TuringMachineClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1159, 21));
        TuringMachineClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TuringMachineClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TuringMachineClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TuringMachineClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TuringMachineClass->setStatusBar(statusBar);

        retranslateUi(TuringMachineClass);

        QMetaObject::connectSlotsByName(TuringMachineClass);
    } // setupUi

    void retranslateUi(QMainWindow *TuringMachineClass)
    {
        TuringMachineClass->setWindowTitle(QApplication::translate("TuringMachineClass", "TuringMachine", 0));
        groupBox->setTitle(QApplication::translate("TuringMachineClass", "\320\233\320\265\320\275\321\202\320\260", 0));
        step->setText(QApplication::translate("TuringMachineClass", "\320\250\320\260\320\263", 0));
        begin->setText(QApplication::translate("TuringMachineClass", "\320\235\320\260\321\207\320\260\321\202\321\214", 0));
        stop->setText(QApplication::translate("TuringMachineClass", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0));
        exportTape->setText(QApplication::translate("TuringMachineClass", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202", 0));
        importTape->setText(QApplication::translate("TuringMachineClass", "\320\230\320\274\320\277\320\276\321\200\321\202", 0));
        groupBox_2->setTitle(QApplication::translate("TuringMachineClass", "\320\243\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", 0));
        label_3->setText(QApplication::translate("TuringMachineClass", "\320\241\320\273\320\265\320\264\321\203\321\216\321\211\320\260\321\217 \320\272\320\276\320\274\320\260\320\275\320\264\320\260:", 0));
        nextCommand->setText(QApplication::translate("TuringMachineClass", "-", 0));
        label->setText(QApplication::translate("TuringMachineClass", "\320\242\320\265\320\272\321\203\321\211\320\265\320\265 \321\201\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265:", 0));
        currentState->setText(QApplication::translate("TuringMachineClass", "-", 0));
        exportController->setText(QApplication::translate("TuringMachineClass", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202", 0));
        importController->setText(QApplication::translate("TuringMachineClass", "\320\230\320\274\320\277\320\276\321\200\321\202", 0));
    } // retranslateUi

};

namespace Ui {
    class TuringMachineClass: public Ui_TuringMachineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TURINGMACHINE_H
