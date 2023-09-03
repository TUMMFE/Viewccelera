#include "rawdatatab.h"

RawDataTab::RawDataTab(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout;

    overviewPlot_ = new QCustomPlot(this);
    overviewPlot_->setObjectName("overviewPlot");
    eventPlot_ = new QCustomPlot(this);
    eventPlot_->setObjectName("eventPlot");

    layout->addWidget(overviewPlot_);
    layout->addWidget(eventPlot_);
    setLayout(layout);

    prepareOverviewPlot();
    prepareEventPlot();
    currentEventId_ = 0;

}


///***********************************************************************************************
///*** PUBLIC METHODS
///***********************************************************************************************

/// @brief Set the data matrix
/// @param *data - pointer to the data
void RawDataTab::setData(DataFile *data) {
    data_ = data;
    eventStartTimes_ = data_->getEventStartTimes();
    eventStopTimes_ = data_->getEventStopTimes();
    overviewPlot_->graph(0)->data()->clear();
    overviewPlot_->replot();
    eventPlot_->graph(0)->data()->clear();
    eventPlot_->graph(1)->data()->clear();
    eventPlot_->graph(2)->data()->clear();
    eventPlot_->graph(3)->data()->clear();
    eventPlot_->replot();
    createPlotData();
    updateOverviewPlot();
    updateEventPlot(currentEventId_); //show first event

}

/// @brief Draw a circle to mark the start point of the analysis at the first visible graph.
/// @note Method will do a replot - if not graph is visible nothing will be drawn
/// @param idx - time point of the data key
void RawDataTab::setStartMarker(double time) {
    int graphIdx = 0;
    bool vis = false;

    for (int i = 0; i < visibilityList_.size(); i++) {
        if (visibilityList_[i] == true) {
            vis = true;
            graphIdx = i;
            break;
        }
    }
    if (vis == true) {
        QCPGraph *graph = eventPlot_->graph(graphIdx);
        startMarker_->setGraph(graph);
        startMarker_->setGraphKey(time);
        eventPlot_->replot();
    }

}

/// @brief Draw a circle to mark the stop point of the analysis at the first visible graph.
/// @note Method will do a replot - if not graph is visible nothing will be drawn
/// @param idx - time point of the data key
void RawDataTab::setStopMarker(double time) {
    int graphIdx = 0;
    bool vis = false;

    for (int i = 0; i < visibilityList_.size(); i++) {
        if (visibilityList_[i] == true) {
            vis = true;
            graphIdx = i;
            break;
        }
    }
    if (vis == true) {
        QCPGraph *graph = eventPlot_->graph(graphIdx);
        stopMarker_->setGraph(graph);
        stopMarker_->setGraphKey(time);
        eventPlot_->replot();
    }
}

/// @brief Safe the overview plot to a png file
/// @param filename - file name including directory
void RawDataTab::saveOverviewPlot(QString filename) {
    overviewPlot_->savePng(filename,0,0,1.0,-1);
}

/// @brief Safe the event plot to a png file
/// @param filename - file name including directory
void RawDataTab::saveEventPlot(QString filename) {
    eventPlot_->savePng(filename,0,0,1.0,-1);
}

///***********************************************************************************************
///*** PUBLIC SLOTS
///***********************************************************************************************

/// @brief Called, whenever the event id has changed
/// Method will set the current event id to the event id and update the plot
void RawDataTab::eventIdChanged(int eventId) {
    currentEventId_ = eventId;
    updateEventPlot(currentEventId_);
}

/// @brief Called, whenever the visibility of a plot should be changed
/// Method will change the visibility of the plot and rearange the markers
/// @param graphId - index of the graph 0 = x-axis, 1 = y-axis, 2 = z-axis, 3 = abs-axis
/// @param isVisible - true for visible, false for invisible
void RawDataTab::setVisibility(int graphId, bool isVisible) {
    if ((graphId >= 0) && (graphId < 4)) {
        eventPlot_->graph(graphId)->setVisible(isVisible);
        visibilityList_[graphId] = isVisible;
        if (isVisible == false) {
            //we need to change the graph lock for the start and stop markers
            //find the first graph which is visible
            int idx = -1;
            for (int i = 0; i < visibilityList_.size(); i++) {
                if (visibilityList_[i] == true) {
                    idx = i;
                    break;
                }
            }
            if (idx >= 0) {
                QCPGraph *graph = eventPlot_->graph(idx);
                startMarker_->setGraph(graph);
                stopMarker_->setGraph(graph);
            }
        }
        updateEventPlot(currentEventId_);
    }
}

///***********************************************************************************************
///*** PRIVATE METHODS
///***********************************************************************************************

/// @brief Prepare the overview plot
/// clear the plot view, add a single plot, label the axes and the caption, connect signals to top and right axes
/// as well as for the interaction to select a event for the detailed plot.
void RawDataTab::prepareOverviewPlot() {
    overviewPlot_->clearGraphs();
    overviewPlot_->addGraph();
    overviewPlot_->graph()->setPen(QPen(QColor(56,89,26)));
    overviewPlot_->axisRect()->setupFullAxesBox();
    overviewPlot_->xAxis->setLabel("time in s");
    overviewPlot_->yAxis->setLabel("acceleration in m/s²");
    overviewPlot_->plotLayout()->insertRow(0);
    overviewPlot_->plotLayout()->addElement(0, 0, new QCPTextElement(overviewPlot_, "Overview |a|", QFont("sans", 12, QFont::Bold)));


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(overviewPlot_->xAxis, SIGNAL(rangeChanged(QCPRange)), overviewPlot_->xAxis2, SLOT(setRange(QCPRange)));
    connect(overviewPlot_->yAxis, SIGNAL(rangeChanged(QCPRange)), overviewPlot_->yAxis2, SLOT(setRange(QCPRange)));
    // connect slot that allows to select the event for the detailed plot when a graph is clicked:
    connect(overviewPlot_, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(overviewPlotClicked(QCPAbstractPlottable*,int)));
}

/// @brief Prepare the detailed plot
/// clear the plot view, add four plots, label the axes and the caption, connect signals to top and right axes
/// and set all plots to invisible
void RawDataTab::prepareEventPlot() {
    eventPlot_->clearGraphs();
    eventPlot_->axisRect()->setupFullAxesBox();
    eventPlot_->xAxis->setLabel("time in s");
    eventPlot_->yAxis->setLabel("acceleration in m/s²");
    eventPlot_->legend->setVisible(true);
    eventPlot_->legend->setSelectableParts(QCPLegend::spItems);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(eventPlot_->xAxis, SIGNAL(rangeChanged(QCPRange)), eventPlot_->xAxis2, SLOT(setRange(QCPRange)));
    connect(eventPlot_->yAxis, SIGNAL(rangeChanged(QCPRange)), eventPlot_->yAxis2, SLOT(setRange(QCPRange)));
    // connect slot that transfer data to the stash dock when a graph is clicked:
    connect(eventPlot_, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(eventPlotClicked(QCPAbstractPlottable*,int)));

    //add all plots to the detailed view and hide them
    eventPlot_->addGraph();
    eventPlot_->addGraph();
    eventPlot_->addGraph();
    eventPlot_->addGraph();
    eventPlot_->graph(0)->setPen(QPen(QColor(42,139,129)));
    eventPlot_->graph(0)->setName(tr("x-direction"));
    eventPlot_->graph(0)->setVisible(false);
    visibilityList_.append(false);
    eventPlot_->graph(1)->setPen(QPen(QColor(109,46,127)));
    eventPlot_->graph(1)->setName(tr("y-direction"));
    eventPlot_->graph(1)->setVisible(false);
    visibilityList_.append(false);
    eventPlot_->graph(2)->setPen(QPen(QColor(192,115,28)));
    eventPlot_->graph(2)->setName(tr("z-direction"));
    eventPlot_->graph(2)->setVisible(false);
    visibilityList_.append(false);
    eventPlot_->graph(3)->setPen(QPen(QColor(56,89,26)));
    eventPlot_->graph(3)->setName(tr("|a|"));
    eventPlot_->graph(3)->setVisible(false);
    visibilityList_.append(false);

    eventLabelText_ = new QCPItemText(overviewPlot_);
    eventLabelText_->position->setType(QCPItemPosition::ptAxisRectRatio);
    eventLabelText_->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    eventLabelText_->position->setCoords(0.5, 0.0); // lower right corner of axis rect

    eventLabelText_->setTextAlignment(Qt::AlignLeft);
    eventLabelText_->setFont(QFont(font().family(), 46));
    eventLabelText_->setPadding(QMargins(8, 0, 8, 0));
    eventLabelText_->setText("");

    startMarker_ = new QCPItemTracer(eventPlot_);
    startMarker_->setInterpolating(true);
    startMarker_->setStyle(QCPItemTracer::tsCircle);
    startMarker_->setPen(QPen(Qt::green));
    startMarker_->setBrush(Qt::green);
    startMarker_->setSize(7);

    stopMarker_ = new QCPItemTracer(eventPlot_);
    stopMarker_->setInterpolating(true);
    stopMarker_->setStyle(QCPItemTracer::tsCircle);
    stopMarker_->setPen(QPen(Qt::red));
    stopMarker_->setBrush(Qt::red);
    stopMarker_->setSize(7);
}

/// @brief Add the data from the datafile object to both plots
/// Method will show a progressbar during adding the data to the graphs
void RawDataTab::createPlotData() {
    if (data_->time.count() > 0) {
        QProgressDialog progress("Preparing graphs...", "Cancel", 0, 100, this);
        progress.setWindowModality(Qt::WindowModal);
        progress.setMinimumDuration(0);
        auto size = data_->time.size();
        for (int i = 0; i < size; i++) {
            auto time = data_->time[i];
            overviewPlot_->graph(0)->addData(time, data_->absAcceleration[i]);
            eventPlot_->graph(0)->addData(time, data_->xAcceleration[i]);
            eventPlot_->graph(1)->addData(time, data_->yAcceleration[i]);
            eventPlot_->graph(2)->addData(time, data_->zAcceleration[i]);
            eventPlot_->graph(3)->addData(time, data_->absAcceleration[i]);

            auto remains = size-i;
            auto prog = ((size-remains)*100)/size;
            if (progress.wasCanceled()) {
                break;
            }
            progress.setValue(prog);
        }
        progress.setValue(100);
    }
}

/// @brief Rescale and Replot the overview graph
void RawDataTab::updateOverviewPlot() {
    overviewPlot_->graph(0)->rescaleAxes();
    overviewPlot_->replot();
}

/// @brief Will update the plot depending on the event id
/// The method will also check which parameter is shown or not and will set the
/// corresponding visibility accordingly. The method will adapt the range of the
/// x-axis as well as of the y-axis. The event id will be shown in the lower
/// right corner of the plot view. Finally the plot will be reploted.
/// @param eventId  - event id
void RawDataTab::updateEventPlot(int eventId) {
    bool vis = false;

    for (int i = 0; i < visibilityList_.size(); i++) {
        if (visibilityList_[i] == true) {
            vis = true;
            break;
        }
    }
    if (vis == false) {
        //no graph is visibile --> hide all markers
        startMarker_->setVisible(false);
        stopMarker_->setVisible(false);
    } else {
        startMarker_->setVisible(true);
        stopMarker_->setVisible(true);
    }

    if ((eventStartTimes_.size() > 0) && (eventStopTimes_.size() >0)) {
        eventLabelText_->setText("Event ID: "+ QString::number(eventId));
        eventPlot_->xAxis->setRange(eventStartTimes_[eventId], eventStopTimes_[eventId]);
        eventPlot_->yAxis->setRange(getMinRange(eventId)*1.1, getMaxRange(eventId)*1.1);
    }
    eventPlot_->replot();
    overviewPlot_->replot(); //rewrite the ID number.
}

/// @brief Calculate the minimum value of the current event id
/// Determine the minimum value of the current event id for each parameter
/// (x, y, z and absolute value).
/// Depending on which parameters are shown currently, return the overall minimum
/// of the shown parameters.
/// @note The method is used to rescale the Y-axis of the detailed plot depending on
/// which parameters are show and depending on the current event id.
/// @param eventId - event id for which the result must be calculated
/// @retval minimum of the shown parameters
double RawDataTab::getMinRange(int eventId) {
    double retVal;

    int lowerIdx = data_->startTimeIdx[eventId];
    int upperIdx = data_->stopTimeIdx[eventId];
    double minX = *std::min_element(data_->xAcceleration.begin()+lowerIdx, data_->xAcceleration.begin()+upperIdx);
    double minY = *std::min_element(data_->yAcceleration.begin()+lowerIdx, data_->yAcceleration.begin()+upperIdx);
    double minZ = *std::min_element(data_->zAcceleration.begin()+lowerIdx, data_->zAcceleration.begin()+upperIdx);
    double minAbs = *std::min_element(data_->absAcceleration.begin()+lowerIdx, data_->absAcceleration.begin()+upperIdx);

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

/// @brief Calculate the maximum value of the current event id
/// Determine the maximum value of the current event id for each parameter
/// (x, y, z and absolute value).
/// Depending on which parameters are shown currently, return the overall maximum
/// of the shown parameters.
/// @note The method is used to rescale the Y-axis of the detailed plot depending on
/// which parameters are show and depending on the current event id.
/// @param eventId - event id for which the result must be calculated
/// @retval maximum of the shown parameters
double RawDataTab::getMaxRange(int eventId) {
    double retVal;
    int lowerIdx = data_->startTimeIdx[eventId];
    int upperIdx = data_->stopTimeIdx[eventId];
    double maxX = *std::max_element(data_->xAcceleration.begin()+lowerIdx, data_->xAcceleration.begin()+upperIdx);
    double maxY = *std::max_element(data_->yAcceleration.begin()+lowerIdx, data_->yAcceleration.begin()+upperIdx);
    double maxZ = *std::max_element(data_->zAcceleration.begin()+lowerIdx, data_->zAcceleration.begin()+upperIdx);
    double maxAbs = *std::max_element(data_->absAcceleration.begin()+lowerIdx, data_->absAcceleration.begin()+upperIdx);

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

/// @brief Find the closest event id to a given time
/// @note Can be used to select a event in the overview plot which should be shown as a detailed view
/// @param time - time value (e.g. by click on a graph)
/// @retval closest event id
int RawDataTab::getEventId(double time) {
    int idx = 0;
    //bool finished = false;
    int size = eventStartTimes_.size();
    int i = 0;
    while ((time >= eventStartTimes_[i]) && (i<size)) {
        i++;
    }
    idx = i;
    /*
    do {
        if (time < eventStartTimes_[i]) {
            finished = true;
            idx = i;
        }
        i++;
    } while ((finished == false) && (i<size));
*/
    return idx;
}

///***********************************************************************************************
///*** PRIVATE SLOTS
///***********************************************************************************************

/// @brief Called, if a user clicks on a data point in the overview plot
/// After the user has clicked on a data point in the overview plot, the method will calculate
/// the closest corresponding event id and will set this event id as the new current event id.
/// Afterwards, the event plot will be updated.
/// @param *plottable - pointer to the graph it self
/// @param dataIndex - index of the selected data point
void RawDataTab::overviewPlotClicked(QCPAbstractPlottable *plottable, int dataIndex) {
    //dataIndex is the corresponding index of the time list
    double time = data_->time[dataIndex];
    currentEventId_ = getEventId(time);
    updateEventPlot(currentEventId_);
    emit currentEventIdChanged(currentEventId_);
}

/// @brief Called, if a user clicks on a data point in the detailed plot
/// After the user has clicked on a data point in the detailed plot, the method will forward this values
/// to the dock widget
/// @param *plottable - pointer to the graph it self
/// @param dataIndex - index of the selected data point
void RawDataTab::eventPlotClicked(QCPAbstractPlottable *plottable, int dataIndex) {
    double time = data_->time[dataIndex];
    emit eventPlotDataPointSelected(currentEventId_, time, dataIndex);
}
