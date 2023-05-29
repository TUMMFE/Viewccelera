#ifndef ANALYSISDATAFRAME_H
#define ANALYSISDATAFRAME_H

#include <QObject>

class AnalysisDataFrame
{

public:

    QVector<double> time;
    QVector<double> xAcceleration;
    QVector<double> yAcceleration;
    QVector<double> zAcceleration;
    QVector<double> absAcceleration;
    QVector<double> temperature;
    int startTimeIdx;
    int stopTimeIdx;
    quint16 eventId;
    quint16 blockId;

    QVector<double> xVelocity;
    QVector<double> yVelocity;
    QVector<double> zVelocity;
    QVector<double> absVelocity;

    QVector<double> xDisplacement;
    QVector<double> yDisplacement;
    QVector<double> zDisplacement;
    QVector<double> absDisplacement;

    double maxXAcceleration;
    double maxYAcceleration;
    double maxZAcceleration;
    double maxAbsAcceleration;

    double averageXAcceleration;
    double averageYAcceleration;
    double averageZAcceleration;
    double averageAbsAcceleration;

    double maxXVelocity;
    double maxYVelocity;
    double maxZVelocity;
    double maxAbsVelocity;

    double averageXVelocity;
    double averageYVelocity;
    double averageZVelocity;
    double averageAbsVelocity;

    double maxXDisplacement;
    double maxYDisplacement;
    double maxZDisplacement;
    double maxAbsDisplacement;

    double averageXDisplacement;
    double averageYDisplacement;
    double averageZDisplacement;
    double averageAbsDisplacement;



};

#endif // ANALYSISDATAFRAME_H
