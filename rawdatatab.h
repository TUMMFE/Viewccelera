#ifndef RAWDATATAB_H
#define RAWDATATAB_H

#include <QObject>
#include <QWidget>

#include "qcustomplot.h"
#include "datafile.h"

class RawDataTab : public QWidget
{
    Q_OBJECT
public:
    explicit RawDataTab(QWidget *parent = nullptr);
    void setData(DataFile *data);
    void setStartMarker(double time);
    void setStopMarker(double time);
    void saveOverviewPlot(QString filename);
    void saveEventPlot(QString filename);



signals:
    void eventPlotDataPointSelected(int eventId, double time, int dataIndex);
    void currentEventIdChanged(int eventId);

private:
    QCustomPlot *overviewPlot_;
    QCustomPlot *eventPlot_;
    QCPItemText *eventLabelText_;
    QCPItemTracer *startMarker_;
    QCPItemTracer *stopMarker_;
    QList<double> eventStartTimes_;
    QList<double> eventStopTimes_;
    QList<bool> visibilityList_;
    DataFile *data_;
    int currentEventId_;


    void prepareOverviewPlot();
    void prepareEventPlot();
    void createPlotData();
    void updateOverviewPlot();
    void updateEventPlot(int eventId);
    double getMinRange(int eventId);
    double getMaxRange(int eventId);
    int getEventId(double time);


public slots:
    void eventIdChanged(int eventId);
    void setVisibility(int graphId, bool isVisible);

private slots:
    void overviewPlotClicked(QCPAbstractPlottable *plottable, int dataIndex);
    void eventPlotClicked(QCPAbstractPlottable *plottable, int dataIndex);
};

#endif // RAWDATATAB_H
