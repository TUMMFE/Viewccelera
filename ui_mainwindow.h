/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionFirstEvent;
    QAction *actionPreviousEvent;
    QAction *actionNextEvent;
    QAction *actionLastEvent;
    QAction *actionAddXDirection;
    QAction *actionAddYDirection;
    QAction *actionAddZDirection;
    QAction *actionAddAbsolutValue;
    QAction *actionExportPicture;
    QAction *actionShowDataDock;
    QAction *actionAbout;
    QAction *actionExportData;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QStatusBar *statusbar;
    QToolBar *toolBarGeneral;
    QToolBar *toolBarDetailedChart;
    QToolBar *toolBarPlotData;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QTableWidget *analysisResultTable;
    QListWidget *analyzedFramesList;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *deleteButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1555, 514);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/ViewCcelera_256.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Images/Open_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionFirstEvent = new QAction(MainWindow);
        actionFirstEvent->setObjectName("actionFirstEvent");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Images/First_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFirstEvent->setIcon(icon2);
        actionPreviousEvent = new QAction(MainWindow);
        actionPreviousEvent->setObjectName("actionPreviousEvent");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Images/Previous_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreviousEvent->setIcon(icon3);
        actionNextEvent = new QAction(MainWindow);
        actionNextEvent->setObjectName("actionNextEvent");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Images/Next_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNextEvent->setIcon(icon4);
        actionLastEvent = new QAction(MainWindow);
        actionLastEvent->setObjectName("actionLastEvent");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Images/Last_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLastEvent->setIcon(icon5);
        actionAddXDirection = new QAction(MainWindow);
        actionAddXDirection->setObjectName("actionAddXDirection");
        actionAddXDirection->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Images/XAxis_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddXDirection->setIcon(icon6);
        actionAddYDirection = new QAction(MainWindow);
        actionAddYDirection->setObjectName("actionAddYDirection");
        actionAddYDirection->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Images/YAxis_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddYDirection->setIcon(icon7);
        actionAddZDirection = new QAction(MainWindow);
        actionAddZDirection->setObjectName("actionAddZDirection");
        actionAddZDirection->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Images/ZAxis_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddZDirection->setIcon(icon8);
        actionAddAbsolutValue = new QAction(MainWindow);
        actionAddAbsolutValue->setObjectName("actionAddAbsolutValue");
        actionAddAbsolutValue->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Images/Absolute_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddAbsolutValue->setIcon(icon9);
        actionExportPicture = new QAction(MainWindow);
        actionExportPicture->setObjectName("actionExportPicture");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Images/SavePicture_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExportPicture->setIcon(icon10);
        actionShowDataDock = new QAction(MainWindow);
        actionShowDataDock->setObjectName("actionShowDataDock");
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Images/Bar_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowDataDock->setIcon(icon11);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Images/About_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon12);
        actionExportData = new QAction(MainWindow);
        actionExportData->setObjectName("actionExportData");
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Images/SavePart_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExportData->setIcon(icon13);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(0, 0));
        centralwidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBarGeneral = new QToolBar(MainWindow);
        toolBarGeneral->setObjectName("toolBarGeneral");
        toolBarGeneral->setIconSize(QSize(48, 48));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarGeneral);
        toolBarDetailedChart = new QToolBar(MainWindow);
        toolBarDetailedChart->setObjectName("toolBarDetailedChart");
        toolBarDetailedChart->setIconSize(QSize(48, 48));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarDetailedChart);
        toolBarPlotData = new QToolBar(MainWindow);
        toolBarPlotData->setObjectName("toolBarPlotData");
        toolBarPlotData->setIconSize(QSize(48, 48));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarPlotData);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName("dockWidget");
        dockWidget->setMinimumSize(QSize(91, 254));
        dockWidget->setMaximumSize(QSize(524287, 524287));
        dockWidget->setFloating(false);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        dockWidgetContents->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        analysisResultTable = new QTableWidget(dockWidgetContents);
        analysisResultTable->setObjectName("analysisResultTable");

        verticalLayout->addWidget(analysisResultTable);

        analyzedFramesList = new QListWidget(dockWidgetContents);
        analyzedFramesList->setObjectName("analyzedFramesList");

        verticalLayout->addWidget(analyzedFramesList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        deleteButton = new QToolButton(dockWidgetContents);
        deleteButton->setObjectName("deleteButton");
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Images/Delete_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteButton->setIcon(icon14);
        deleteButton->setIconSize(QSize(48, 48));

        horizontalLayout->addWidget(deleteButton);


        verticalLayout->addLayout(horizontalLayout);

        dockWidget->setWidget(dockWidgetContents);
        analyzedFramesList->raise();
        analysisResultTable->raise();
        MainWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
        dockWidget->raise();

        toolBarGeneral->addAction(actionOpen);
        toolBarGeneral->addAction(actionExportData);
        toolBarGeneral->addAction(actionExportPicture);
        toolBarGeneral->addAction(actionShowDataDock);
        toolBarGeneral->addAction(actionAbout);
        toolBarDetailedChart->addAction(actionFirstEvent);
        toolBarDetailedChart->addAction(actionPreviousEvent);
        toolBarDetailedChart->addAction(actionNextEvent);
        toolBarDetailedChart->addAction(actionLastEvent);
        toolBarPlotData->addAction(actionAddXDirection);
        toolBarPlotData->addAction(actionAddYDirection);
        toolBarPlotData->addAction(actionAddZDirection);
        toolBarPlotData->addAction(actionAddAbsolutValue);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Viewccelera - The Accelera Viewer", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("MainWindow", "Open an Accelera file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Alt+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFirstEvent->setText(QCoreApplication::translate("MainWindow", "FirstEvent", nullptr));
#if QT_CONFIG(shortcut)
        actionFirstEvent->setShortcut(QCoreApplication::translate("MainWindow", "Up", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPreviousEvent->setText(QCoreApplication::translate("MainWindow", "PreviousEvent", nullptr));
#if QT_CONFIG(shortcut)
        actionPreviousEvent->setShortcut(QCoreApplication::translate("MainWindow", "Left", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNextEvent->setText(QCoreApplication::translate("MainWindow", "NextEvent", nullptr));
#if QT_CONFIG(shortcut)
        actionNextEvent->setShortcut(QCoreApplication::translate("MainWindow", "Right", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLastEvent->setText(QCoreApplication::translate("MainWindow", "LastEvent", nullptr));
#if QT_CONFIG(shortcut)
        actionLastEvent->setShortcut(QCoreApplication::translate("MainWindow", "Down", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddXDirection->setText(QCoreApplication::translate("MainWindow", "AddXDirection", nullptr));
        actionAddYDirection->setText(QCoreApplication::translate("MainWindow", "AddYDirection", nullptr));
        actionAddZDirection->setText(QCoreApplication::translate("MainWindow", "AddZDirection", nullptr));
        actionAddAbsolutValue->setText(QCoreApplication::translate("MainWindow", "AddAbsolutValue", nullptr));
        actionExportPicture->setText(QCoreApplication::translate("MainWindow", "ExportPicture", nullptr));
        actionShowDataDock->setText(QCoreApplication::translate("MainWindow", "ShowDataDock", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionExportData->setText(QCoreApplication::translate("MainWindow", "ExportStash", nullptr));
        toolBarGeneral->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        toolBarDetailedChart->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar_2", nullptr));
        toolBarPlotData->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        dockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Data Analysis", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
