
#include "mainwindow.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"
#include "datafile.h"
#include "analysisdataframe.h"
#include "rawdatatab.h"
#include "savedialog.h"

#include <QSettings>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFile>
#include <QProgressDialog>
#include <QtMath>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create settings_ member - the application will use a INI File instead of registry entries
    settings_ = new QSettings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());

    loadSettings();

    ui->actionOpen->setEnabled(true);
    ui->actionFirstEvent->setEnabled(false);
    ui->actionLastEvent->setEnabled(false);
    ui->actionNextEvent->setEnabled(false);
    ui->actionPreviousEvent->setEnabled(false);
    ui->actionAddAbsolutValue->setEnabled(false);
    ui->actionAddXDirection->setEnabled(false);
    ui->actionAddYDirection->setEnabled(false);
    ui->actionAddZDirection->setEnabled(false);
    ui->actionExportPicture->setEnabled(false);
    ui->actionExportData->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    if (ui->dockWidget->isHidden() == true) {
        ui->actionShowDataDock->setEnabled(true);
    } else {
        ui->actionShowDataDock->setEnabled(false);
    }

    rawDataTab_ = new RawDataTab();
    ui->tabWidget->addTab(rawDataTab_, tr("Raw Data"));
    QIcon icon(":/Images/Acceleration_256.png");
    ui->tabWidget->setTabIcon(0, icon);
    QSize size(48,48);
    ui->tabWidget->setIconSize(size);

    processedDataTab_ = new ProcessedDataTab();
    ui->tabWidget->addTab(processedDataTab_, tr("Processed Data"));
    QIcon icon2(":/Images/Vel_Loc_256.png");
    ui->tabWidget->setTabIcon(1, icon2);
    QSize size2(48,48);
    ui->tabWidget->setIconSize(size2);
    ui->tabWidget->setTabEnabled(1, false);



    connect(ui->actionOpen,  &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionFirstEvent, &QAction::triggered, this, &MainWindow::showFirstEvent);
    connect(ui->actionLastEvent, &QAction::triggered, this, &MainWindow::showLastEvent);
    connect(ui->actionNextEvent, &QAction::triggered, this, &MainWindow::showNextEvent);
    connect(ui->actionPreviousEvent, &QAction::triggered, this, &MainWindow::showPreviousEvent);

    connect(ui->actionAddAbsolutValue, &QAction::toggled, this, &MainWindow::ToggleAbsAxis);
    connect(ui->actionAddXDirection, &QAction::toggled, this, &MainWindow::ToggleXAxis);
    connect(ui->actionAddYDirection, &QAction::toggled, this, &MainWindow::ToggleYAxis);
    connect(ui->actionAddZDirection, &QAction::toggled, this, &MainWindow::ToggleZAxis);
    connect(ui->actionShowDataDock, &QAction::triggered, this, &MainWindow::showDockWidget);

    connect(ui->actionExportPicture, &QAction::triggered, this, &MainWindow::savePlotToFile);
    connect(ui->actionExportData, &QAction::triggered, this, &MainWindow::saveDataToFile);


    connect(ui->deleteButton, &QToolButton::clicked, this, &MainWindow::deleteAnalyzedDataFrame);


    connect(ui->dockWidget, SIGNAL(visibilityChanged(bool)), SLOT(dockWidgetClosed(bool)));
    connect(ui->analyzedFramesList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this,  SLOT(analyzedFramesListDoubleClick(QListWidgetItem*)));


    //todo: replace once Jonathan is finished
    analyser_ = new Analyser();
    connect(this, &MainWindow::analyzeRequest, analyser_, &Analyser::startAnalysis);
    connect(analyser_, &Analyser::analysisFinishied, this, &MainWindow::analyzeFinished);

    connect(this, SIGNAL(visibilityRawDataChanged(int, bool)),rawDataTab_, SLOT(setVisibility(int, bool)));
    connect(this, SIGNAL(visibilityProcessedDataChanged(int, bool)),processedDataTab_, SLOT(setVisibility(int, bool)));

    connect(this, SIGNAL(eventIdChanged(int)),rawDataTab_, SLOT(eventIdChanged(int)));
    connect(this, SIGNAL(dataFrameChanged(AnalysisDataFrame)), processedDataTab_, SLOT(dataFrameChanged(AnalysisDataFrame)));

    connect(rawDataTab_, SIGNAL(currentEventIdChanged(int)), this, SLOT(currentEventIdChanged(int)));
    connect(rawDataTab_, SIGNAL(eventPlotDataPointSelected(int, double, int)), this, SLOT(eventPlotDataPointSelected(int, double, int)));


    fillHeaderDataAnalysis();
}

MainWindow::~MainWindow()
{
    delete ui;
}

///***********************************************************************************************
///*** PUBLIC METHODS
///***********************************************************************************************

///***********************************************************************************************
///*** PROTECTED METHODS
///***********************************************************************************************

/// @brief Override the closeEvent. Will open a message box and in case of closing, save the settings
void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("Leave the application..."),
                                                               tr("All unsaved date will be lost.\nAre you sure?\n"),
                                                               QMessageBox::No | QMessageBox::Yes,
                                                               QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        saveSettings();
        event->accept();
    }
}


///***********************************************************************************************
///*** PUBLIC SLOTS
///***********************************************************************************************


///***********************************************************************************************
///*** PRIVATE METHODS
///***********************************************************************************************

/// @brief Load the settings from the settings file
void MainWindow::loadSettings() {
    lastOpenFileDirectory_ = settings_->value("LastOpenDir", QDir::homePath()).toString();
    restoreGeometry(settings_->value("Geometry").toByteArray());
    restoreState(settings_->value("WindowState").toByteArray());
    isXShown_ = settings_->value("ActiveGraphs/X").toBool();
    isYShown_ = settings_->value("ActiveGraphs/Y").toBool();
    isZShown_ = settings_->value("ActiveGraphs/Z").toBool();
    isAbsShown_ = settings_->value("ActiveGraphs/Abs").toBool();
}

/// @brief Safe the settings to the settings file
void MainWindow::saveSettings() {
    settings_->setValue("LastOpenDir", lastOpenFileDirectory_);
    settings_->setValue("Geometry", saveGeometry());
    settings_->setValue("WindowState", saveState());

    settings_->setValue("ActiveGraphs/X", isXShown_);
    settings_->setValue("ActiveGraphs/Y", isYShown_);
    settings_->setValue("ActiveGraphs/Z", isZShown_);
    settings_->setValue("ActiveGraphs/Abs", isAbsShown_);
    settings_->sync();
}

/// @brief Fill the header rows and columns of the analysis table widget
void MainWindow::fillHeaderDataAnalysis() {
    QStringList h({"x","y","z","|abs|"});
    QStringList v({"Start (s)", "Stop (s)", "Max. Acc. (m/s²)",
                                            "Ave. Acc. (m/s²)",
                                            "Min. Acc. (m/s²)",
                                            "Max. Vel. (m/s)",
                                            "Ave. Vel. (m/s)",
                                            "Min. Vel. (m/s)",
                                            "Max. Dis. (m)",
                                            "Ave. Dis. (m)",
                                            "Min. Dis. (m)"});

    ui->analysisResultTable->setColumnCount(h.size());
    ui->analysisResultTable->setRowCount(v.size());
    ui->analysisResultTable->setAlternatingRowColors(true);

    QFont font = ui->analysisResultTable->horizontalHeader()->font();
    font.setBold(true);
    ui->analysisResultTable->horizontalHeader()->setFont(font);
    ui->analysisResultTable->verticalHeader()->setFont(font);
    ui->analysisResultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->analysisResultTable->setHorizontalHeaderLabels(h);
    ui->analysisResultTable->setVerticalHeaderLabels(v);

    ui->analysisResultTable->resizeColumnsToContents();

}

/// @brief Clears all data cells in the analysisResultTable
void MainWindow::clearDataCells() {
    ui->analysisResultTable->clearContents();
}

/// @brief Show the result of data analysis in the table widget
void MainWindow::updateDataTable() {

    int idx = -1;
    for (int i = 0; i < analysisDataFrames_.size(); i++) {
        if (analysisDataFrames_[i].eventId == currentEventId_) {
            idx = i;
            break;
        }
    }
    if (idx >= 0) {
        //data is in the list - show data
        if (analysisDataFrames_[idx].startTimeIdx >=0) {
            double starttime = analysisDataFrames_[idx].time[analysisDataFrames_[idx].startTimeIdx];
            rawDataTab_->setStartMarker(starttime);
            ui->analysisResultTable->setItem(0,3, new QTableWidgetItem(QString::number(starttime)));
        }
        if (analysisDataFrames_[idx].stopTimeIdx >=0) {
            double stoptime = analysisDataFrames_[idx].time[analysisDataFrames_[idx].stopTimeIdx];
            rawDataTab_->setStopMarker(stoptime);
            ui->analysisResultTable->setItem(1,3, new QTableWidgetItem(QString::number(stoptime)));
        }
        ui->analysisResultTable->setItem(2,0, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxXAcceleration)));
        ui->analysisResultTable->setItem(2,1, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxYAcceleration)));
        ui->analysisResultTable->setItem(2,2, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxZAcceleration)));
        ui->analysisResultTable->setItem(2,3, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxAbsAcceleration)));

        ui->analysisResultTable->setItem(3,0, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageXAcceleration)));
        ui->analysisResultTable->setItem(3,1, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageYAcceleration)));
        ui->analysisResultTable->setItem(3,2, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageZAcceleration)));
        ui->analysisResultTable->setItem(3,3, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageAbsAcceleration)));

        ui->analysisResultTable->setItem(4,0, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minXAcceleration)));
        ui->analysisResultTable->setItem(4,1, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minYAcceleration)));
        ui->analysisResultTable->setItem(4,2, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minZAcceleration)));
        ui->analysisResultTable->setItem(4,3, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minAbsAcceleration)));

        ui->analysisResultTable->setItem(5,0, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxXVelocity)));
        ui->analysisResultTable->setItem(5,1, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxYVelocity)));
        ui->analysisResultTable->setItem(5,2, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxZVelocity)));
        ui->analysisResultTable->setItem(5,3, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxAbsVelocity)));

        ui->analysisResultTable->setItem(6,0, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageXVelocity)));
        ui->analysisResultTable->setItem(6,1, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageYVelocity)));
        ui->analysisResultTable->setItem(6,2, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageZVelocity)));
        ui->analysisResultTable->setItem(6,3, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageAbsVelocity)));

        ui->analysisResultTable->setItem(7,0, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minXVelocity)));
        ui->analysisResultTable->setItem(7,1, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minYVelocity)));
        ui->analysisResultTable->setItem(7,2, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minZVelocity)));
        ui->analysisResultTable->setItem(7,3, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minAbsVelocity)));

        ui->analysisResultTable->setItem(8,0, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxXDisplacement)));
        ui->analysisResultTable->setItem(8,1, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxYDisplacement)));
        ui->analysisResultTable->setItem(8,2, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxZDisplacement)));
        ui->analysisResultTable->setItem(8,3, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].maxAbsDisplacement)));

        ui->analysisResultTable->setItem(9,0, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageXDisplacement)));
        ui->analysisResultTable->setItem(9,1, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageYDisplacement)));
        ui->analysisResultTable->setItem(9,2, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageZDisplacement)));
        ui->analysisResultTable->setItem(9,3, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].averageAbsDisplacement)));

        ui->analysisResultTable->setItem(10,0, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minXDisplacement)));
        ui->analysisResultTable->setItem(10,1, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minYDisplacement)));
        ui->analysisResultTable->setItem(10,2, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minZDisplacement)));
        ui->analysisResultTable->setItem(10,3, new QTableWidgetItem(QString::number(analysisDataFrames_[idx].minAbsDisplacement)));
    } else {
        clearDataCells();   //clear the list, since there is no data available
    }
    ui->analysisResultTable->resizeColumnsToContents();

}

/// @brief Check if current event ID is already analyzed, if yes show data
/// @param eventId - event ID
/// @return true if exists, false if not in the list
bool MainWindow::isInAnalyzedList(int eventId) {
    bool retval = false;
    for (int i = 0; i < analysisDataFrames_.size(); i++) {
        if (eventId == analysisDataFrames_[i].eventId)
        {
            retval = true;
            emit dataFrameChanged(analysisDataFrames_[i]);
            break;
        }
    }    
    return retval;
}

///***********************************************************************************************
///*** USER INTERACTIONS
///***********************************************************************************************

/// @brief Show an open file dialog, open and parse the file,
/// rebase the time vector and provide a data set used for plotting.
void MainWindow::openFile() {
    QString selfilter = tr("CSV-Files (*.csv)");
    openFileName_ = QFileDialog::getOpenFileName(this, tr("Open Accelera File"),lastOpenFileDirectory_,tr("CSV-Files (*.csv)"), &selfilter);
    if (openFileName_.isNull() == false ) {
        lastOpenFileDirectory_ = QFileInfo(openFileName_).path();
        QString timeFileName = lastOpenFileDirectory_+ "/"+QFileInfo(openFileName_).baseName() + ".time";
        QFile timeFile(timeFileName);
        QFile dataFile(openFileName_);
        if (timeFile.exists() == false) {
            QMessageBox::warning( this, tr("Error..."), tr("Corresponding time file \n") + timeFileName + tr(" is missing.\nOpen process is cancled.")+ timeFileName,
                                                                       QMessageBox::Ok,
                                                                       QMessageBox::Ok);
        } else {
            dataFile_ = new DataFile(this, openFileName_, timeFileName);

            QProgressDialog *parseFileProgress_ = new QProgressDialog();
            connect(dataFile_, &DataFile::progressReadingFiles, parseFileProgress_, &QProgressDialog::setValue);
            parseFileProgress_->setLabelText(tr("Opening and parsing data files ..."));
            parseFileProgress_->setCancelButtonText(tr("Cancel"));
            parseFileProgress_->setMinimum(0);
            parseFileProgress_->setMaximum(100);
            parseFileProgress_->setMinimumDuration(0);
            parseFileProgress_->setAttribute(Qt::WA_DeleteOnClose, true);
            parseFileProgress_->setWindowModality(Qt::WindowModal);
            parseFileProgress_->setAutoClose(false);
            dataFile_->readDataFromFile();

            parseFileProgress_->close();


            QProgressDialog *pd = new QProgressDialog();
            connect(dataFile_, &DataFile::progressRebasingTimeVector, pd, &QProgressDialog::setValue);
            pd->setLabelText(tr("Rebasing Time Vector and preparing plot ..."));
            pd->setCancelButtonText(tr("Cancel"));
            pd->setMinimum(0);
            pd->setMaximum(100);
            pd->setMinimumDuration(0);
            pd->setAttribute(Qt::WA_DeleteOnClose, true);
            pd->setWindowModality(Qt::WindowModal);
            pd->setAutoClose(false);
            dataFile_->rebaseData();
            pd->close();
            startTimes_ = dataFile_->getEventStartTimes();
            stopTimes_ = dataFile_->getEventStopTimes();
            eventIds_ = dataFile_->getEventIds();
            currentEventId_ = 0;

            //enable the toolbar actions
            ui->actionOpen->setEnabled(true);
            ui->actionFirstEvent->setEnabled(true);
            ui->actionLastEvent->setEnabled(true);
            ui->actionNextEvent->setEnabled(true);
            ui->actionPreviousEvent->setEnabled(true);
            ui->actionAddAbsolutValue->setEnabled(true);
            ui->actionAddXDirection->setEnabled(true);
            ui->actionAddYDirection->setEnabled(true);
            ui->actionAddZDirection->setEnabled(true);

            ui->actionAddXDirection->setChecked(isXShown_);
            ui->actionAddYDirection->setChecked(isYShown_);
            ui->actionAddZDirection->setChecked(isZShown_);
            ui->actionAddAbsolutValue->setChecked(isAbsShown_);

            ui->actionExportPicture->setEnabled(true);
            ui->actionExportData->setEnabled(true);

            rawDataTab_->setData(dataFile_);
            emit eventIdChanged(currentEventId_);
            updateDataTable();
        }
    }

}

/// @brief Set the current event id to the first event id and update the plot
void MainWindow::showFirstEvent() {
    currentEventId_ = eventIds_.first();
    updateDataTable();
    emit eventIdChanged(currentEventId_);
    ui->tabWidget->setTabEnabled(1, isInAnalyzedList(currentEventId_));
}

/// @brief Set the current event id to the last event id and update the plot
void MainWindow::showLastEvent() {
    currentEventId_ = eventIds_.last();
    updateDataTable();
    emit eventIdChanged(currentEventId_);
    ui->tabWidget->setTabEnabled(1, isInAnalyzedList(currentEventId_));
}

/// @brief Increment current event id to the first event id and update the plot
/// @note if the current event id is the last event id, do nothing.
void MainWindow::showNextEvent() {
    if (currentEventId_ != eventIds_.last()) {
       currentEventId_++;
       updateDataTable();
       emit eventIdChanged(currentEventId_);
       ui->tabWidget->setTabEnabled(1, isInAnalyzedList(currentEventId_));
    }
}

/// @brief Decrement current event id to the first event id and update the plot
/// @note if the current event id is the first event id, do nothing.
void MainWindow::showPreviousEvent() {
    if (currentEventId_ != eventIds_.first()) {
        currentEventId_--;
        updateDataTable();
        emit eventIdChanged(currentEventId_);
        ui->tabWidget->setTabEnabled(1, isInAnalyzedList(currentEventId_));
    }
}

/// @brief Update the variables and update the plot
void MainWindow::ToggleXAxis() {
    isXShown_ = ui->actionAddXDirection->isChecked();
    emit visibilityRawDataChanged(0, isXShown_);
    if (processedDataTab_->isDataShown(currentEventId_) == true) {
        emit visibilityProcessedDataChanged(0, isXShown_);
    }
    updateDataTable();
}

/// @brief Update the variables and update the plot
void MainWindow::ToggleYAxis() {
    isYShown_ = ui->actionAddYDirection->isChecked();
    emit visibilityRawDataChanged(1, isYShown_);
    if (processedDataTab_->isDataShown(currentEventId_) == true) {
        emit visibilityProcessedDataChanged(1, isYShown_);
    }
    updateDataTable();
}

/// @brief Update the variables and update the plot
void MainWindow::ToggleZAxis() {
    isZShown_ =ui->actionAddZDirection->isChecked();
    emit visibilityRawDataChanged(2, isZShown_);
    if (processedDataTab_->isDataShown(currentEventId_) == true) {
        emit visibilityProcessedDataChanged(2, isZShown_);
    }
    updateDataTable();
}

/// @brief Update the variables and update the plot
void MainWindow::ToggleAbsAxis() {
    isAbsShown_ = ui->actionAddAbsolutValue->isChecked();
    emit visibilityRawDataChanged(3, isAbsShown_);
    if (processedDataTab_->isDataShown(currentEventId_) == true) {
        emit visibilityProcessedDataChanged(3, isAbsShown_);
    }
    updateDataTable();
}

/// @brief Make the dock widget visible again
void MainWindow::showDockWidget() {
    if (ui->dockWidget->isHidden() == true) {
        ui->dockWidget->setVisible(true);
        ui->actionShowDataDock->setEnabled(false);
    }
}

/// @brief Deletes a already analyzed data frame from the frame list
void MainWindow::deleteAnalyzedDataFrame() {
    int row = ui->analyzedFramesList->currentRow();
    if (row >= 0) {        
        analysisDataFrames_.removeAt(row);        
        delete ui->analyzedFramesList->takeItem(row);
        updateDataTable();
        emit eventIdChanged(currentEventId_);       
    }
    ui->deleteButton->setEnabled(false);
    ui->tabWidget->setTabEnabled(1, false);
}

/// @brief Saves a plot to a png file
/// Method will open a save file dialog first and second opens a dialog where the user can
/// choose which plot should be saved. The filenames will get some suffixes to distinguish the
/// different plots
void MainWindow::savePlotToFile() {
    QString selfilter = tr("PNG-Files (*.png)");
    QString filename;

    filename = QFileDialog::getSaveFileName(this, tr("Export Detailed Plot View"),lastOpenFileDirectory_,tr("PNG-Files (*.png)"), &selfilter);

    if (filename.isNull() == false) {
        lastOpenFileDirectory_ = QFileInfo(filename).path();

        QString eventId = "EventId_"+QString::number(currentEventId_);
        QString overviewFileName = lastOpenFileDirectory_+ "/"+QFileInfo(filename).baseName() + "_overview." + QFileInfo(filename).suffix();
        QString accelerationFileName = lastOpenFileDirectory_+ "/"+QFileInfo(filename).baseName() +"_" + eventId + "_acceleration." + QFileInfo(filename).suffix();
        QString velocityFileName = lastOpenFileDirectory_+ "/"+QFileInfo(filename).baseName() + "_" + eventId + "_velocity." + QFileInfo(filename).suffix();
        QString displacementFileName = lastOpenFileDirectory_+ "/"+QFileInfo(filename).baseName() +"_" + eventId + "_displacement." + QFileInfo(filename).suffix();


        QStringList options;
        options.append("Overview Plot (_overview)");
        options.append("Acceleration Plot (_acceleration) of Event Id " + QString::number(currentEventId_));
        options.append("Velocity Plot (_velocity) of Event Id " + QString::number(currentEventId_));
        options.append("Displacement Plot (_displacement) of Event Id " + QString::number(currentEventId_));
        QList<bool> enableList;
        enableList.append(true);
        enableList.append(true);
        enableList.append(processedDataTab_->isDataShown(currentEventId_));
        enableList.append(processedDataTab_->isDataShown(currentEventId_));
        SaveDialog *dialog = new SaveDialog(this, enableList, options);
        if (dialog->exec() == QDialog::Accepted) {
            QList<bool> saveList;
            saveList = dialog->userChoice;
            if (saveList[0] == true) {
                rawDataTab_->saveOverviewPlot(overviewFileName);
            }
            if (saveList[1] == true) {
                rawDataTab_->saveEventPlot(accelerationFileName);
            }
            if (saveList[2] == true) {
                processedDataTab_->saveVelocityPlot(velocityFileName);
            }
            if (saveList[3] == true) {
                processedDataTab_->saveDisplacementPlot(displacementFileName);
            }
        }
    }
}

/// @brief Saves data to a file
/// Method will open a save file dialog first and second opens a dialog where the user can
/// choose which data should be saved. The filenames will get some suffixes to distinguish the
/// different plots
void MainWindow::saveDataToFile() {
    QString selfilter = tr("CSV-Files (*.csv)");
    QString filename;

    filename = QFileDialog::getSaveFileName(this, tr("Export Detailed Plot View"),lastOpenFileDirectory_,tr("CSV-Files (*.csv)"), &selfilter);

    if (filename.isNull() == false) {
        lastOpenFileDirectory_ = QFileInfo(filename).path();

        QString eventId = "EventId_"+QString::number(currentEventId_);
        QString overviewFileName = lastOpenFileDirectory_+ "/"+QFileInfo(filename).baseName() + "_overview." + QFileInfo(filename).suffix();
        QString analyzedFileName = lastOpenFileDirectory_+ "/"+QFileInfo(filename).baseName() + "_analyzed." + QFileInfo(filename).suffix();
        QString eventDataFileName = lastOpenFileDirectory_+ "/"+QFileInfo(filename).baseName() + "_"+ eventId + "_eventdata." + QFileInfo(filename).suffix();

        QStringList options;
        options.append("Overview Raw Data (_overview)");
        options.append("Analyzed Data (_analyzed)");
        options.append("Event Data (_eventdata) of Event Id " + QString::number(currentEventId_));
        QList<bool> enableList;
        enableList.append(true);
        if (analysisDataFrames_.size()>0) {
            enableList.append(true);
        } else {
            enableList.append(false);
        }
        enableList.append(processedDataTab_->isDataShown(currentEventId_));
        SaveDialog *dialog = new SaveDialog(this, enableList, options);
        if (dialog->exec() == QDialog::Accepted) {
            QList<bool> saveList;
            saveList = dialog->userChoice;
            if (saveList[0] == true) {
                QProgressDialog *saveProgressDialog = new QProgressDialog();
                connect(dataFile_, &DataFile::progressSavingData, saveProgressDialog, &QProgressDialog::setValue);
                saveProgressDialog->setLabelText(tr("Saving rebased general data file ..."));
                saveProgressDialog->setCancelButtonText(tr("Cancel"));
                saveProgressDialog->setMinimum(0);
                saveProgressDialog->setMaximum(100);
                saveProgressDialog->setMinimumDuration(0);
                saveProgressDialog->setAttribute(Qt::WA_DeleteOnClose, true);
                saveProgressDialog->setWindowModality(Qt::WindowModal);
                saveProgressDialog->setAutoClose(false);
                dataFile_->saveRebasedVectors(overviewFileName);
                saveProgressDialog->close();
            }
            if (saveList[1] == true) {
                qDebug() << "Save Analyzed Data";
                analyser_->saveAnalysedData(analysisDataFrames_, filename);
            }
            if (saveList[2] == true) {
                qDebug() << "Save Event Data" << currentEventId_ << &analysisDataFrames_;
                int idx = -1;
                for (int i = 0; i<analysisDataFrames_.size();i++)
                {
                    if (analysisDataFrames_[i].eventId == currentEventId_)
                    {
                        idx = i;
                        break;
                    }
                }
                if (idx >= 0)
                {
                    analyser_->saveEventData(analysisDataFrames_[idx], filename);
                }
            }
        }
    }

}

///***********************************************************************************************
///*** PUBLIC SLOTS
///***********************************************************************************************

/// @brief Will be called once the data analysis is finished.
/// The method will add the datafram to the list of analyzed data frames, than update the
/// current event id and update the plot view as well.
/// @param dataFrame - data frame with the results of the data analysis
void MainWindow::analyzeFinished(AnalysisDataFrame dataFrame) {
    int findEvent = -1;
    for (int i = 0; i < analysisDataFrames_.size(); i++) {
        if (currentEventId_ == analysisDataFrames_[i].eventId)
        {
            findEvent = i;
            break;
        }
    }
    if (findEvent >= 0) {
        analysisDataFrames_[findEvent] = dataFrame;
        new QListWidgetItem(tr("Event ")+QString::number(dataFrame.eventId), ui->analyzedFramesList);
        currentEventId_ = dataFrame.eventId;
        updateDataTable();
        emit eventIdChanged(currentEventId_);
        emit dataFrameChanged(dataFrame);

    }
}


///***********************************************************************************************
///*** PRIVATE SLOTS
///***********************************************************************************************

/// @brief Called, if the user closes the dock widgets.
/// @note Will enable the corresponding toolbar action to make it visible again.
void MainWindow::dockWidgetClosed(bool) {
    if (ui->dockWidget->isHidden() == true) {
        ui->actionShowDataDock->setEnabled(true);
    } else {
        ui->actionShowDataDock->setEnabled(false);
    }
}

/// @brief Called, if a s uses make a double click on one list item in the list box
/// The method will set the event of the clicked item as the current event id and
/// than the method will update the plot.
void MainWindow::analyzedFramesListDoubleClick(QListWidgetItem *) {
    int idx = ui->analyzedFramesList->currentRow();
    if (idx >= 0) {
        currentEventId_ = analysisDataFrames_[idx].eventId;
        updateDataTable();
        emit eventIdChanged(currentEventId_);
        emit dataFrameChanged(analysisDataFrames_[idx]);
        ui->tabWidget->setTabEnabled(1, true);
        ui->deleteButton->setEnabled(true);
    } else {
        ui->deleteButton->setEnabled(false);
    }

}

/// @brief Called, when the user has selected one or two data points in the event plot
/// @param eventId - event id where the data points where selected
/// @param time - time in s at of the selected data point
/// @param dataIndex - index of the selected data point
void MainWindow::eventPlotDataPointSelected(int eventId, double time, int dataIndex) {
    AnalysisDataFrame frame;
    frame.startTimeIdx = -1;
    frame.stopTimeIdx = -1;

    currentEventId_ = eventId;

    int findEvent = -1;
    for (int i = 0; i < analysisDataFrames_.size(); i++) {
        if (currentEventId_ == analysisDataFrames_[i].eventId)
        {
            findEvent = i;
            break;
        }
    }

    if (findEvent < 0) {
        //data does not exist already - always begin with a starting mark
        frame = dataFile_->getAnalysisDataFrame(dataIndex);
        frame.startTimeIdx = frame.time.indexOf(time); //project the index to the coordinate system of the data frame sub vectors
        rawDataTab_->setStartMarker(time);
        analysisDataFrames_.append(frame);
    } else {
        //there is already a data frame
        //if there is no starting mark, than create a green one, if there is already a green one, than create a red one, if
        //both exists, than do nothing.
        if (analysisDataFrames_[findEvent].startTimeIdx == -1) {
            //create a green one
            analysisDataFrames_[findEvent].startTimeIdx = analysisDataFrames_[findEvent].time.indexOf(time); //project the index to the coordinate system of the data frame sub vectors
            rawDataTab_->setStartMarker(time);
        } else if (analysisDataFrames_[findEvent].stopTimeIdx == -1) {
            //create a red one
            analysisDataFrames_[findEvent].stopTimeIdx = analysisDataFrames_[findEvent].time.indexOf(time); //project the index to the coordinate system of the data frame sub vectors
            rawDataTab_->setStopMarker(time);
            emit analyzeRequest(analysisDataFrames_[findEvent]);
        }
    }
}

/// @brief Called, when the event id has changed
/// @note This can happen, if the user selects one event in the overview plot
/// @param eventId - new event id
void MainWindow::currentEventIdChanged(int eventId) {
    currentEventId_ = eventId;
    updateDataTable();
}
