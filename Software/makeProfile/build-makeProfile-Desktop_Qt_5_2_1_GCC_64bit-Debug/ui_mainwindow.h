/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBeaglebone;
    QAction *actionUS_Sensor;
    QAction *actionAccelerometer;
    QAction *actionGyroscope;
    QAction *actionGPS;
    QAction *actionCompass;
    QAction *actionAltimiter;
    QAction *actionIR_Sensor;
    QAction *actionOpen_Command_Window;
    QAction *actionOpen_Output_Window;
    QAction *actionConnect_Device;
    QAction *actionDisconnect_Device;
    QAction *actionWrite_to_PDF;
    QAction *actionOpen_Command_Window_2;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QFormLayout *formLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxNumSample;
    QSpinBox *spinBoxSampleDelay;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonPauseResume;
    QPushButton *pushButtonRecord;
    QPushButton *pushButtonSample;
    QGroupBox *groupBox;
    QFormLayout *formLayout_3;
    QRadioButton *radioFilter;
    QRadioButton *radioRunningAverage;
    QRadioButton *radioSample;
    QRadioButton *radioKalman;
    QCustomPlot *mainPlot;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioRaw;
    QRadioButton *radioConvert;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBoxData1;
    QLabel *labelBlue;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxData2;
    QLabel *labelRed;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBoxData3;
    QLabel *labelGreen;
    QPlainTextEdit *plainTextOutput;
    QMenuBar *menuBar;
    QMenu *menuInterface;
    QMenu *menuInterface_2;
    QMenu *menuFusion;
    QMenu *menuDocument;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(857, 581);
        actionBeaglebone = new QAction(MainWindow);
        actionBeaglebone->setObjectName(QStringLiteral("actionBeaglebone"));
        actionUS_Sensor = new QAction(MainWindow);
        actionUS_Sensor->setObjectName(QStringLiteral("actionUS_Sensor"));
        actionAccelerometer = new QAction(MainWindow);
        actionAccelerometer->setObjectName(QStringLiteral("actionAccelerometer"));
        actionGyroscope = new QAction(MainWindow);
        actionGyroscope->setObjectName(QStringLiteral("actionGyroscope"));
        actionGPS = new QAction(MainWindow);
        actionGPS->setObjectName(QStringLiteral("actionGPS"));
        actionCompass = new QAction(MainWindow);
        actionCompass->setObjectName(QStringLiteral("actionCompass"));
        actionAltimiter = new QAction(MainWindow);
        actionAltimiter->setObjectName(QStringLiteral("actionAltimiter"));
        actionIR_Sensor = new QAction(MainWindow);
        actionIR_Sensor->setObjectName(QStringLiteral("actionIR_Sensor"));
        actionOpen_Command_Window = new QAction(MainWindow);
        actionOpen_Command_Window->setObjectName(QStringLiteral("actionOpen_Command_Window"));
        actionOpen_Output_Window = new QAction(MainWindow);
        actionOpen_Output_Window->setObjectName(QStringLiteral("actionOpen_Output_Window"));
        actionConnect_Device = new QAction(MainWindow);
        actionConnect_Device->setObjectName(QStringLiteral("actionConnect_Device"));
        actionDisconnect_Device = new QAction(MainWindow);
        actionDisconnect_Device->setObjectName(QStringLiteral("actionDisconnect_Device"));
        actionWrite_to_PDF = new QAction(MainWindow);
        actionWrite_to_PDF->setObjectName(QStringLiteral("actionWrite_to_PDF"));
        actionOpen_Command_Window_2 = new QAction(MainWindow);
        actionOpen_Command_Window_2->setObjectName(QStringLiteral("actionOpen_Command_Window_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMaximumSize(QSize(301, 164));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout_2 = new QFormLayout(frame);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::FieldRole, label_2);

        spinBoxNumSample = new QSpinBox(frame);
        spinBoxNumSample->setObjectName(QStringLiteral("spinBoxNumSample"));

        formLayout->setWidget(1, QFormLayout::LabelRole, spinBoxNumSample);

        spinBoxSampleDelay = new QSpinBox(frame);
        spinBoxSampleDelay->setObjectName(QStringLiteral("spinBoxSampleDelay"));

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxSampleDelay);


        verticalLayout_3->addLayout(formLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButtonPauseResume = new QPushButton(frame);
        pushButtonPauseResume->setObjectName(QStringLiteral("pushButtonPauseResume"));

        verticalLayout->addWidget(pushButtonPauseResume);

        pushButtonRecord = new QPushButton(frame);
        pushButtonRecord->setObjectName(QStringLiteral("pushButtonRecord"));

        verticalLayout->addWidget(pushButtonRecord);


        verticalLayout_2->addLayout(verticalLayout);

        pushButtonSample = new QPushButton(frame);
        pushButtonSample->setObjectName(QStringLiteral("pushButtonSample"));

        verticalLayout_2->addWidget(pushButtonSample);


        horizontalLayout->addLayout(verticalLayout_2);


        formLayout_2->setLayout(0, QFormLayout::LabelRole, horizontalLayout);


        gridLayout->addWidget(frame, 1, 2, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(164, 138));
        formLayout_3 = new QFormLayout(groupBox);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        radioFilter = new QRadioButton(groupBox);
        radioFilter->setObjectName(QStringLiteral("radioFilter"));
        radioFilter->setChecked(true);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, radioFilter);

        radioRunningAverage = new QRadioButton(groupBox);
        radioRunningAverage->setObjectName(QStringLiteral("radioRunningAverage"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, radioRunningAverage);

        radioSample = new QRadioButton(groupBox);
        radioSample->setObjectName(QStringLiteral("radioSample"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, radioSample);

        radioKalman = new QRadioButton(groupBox);
        radioKalman->setObjectName(QStringLiteral("radioKalman"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, radioKalman);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        mainPlot = new QCustomPlot(centralWidget);
        mainPlot->setObjectName(QStringLiteral("mainPlot"));

        gridLayout->addWidget(mainPlot, 0, 0, 1, 3);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(256, 84));
        verticalLayout_6 = new QVBoxLayout(groupBox_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        radioRaw = new QRadioButton(groupBox_2);
        radioRaw->setObjectName(QStringLiteral("radioRaw"));
        radioRaw->setMinimumSize(QSize(105, 21));
        radioRaw->setMaximumSize(QSize(105, 21));
        radioRaw->setChecked(true);

        verticalLayout_6->addWidget(radioRaw);

        radioConvert = new QRadioButton(groupBox_2);
        radioConvert->setObjectName(QStringLiteral("radioConvert"));
        radioConvert->setMinimumSize(QSize(105, 21));
        radioConvert->setMaximumSize(QSize(105, 21));

        verticalLayout_6->addWidget(radioConvert);


        verticalLayout_5->addWidget(groupBox_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBoxData1 = new QCheckBox(centralWidget);
        checkBoxData1->setObjectName(QStringLiteral("checkBoxData1"));
        checkBoxData1->setChecked(true);

        horizontalLayout_2->addWidget(checkBoxData1);

        labelBlue = new QLabel(centralWidget);
        labelBlue->setObjectName(QStringLiteral("labelBlue"));

        horizontalLayout_2->addWidget(labelBlue);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBoxData2 = new QCheckBox(centralWidget);
        checkBoxData2->setObjectName(QStringLiteral("checkBoxData2"));
        checkBoxData2->setChecked(true);

        horizontalLayout_3->addWidget(checkBoxData2);

        labelRed = new QLabel(centralWidget);
        labelRed->setObjectName(QStringLiteral("labelRed"));

        horizontalLayout_3->addWidget(labelRed);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBoxData3 = new QCheckBox(centralWidget);
        checkBoxData3->setObjectName(QStringLiteral("checkBoxData3"));
        checkBoxData3->setChecked(true);

        horizontalLayout_4->addWidget(checkBoxData3);

        labelGreen = new QLabel(centralWidget);
        labelGreen->setObjectName(QStringLiteral("labelGreen"));

        horizontalLayout_4->addWidget(labelGreen);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout_5->addLayout(verticalLayout_4);

        plainTextOutput = new QPlainTextEdit(centralWidget);
        plainTextOutput->setObjectName(QStringLiteral("plainTextOutput"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plainTextOutput->sizePolicy().hasHeightForWidth());
        plainTextOutput->setSizePolicy(sizePolicy);
        plainTextOutput->setReadOnly(true);

        verticalLayout_5->addWidget(plainTextOutput);


        gridLayout_2->addLayout(verticalLayout_5, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 857, 25));
        menuInterface = new QMenu(menuBar);
        menuInterface->setObjectName(QStringLiteral("menuInterface"));
        menuInterface_2 = new QMenu(menuBar);
        menuInterface_2->setObjectName(QStringLiteral("menuInterface_2"));
        menuFusion = new QMenu(menuBar);
        menuFusion->setObjectName(QStringLiteral("menuFusion"));
        menuDocument = new QMenu(menuBar);
        menuDocument->setObjectName(QStringLiteral("menuDocument"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuInterface->menuAction());
        menuBar->addAction(menuInterface_2->menuAction());
        menuBar->addAction(menuFusion->menuAction());
        menuBar->addAction(menuDocument->menuAction());
        menuInterface->addAction(actionUS_Sensor);
        menuInterface->addAction(actionAccelerometer);
        menuInterface->addAction(actionGyroscope);
        menuInterface->addAction(actionGPS);
        menuInterface->addAction(actionCompass);
        menuInterface->addAction(actionAltimiter);
        menuInterface->addAction(actionIR_Sensor);
        menuInterface_2->addAction(actionConnect_Device);
        menuInterface_2->addAction(actionDisconnect_Device);
        menuInterface_2->addAction(actionOpen_Command_Window_2);
        menuDocument->addAction(actionWrite_to_PDF);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionBeaglebone->setText(QApplication::translate("MainWindow", "Beaglebone", 0));
        actionUS_Sensor->setText(QApplication::translate("MainWindow", "US Sensor", 0));
        actionAccelerometer->setText(QApplication::translate("MainWindow", "Accelerometer", 0));
        actionGyroscope->setText(QApplication::translate("MainWindow", "Gyroscope", 0));
        actionGPS->setText(QApplication::translate("MainWindow", "GPS", 0));
        actionCompass->setText(QApplication::translate("MainWindow", "Compass", 0));
        actionAltimiter->setText(QApplication::translate("MainWindow", "Altimiter", 0));
        actionIR_Sensor->setText(QApplication::translate("MainWindow", "IR Sensor", 0));
        actionOpen_Command_Window->setText(QApplication::translate("MainWindow", "Open Command Window", 0));
        actionOpen_Output_Window->setText(QApplication::translate("MainWindow", "Open Output Window", 0));
        actionConnect_Device->setText(QApplication::translate("MainWindow", "Connect Device", 0));
        actionDisconnect_Device->setText(QApplication::translate("MainWindow", "Disconnect Device", 0));
        actionWrite_to_PDF->setText(QApplication::translate("MainWindow", "Write to PDF", 0));
        actionOpen_Command_Window_2->setText(QApplication::translate("MainWindow", "Open Command Window", 0));
        label->setText(QApplication::translate("MainWindow", "# samples", 0));
        label_2->setText(QApplication::translate("MainWindow", "Sample Delay", 0));
        pushButtonPauseResume->setText(QApplication::translate("MainWindow", "Pause/Resume", 0));
        pushButtonRecord->setText(QApplication::translate("MainWindow", "Record", 0));
        pushButtonSample->setText(QApplication::translate("MainWindow", "Sample", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Options:", 0));
        radioFilter->setText(QApplication::translate("MainWindow", "No Filter", 0));
        radioRunningAverage->setText(QApplication::translate("MainWindow", "Running Average", 0));
        radioSample->setText(QApplication::translate("MainWindow", "Sample", 0));
        radioKalman->setText(QApplication::translate("MainWindow", "Kalman Filter", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Data:", 0));
        radioRaw->setText(QApplication::translate("MainWindow", "Raw", 0));
        radioConvert->setText(QApplication::translate("MainWindow", "Convert", 0));
        checkBoxData1->setText(QApplication::translate("MainWindow", "Axis 1", 0));
        labelBlue->setText(QApplication::translate("MainWindow", "(Blue)", 0));
        checkBoxData2->setText(QApplication::translate("MainWindow", "Axis 2", 0));
        labelRed->setText(QApplication::translate("MainWindow", "(Red)", 0));
        checkBoxData3->setText(QApplication::translate("MainWindow", "Axis 3", 0));
        labelGreen->setText(QApplication::translate("MainWindow", "(Green)", 0));
        menuInterface->setTitle(QApplication::translate("MainWindow", "Sensor", 0));
        menuInterface_2->setTitle(QApplication::translate("MainWindow", "Device", 0));
        menuFusion->setTitle(QApplication::translate("MainWindow", "Fusion", 0));
        menuDocument->setTitle(QApplication::translate("MainWindow", "Document", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
