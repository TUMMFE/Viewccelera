#include "processeddatatab.h"
#include "analysisdataframe.h"

ProcessedDataTab::ProcessedDataTab(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout;

    velocityPlot_ = new QCustomPlot(this);
    velocityPlot_->setObjectName("velocityPlot");
    displacementPlot_ = new QCustomPlot(this);
    displacementPlot_->setObjectName("displacementPlot");

    layout->addWidget(velocityPlot_);
    layout->addWidget(displacementPlot_);
    setLayout(layout);
    prepareVelocityPlot();
    prepareDisplacementPlot();
    currentEventId_ = 0;
    currentDataFrame_ = nullptr;

}



///***********************************************************************************************
///*** PUBLIC METHODS
///***********************************************************************************************



/// @brief Safe the velocity plot to a png file
/// @param filename - file name including directory
void ProcessedDataTab::saveVelocityPlot(QString filename) {
    velocityPlot_->savePng(filename,0,0,1.0,-1);
}

/// @brief Safe the displacement plot to a png file
/// @param filename - file name including directory
void ProcessedDataTab::saveDisplacementPlot(QString filename) {
    displacementPlot_->savePng(filename,0,0,1.0,-1);
}

/// @brief Check if the event id is the same as the used one
/// @param eventId - event Id to check
/// @return true, if eventId corresponds to displayed event If.
bool ProcessedDataTab::isDataShown(int eventId) {
    bool retval = false;
    if (currentEventId_ == eventId) {
        retval = true;
    }
    return retval;
}




///***********************************************************************************************
///*** PUBLIC SLOTS
///***********************************************************************************************

/// @brief Called, whenever the event id has changed
/// Method will set the current data frame and the event id and update the plot
void ProcessedDataTab::dataFrameChanged(AnalysisDataFrame dataFrame) {
    df = dataFrame;
    setData(&df);
}

/// @brief Called, whenever the visibility of a plot should be changed
/// Method will change the visibility of the plot
/// @param graphId - index of the graph 0 = x-axis, 1 = y-axis, 2 = z-axis, 3 = abs-axis
/// @param isVisible - true for visible, false for invisible
void ProcessedDataTab::setVisibility(int graphId, bool isVisible) {
    if ((graphId >= 0) && (graphId < 4)) {
        velocityPlot_->graph(graphId)->setVisible(isVisible);
        displacementPlot_->graph(graphId)->setVisible(isVisible);
        visibilityList_[graphId] = isVisible;
        updateVelocityPlot();
        updateDisplacementPlot();
    }
}



///***********************************************************************************************
///*** PRIVATE METHODS
///***********************************************************************************************

/// @brief Set the data frame
/// @param *data - pointer to the data
void ProcessedDataTab::setData(AnalysisDataFrame *data) {
    currentDataFrame_ = data;
    currentEventId_ = currentDataFrame_->eventId;

    for (int i = 0; i < velocityPlot_->graphCount(); i ++) {
        velocityPlot_->graph(i)->data()->clear();
    }
    velocityPlot_->graph(0)->setData(currentDataFrame_->time, currentDataFrame_->xVelocity);
    velocityPlot_->graph(1)->setData(currentDataFrame_->time, currentDataFrame_->yVelocity);
    velocityPlot_->graph(2)->setData(currentDataFrame_->time, currentDataFrame_->zVelocity);
    velocityPlot_->graph(3)->setData(currentDataFrame_->time, currentDataFrame_->absVelocity);
    velocityLabelText_->setText(QString::number(currentEventId_));

    for (int i = 0; i < displacementPlot_->graphCount(); i ++) {
        displacementPlot_->graph(i)->data()->clear();
    }
    displacementPlot_->graph(0)->setData(currentDataFrame_->time, currentDataFrame_->xDisplacement);
    displacementPlot_->graph(1)->setData(currentDataFrame_->time, currentDataFrame_->yDisplacement);
    displacementPlot_->graph(2)->setData(currentDataFrame_->time, currentDataFrame_->zDisplacement);
    displacementPlot_->graph(3)->setData(currentDataFrame_->time, currentDataFrame_->absDisplacement);

    displacementLabelText_->setText(QString::number(currentEventId_));

    updateVelocityPlot();
    updateDisplacementPlot();
}

/// @brief Prepare the velocity plot
/// clear the plot view, add four plots, label the axes and the caption, connect signals to top and right axes
/// and set all plots to invisible
void ProcessedDataTab::prepareVelocityPlot()  {
    velocityPlot_->clearGraphs();
    velocityPlot_->axisRect()->setupFullAxesBox();
    velocityPlot_->xAxis->setLabel("time in s");
    velocityPlot_->yAxis->setLabel("velocity in m/s");
    velocityPlot_->legend->setVisible(true);
    velocityPlot_->legend->setSelectableParts(QCPLegend::spItems);

    velocityPlot_->plotLayout()->insertRow(0);
    velocityPlot_->plotLayout()->addElement(0, 0, new QCPTextElement(velocityPlot_, "Velocity", QFont("sans", 12, QFont::Bold)));


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(velocityPlot_->xAxis, SIGNAL(rangeChanged(QCPRange)), velocityPlot_->xAxis2, SLOT(setRange(QCPRange)));
    connect(velocityPlot_->yAxis, SIGNAL(rangeChanged(QCPRange)), velocityPlot_->yAxis2, SLOT(setRange(QCPRange)));

    //add all plots to the detailed view and hide them
    velocityPlot_->addGraph();
    velocityPlot_->addGraph();
    velocityPlot_->addGraph();
    velocityPlot_->addGraph();
    velocityPlot_->graph(0)->setPen(QPen(QColor(42,139,129)));
    velocityPlot_->graph(0)->setName(tr("x-direction"));
    velocityPlot_->graph(0)->setVisible(false);
    visibilityList_.append(false);
    velocityPlot_->graph(1)->setPen(QPen(QColor(109,46,127)));
    velocityPlot_->graph(1)->setName(tr("y-direction"));
    velocityPlot_->graph(1)->setVisible(false);
    visibilityList_.append(false);
    velocityPlot_->graph(2)->setPen(QPen(QColor(192,115,28)));
    velocityPlot_->graph(2)->setName(tr("z-direction"));
    velocityPlot_->graph(2)->setVisible(false);
    visibilityList_.append(false);
    velocityPlot_->graph(3)->setPen(QPen(QColor(56,89,26)));
    velocityPlot_->graph(3)->setName(tr("|v|"));
    velocityPlot_->graph(3)->setVisible(false);
    visibilityList_.append(false);

    velocityLabelText_ = new QCPItemText(velocityPlot_);
    velocityLabelText_->position->setType(QCPItemPosition::ptAxisRectRatio);
    velocityLabelText_->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    velocityLabelText_->position->setCoords(0.95, 0.95); // lower right corner of axis rect

    velocityLabelText_->setTextAlignment(Qt::AlignLeft);
    velocityLabelText_->setFont(QFont(font().family(), 46));
    velocityLabelText_->setPadding(QMargins(8, 0, 8, 0));
    velocityLabelText_->setText("");
}

/// @brief Prepare the displacement plot
/// clear the plot view, add a four plots, label the axes and the caption, connect signals to top and right axes
/// and set all plots to invisible
void ProcessedDataTab::prepareDisplacementPlot()  {
    displacementPlot_->clearGraphs();
    displacementPlot_->axisRect()->setupFullAxesBox();
    displacementPlot_->xAxis->setLabel("time in s");
    displacementPlot_->yAxis->setLabel("displacement in m");
    displacementPlot_->legend->setVisible(true);
    displacementPlot_->legend->setSelectableParts(QCPLegend::spItems);

    displacementPlot_->plotLayout()->insertRow(0);
    displacementPlot_->plotLayout()->addElement(0, 0, new QCPTextElement(displacementPlot_, "Displacement", QFont("sans", 12, QFont::Bold)));


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(displacementPlot_->xAxis, SIGNAL(rangeChanged(QCPRange)), displacementPlot_->xAxis2, SLOT(setRange(QCPRange)));
    connect(displacementPlot_->yAxis, SIGNAL(rangeChanged(QCPRange)), displacementPlot_->yAxis2, SLOT(setRange(QCPRange)));

    //add all plots to the detailed view and hide them
    displacementPlot_->addGraph();
    displacementPlot_->addGraph();
    displacementPlot_->addGraph();
    displacementPlot_->addGraph();
    displacementPlot_->graph(0)->setPen(QPen(QColor(42,139,129)));
    displacementPlot_->graph(0)->setName(tr("x-direction"));
    displacementPlot_->graph(0)->setVisible(false);
    displacementPlot_->graph(1)->setPen(QPen(QColor(109,46,127)));
    displacementPlot_->graph(1)->setName(tr("y-direction"));
    displacementPlot_->graph(1)->setVisible(false);
    displacementPlot_->graph(2)->setPen(QPen(QColor(192,115,28)));
    displacementPlot_->graph(2)->setName(tr("z-direction"));
    displacementPlot_->graph(2)->setVisible(false);
    displacementPlot_->graph(3)->setPen(QPen(QColor(56,89,26)));
    displacementPlot_->graph(3)->setName(tr("|d|"));
    displacementPlot_->graph(3)->setVisible(false);

    displacementLabelText_ = new QCPItemText(displacementPlot_);
    displacementLabelText_->position->setType(QCPItemPosition::ptAxisRectRatio);
    displacementLabelText_->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    displacementLabelText_->position->setCoords(0.95, 0.95); // lower right corner of axis rect

    displacementLabelText_->setTextAlignment(Qt::AlignLeft);
    displacementLabelText_->setFont(QFont(font().family(), 46));
    displacementLabelText_->setPadding(QMargins(8, 0, 8, 0));
    displacementLabelText_->setText("");
}

/// @brief Update the velocity plot
void ProcessedDataTab::updateVelocityPlot()  {
    if (currentDataFrame_ !=nullptr) {
        int idx = currentDataFrame_->time.size()-1;
        velocityPlot_->xAxis->setRange(currentDataFrame_->time[0], currentDataFrame_->time[idx]);
        velocityPlot_->yAxis->setRange(getMinRangeVelocity()*1.1, getMaxRangeVelocity()*1.1);
        velocityPlot_->replot();
    }
}

/// @brief Update the displacement plot
void ProcessedDataTab::updateDisplacementPlot()  {
    if (currentDataFrame_ !=nullptr) {
        int idx = currentDataFrame_->time.size()-1;
        displacementPlot_->xAxis->setRange(currentDataFrame_->time[0], currentDataFrame_->time[idx]);
        displacementPlot_->yAxis->setRange(getMinRangeDisplacement()*1.1, getMaxRangeDisplacement()*1.1);
        displacementPlot_->replot();
    }
}

/// @brief Calculate the minimum value of the current frame (velocity)
/// Determine the minimum value of the current frame for each parameter
/// (x, y, z and absolute value).
/// Depending on which parameters are shown currently, return the overall minimum
/// of the shown parameters.
/// @note The method is used to rescale the Y-axis of the detailed plot depending on
/// which parameters are show and depending on the current event id.
/// @retval minimum of the shown parameters
double ProcessedDataTab::getMinRangeVelocity()  {
    double retVal;

    double minX = *std::min_element(currentDataFrame_->xVelocity.begin(), currentDataFrame_->xVelocity.end());
    double minY = *std::min_element(currentDataFrame_->yVelocity.begin(), currentDataFrame_->yVelocity.end());
    double minZ = *std::min_element(currentDataFrame_->zVelocity.begin(), currentDataFrame_->zVelocity.end());
    double minAbs = *std::min_element(currentDataFrame_->absVelocity.begin(), currentDataFrame_->absVelocity.end());

    QVector<double> min;

    if (visibilityList_[0] == true) {
        min.append(minX);
    }
    if (visibilityList_[1] == true) {
        min.append(minY);
    }
    if (visibilityList_[2] == true) {
        min.append(minZ);
    }
    if (visibilityList_[3] == true) {
        min.append(minAbs);
    }

    if (min.size()>0) {
        retVal = *std::min_element(min.begin(), min.end());
    } else {
        retVal = 0;
    }
    return retVal;
}

/// @brief Calculate the maximum value of the current frame (velocity)
/// Determine the maximum value of the current frame for each parameter
/// (x, y, z and absolute value).
/// Depending on which parameters are shown currently, return the overall minimum
/// of the shown parameters.
/// @note The method is used to rescale the Y-axis of the detailed plot depending on
/// which parameters are show and depending on the current event id.
/// @retval minimum of the shown parameters
double ProcessedDataTab::getMaxRangeVelocity()  {
    double retVal;

    double maxX = *std::max_element(currentDataFrame_->xVelocity.begin(), currentDataFrame_->xVelocity.end());
    double maxY = *std::max_element(currentDataFrame_->yVelocity.begin(), currentDataFrame_->yVelocity.end());
    double maxZ = *std::max_element(currentDataFrame_->zVelocity.begin(), currentDataFrame_->zVelocity.end());
    double maxAbs = *std::max_element(currentDataFrame_->absVelocity.begin(), currentDataFrame_->absVelocity.end());

    QVector<double> max;

    if (visibilityList_[0] == true) {
        max.append(maxX);
    }
    if (visibilityList_[1] == true) {
        max.append(maxY);
    }
    if (visibilityList_[2] == true) {
        max.append(maxZ);
    }
    if (visibilityList_[3] == true) {
        max.append(maxAbs);
    }

    if (max.size()>0) {
        retVal = *std::max_element(max.begin(), max.end());
    } else {
        retVal = 0;
    }
    return retVal;
}

/// @brief Calculate the minimum value of the current frame (displacement)
/// Determine the minimum value of the current frame for each parameter
/// (x, y, z and absolute value).
/// Depending on which parameters are shown currently, return the overall minimum
/// of the shown parameters.
/// @note The method is used to rescale the Y-axis of the detailed plot depending on
/// which parameters are show and depending on the current event id.
/// @retval minimum of the shown parameters
double ProcessedDataTab::getMinRangeDisplacement()  {
    double retVal;

    double minX = *std::min_element(currentDataFrame_->xDisplacement.begin(), currentDataFrame_->xDisplacement.end());
    double minY = *std::min_element(currentDataFrame_->yDisplacement.begin(), currentDataFrame_->yDisplacement.end());
    double minZ = *std::min_element(currentDataFrame_->zDisplacement.begin(), currentDataFrame_->zDisplacement.end());
    double minAbs = *std::min_element(currentDataFrame_->absDisplacement.begin(), currentDataFrame_->absDisplacement.end());

    QVector<double> min;

    if (visibilityList_[0] == true) {
        min.append(minX);
    }
    if (visibilityList_[1] == true) {
        min.append(minY);
    }
    if (visibilityList_[2] == true) {
        min.append(minZ);
    }
    if (visibilityList_[3] == true) {
        min.append(minAbs);
    }

    if (min.size()>0) {
        retVal = *std::min_element(min.begin(), min.end());
    } else {
        retVal = 0;
    }
    return retVal;
}

/// @brief Calculate the maximum value of the current frame (displacement)
/// Determine the maximum value of the current frame for each parameter
/// (x, y, z and absolute value).
/// Depending on which parameters are shown currently, return the overall minimum
/// of the shown parameters.
/// @note The method is used to rescale the Y-axis of the detailed plot depending on
/// which parameters are show and depending on the current event id.
/// @retval minimum of the shown parameters
double ProcessedDataTab::getMaxRangeDisplacement()  {
    double retVal;

    double maxX = *std::max_element(currentDataFrame_->xDisplacement.begin(), currentDataFrame_->xDisplacement.end());
    double maxY = *std::max_element(currentDataFrame_->yDisplacement.begin(), currentDataFrame_->yDisplacement.end());
    double maxZ = *std::max_element(currentDataFrame_->zDisplacement.begin(), currentDataFrame_->zDisplacement.end());
    double maxAbs = *std::max_element(currentDataFrame_->absDisplacement.begin(), currentDataFrame_->absDisplacement.end());

    QVector<double> max;

    if (visibilityList_[0] == true) {
        max.append(maxX);
    }
    if (visibilityList_[1] == true) {
        max.append(maxY);
    }
    if (visibilityList_[2] == true) {
        max.append(maxZ);
    }
    if (visibilityList_[3] == true) {
        max.append(maxAbs);
    }

    if (max.size()>0) {
        retVal = *std::max_element(max.begin(), max.end());
    } else {
        retVal = 0;
    }
    return retVal;
}


///***********************************************************************************************
///*** PRIVATE SLOTS
///***********************************************************************************************
