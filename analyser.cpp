#include "analyser.h"
#include <QDebug>
#include <QtMath>
#include <QFile>
#include <QIODevice>
#include <QtAlgorithms>

Analyser::Analyser(QObject *parent)
    : QObject{parent}
{


}

void Analyser::startDataProcessing(DataFile *dataFile)
{
//    QProgressDialog *saveProgressDialog = new QProgressDialog();
//    connect(dataFile_, &DataFile::progressSavingData, saveProgressDialog, &QProgressDialog::setValue);

    for (int i =0; i<dataFile->startTimeIdx.length();i++)
    {
        int startIdx = dataFile->startTimeIdx[i];
        int length = dataFile->stopTimeIdx[i] - startIdx;
        dataFile->xVelocity.append(integrateTrapezoidal(dataFile->time.mid(startIdx, length), dataFile->xAcceleration.mid(startIdx, length)));
        dataFile->yVelocity.append(integrateTrapezoidal(dataFile->time.mid(startIdx, length), dataFile->yAcceleration.mid(startIdx, length)));
        dataFile->zVelocity.append(integrateTrapezoidal(dataFile->time.mid(startIdx, length), dataFile->zAcceleration.mid(startIdx, length)));

        dataFile->xDisplacement.append(integrateTrapezoidal(dataFile->time.mid(startIdx, length), dataFile->xVelocity.mid(startIdx, length)));
        dataFile->yDisplacement.append(integrateTrapezoidal(dataFile->time.mid(startIdx, length), dataFile->yVelocity.mid(startIdx, length)));
        dataFile->zDisplacement.append(integrateTrapezoidal(dataFile->time.mid(startIdx, length), dataFile->zVelocity.mid(startIdx, length)));
    }
    dataFile->absVelocity = getAbs(dataFile->xVelocity, dataFile->yVelocity, dataFile->zVelocity);
    dataFile->absDisplacement = getAbs(dataFile->xDisplacement, dataFile->yDisplacement, dataFile->zDisplacement);

    //dataFile->xAcceleration = movingAverage(dataFile->xAcceleration, 51);
}


void Analyser::startAnalysis(AnalysisDataFrame dataFrame)
{
    AnalysisDataFrame dF = dataFrame;
    if (dF.startTimeIdx > dF.stopTimeIdx)
    {
        dF.startTimeIdx = dF.stopTimeIdx;
        dF.stopTimeIdx = dF.startTimeIdx;
    }
    int startIdx = dF.startTimeIdx;
    int idxLength = dF.stopTimeIdx - dF.startTimeIdx;

    QVector<double> timeSelection = dF.time.mid(startIdx, idxLength);

    QVector<double> xAccelerationSelection = dF.xAcceleration.mid(startIdx, idxLength);
    QVector<double> yAccelerationSelection = dF.yAcceleration.mid(startIdx, idxLength);
    QVector<double> zAccelerationSelection = dF.zAcceleration.mid(startIdx, idxLength);
    QVector<double> absAccelerationSelection = dF.absAcceleration.mid(startIdx, idxLength);
    dF.minXAcceleration = *std::min_element(xAccelerationSelection.begin(), xAccelerationSelection.end());
    dF.minYAcceleration = *std::min_element(yAccelerationSelection.begin(), yAccelerationSelection.end());
    dF.minZAcceleration = *std::min_element(zAccelerationSelection.begin(), zAccelerationSelection.end());
    dF.minAbsAcceleration = *std::min_element(absAccelerationSelection.begin(), absAccelerationSelection.end());
    dF.maxXAcceleration = *std::max_element(xAccelerationSelection.begin(), xAccelerationSelection.end());
    dF.maxYAcceleration = *std::max_element(yAccelerationSelection.begin(), yAccelerationSelection.end());
    dF.maxZAcceleration = *std::max_element(zAccelerationSelection.begin(), zAccelerationSelection.end());
    dF.maxAbsAcceleration = *std::max_element(absAccelerationSelection.begin(), absAccelerationSelection.end());
    dF.averageXAcceleration = std::accumulate(xAccelerationSelection.begin(), xAccelerationSelection.end(), .0) / xAccelerationSelection.length();
    dF.averageYAcceleration = std::accumulate(yAccelerationSelection.begin(), yAccelerationSelection.end(), .0) / yAccelerationSelection.length();
    dF.averageZAcceleration = std::accumulate(zAccelerationSelection.begin(), zAccelerationSelection.end(), .0) / zAccelerationSelection.length();
    dF.averageAbsAcceleration = std::accumulate(absAccelerationSelection.begin(), absAccelerationSelection.end(), .0) / absAccelerationSelection.length();

    QVector<double> xVelocitySelection = dF.xVelocity.mid(startIdx, idxLength);
    QVector<double> yVelocitySelection = dF.yVelocity.mid(startIdx, idxLength);
    QVector<double> zVelocitySelection = dF.zVelocity.mid(startIdx, idxLength);
    QVector<double> absVelocitySelection = getAbs(xVelocitySelection, yVelocitySelection, zVelocitySelection);
    dF.minXVelocity = *std::min_element(xVelocitySelection.begin(), xVelocitySelection.end());
    dF.minYVelocity = *std::min_element(yVelocitySelection.begin(), yVelocitySelection.end());
    dF.minZVelocity = *std::min_element(zVelocitySelection.begin(), zVelocitySelection.end());
    dF.minAbsVelocity = *std::min_element(absVelocitySelection.begin(), absVelocitySelection.end());
    dF.maxXVelocity = *std::max_element(xVelocitySelection.begin(), xVelocitySelection.end());
    dF.maxYVelocity = *std::max_element(yVelocitySelection.begin(), yVelocitySelection.end());
    dF.maxZVelocity = *std::max_element(zVelocitySelection.begin(), zVelocitySelection.end());
    dF.maxAbsVelocity = *std::max_element(absVelocitySelection.begin(), absVelocitySelection.end());
    dF.averageXVelocity = std::accumulate(xVelocitySelection.begin(), xVelocitySelection.end(), .0) / xVelocitySelection.length();
    dF.averageYVelocity = std::accumulate(yVelocitySelection.begin(), yVelocitySelection.end(), .0) / yVelocitySelection.length();
    dF.averageZVelocity = std::accumulate(zVelocitySelection.begin(), zVelocitySelection.end(), .0) / zVelocitySelection.length();
    dF.averageAbsVelocity = std::accumulate(absVelocitySelection.begin(), absVelocitySelection.end(), .0) / absVelocitySelection.length();

    QVector<double> xDisplacementSelection = dF.xDisplacement.mid(startIdx, idxLength);
    QVector<double> yDisplacementSelection = dF.yDisplacement.mid(startIdx, idxLength);
    QVector<double> zDisplacementSelection = dF.zDisplacement.mid(startIdx, idxLength);
    QVector<double> absDisplacementSelection = getAbs(xDisplacementSelection, yDisplacementSelection, zDisplacementSelection);
    dF.minXDisplacement = *std::min_element(xDisplacementSelection.begin(), xDisplacementSelection.end());
    dF.minYDisplacement = *std::min_element(yDisplacementSelection.begin(), yDisplacementSelection.end());
    dF.minZDisplacement = *std::min_element(zDisplacementSelection.begin(), zDisplacementSelection.end());
    dF.minAbsDisplacement = *std::min_element(absDisplacementSelection.begin(), absDisplacementSelection.end());
    dF.maxXDisplacement = *std::max_element(xDisplacementSelection.begin(), xDisplacementSelection.end());
    dF.maxYDisplacement = *std::max_element(yDisplacementSelection.begin(), yDisplacementSelection.end());
    dF.maxZDisplacement = *std::max_element(zDisplacementSelection.begin(), zDisplacementSelection.end());
    dF.maxAbsDisplacement = *std::max_element(absDisplacementSelection.begin(), absDisplacementSelection.end());
    dF.averageXDisplacement = std::accumulate(xDisplacementSelection.begin(), xDisplacementSelection.end(), .0) / xDisplacementSelection.length();
    dF.averageYDisplacement = std::accumulate(yDisplacementSelection.begin(), yDisplacementSelection.end(), .0) / yDisplacementSelection.length();
    dF.averageZDisplacement = std::accumulate(zDisplacementSelection.begin(), zDisplacementSelection.end(), .0) / zDisplacementSelection.length();
    dF.averageAbsDisplacement = std::accumulate(absDisplacementSelection.begin(), absDisplacementSelection.end(), .0) / absDisplacementSelection.length();

    emit analysisFinishied(dF);
}

QVector<double> Analyser::integrateTrapezoidal(QVector<double> time, QVector<double> data)
{
    QVector<double> integral;
    for (int i = 0; i<=time.length()-1; i++)
    {
        double currentValue = ( (data[i] + data[i+1]) / 2 ) * (time[i+1]-time[i]);
        if (i == 0)
        {
            integral.append(currentValue);
        }
        else
        {
            integral.append(integral[i-1] + currentValue);
        }
    }
    integral.append(integral.last());
    return integral;
}

QVector<double> Analyser::integrate(QVector<double> time, QVector<double> data)
{
    QVector<double> integral;
    for (int i = 0; i<time.length()-1; i++)
    {
        double currentValue = ( (data[i] + data[i+1]) / 2 ) * (time[i+1]-time[i]);
        integral.append(currentValue);
    }
    integral.append(integral.last());
    return integral;
}

QVector<double> Analyser::getAbs(QVector<double> x, QVector<double> y, QVector<double> z)
{
    QVector<double> absVal;
    for (int i = 0; i<x.length(); i++)
    {
        absVal.append(qSqrt(qPow(x[i],2) + qPow(y[i],2) + qPow(z[i],2)));
    }
    return absVal;
}

void Analyser::saveEventData(AnalysisDataFrame dataFrame, QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "Time,xAcceleration,yAcceleration,zAcceleration,absAcceleration,xVelocity,yVelocity,zVelocity,absVelocity,xDisplacement,yDisplacement,zDisplacement,"
                  "absDisplacement,Temperature"
               << Qt::endl;
        for (int i=0; i < dataFrame.time.size(); i++ ) // v1 and v2 better be same size!
            stream << dataFrame.time[i] << "," << dataFrame.xAcceleration[i] << ","  << dataFrame.yAcceleration[i] << ","  << dataFrame.zAcceleration[i] << "," << dataFrame.absAcceleration[i] << ","
                   << dataFrame.xVelocity[i] << "," << dataFrame.yVelocity[i] << "," << dataFrame.zVelocity[i] << "," << dataFrame.absVelocity[i] << ","
                   << dataFrame.xDisplacement[i] << "," << dataFrame.yDisplacement[i] << "," << dataFrame.zDisplacement[i] << "," << dataFrame.absDisplacement[i]
                   << Qt::endl;
    }
    file.close();
}

void Analyser::saveAnalysedData(QList<AnalysisDataFrame> dataFrames, QString filename)
{
    std::sort(dataFrames.begin(), dataFrames.end(), compare);
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
                QTextStream stream(&file);
        stream << "AnalysedDataFile" << Qt::endl;
        stream << "TimeStamp,EventId,"
                  "minXAcceleration,minYAcceleration,minZAcceleration,minAbsAcceleration,"
                  "maxXAcceleration,maxYAcceleration,maxZAcceleration,maxAbsAcceleration,"
                  "averageXAcceleration,averageYAcceleration,averageZAcceleration,averageAbsAcceleration,"
                  "minXVelocity,minYVelocity,minZVelocity,minAbsVelocity,"
                  "maxXVelocity,maxYVelocity,maxZVelocity,maxAbsVelocity,"
                  "averageXVelocity,averageYVelocity,averageZVelocity,averageAbsVelocity,"
                  "minXDisplacement,minYDisplacement,minZDisplacement,minAbsDisplacement,"
                  "maxXDisplacement,maxYDisplacement,maxZDisplacement,maxAbsDisplacement,"
                  "averageXDisplacement,averageYDisplacement,averageZDisplacement,averageAbsDisplacement"
               << Qt::endl;
        for (int i=0; i < dataFrames.size(); i++ ) // v1 and v2 better be same size!
            stream << dataFrames[i].time[dataFrames[i].startTimeIdx] << "," << dataFrames[i].eventId << ","
                   << dataFrames[i].minXAcceleration << "," << dataFrames[i].minYAcceleration << "," << dataFrames[i].minZAcceleration << "," << dataFrames[i].minAbsAcceleration << ","
                   << dataFrames[i].maxXAcceleration << "," << dataFrames[i].maxYAcceleration << "," << dataFrames[i].maxZAcceleration << "," << dataFrames[i].maxAbsAcceleration << ","
                   << dataFrames[i].averageXAcceleration << "," << dataFrames[i].averageYAcceleration << "," << dataFrames[i].averageZAcceleration << "," << dataFrames[i].averageAbsAcceleration << ","
                   << dataFrames[i].minXVelocity << "," << dataFrames[i].minYVelocity << "," << dataFrames[i].minZVelocity << "," << dataFrames[i].minAbsVelocity << ","
                   << dataFrames[i].maxXVelocity << "," << dataFrames[i].maxYVelocity<< "," << dataFrames[i].maxZVelocity << "," << dataFrames[i].maxAbsVelocity << ","
                   << dataFrames[i].averageXVelocity << "," << dataFrames[i].averageYVelocity << "," << dataFrames[i].averageZVelocity << "," << dataFrames[i].averageAbsVelocity << ","
                   << dataFrames[i].minXDisplacement << "," << dataFrames[i].minYDisplacement << "," << dataFrames[i].minZDisplacement << "," << dataFrames[i].minAbsDisplacement << ","
                   << dataFrames[i].maxXDisplacement << "," << dataFrames[i].maxYDisplacement << "," << dataFrames[i].maxZDisplacement << "," << dataFrames[i].maxAbsDisplacement << ","
                   << dataFrames[i].averageXDisplacement << "," << dataFrames[i].averageYDisplacement << "," << dataFrames[i].averageZDisplacement << "," << dataFrames[i].averageAbsDisplacement << ","
                   << Qt::endl;
    }
    file.close();
}

bool Analyser::compare(const AnalysisDataFrame& i, const AnalysisDataFrame& j)
{
    return i.eventId < j.eventId;
}

QVector<double> Analyser::movingAverage(QVector<double> data, int order)
{
    QVector<double> averagedData;
    for (int i; i<=data.length(); i++)
    {
        if (i < order)
        {
            averagedData.append(std::accumulate(data.begin()+i, data.end()+i+order, 0.) /data.mid(i,i+order).length());
        }
        else if ((i+order)>data.length())
        {
            averagedData.append(std::accumulate(data.begin()+i-order, data.end()+i, 0.) /data.mid(i-order,i).length());
        }
        else
        {
            averagedData.append(std::accumulate(data.begin()+i-order, data.end()+i+order, 0.) /data.mid(i-order,i+order).length());  // TODO: order/2??
        }
    }
    return averagedData;
}
