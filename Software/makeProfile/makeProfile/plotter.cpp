#include "plotter.h"
#include "mainwindow.h"

Plotter::Plotter(MainWindow *mainwindowin, QObject *parent) :
    QObject(parent)
{
    mainwindow = mainwindowin;
    mainPlot = mainwindowin->get_qplot();
}

Plotter::~Plotter(){
    delete mainPlot;
    delete mainwindow;
}

/********************************************************************
 * Helper Methods                                                   *
 *******************************************************************/

void Plotter::clear_all_graph_data(){
    QMapIterator <QString, QCPGraph*> i(usedGraphs);
    while(i.hasNext()){
        i.next();
        i.value()->clearData();
    }
}

void Plotter::clear_graph_data(QString graph_name){
    if(usedGraphs.contains(graph_name)){
        usedGraphs.value(graph_name)->clearData();
    }
}

void Plotter::create_graph(QString graph_name){
    usedGraphs.insert(graph_name,mainPlot->addGraph());
}

void Plotter::remove_graph(QString graph_name){
    if(usedGraphs.contains(graph_name)){
        mainPlot->removeGraph(usedGraphs.value(graph_name));
        usedGraphs.remove(graph_name);
    }
}
