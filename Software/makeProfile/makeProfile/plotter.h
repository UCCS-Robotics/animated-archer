#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QMap>
#include "qcustomplot.h"

class MainWindow;

class Plotter : public QObject
{
    Q_OBJECT
public:
    explicit Plotter(MainWindow *mainwindowin, QObject *parent = 0);
    void create_graph(QString graph_name);
    void remove_graph(QString graph_name);
    void clear_graph_data(QString graph_name);
    void clear_all_graph_data();


signals:

public slots:

private:
    QMap<QString,char> usedGraphs;    // List of active graphs
    MainWindow *mainwindow;
    QCustomPlot *mainPlot;
};

#endif // PLOTTER_H
