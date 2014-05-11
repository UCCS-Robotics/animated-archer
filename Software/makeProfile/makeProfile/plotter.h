#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QMap>
#include <QClipboard>
#include "qcustomplot.h"

class MainWindow;

class Plotter : public QObject
{
    Q_OBJECT
public:
    explicit Plotter(MainWindow *mainwindowin, QObject *parent = 0);
    ~Plotter();

    /********************************************************************
     * Implimentors                                                     *
     *******************************************************************/



    /********************************************************************
     * Helpers                                                          *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief add_graph_data
    /// \param graph_name
    /// \param xData
    /// \param yData
    /// Add datapoints to the given graph. Vectors must be same length.
    /////////////////////////////////////////////////////////////////////
    void add_graph_data(char graph_name, const QVector<double> &xData,
                        const QVector<double> &yData);

    /////////////////////////////////////////////////////////////////////
    /// \brief add_graph_data
    /// \param graph_name
    /// \param xData
    /// \param yData
    /// Override method for the vector form of this method. Simply adds
    /// a single datapoint to the given graph.
    /////////////////////////////////////////////////////////////////////
    void add_graph_data(char graph_name, double xData, double yData);

    /////////////////////////////////////////////////////////////////////
    /// \brief clear_all_graph_data
    /// Clears all data for all graphs.
    /////////////////////////////////////////////////////////////////////
    void clear_all_graph_data();

    /////////////////////////////////////////////////////////////////////
    /// \brief clear_graph_data
    /// \param graph_name
    /// Clears all of the data relating to the given graph.
    /////////////////////////////////////////////////////////////////////
    void clear_graph_data(char graph_name);

    /////////////////////////////////////////////////////////////////////
    /// \brief create_graph
    /// \param graph_name
    /// This is an abstraction of the QCustomPlot add graph, such that
    /// the developer needs not keep track of each graph.
    /////////////////////////////////////////////////////////////////////
    void create_graph(char graph_name);

    /////////////////////////////////////////////////////////////////////
    /// \brief hide_graph
    /// \param graph_name
    /// Hide the given graph from the plot
    /////////////////////////////////////////////////////////////////////
    void hide_graph(char graph_name);

    /////////////////////////////////////////////////////////////////////
    /// \brief rescale_all
    /// Rescale to fit all data into window.
    /////////////////////////////////////////////////////////////////////
    void rescale_all(){ mainPlot->rescaleAxes(true); }

    /////////////////////////////////////////////////////////////////////
    /// \brief remove_all_graphs
    /// Self explanitory
    /////////////////////////////////////////////////////////////////////
    void remove_all_graphs();

    /////////////////////////////////////////////////////////////////////
    /// \brief remove_graph
    /// \param graph_name
    /// Remove the user indicated graph from the plot.
    /////////////////////////////////////////////////////////////////////
    void remove_graph(char graph_name);

    /////////////////////////////////////////////////////////////////////
    /// \brief reset_plot
    /// Clears the data from the plot, and replots.
    /////////////////////////////////////////////////////////////////////
    void reset_plot();

    /////////////////////////////////////////////////////////////////////
    /// \brief show_graph
    /// \param graph_name
    /// Show the given graph on the plot.
    /////////////////////////////////////////////////////////////////////
    void show_graph(char graph_name);

    /////////////////////////////////////////////////////////////////////
    /// \brief update_plot
    /// Update the plot, any change to the plot requres an update to
    /// display.
    /////////////////////////////////////////////////////////////////////
    void update_plot(){ mainPlot->replot(); }

    /********************************************************************
     * Getters                                                          *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief get_used_graphs
    /// \return
    /// Returns the current graph-name to graph-pointer mapping.
    /////////////////////////////////////////////////////////////////////
    const QMap<char, QCPGraph*> &get_used_graphs() const { return usedGraphs; }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_title
    /// \return
    /// Returns the current title in use for the plot.
    /////////////////////////////////////////////////////////////////////
    QString get_title() const { return currentTitle; }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_xAxis1_label
    /// \return
    /// Returns the current bottom xAxis label.
    /////////////////////////////////////////////////////////////////////
    QString get_xAxis1_label() const { return mainPlot->xAxis->label(); }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_xAxis2_label
    /// \return
    /// Returns the current top xAxis label.
    /////////////////////////////////////////////////////////////////////
    QString get_xAxis2_label() const { return mainPlot->xAxis2->label(); }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_yAxis1_label
    /// \return
    /// Returns the current left yAxis label.
    /////////////////////////////////////////////////////////////////////
    QString get_yAxis1_label() const { return mainPlot->yAxis->label(); }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_yAxis2_label
    /// \return
    /// Returns the current right yAxis label.
    /////////////////////////////////////////////////////////////////////
    QString get_yAxis2_label() const { return mainPlot->yAxis2->label(); }

    /********************************************************************
     * Setters                                                          *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief set_auto_range_scale
    /// \param range_scale
    /// Determine whether or not to auto range and scale.
    /////////////////////////////////////////////////////////////////////
    void set_auto_range_scale(bool range_scale) { autoRangeScale = range_scale; }

    /////////////////////////////////////////////////////////////////////
    /// \brief set_graph_data
    /// \param graph_name
    /// \param xData
    /// \param yData
    /// Resets the given graph data with new data. Vectors must be same
    /// length.
    /////////////////////////////////////////////////////////////////////
    void set_graph_data(char graph_name, const QVector<double> &xData,
                        const QVector<double> &yData);

    /////////////////////////////////////////////////////////////////////
    /// \brief set_graph_pen
    /// \param graph_name
    /// \param pen
    /// Set graph color.
    /////////////////////////////////////////////////////////////////////
    void set_graph_pen(char graph_name, QPen pen);

    /////////////////////////////////////////////////////////////////////
    /// \brief set_graph_name
    /// \param graph_name
    /// \param new_graph_name
    /// Changes the displayed graph name, not the name of the graph for
    /// accessing the graph itself.
    /////////////////////////////////////////////////////////////////////
    void set_graph_name(char graph_name, QString new_graph_name);

    /////////////////////////////////////////////////////////////////////
    /// \brief set_number_xData_points
    /// \param data_points
    /// Set the number of data points for the x window to fit.
    /////////////////////////////////////////////////////////////////////
    void set_number_xData_points(quint32 data_points){ dataPoints = data_points; }

    /////////////////////////////////////////////////////////////////////
    /// \brief set_title
    /// \param title
    /// Changes the plot title to the given string.
    /////////////////////////////////////////////////////////////////////
    void set_title(QString title);

    /////////////////////////////////////////////////////////////////////
    /// \brief set_xAxis1
    /// \param name
    /// Sets the bottom xAxis name.
    /////////////////////////////////////////////////////////////////////
    void set_xAxis1_label(QString name){ mainPlot->xAxis->setLabel(name); }

    /////////////////////////////////////////////////////////////////////
    /// \brief set_xAxis2
    /// \param name
    /// Sets the top xAxis name.
    /////////////////////////////////////////////////////////////////////
    void set_xAxis2_label(QString name){ mainPlot->xAxis2->setLabel(name); }

    /////////////////////////////////////////////////////////////////////
    /// \brief set_xAxis_range
    /// \param lower
    /// \param upper
    /// Sets the xAxis range
    /////////////////////////////////////////////////////////////////////
    void set_xAxis_range(double lower, double upper);

    /////////////////////////////////////////////////////////////////////
    /// \brief set_xAxis_scale
    /// \param scale
    /// Set the scale of the xAxis with respect to the yAxis when the
    /// scale value for the xAxis was 0.
    /////////////////////////////////////////////////////////////////////
    void set_xAxis_scale(int scale);

    void set_xWindow_range(quint32 data_points);

    /////////////////////////////////////////////////////////////////////
    /// \brief set_yAxis1
    /// \param name
    /// Sets the left yAxis name.
    /////////////////////////////////////////////////////////////////////
    void set_yAxis1_label(QString name){ mainPlot->yAxis->setLabel(name); }

    /////////////////////////////////////////////////////////////////////
    /// \brief set_yAxis2
    /// \param name
    /// Sets the right yAxis name.
    /////////////////////////////////////////////////////////////////////
    void set_yAxis2_label(QString name){ mainPlot->yAxis2->setLabel(name); }

    /////////////////////////////////////////////////////////////////////
    /// \brief set_yAxis_range
    /// \param lower
    /// \param upper
    /// Set the range of the yAxis
    /////////////////////////////////////////////////////////////////////
    void set_yAxis_range(double lower, double upper);

    /////////////////////////////////////////////////////////////////////
    /// \brief set_yAxis_scale
    /// \param scale
    /// Set the scale of the yAxis with respect to the xAxis when the
    /// scale value for the xAxis was 10.
    /////////////////////////////////////////////////////////////////////
    void set_yAxis_scale(int scale);


signals:

    /////////////////////////////////////////////////////////////////////
    /// \brief copu_graph_data
    /// Emitted when the user requested a copy of graph data.
    /////////////////////////////////////////////////////////////////////
    void copy_graph_data();

    /////////////////////////////////////////////////////////////////////
    /// \brief copy_plot_image
    /// Emitted when the user requested a copy of the current window.
    /////////////////////////////////////////////////////////////////////
    void copy_plot_image();

    /////////////////////////////////////////////////////////////////////
    /// \brief graph_clicked
    /// \param plottable
    /// Emitted when the graph has been clicked.
    /////////////////////////////////////////////////////////////////////
    void graph_clicked(QCPAbstractPlottable *plottable);

    /////////////////////////////////////////////////////////////////////
    /// \brief legend_double_clicked
    /// \param plItem
    /// Emitted when the plot legend has been double clicked.
    /////////////////////////////////////////////////////////////////////
    void legend_double_clicked(QCPPlottableLegendItem *plItem);

public slots:
    /////////////////////////////////////////////////////////////////////
    /// \brief on_axis_label_double_click
    /// \param axis
    /// \param part
    /// Used to allow the user to rename any axis.
    /////////////////////////////////////////////////////////////////////
    void on_axis_label_double_click(QCPAxis *axis, QCPAxis::SelectablePart part);

    /////////////////////////////////////////////////////////////////////
    /// \brief on_context_menu_request
    /// \param pos
    /// Show's menu items when the plot has been right clicked.
    /////////////////////////////////////////////////////////////////////
    void on_context_menu_request(QPoint pos);

    /////////////////////////////////////////////////////////////////////
    /// \brief on_copy_graph_data
    /// Copies graph data to the clipboard.
    /////////////////////////////////////////////////////////////////////
    void on_copy_graph_data();

    /////////////////////////////////////////////////////////////////////
    /// \brief on_copy_plot_image
    /// Copy image of current plot window to clipboard.
    /////////////////////////////////////////////////////////////////////
    void on_copy_plot_image();

    /////////////////////////////////////////////////////////////////////
    /// \brief on_graph_clicked
    /// \param plottable
    /// Emit signal when the graph has been clicked.
    /////////////////////////////////////////////////////////////////////
    void on_graph_clicked(QCPAbstractPlottable *plottable);

    /////////////////////////////////////////////////////////////////////
    /// \brief on_legend_double_click
    /// \param legend
    /// \param item
    /// When the legend has been double clicked, allow user to rename
    /// graph
    /////////////////////////////////////////////////////////////////////
    void on_legend_double_click(QCPLegend *legend, QCPAbstractLegendItem *item);

    /////////////////////////////////////////////////////////////////////
    /// \brief on_mouse_press
    /// if an axis is selected, only allow the direction of that axis to
    /// be dragged if no axis is selected, both directions may be dragged
    /////////////////////////////////////////////////////////////////////
    void on_mouse_press();

    /////////////////////////////////////////////////////////////////////
    /// \brief on_mouse_wheel
    /// if an axis is selected, only allow the direction of that axis to
    /// be zoomed if no axis is selected, both directions may be zoomed.
    /////////////////////////////////////////////////////////////////////
    void on_mouse_wheel();

    /////////////////////////////////////////////////////////////////////
    /// \brief on_move_legend
    /// Handle moving the legend.
    /////////////////////////////////////////////////////////////////////
    void on_move_legend();

    /////////////////////////////////////////////////////////////////////
    /// \brief on_selection_changed
    /// normally, axis base line, axis tick labels and axis labels are
    /// selectable separately, but we want the user only to be able to
    /// select the axis as a whole, so we tie the selected states of the
    /// tick labels and the axis base line together. However, the axis
    /// label shall be selectable individually.
    ///
    /// The selection state of the left and right axes shall be
    /// synchronized as well as the state of the bottom and top axes.
    ///
    /// Further, we want to synchronize the selection of the graphs with
    /// the selection state of the respective legend item belonging to
    /// that graph. So the user can select a graph by either clicking on
    /// the graph itself or on its legend item.
    /// /////////////////////////////////////////////////////////////////
    void on_selection_changed();

    /////////////////////////////////////////////////////////////////////
    /// \brief on_title_double_click
    /// \param event
    /// \param title
    /// When the title is double clicked, allow title to be renamed.
    /////////////////////////////////////////////////////////////////////
    void on_title_double_click(QMouseEvent* event, QCPPlotTitle* title);

private:
    QMap<char,QCPGraph*> usedGraphs;    // List of active graphs
    MainWindow *mainwindow;
    QCustomPlot *mainPlot, *refPlot;
    QClipboard *clipboard;
    QString currentTitle;
    int xScale, yScale;
    quint32 dataPoints;
    double minimumValue, maximumValue;
    bool autoRangeScale;

    /********************************************************************
     * Helpers                                                          *
     *******************************************************************/

    void auto_find_yAxis_range();

    /********************************************************************
     * Setters                                                          *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief set_used_graphs
    /// \param used_graphs
    /// Set the used graphs map, this will probably not see any usage
    /////////////////////////////////////////////////////////////////////
    void set_used_graphs(const QMap<char, QCPGraph*> &used_graphs){ usedGraphs = used_graphs; }


    void set_yWindow_range(double minimum_value, double maximum_value);
    /********************************************************************
     * Initialization                                                   *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief init_plot
    /// Initialize the plot with everything that will be used in for
    /// sensor profiling
    /////////////////////////////////////////////////////////////////////
    void init_plot();
};

#endif // PLOTTER_H
