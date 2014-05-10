#include "plotter.h"
#include "mainwindow.h"

Plotter::Plotter(MainWindow *mainwindowin, QObject *parent) :
    QObject(parent)
{
    mainwindow = mainwindowin;
    mainPlot = mainwindowin->get_qplot();
    clipboard = QApplication::clipboard();
    init_plot();
}

Plotter::~Plotter(){
    delete mainPlot;
    delete mainwindow;
}

/********************************************************************
 * Helper Methods                                                   *
 *******************************************************************/

void Plotter::add_graph_data(QString graph_name,
                             const QVector<double> &xData,
                             const QVector<double> &yData){
    if(usedGraphs.contains(graph_name))
        usedGraphs.value(graph_name)->addData(xData,yData);
    set_xWindow_range(dataPoints);
    if(autoRangeScale){
        auto_find_yAxis_range();
        mainPlot->yAxis->rescale(true);
    }
}

void Plotter::add_graph_data(QString graph_name, double xData, double yData){
    add_graph_data(graph_name, QVector<double>() << xData, QVector<double>() << yData);
}

void Plotter::auto_find_yAxis_range(){
    QMap<double, QCPData>::const_iterator dataIterator;
    QMapIterator <QString, QCPGraph*> graphIterator(usedGraphs);
    bool allocated = false;
    quint32 i = 0;

    while(graphIterator.hasNext()){ // Cycle through graphs
        graphIterator.next();
        dataIterator = graphIterator.value()->data()->constEnd();
        // Iterate through data for current graph from end until either beginning or
        // number of data points has been reached, from this list find the min and max
        // to auto set yAxis range
        while (dataIterator != graphIterator.value()->data()->constBegin() && i < dataPoints) {
            if(!allocated){
                allocated = true;
                minimumValue = dataIterator.value().value;
                maximumValue = minimumValue;
            }

            if(minimumValue > dataIterator.value().value)
                minimumValue = dataIterator.value().value;

            if(maximumValue < dataIterator.value().value)
                maximumValue = dataIterator.value().value;

            ++i;
            --dataIterator;
        }
    }

    set_yWindow_range(minimumValue, maximumValue);
}

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
    usedGraphs.value(graph_name)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    usedGraphs.value(graph_name)->setLineStyle(QCPGraph::lsLine);
    usedGraphs.value(graph_name)->setName(graph_name);
}

void Plotter::hide_graph(QString graph_name){
    usedGraphs.value(graph_name)->setVisible(false);
    usedGraphs.value(graph_name)->removeFromLegend();
}

void Plotter::remove_all_graphs(){
    QMapIterator <QString, QCPGraph*> i(usedGraphs);
    while(i.hasNext()){
        i.next();
        mainPlot->removeGraph(i.value());
    }
}

void Plotter::remove_graph(QString graph_name){
    if(usedGraphs.contains(graph_name)){
        mainPlot->removeGraph(usedGraphs.value(graph_name));
        usedGraphs.remove(graph_name);
    }
}

void Plotter::reset_plot(){
    clear_all_graph_data();
    mainPlot->replot();
}

void Plotter::show_graph(QString graph_name){
    usedGraphs.value(graph_name)->setVisible(true);
    usedGraphs.value(graph_name)->addToLegend();
}

/********************************************************************
 * Setters                                                          *
 *******************************************************************/

void Plotter::set_graph_data(QString graph_name, const QVector<double> &xData, const QVector<double> &yData){
    if(usedGraphs.contains(graph_name))
        usedGraphs.value(graph_name)->setData(xData,yData);
}

void Plotter::set_graph_pen(QString graph_name, QPen pen){
    if(usedGraphs.contains(graph_name))
        usedGraphs.value(graph_name)->setPen(pen);
}

void Plotter::set_graph_name(QString graph_name, QString new_graph_name){
    if(usedGraphs.contains(graph_name))
        usedGraphs.value(graph_name)->setName(new_graph_name);
}

void Plotter::set_title(QString title){
    currentTitle=title;
    mainPlot->plotLayout()->removeAt(0);
    mainPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(mainPlot, title));
}


void Plotter::set_xAxis_range(double lower, double upper){
    mainPlot->xAxis->setRangeLower(lower);
    mainPlot->xAxis->setRangeUpper(upper);
}

void Plotter::set_xAxis_scale(int scale){
    xScale = scale;

    if(yScale == 0)
        refPlot->xAxis = mainPlot->xAxis;

    mainPlot->xAxis->setScaleRatio(refPlot->yAxis,scale);
}

void Plotter::set_xWindow_range(quint32 data_points){
    dataPoints = data_points;

    mainPlot->xAxis->setRange(usedGraphs.begin().value()->data()->end().key()-dataPoints,//Max - #data points (min)
                              usedGraphs.begin().value()->data()->end().key()); //Max
}

void Plotter::set_yAxis_range(double lower, double upper){
    mainPlot->yAxis->setRangeLower(lower);
    mainPlot->yAxis->setRangeUpper(upper);
}

void Plotter::set_yAxis_scale(int scale){
    yScale = scale;

    if(xScale == 10)
        refPlot->yAxis = mainPlot->yAxis;

    mainPlot->yAxis->setScaleRatio(refPlot->xAxis,scale);
}

void Plotter::set_yWindow_range(double minimum_value, double maximum_value){
    mainPlot->yAxis->setRange(minimum_value, maximum_value);
}

/********************************************************************
 * Slots                                                            *
 *******************************************************************/

void Plotter::on_axis_label_double_click(QCPAxis *axis, QCPAxis::SelectablePart part){
    // Set an axis label by double clicking on it
    if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
    {
        bool ok;
        QString newLabel = QInputDialog::getText(mainwindow, "Rename Axis", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
        if (ok)
        {
            axis->setLabel(newLabel);
            mainPlot->replot();
        }
    }
}

void Plotter::on_context_menu_request(QPoint pos){
    QMenu *menu = new QMenu(mainwindow);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    if (mainPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
    {
        menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
        menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
        menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
        menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
        menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
    } else  // general context menu on graphs requested
    {
        menu->addAction("Copy as Image", this, SLOT(on_copy_plot_image()));
        if (mainPlot->selectedGraphs().size() > 0)
            menu->addAction("Copy selected graph", this, SLOT(on_copy_graph_data()));
    }

    menu->popup(mainPlot->mapToGlobal(pos));
}

void Plotter::on_copy_graph_data(){
    QString output; // String to be placed in clipboard
    QCPGraph * selected;    // Used to determine which graph is selected
    QMapIterator <QString, QCPGraph*> i(usedGraphs);
    QMap<double, QCPData>::const_iterator dataIterator;

    // Make darn sure that exactly one graph is selected
    if (mainPlot->selectedGraphs().size() == 1){
        // Get the graph
        selected = mainPlot->selectedGraphs().first();

        // Determine which one it is, and add to output string
        while(i.hasNext()){
            i.next();
            if(selected == i.value()){  // Figure out which graph was selected
                dataIterator = i.value()->data()->constBegin();
                while (dataIterator != i.value()->data()->constEnd()){    // Copy data to output string
                    output += QString::number(dataIterator.value().key) + "\t" + QString::number(dataIterator.value().value) + "\n";
                    ++dataIterator;
                }
                break;
            }
        }

        clipboard->setText(output);
        emit copy_graph_data();
    }
}

void Plotter::on_copy_plot_image(){
    clipboard->setPixmap(mainPlot->toPixmap(800,600,1));
    emit copy_plot_image();
}

void Plotter::on_graph_clicked(QCPAbstractPlottable *plottable){
    emit graph_clicked(plottable);
}

void Plotter::on_legend_double_click(QCPLegend *legend, QCPAbstractLegendItem *item){
    // Rename a graph by double clicking on its legend item
    Q_UNUSED(legend)
    if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        bool ok;
        QString newName = QInputDialog::getText(mainwindow, "Rename Graph", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
        if (ok)
        {
            emit legend_double_clicked(plItem);
            plItem->plottable()->setName(newName);
            mainPlot->replot();
        }
    }
}

void Plotter::on_mouse_press(){
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (mainPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        mainPlot->axisRect()->setRangeDrag(mainPlot->xAxis->orientation());
    else if (mainPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        mainPlot->axisRect()->setRangeDrag(mainPlot->yAxis->orientation());
    else
        mainPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void Plotter::on_mouse_wheel(){
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (mainPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        mainPlot->axisRect()->setRangeZoom(mainPlot->xAxis->orientation());
    else if (mainPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        mainPlot->axisRect()->setRangeZoom(mainPlot->yAxis->orientation());
    else
        mainPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void Plotter::on_move_legend(){
    if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            mainPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
            mainPlot->replot();
        }
    }
}

void Plotter::on_selection_changed(){
    /********************************************************************
     * normally, axis base line, axis tick labels and axis labels are
     * selectable separately, but we want the user only to be able to
     * select the axis as a whole, so we tie the selected states of the
     * tick labels and the axis base line together. However, the axis
     * label shall be selectable individually.
     *
     * The selection state of the left and right axes shall be
     * synchronized as well as the state of the bottom and top axes.
     *
     * Further, we want to synchronize the selection of the graphs with
     * the selection state of the respective legend item belonging to
     * that graph. So the user can select a graph by either clicking on
     * the graph itself or on its legend item.
     *******************************************************************/

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (mainPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || mainPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            mainPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || mainPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        mainPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        mainPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (mainPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || mainPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            mainPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || mainPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        mainPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        mainPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i=0; i<mainPlot->graphCount(); ++i)
    {
        QCPGraph *graph = mainPlot->graph(i);
        QCPPlottableLegendItem *item = mainPlot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelected(true);
        }
    }
}

void Plotter::on_title_double_click(QMouseEvent *event, QCPPlotTitle *title){
    Q_UNUSED(event)
    // Set the plot title by double clicking on it
    bool ok;
    QString newTitle = QInputDialog::getText(mainwindow, "Rename Title", "New plot title:", QLineEdit::Normal, title->text(), &ok);
    if (ok)
    {
        title->setText(newTitle);
        mainPlot->replot();
    }
}

/********************************************************************
 * Initializer                                                      *
 *******************************************************************/

void Plotter::init_plot(){
    mainPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    mainPlot->legend->setVisible(true);
    QFont legendFont = mainwindow->font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    mainPlot->legend->setFont(legendFont);
    mainPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    mainPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop |Qt::AlignLeft);

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    mainPlot->xAxis2->setVisible(true);
    mainPlot->xAxis2->setTickLabels(false);
    mainPlot->yAxis2->setVisible(true);
    mainPlot->yAxis2->setTickLabels(false);

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(mainPlot, SIGNAL(selectionChangedByUser()), this, SLOT(on_selection_changed()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(mainPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(on_mouse_press()));
    connect(mainPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(on_mouse_wheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(mainPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), mainPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(mainPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), mainPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(mainPlot, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(on_title_double_click(QMouseEvent*,QCPPlotTitle*)));
    connect(mainPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(on_axis_label_double_click(QCPAxis*,QCPAxis::SelectablePart)));
    connect(mainPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(on_legend_double_click(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(mainPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(on_graph_clicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    mainPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mainPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_context_menu_request(QPoint)));

    // Note: we could have also just called mainPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    mainPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                              QCP::iSelectLegend | QCP::iSelectPlottables);
    mainPlot->axisRect()->setupFullAxesBox();
    mainPlot->legend->setSelectedFont(legendFont);
    mainPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    // Set axis display type
    mainPlot->xAxis->setDateTimeFormat("mm:ss:zzz");
    mainPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);

    mainPlot->plotLayout()->insertRow(0);
    set_title("Live Data");

    set_xAxis1_label("Time (sec)");
    set_yAxis1_label("Data");

    dataPoints = 10;
    autoRangeScale = true;

    // Used for scaling
    refPlot = mainPlot;
}
