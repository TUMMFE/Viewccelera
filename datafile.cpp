
#include "datafile.h"

#include <QRandomGenerator>

DataFile::DataFile(QObject *parent, QString dataFile, QString timeFile)
    : QObject{parent}
{
    datafile_ = new QFile(dataFile);
    timefile_ = new QFile(timeFile);
    maxBytesToRead_ = datafile_->size()+timefile_->size();
}

DataFile::~DataFile() {
    delete datafile_;
    delete timefile_;
}

///***********************************************************************************************
///*** PUBLIC METHODS
///***********************************************************************************************

/// @brief Open and parse the data and the time files
void DataFile::readDataFromFile() {
    parseDataFile();
    parseTimeFile();
    emit progressReadingFiles(100);
}

/// @brief Return the uncorrected dataset
/// @return Uncorrected dataset
QList<adxl355data> DataFile::getRawData() {
    return datasetRaw_;
}

/// @brief Rebase the data set
/// During rebasing, the time vector from the raw data set will be changed according to the information
/// of the *.TIME file. Thus, all pauses and DAQ started events will be taken into account and a new
/// time vector is created. This time vector now reflect, the real time of the data. Than, all data where
/// the raw values are 0 will be removed and the public vectors with the data will be created.
/// @note Each step will emit a signal with the percentage of the progress. This can be used with a
/// QProgressDialog
void DataFile::rebaseData() {
    rebasingSteps_ = 0;
    if ((datasetRaw_.size() > 0) && (timeList_.size()>1)) {
        datasetRebased_ = datasetRaw_;
        //time file and data file already parsed
        timeList_.removeAt(0); //the first element is always at time 0 and thus it is not needed
        //calculate the needed rebasingSteps
        //1. loop for including correcting event ID with the time step
        rebasingSteps_ += datasetRebased_.size();
        //2. loop for including pauses in the data file (nested loop)
        rebasingSteps_ += datasetRebased_.size() * timeList_.size();
        //3. loop for removing all invalid data, where the raw data is 0
        rebasingSteps_ += datasetRebased_.size();
        //4. loop for creating the start time list and stop time list
        rebasingSteps_ += datasetRebased_.size(); //this is maximum value in the case nothing was deleted
        //5. loop for creating the vectors
        rebasingSteps_ += datasetRebased_.size(); //this is maximum value in the case nothing was deleted

        rebaseByEvents(datasetRebased_);
        rebaseTimeVector(datasetRebased_, timeList_);
        removeInvalidData(datasetRebased_);
        createTimeSampleSizeVectors(datasetRebased_);
        createVectors();

        emit progressRebasingTimeVector(100);
    }
    emit progressRebasingTimeVector(100);
}

/// @brief Return the uncorrected dataset
/// @return Uncorrected dataset
QList<adxl355data> DataFile::getRebasedData() {
    return datasetRebased_;
}

/// @brief Get a list with all time point at which a event starts
/// @note The index of the returned list may correspond to the event id.
/// (only may, because the case that a complete event was removed due to
/// invalid data cannot be excluded)
/// @return List of all event starts.
QList<double> DataFile::getEventStartTimes() {
    return eventStartTime_;
}

/// @brief Get a list with all time point at which a event stops
/// @note The index of the returned list may correspond to the event id.
/// (only may, because the case that a complete event was removed due to
/// invalid data cannot be excluded)
/// @return List of all event stops.
QList<double> DataFile::getEventStopTimes() {
    return eventStopTime_;
}

/// @brief Get a list with all eventId
/// @note The index of the returned list corresponds to the event id.
/// If there is no removed event the index and the corresponding value
/// matches. If there was a complete invalid and thus, removed, event
/// the event ID is the value of the list.
/// @return List of all event starts.
QList<int> DataFile::getEventIds() {
    return eventId_;
}

/// @brief Get a anaylsis data frame from the existing data
/// Create a data frame for further analysis at a certain index in the whole rebased data set
/// The start and stop indices will be set to -1, because these points must be set by the user
/// during sliding through the plots.
/// The data vectors will be shrinked to the event size
/// @param idx - index of the data point inside the whole dataset
/// @return a data frame
AnalysisDataFrame DataFile::getAnalysisDataFrame(int idx) {
    AnalysisDataFrame frame;
    frame.eventId = datasetRebased_[idx].eventId;
    frame.blockId = datasetRebased_[idx].blockId;
    frame.startTimeIdx = -1;
    frame.stopTimeIdx = -1;

    frame.xAcceleration = {xAcceleration.begin()+startTimeIdx[frame.eventId], xAcceleration.begin()+stopTimeIdx[frame.eventId]};
    frame.yAcceleration = {yAcceleration.begin()+startTimeIdx[frame.eventId], yAcceleration.begin()+stopTimeIdx[frame.eventId]};
    frame.zAcceleration = {zAcceleration.begin()+startTimeIdx[frame.eventId], zAcceleration.begin()+stopTimeIdx[frame.eventId]};
    frame.absAcceleration = {absAcceleration.begin()+startTimeIdx[frame.eventId], absAcceleration.begin()+stopTimeIdx[frame.eventId]};
    frame.temperature = {temperature.begin()+startTimeIdx[frame.eventId], temperature.begin()+stopTimeIdx[frame.eventId]};
    frame.time = {time.begin()+startTimeIdx[frame.eventId], time.begin()+stopTimeIdx[frame.eventId]};


    frame.xVelocity.resize(frame.time.size());
    frame.yVelocity.resize(frame.time.size());
    frame.zVelocity.resize(frame.time.size());
    frame.absVelocity.resize(frame.time.size());

    frame.xDisplacement.resize(frame.time.size());
    frame.yDisplacement.resize(frame.time.size());
    frame.zDisplacement.resize(frame.time.size());
    frame.absDisplacement.resize(frame.time.size());

    for (int i = 0; i < frame.time.size(); i++) {
        frame.xVelocity[i] = QRandomGenerator::global()->bounded(5)-2.5;
        frame.yVelocity[i] = QRandomGenerator::global()->bounded(3)-2.5;
        frame.zVelocity[i] = QRandomGenerator::global()->bounded(7)-2.5;
        frame.absVelocity[i] = QRandomGenerator::global()->bounded(1)-2.5;

        frame.xDisplacement[i] = QRandomGenerator::global()->bounded(4)-2.5;
        frame.yDisplacement[i] = QRandomGenerator::global()->bounded(2)-2.5;
        frame.zDisplacement[i] = QRandomGenerator::global()->bounded(8)-2.5;
        frame.absDisplacement[i] = QRandomGenerator::global()->bounded(3)-2.5;
    }

    frame.maxXAcceleration = 0.0;
    frame.maxYAcceleration = 0.0;
    frame.maxZAcceleration = 0.0;
    frame.maxAbsAcceleration = 0.0;

    frame.averageXAcceleration = 0.0;
    frame.averageYAcceleration = 0.0;
    frame.averageZAcceleration = 0.0;
    frame.averageAbsAcceleration = 0.0;

    frame.maxXVelocity = 0.0;
    frame.maxYVelocity = 0.0;
    frame.maxZVelocity = 0.0;
    frame.maxAbsVelocity = 0.0;

    frame.averageXVelocity = 0.0;
    frame.averageYVelocity = 0.0;
    frame.averageZVelocity = 0.0;
    frame.averageAbsVelocity = 0.0;

    frame.maxXDisplacement = 0.0;
    frame.maxYDisplacement = 0.0;
    frame.maxZDisplacement = 0.0;
    frame.maxAbsDisplacement = 0.0;

    frame.averageXDisplacement = 0.0;
    frame.averageYDisplacement = 0.0;
    frame.averageZDisplacement = 0.0;
    frame.averageAbsDisplacement = 0.0;


    return frame;
}

/// @brief Write rebased vectors to a csv file
/// @param filename - filename including directory
void DataFile::saveRebasedVectors(QString filename) {
    QFile *file = new QFile(filename);
    QTextStream out(file);
    int size = time.size();
    file->open(QFile::WriteOnly | QFile::Text);
    QString line;
    line = "time (s); ax (m/s^2); ay (m/s^2); az (m/s^2); |a| (m/s^2); T (°C)\n";
    out << line;

    for (int i = 0; i< size; i++) {
        line = QString::number(time[i])+";"+QString::number(xAcceleration[i])+";"+QString::number(yAcceleration[i])+";"+QString::number(zAcceleration[i])+";"+QString::number(absAcceleration[i])+";"+QString::number(temperature[i])+"\n";
        out << line;
        auto progress = (i*100)/size;
        emit progressSavingData(progress);
    }
    file->close();
}

///***********************************************************************************************
///*** PRIVATE METHODS
///***********************************************************************************************


/// @brief Open and parse the data file
/// Collect all lines and writes them to a list container.
/// The first row of the data is neglected since it is the header only.
/// The method emits a signal with the current progress in percent.
/// Gravity will be removed as well using the simple linerar algebra approach:
/// a*s = |a| - g,
/// where a is the vector of the acceleration and |a| its absolute value. g is the
/// gravitiy.
void DataFile::parseDataFile() {
    adxl355data data;
    quint32 counter = 0;
    QTextStream in(datafile_);

    sampleSize_ = 0;
    datasetRaw_.clear();
    datafile_->open(QFile::ReadOnly | QFile::Text);
    QString line = in.readLine(); //read first line and throw it away - only header line which is not needed
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList list = line.split(QLatin1Char(','));

        //data processing
        data.dataValid = QVariant(list[0]).toBool();
        data.errorCode = list[1].toInt();
        data.mode = list[2].toInt();
        data.state = list[3].toInt();
        data.sampleId = list[4].toInt();
        data.eventId = list[5].toInt();
        data.blockId = list[6].toInt();
        data.time = list[7].toDouble();
        data.x = list[8].toDouble();
        data.y = list[9].toDouble();
        data.z = list[10].toDouble();
        data.absValue = qSqrt(qPow(data.x,2)+qPow(data.y,2)+qPow(data.z,2));
        data.temperature = list[11].toDouble();
        data.xraw = list[12].toDouble();
        data.yraw = list[13].toDouble();
        data.zraw = list[14].toDouble();
        data.temperatureRaw = list[15].toDouble();

        double s;
        s = (data.absValue - GRAVITY)/data.absValue;
        data.x = s*data.x;
        data.y = s*data.y;
        data.z = s*data.z;
        data.absValue = qSqrt(qPow(data.x,2)+qPow(data.y,2)+qPow(data.z,2));


        counter++;
        if ((data.sampleId == 0) && (counter > 1)) {
            sampleSize_ = counter;
            counter = 0;
        }
        datasetRaw_.append(data);
        auto remains = datafile_->bytesAvailable();
        auto progress = ((maxBytesToRead_-remains)*100)/maxBytesToRead_;
        //qDebug() << "DATA FILE: Remains: " << remains << " MaxBytes: " << maxBytesToRead_ << " Progress: " << progress ;

        emit progressReadingFiles(progress);
    }
    //the time step is the the same througout the dataset.
    //the first data point is always at time 0, thus the the time at
    //the second data point corresponds to the time step.
    timeStepSize_ = datasetRaw_[1].time;
    dataRate_ = 1/timeStepSize_; //sampling frequency is 1/timestep
    datafile_->close();
}

/// @brief Open and parse the *.TIME file
/// Collect all "DAQ Started" time events (relative time only) and writes them to a
/// list container.
/// The first row of the data is neglected since it is the header only.
/// The method emits a signal with the current progress in percent.
void DataFile::parseTimeFile() {
    QTextStream in(timefile_);
    timeList_.clear();
    timefile_->open(QFile::ReadOnly | QFile::Text);
    QString line = in.readLine(); //read first line and throw it away - only header line which is not needed
    while (!in.atEnd()) {
        line = in.readLine();
        //process line and stash only DAQ Started elements in the list
        QStringList list = line.split(QLatin1Char(','));
        if (list[0] == "DAQ Started") {
            timeList_.append(list[2].toDouble());
        }
        //calculate the progress in percent
        auto remains = timefile_->bytesAvailable();
        auto progress = ((maxBytesToRead_-remains)*100)/maxBytesToRead_;
        //qDebug() << "TIME FILE: Remains: " << remains << " MaxBytes: " << maxBytesToRead_ << " Progress: " << progress ;
        emit progressReadingFiles(progress);
    }
    timefile_->close();
}

/// @brief Rebase the time vector by combining the time file with the data file
/// @param &data - pointer to the data set
/// @param &timelist - pointer to the list of times from the *.TIME file
void DataFile::rebaseTimeVector(QList<adxl355data> &data, QList<double> &timeList) {
    const auto datasize = data.size();
    const auto timesize = timeList.size();
    int remains = 0;
    int progress = 0;

    for (quint32 i = 0; i < timesize; i++ ) {
        for (quint32 j = 0; j < datasize; j++) {
            if ((j/sampleSize_) > i) {
                data[j].time = data[j].time+timeList[i]-data[i*sampleSize_].time;
            }
            remains = rebasingSteps_ - j;
            progress = ((rebasingSteps_ - remains)*100)/rebasingSteps_;
            emit progressRebasingTimeVector(progress);
        }
        remains = rebasingSteps_ - i;
        progress = ((rebasingSteps_ - remains)*100)/rebasingSteps_;
        emit progressRebasingTimeVector(progress);
    }
}

/// @brief Remove all invalid data
/// @note Data is invalid, when raw data of acceleration is 0
/// @param &data - pointer to the data set
void DataFile::removeInvalidData(QList<adxl355data> &data) {
    QList<adxl355data> temp;
    foreach (adxl355data d, data ) {
        if ((d.xraw != 0) && (d.yraw != 0) && (d.zraw != 0)) {
            temp.append(d);
        }
    }
    data = temp;
}

/// @brief Corrects the time vector with event id
/// @note The time vector starts at zero for every event. To create an ascending time vector,
/// the timesteps will be adjusted accordingly
/// @param &data - pointer to the data set
void DataFile::rebaseByEvents(QList<adxl355data> &data) {

    for (quint32 i = 0; i < data.size(); i++) {
        data[i].time = data[i].time+data[i].eventId*timeStepSize_;
        auto remains = rebasingSteps_ - i;
        auto progress = ((rebasingSteps_ - remains)*100)/rebasingSteps_;
        emit progressRebasingTimeVector(progress);
    }
}

/// @brief Creat the lists of start and stop events, event id list
/// @note This method will create list for start and stop times and indices for every event.
/// @param &data - pointer to the data set
void DataFile::createTimeSampleSizeVectors(QList<adxl355data> &data) {

    eventStartTime_.append(data[0].time);
    startTimeIdx.append(0);
    eventId_.append(data[0].eventId);
    for (int i = 1; i<data.size(); i++) {
        if (data[i].eventId != data[i-1].eventId) {
            eventStartTime_.append(data[i].time);
            startTimeIdx.append(i);
            eventId_.append(data[i].eventId);
            eventStopTime_.append(data[i-1].time);
            stopTimeIdx.append(i-1);
        }
    }
    eventStopTime_.append(data.last().time);
    stopTimeIdx.append(data.size()-1);
}

/// @brief Create the public data vectors from the the dataset
void DataFile::createVectors() {
    for (int i = 0; i < datasetRebased_.size(); i++) {

        time.append(datasetRebased_[i].time);
        xAcceleration.append(datasetRebased_[i].x);
        yAcceleration.append(datasetRebased_[i].y);
        zAcceleration.append(datasetRebased_[i].z);
        absAcceleration.append(datasetRebased_[i].absValue);
        temperature.append(datasetRebased_[i].temperature);

        auto remains = rebasingSteps_ - i;
        auto progress = ((rebasingSteps_ - remains)*100)/rebasingSteps_;
        emit progressRebasingTimeVector(progress);
    }
}
