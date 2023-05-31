
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "datafile.h"
#include "analysisdataframe.h"
#include "rawdatatab.h"
#include "processeddatatab.h"
#include "analyser.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    QSettings *settings_;    //used for application specific settings
    QString lastOpenFileDirectory_;
    QString openFileName_;
    QList<int> eventIds_;
    int currentEventId_;
    bool isXShown_;
    bool isYShown_;
    bool isZShown_;
    bool isAbsShown_;

    DataFile *dataFile_;
    QList<double> startTimes_;
    QList<double> stopTimes_;

    RawDataTab *rawDataTab_;
    ProcessedDataTab *processedDataTab_;


    QList<int> dataAnalysisStart_;  //index is event id
    QList<int> dataAnalysisStop_;  //index is event id

    QList<AnalysisDataFrame> analysisDataFrames_;
    Analyser *analyser_;

    void loadSettings();
    void saveSettings();


    void fillHeaderDataAnalysis();
    void clearDataCells();
    void updateDataTable();
    bool isInAnalyzedList(int eventId);


    void openFile();
    void showFirstEvent();
    void showLastEvent();
    void showNextEvent();
    void showPreviousEvent();
    void ToggleXAxis();
    void ToggleYAxis();
    void ToggleZAxis();
    void ToggleAbsAxis();
    void showDockWidget();         
    void deleteAnalyzedDataFrame();
    
    void savePlotToFile();
    void saveDataToFile();


signals:
    void analyzeRequest(AnalysisDataFrame dataFrame);
    void eventIdChanged(int eventId);
    void visibilityRawDataChanged(int graphId, bool isVisible);
    void visibilityProcessedDataChanged(int graphId, bool isVisible);
    void dataFrameChanged(AnalysisDataFrame dataFrame);

public slots:
    void analyzeFinished(AnalysisDataFrame dataFrame);

private slots:
    void dockWidgetClosed(bool);
    void analyzedFramesListDoubleClick(QListWidgetItem *);

    void eventPlotDataPointSelected(int eventId, double time, int dataIndex);
    void currentEventIdChanged(int eventId);
};

#endif // MAINWINDOW_H
