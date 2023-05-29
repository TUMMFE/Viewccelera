#ifndef PROCESSEDDATATAB_H
#define PROCESSEDDATATAB_H

#include <QObject>
#include <QWidget>

#include "qcustomplot.h"
#include "analysisdataframe.h"

class ProcessedDataTab : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessedDataTab(QWidget *parent = nullptr);

    void saveVelocityPlot(QString filename);
    void saveDisplacementPlot(QString filename);
    bool isDataShown(int eventId);

public slots:
    void dataFrameChanged(AnalysisDataFrame dataFrame);
    void setVisibility(int graphId, bool isVisible);

signals:

private:
    QCustomPlot *velocityPlot_;
    QCustomPlot *displacementPlot_;
    QCPItemText *velocityLabelText_;
    QCPItemText *displacementLabelText_;

    QList<bool> visibilityList_;
    int currentEventId_;
    AnalysisDataFrame *currentDataFrame_;
    AnalysisDataFrame df;

    void setData(AnalysisDataFrame *data);

    void prepareVelocityPlot();
    void prepareDisplacementPlot();
    void updateVelocityPlot();
    void updateDisplacementPlot();
    double getMinRangeVelocity();
    double getMaxRangeVelocity();
    double getMinRangeDisplacement();
    double getMaxRangeDisplacement();
};

#endif // PROCESSEDDATATAB_H
