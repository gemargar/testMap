#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "qcustomplot.h"

#define ANCHORS 6
#define LENGTH 101

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct anchor2key {
    int totalAnchors;
    int finalKey;
};

struct range_info {
    double * ranges;
    bool * anchors;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void append_data(range_info rac);
    void plot_data();
    void setAnchorCoords(double * x, double * y);
    void matrix_init6();
    void matrix_init5();
    void matrix_init4();
    void matrix_init3();
    anchor2key encodeEnableAnchors();
    void init_surroundings();
    void test();
    void loadFile(const QString &fileName);
    void loadOffsetFile(const QString &fileName);
    void clearAll();
    void circles(int anchor);
    void lines(int group, int comb);
    void legendInit();

private slots:
    void on_testButton_clicked();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

    void on_comb3Button_clicked();
    void on_comb4Button_clicked();
    void on_comb5Button_clicked();
    void on_comb6Button_clicked();

    void on_targetCheckBox_stateChanged(int arg1);
    void on_circleCheckBox_stateChanged(int arg1);
    void on_polygonCheckBox_stateChanged(int arg1);
    void on_losCheckBox_stateChanged(int arg1);

    void on_actionOpen_triggered();
//    void on_actionOffset_triggered();

    void on_legendButton_clicked();

    void on_eqCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *m_ui = nullptr;
    QCustomPlot *xyPlot;
    QCPItemText *anchorLabel[ANCHORS], *nodeLabel[17];
    QCPItemLine *arrow[ANCHORS];
    QPointer<QCPGraph> anchorNodes, xyLine1, xyLine2, xyLines[ANCHORS];
    QPointer<QCPCurve> test6, test5, test4, test3, temp;
    QPointer<QCPCurve> xyWall, xyColumn, xyLegend, xyPolygon, xyCircles[ANCHORS];
    QString text;

    QVector<double> *keys5, *values5, *t5;
    QVector<double> *keys4, *values4, *t4;
    QVector<double> *keys3, *values3, *t3;

//    int N = 3;
//    int n = 0;
    int key3[20][3];
    int key4[15][4];
    int key5[6][5];
    int comb3, comb4, comb5;
    bool comb6;

    anchor2key feed;
    range_info rawDataFeed;

    double * ranges;
    double A6[5][2], A_inv6[2][5], b6[5], X6[2]; // sets of 6 out of 6 = 1 combination
    double A5[6][4][2], A_inv5[6][2][4], b5[6][4], X5[6][2]; // sets of 5 out of 6 = 6 combinations
    double A4[15][3][2], A_inv4[15][2][3], b4[15][3], X4[15][2]; // sets of 4 out of 6 = 15 combinations
    double A3[20][2][2], A_inv3[20][2][2], b3[20][2], X3[20][2]; // sets of 3 out of 6 = 20 combinations

    double xa[ANCHORS];
    double ya[ANCHORS];
    double x_circle[LENGTH], y_circle[LENGTH];
    double x_line[LENGTH], y_line1[LENGTH], y_line2[LENGTH];

    bool * enabled;
    bool nodesFlag = false;
    bool testFlag = false;
    bool targetFlag = true;
    bool losFlag = true;
    bool circlesFlag = true;
    bool polygonFlag = true;
    bool eqFlag = true;

    double raw_data[ANCHORS], test_ranges[ANCHORS];
    double offset[ANCHORS];
    double xa_real[ANCHORS] = {6.293, 10.916, 10.519, 6.8, 2.75, 1.387};
    double ya_real[ANCHORS] = {0, 2.452, 7.396, 9.648, 7.814, 2.925};
    bool test_enabled[ANCHORS] = {1,1,1,1,1,1};
};

#endif // MAINWIDOW_H
