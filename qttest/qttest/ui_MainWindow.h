/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Thu 21. Jun 08:12:56 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionInfo;
    QAction *actionExit;
    QAction *action_Beenden;
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QGroupBox *groupBox;
    QPushButton *pushButton_6;
    QPushButton *pushButton;
    QComboBox *comboBox_2;
    QCheckBox *checkBox;
    QCheckBox *SPIMode;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QPushButton *pushButton_5;
    QCheckBox *RTSSet;
    QGroupBox *Cbus;
    QCheckBox *CBus0;
    QCheckBox *CBus1;
    QCheckBox *CBus2;
    QCheckBox *CBus3;
    QGroupBox *SPIGr;
    QTextEdit *SPIText;
    QPushButton *Send;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 530);
        MainWindow->setMinimumSize(QSize(600, 530));
        MainWindow->setMaximumSize(QSize(600, 530));
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName(QString::fromUtf8("actionInfo"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        action_Beenden = new QAction(MainWindow);
        action_Beenden->setObjectName(QString::fromUtf8("action_Beenden"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(true);
        textEdit->setGeometry(QRect(20, 150, 560, 339));
        textEdit->setMinimumSize(QSize(560, 339));
        textEdit->setMaximumSize(QSize(560, 340));
        textEdit->setReadOnly(true);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 261, 81));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(140, 20, 75, 23));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 20, 75, 23));
        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(10, 20, 31, 22));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(10, 50, 70, 17));
        SPIMode = new QCheckBox(groupBox);
        SPIMode->setObjectName(QString::fromUtf8("SPIMode"));
        SPIMode->setGeometry(QRect(110, 50, 70, 17));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(300, 10, 281, 81));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 20, 75, 23));
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 50, 75, 23));
        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(90, 20, 75, 23));
        verticalLayoutWidget = new QWidget(groupBox_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(180, 10, 91, 61));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(verticalLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        RTSSet = new QCheckBox(groupBox_2);
        RTSSet->setObjectName(QString::fromUtf8("RTSSet"));
        RTSSet->setGeometry(QRect(100, 50, 70, 17));
        Cbus = new QGroupBox(centralwidget);
        Cbus->setObjectName(QString::fromUtf8("Cbus"));
        Cbus->setGeometry(QRect(20, 90, 111, 51));
        CBus0 = new QCheckBox(Cbus);
        CBus0->setObjectName(QString::fromUtf8("CBus0"));
        CBus0->setGeometry(QRect(40, 10, 31, 17));
        CBus1 = new QCheckBox(Cbus);
        CBus1->setObjectName(QString::fromUtf8("CBus1"));
        CBus1->setGeometry(QRect(80, 10, 31, 17));
        CBus2 = new QCheckBox(Cbus);
        CBus2->setObjectName(QString::fromUtf8("CBus2"));
        CBus2->setGeometry(QRect(40, 30, 31, 17));
        CBus3 = new QCheckBox(Cbus);
        CBus3->setObjectName(QString::fromUtf8("CBus3"));
        CBus3->setGeometry(QRect(80, 30, 31, 17));
        SPIGr = new QGroupBox(centralwidget);
        SPIGr->setObjectName(QString::fromUtf8("SPIGr"));
        SPIGr->setGeometry(QRect(140, 90, 321, 51));
        SPIText = new QTextEdit(SPIGr);
        SPIText->setObjectName(QString::fromUtf8("SPIText"));
        SPIText->setGeometry(QRect(30, 10, 171, 21));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SPIText->sizePolicy().hasHeightForWidth());
        SPIText->setSizePolicy(sizePolicy);
        SPIText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Send = new QPushButton(SPIGr);
        Send->setObjectName(QString::fromUtf8("Send"));
        Send->setGeometry(QRect(210, 10, 75, 23));
        label = new QLabel(SPIGr);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 111, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 20));
        menubar->setMinimumSize(QSize(10, 10));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOptions->menuAction());
        menuOptions->addAction(actionInfo);
        menuOptions->addAction(action_Beenden);

        retranslateUi(MainWindow);
        QObject::connect(action_Beenden, SIGNAL(triggered()), MainWindow, SLOT(close()));

        comboBox_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TestTool", 0, QApplication::UnicodeUTF8));
        actionInfo->setText(QApplication::translate("MainWindow", "Info", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        action_Beenden->setText(QApplication::translate("MainWindow", "&Beenden", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
        );
        checkBox->setText(QApplication::translate("MainWindow", "RFC CMDS", 0, QApplication::UnicodeUTF8));
        SPIMode->setText(QApplication::translate("MainWindow", "SPI-Mode", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Actions", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Header", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "Vars", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainWindow", "Data", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "115200", 0, QApplication::UnicodeUTF8)
        );
        pushButton_5->setText(QApplication::translate("MainWindow", "Data@Speed", 0, QApplication::UnicodeUTF8));
        RTSSet->setText(QApplication::translate("MainWindow", "RTS", 0, QApplication::UnicodeUTF8));
        Cbus->setTitle(QApplication::translate("MainWindow", "CBus", 0, QApplication::UnicodeUTF8));
        CBus0->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        CBus1->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        CBus2->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        CBus3->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        SPIGr->setTitle(QApplication::translate("MainWindow", "SPI", 0, QApplication::UnicodeUTF8));
        Send->setText(QApplication::translate("MainWindow", "Send", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "(Hex / max. 8 Zeichen", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
