#ifndef ADXL355DATA_H
#define ADXL355DATA_H

#include <QObject>

class adxl355data
{

public:
    bool dataValid;
    qint8 errorCode;
    qint8 mode;
    qint8 state;
    quint16 sampleId;
    quint16 eventId;
    quint16 blockId;
    double time;
    double x;
    double y;
    double z;
    double absValue;
    double temperature;
    quint32 xraw;
    quint32 yraw;
    quint32 zraw;
    quint16 temperatureRaw;

};

#endif // ADXL355DATA_H
