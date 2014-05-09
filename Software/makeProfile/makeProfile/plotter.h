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
    ~Plotter();

    /////////////////////////////////////////////////////////////////////
    /// \brief clear_all_graph_data
    /// Clears all data for all graphs
    /////////////////////////////////////////////////////////////////////
    void clear_all_graph_data();

    /////////////////////////////////////////////////////////////////////
    /// \brief clear_graph_data
    /// \param graph_name
    /// Clears all of the data relating to the given graph.
    /////////////////////////////////////////////////////////////////////
    void clear_graph_data(QString graph_name);

    /////////////////////////////////////////////////////////////////////
    /// \brief create_graph
    /// \param graph_name
    /// This is an abstraction of the QCustomPlot add graph, such that
    /// the developer needs not keep track of each graph.
    /////////////////////////////////////////////////////////////////////
    void create_graph(QString graph_name);

    /////////////////////////////////////////////////////////////////////
    /// \brief remove_graph
    /// \param graph_name
    /// Remove the user indicated graph from the plot.
    /////////////////////////////////////////////////////////////////////
    void remove_graph(QString graph_name);

    /********************************************************************
     * Getters                                                          *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief get_used_graphs
    /// \return
    /// Returns the current graph-name to graph-pointer mapping
    /////////////////////////////////////////////////////////////////////
    const QMap<QString, QCPGraph*> &get_used_graphs() const { return usedGraphs; }

    /********************************************************************
     * Setters                                                          *
     *******************************************************************/


signals:

public slots:

private:
    QMap<QString,QCPGraph*> usedGraphs;    // List of active graphs
    MainWindow *mainwindow;
    QCustomPlot *mainPlot;

    /********************************************************************
     * Setters                                                          *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief set_used_graphs
    /// \param used_graphs
    /// Set the used graphs map, this will probably not see any usage
    /////////////////////////////////////////////////////////////////////
    void set_used_graphs(const QMap<QString, QCPGraph*> &used_graphs){ usedGraphs = used_graphs; }
};

#endif // PLOTTER_H
