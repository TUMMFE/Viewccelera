#ifndef ANALYSER_H
#define ANALYSER_H

#include <QObject>

#include "analysisdataframe.h"
#include "datafile.h"

class Analyser : public QObject
{
    Q_OBJECT
public:
    explicit Analyser(QObject *parent = nullptr);

public slots:
    void startDataProcessing(DataFile *dataFile);
    void filterAllData(DataFile *dataFile);
    void startAnalysis(AnalysisDataFrame dataFrame);
    void saveEventData(AnalysisDataFrame dataFrame, QString filename);
    void saveAnalysedData(QList<AnalysisDataFrame> dataFrames, QString filename);

protected:
    QVector<double> integrate(QVector<double> time, QVector<double> data);
    QVector<double> integrateTrapezoidal(QVector<double> time, QVector<double> data);
    QVector<double> getAbs(QVector<double> x, QVector<double> y, QVector<double> z);
    QVector<double> movingAverage(QVector<double> data, int order);
    static bool compare(const AnalysisDataFrame& i, const AnalysisDataFrame& j);


signals:
    void analysisFinishied(AnalysisDataFrame dataFrame);
    void progressFilterData(int progress);
};

#endif // ANALYSER_H

