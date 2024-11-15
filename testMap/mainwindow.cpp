#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    xyPlot = m_ui->mPlot;
    xyPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    xyPlot->xAxis->setLabel("X (m)");
    xyPlot->yAxis->setLabel("Y (m)");
    xyPlot->legend->setVisible(false);
    xyPlot->legend->setFont(QFont("Helvetica", 9));

    // move bars above graphs and grid below bars:
    xyPlot->addLayer("abovemain", xyPlot->layer("main"), QCustomPlot::limAbove);
    xyPlot->addLayer("belowmain", xyPlot->layer("main"), QCustomPlot::limBelow);
    xyPlot->xAxis->grid()->setLayer("abovemain");
    xyPlot->xAxis->grid()->setPen(QPen(Qt::gray, 1, Qt::DashLine));
    xyPlot->yAxis->grid()->setLayer("abovemain");
    xyPlot->yAxis->grid()->setPen(QPen(Qt::gray, 1, Qt::DashLine));
    xyPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(xyPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

    // add the anchor labels:
    QString text;
    for (int i=0; i<ANCHORS; i++) {
        text = "A" + QString::number(i+1);
        anchorLabel[i] = new QCPItemText(xyPlot);
        anchorLabel[i]->setText(text);
        anchorLabel[i]->setFont(QFont(font().family(), 10));
        anchorLabel[i]->setVisible(false);
        anchorLabel[i]->setLayer("abovemain");
        // create arrows
        arrow[i] = new QCPItemLine(xyPlot);
        arrow[i]->setLayer("abovemain");
        arrow[i]->setVisible(false);
    }

    // create anchors points
    anchorNodes = new QCPGraph(xyPlot->xAxis, xyPlot->yAxis);
    anchorNodes->setLineStyle(QCPGraph::lsNone);
    anchorNodes->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    anchorNodes->setName("Disabled Anchors");
    anchorNodes->removeFromLegend();
    anchorNodes->setLayer("abovemain");

    // create Lines
    for(int i=0; i<ANCHORS; i++)
    {
        xyLines[i] = new QCPGraph(xyPlot->xAxis, xyPlot->yAxis);
        xyLines[i]->setPen(QPen(Qt::red, 1.5));
        xyLines[i]->setLayer("abovemain");
        xyLines[i]->removeFromLegend();
        xyCircles[i] = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
        xyCircles[i]->setLayer("abovemain");
        xyCircles[i]->removeFromLegend();
    }

    // create line 1
    xyLine1 = new QCPGraph(xyPlot->xAxis, xyPlot->yAxis);
    xyLine1->setPen(QPen(Qt::red, 1.5));
    xyLine1->setName("First Line");
    xyLine1->removeFromLegend();
    xyLine1->setLayer("abovemain");

    // create line 2
    xyLine2 = new QCPGraph(xyPlot->xAxis, xyPlot->yAxis);
    xyLine2->setPen(QPen(Qt::red, 1.5));
    xyLine2->setName("Second Line");
    xyLine2->removeFromLegend();
    xyLine2->setLayer("abovemain");

    // create polygon
    xyPolygon = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
    xyPolygon->setName("Polygon");
    xyPolygon->removeFromLegend();
    xyPolygon->setLayer("abovemain");
    xyPolygon->setPen(QPen(Qt::blue, 1, Qt::SolidLine));
    xyPolygon->setBrush(QBrush(QColor(255,255,0,75)));

    // create tag
    test6 = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
    test6->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::magenta), 9));
    test6->setLineStyle(QCPCurve::lsNone);
    test6->setName("6 anchors (1 point)");
    test6->setLayer("abovemain");

    // create tag
    test5 = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
    test5->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::red), 9));
    test5->setLineStyle(QCPCurve::lsNone);
    test5->setName("5 anchors (6 points)");
    test5->setLayer("abovemain");

    // create tag
    test4 = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
    test4->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::green), 9));
    test4->setLineStyle(QCPCurve::lsNone);
    test4->setName("4 anchors (15 points)");
    test4->setLayer("abovemain");

    // create tag
    test3 = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
    test3->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::blue), 9));
    test3->setLineStyle(QCPCurve::lsNone);
    test3->setName("3 anchors (20 points)");
    test3->setLayer("abovemain");

    // create tag
    temp = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
    temp->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::red), 9));
    temp->setLineStyle(QCPCurve::lsNone);
    temp->setName("Lateration");
    temp->setLayer("abovemain");
    temp->removeFromLegend();

    t5 = new QVector<double>;
    keys5 = new QVector<double>;
    values5 = new QVector<double>;
    t4 = new QVector<double>;
    keys4 = new QVector<double>;
    values4 = new QVector<double>;
    t3 = new QVector<double>;
    keys3 = new QVector<double>;
    values3 = new QVector<double>;

    comb3 = 0;
    comb4 = 0;
    comb5 = 0;
    comb6 = false;

    for(int cidx=0; cidx<ANCHORS; cidx++)
    {
        offset[cidx] = 0;
        test_ranges[cidx] = 0;
    }

    legendInit();
    init_surroundings();
    setAnchorCoords(xa_real, ya_real);

    QString dir = QDir::currentPath();
    loadFile(dir + "\\stationary\\a.csv");
    loadOffsetFile(dir + "\\offset_files\\5m_all.csv");
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::setAnchorCoords(double * x, double * y)
{
    for (int i=0; i<ANCHORS; i++) {
        xa[i] = x[i];
        ya[i] = y[i];
    }

    matrix_init3();
    matrix_init4();
    matrix_init5();
    matrix_init6();

    anchorNodes->data()->clear();
//    for (int i=0; i<4; i++) {
    for (int i=0; i<ANCHORS; i++) {
        anchorNodes->addData(xa[i], ya[i]);
        anchorLabel[i]->position->setCoords(xa[i], ya[i]+0.5);
        anchorLabel[i]->setVisible(false);
        arrow[i]->start->setCoords(xa[i], ya[i]);
    }
    xyPlot->xAxis->setRange(-1.0, 11.5);
    xyPlot->yAxis->setRange(-1.0, 10.5);
    xyPlot->replot();
}

void MainWindow::append_data(range_info rawDataFeed)
{
    ranges = rawDataFeed.ranges;
    enabled = rawDataFeed.anchors;
    feed = encodeEnableAnchors();

    switch (feed.totalAnchors) {
    case 3:
        // Populate b vector
        for(int i=0; i<2; i++){
            b3[feed.finalKey][i] = pow(rawDataFeed.ranges[key3[feed.finalKey][0]],2) - pow(rawDataFeed.ranges[key3[feed.finalKey][i+1]],2); // r1^2 - ri^2
            b3[feed.finalKey][i] += pow(xa[key3[feed.finalKey][i+1]],2) - pow(xa[key3[feed.finalKey][0]],2); // xi^2 + x1^2
            b3[feed.finalKey][i] += pow(ya[key3[feed.finalKey][i+1]],2) - pow(ya[key3[feed.finalKey][0]],2); // yi^2 + y1^2
        }
        // Least Square Algorithm
        for(int i=0; i<2; i++){
            X3[feed.finalKey][i] = 0;
            for(int k=0; k<2; k++){
                X3[feed.finalKey][i] += A_inv3[feed.finalKey][i][k]*b3[feed.finalKey][k]/2;
            }
        }
        break;
    case 4:
        // Populate b vector
        for(int i=0; i<3; i++){
            b4[feed.finalKey][i] = pow(rawDataFeed.ranges[key4[feed.finalKey][0]],2) - pow(rawDataFeed.ranges[key4[feed.finalKey][i+1]],2); // r1^2 - ri^2
            b4[feed.finalKey][i] += pow(xa[key4[feed.finalKey][i+1]],2) - pow(xa[key4[feed.finalKey][0]],2); // xi^2 + x1^2
            b4[feed.finalKey][i] += pow(ya[key4[feed.finalKey][i+1]],2) - pow(ya[key4[feed.finalKey][0]],2); // yi^2 + y1^2
        }
        // Least Square Algorithm
        for(int i=0; i<2; i++){
            X4[feed.finalKey][i] = 0;
            for(int k=0; k<3; k++){
                X4[feed.finalKey][i] += A_inv4[feed.finalKey][i][k]*b4[feed.finalKey][k]/2;
            }
        }
        break;
    case 5:
        // Populate b vector
        for(int i=0; i<4; i++){
            b5[feed.finalKey][i] = pow(rawDataFeed.ranges[key5[feed.finalKey][0]],2) - pow(rawDataFeed.ranges[key5[feed.finalKey][i+1]],2); // r1^2 - ri^2
            b5[feed.finalKey][i] += pow(xa[key5[feed.finalKey][i+1]],2) - pow(xa[key5[feed.finalKey][0]],2); // xi^2 + x1^2
            b5[feed.finalKey][i] += pow(ya[key5[feed.finalKey][i+1]],2) - pow(ya[key5[feed.finalKey][0]],2); // yi^2 + y1^2
        }
        // Least Square Algorithm
        for(int i=0; i<2; i++){
            X5[feed.finalKey][i] = 0;
            for(int k=0; k<4; k++){
                X5[feed.finalKey][i] += A_inv5[feed.finalKey][i][k]*b5[feed.finalKey][k]/2;
            }
        }
        break;
    case 6:
        // Populate b vector
        for(int i=0; i<5; i++){
            b6[i] = pow(rawDataFeed.ranges[0],2) - pow(rawDataFeed.ranges[i+1],2) + pow(xa[i+1],2) + pow(ya[i+1],2) - pow(xa[0],2) - pow(ya[0],2);
        }
        // Least Square Algorithm
        for(int i=0; i<2; i++){
            X6[i] = 0;
            for(int k=0; k<5; k++){
                X6[i] += A_inv6[i][k]*b6[k]/2;
            }
        }
        break;
    default:
        break;
    }
}

void MainWindow::plot_data()
{
    for(int comb=0; comb<20; comb++) {
        t3->append(comb);
        keys3->append(X3[comb][0]);
        values3->append(X3[comb][1]);
    }
    for(int comb=0; comb<15; comb++) {
        t4->append(comb);
        keys4->append(X4[comb][0]);
        values4->append(X4[comb][1]);
    }
    for(int comb=0; comb<6; comb++) {
        t5->append(comb);
        keys5->append(X5[comb][0]);
        values5->append(X5[comb][1]);
    }
    test3->addData(*t3, *keys3, *values3, true);
    test4->addData(*t4, *keys4, *values4, true);
    test5->addData(*t5, *keys5, *values5, true);
    test6->addData(X6[0], X6[1]);
    test3->setVisible(false);
    test4->setVisible(false);
    test5->setVisible(false);
    test6->setVisible(false);
    xyPlot->replot();
}

void MainWindow::init_surroundings()
{
    // create walls
    xyWall = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
    xyWall->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    xyWall->setBrush(QBrush(Qt::white));
    xyWall->removeFromLegend();
    // create column
    xyColumn = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
    xyColumn->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    xyColumn->setBrush(QBrush(QColor(240,240,240)));
    xyColumn->removeFromLegend();

     // walls
    double walls[11][2] = {{0.273, 0.576}, {2.672, 5.636}, {3.163, 5.466}, {3.182, 6.125}, {2.673, 6.226}, {2.832, 9.511}, {10.328, 9.768}, {11.113, 0}, {0.553, 0}, {0.725, 0.361}, {0.273, 0.576}};
    // column
    double column_center[2] = {6.896, 5.209};
    double column_radius = 0.2865;
    double column[101][2];

    // Plot walls
    for (int i=0; i<11; i++) {
        xyWall->addData(walls[i][0], walls[i][1]);
    }
    // Plot column
    for (int i=0; i<101; i++) {
        column[i][0] = column_center[0] + column_radius*cos((double)i*2*M_PI/100);
        column[i][1] = column_center[1] + column_radius*sin((double)i*2*M_PI/100);
        xyColumn->addData(column[i][0], column[i][1]);
    }
    xyPlot->setBackground(QColor(255,255,255));
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
    // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
    // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
    // dataIndex represents the combination key
    QString message = QString("Clicked on graph '%1' at data point #%2.").arg(plottable->name()).arg(dataIndex);
    m_ui->statusBar->showMessage(message);
    QString name = (plottable->name()).toStdString().c_str();

    xyPolygon->data()->clear();
    for(int i=0; i<ANCHORS; i++){
        enabled[i] = 0;
        arrow[i]->setVisible(false);
    }
    int group = name[0].digitValue();
//    qDebug() << "Number of anchors = " << group << ", Combination key = " << dataIndex;

    switch (group) {
        case 3:
//            qDebug() <<  key3[dataIndex][0] << key3[dataIndex][1] << key3[dataIndex][2];
            for(int i=0; i<3; i++) {
                enabled[key3[dataIndex][i]] = 1;
                arrow[key3[dataIndex][i]]->end->setCoords(X3[dataIndex][0], X3[dataIndex][1]);
                arrow[key3[dataIndex][i]]->setVisible(true);
                xyPolygon->addData(xa[key3[dataIndex][i]], ya[key3[dataIndex][i]]);
            }
            xyPolygon->addData(xa[key3[dataIndex][0]], ya[key3[dataIndex][0]]);
            xyPolygon->setVisible(true);
            break;
        case 4:
//            qDebug() <<  key4[dataIndex][0] << key4[dataIndex][1] << key4[dataIndex][2] << key4[dataIndex][3];
            for(int i=0; i<4; i++) {
                enabled[key4[dataIndex][i]] = 1;
                arrow[key4[dataIndex][i]]->end->setCoords(X4[dataIndex][0], X4[dataIndex][1]);
                arrow[key4[dataIndex][i]]->setVisible(true);
                xyPolygon->addData(xa[key4[dataIndex][i]], ya[key4[dataIndex][i]]);
            }
            xyPolygon->addData(xa[key4[dataIndex][0]], ya[key4[dataIndex][0]]);
            xyPolygon->setVisible(true);
            break;
        case 5:
//            qDebug() <<  key5[dataIndex][0] << key5[dataIndex][1] << key5[dataIndex][2] << key5[dataIndex][3] << key5[dataIndex][4];
            for(int i=0; i<5; i++) {
                enabled[key5[dataIndex][i]] = 1;
                arrow[key5[dataIndex][i]]->end->setCoords(X5[dataIndex][0], X5[dataIndex][1]);
                arrow[key5[dataIndex][i]]->setVisible(true);
                xyPolygon->addData(xa[key5[dataIndex][i]], ya[key5[dataIndex][i]]);
            }
            xyPolygon->addData(xa[key5[dataIndex][0]], ya[key5[dataIndex][0]]);
            xyPolygon->setVisible(true);
            break;
        case 6:
            for(int i=0; i<6; i++) {
                enabled[i] = 1;
                arrow[i]->end->setCoords(X6[0], X6[1]);
                arrow[i]->setVisible(true);
                xyPolygon->addData(xa[i], ya[i]);
            }
            xyPolygon->addData(xa[0], ya[0]);
            xyPolygon->setVisible(true);
            break;
        default:
            break;
    }
    xyPlot->replot();
}

void MainWindow::on_targetCheckBox_stateChanged(int arg1)
{
    targetFlag = arg1;
    temp->setVisible(targetFlag);
    xyPlot->replot();
}

void MainWindow::on_circleCheckBox_stateChanged(int arg1)
{
    circlesFlag = arg1;
    for(int i=0; i<ANCHORS; i++) {
        xyCircles[i]->setVisible(circlesFlag);
    }
    xyPlot->replot();
}

void MainWindow::on_polygonCheckBox_stateChanged(int arg1)
{
    polygonFlag = arg1;
    xyPolygon->setVisible(polygonFlag);
    xyPlot->replot();
}

void MainWindow::on_losCheckBox_stateChanged(int arg1)
{
    losFlag = arg1;
    for(int i=0; i<ANCHORS; i++) {
        arrow[i]->setVisible(enabled[i] && losFlag);
    }
    xyPlot->replot();
}

void MainWindow::on_eqCheckBox_stateChanged(int arg1)
{
    eqFlag = arg1;
    for(int i=0; i<ANCHORS; i++) {
        xyLines[i]->setVisible(eqFlag);
    }
    xyPlot->replot();
}
