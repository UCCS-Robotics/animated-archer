#include "plotter.h"
#include "mainwindow.h"

Plotter::Plotter(MainWindow *mainwindowin, QObject *parent) :
    QObject(parent)
{
    mainwindow = mainwindowin;
    mainPlot = mainwindowin->get_qplot();
}

void Plotter::create_graph(QString graph_name){
    mainPlot->addGraph();
    usedGraphs.insert(graph_name,mainPlot->graphCount()-1);
}

void Plotter::remove_graph(QString graph_name){
    if(usedGraphs.contains(graph_name)){
        mainPlot->removeGraph(usedGraphs.value(graph_name));
        usedGraphs.remove(graph_name);
    }
}

void Plotter::clear_graph_data(QString graph_name){
    if(usedGraphs.contains(graph_name)){
        mainPlot->graph(usedGraphs.value(graph_name))->clearData();
    }
}

void Plotter::clear_all_graph_data(){
    QMapIterator <QString, char> i(usedGraphs);
    while(i.hasNext()){
        i.next();
        clear_graph_data(i.key());
    }
}
