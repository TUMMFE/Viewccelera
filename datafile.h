
#ifndef DATAFILE_H
#define DATAFILE_H


#include <QObject>
#include <QFile>
#include <QProgressDialog>
#include <QtMath>

#include "adxl355data.h"
#include "analysisdataframe.h"

class DataFile : public QObject
{
    Q_OBJECT
public:
    DataFile(QObject *parent, QString dataFile, QString timeFile);
    ~DataFile();

    void readDataFromFile();
    QList<adxl355data> getRawData();
    void rebaseData();
    QList<adxl355data> getRebasedData();
    QList<double> getEventStartTimes();
    QList<double> getEventStopTimes();
    QList<int> getEventIds();
    AnalysisDataFrame getAnalysisDataFrame(int idx);
    void saveRebasedVectors(QString filename);

    QVector<double> time;
    QVector<double> xAcceleration;
    QVector<double> yAcceleration;
    QVector<double> zAcceleration;
    QVector<double> absAcceleration;
    QVector<double> xVelocity;
    QVector<double> yVelocity;
    QVector<double> zVelocity;
    QVector<double> absVelocity;
    QVector<double> xDisplacement;
    QVector<double> yDisplacement;
    QVector<double> zDisplacement;
    QVector<double> absDisplacement;
    QVector<double> temperature;
    QVector<int> startTimeIdx;
    QVector<int> stopTimeIdx;


signals:
    void progressReadingFiles(int progress);    //progress in %
    void progressRebasingTimeVector(int progress);
    void progressSavingData(int progress);


private:
    void parseDataFile();
    void parseTimeFile();
    void rebaseTimeVector(QList<adxl355data> &data, QList<double> &timeList);
    void removeInvalidData(QList<adxl355data> &data);
    void rebaseByEvents(QList<adxl355data> &data);
    void createTimeSampleSizeVectors(QList<adxl355data> &data);
    void createVectors();


    QList<adxl355data> datasetRaw_;
    QList<adxl355data> datasetRebased_;

    QFile *datafile_;
    QFile *timefile_;
    long long maxBytesToRead_;
    long long rebasingSteps_;

    QList<double> timeList_;
    QList<double> eventStartTime_;
    QList<double> eventStopTime_;

    QList<int> eventId_;

    double dataRate_;
    double timeStepSize_;
    quint32 sampleSize_;
    const double GRAVITY =  9.80665;

};

#endif // DATAFILE_H
