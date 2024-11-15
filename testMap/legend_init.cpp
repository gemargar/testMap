#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::legendInit()
{
    // ground truth reference points
    double alpha[2] = {8.03, 1};
    double beta[2] = {2.783, 1};
    double gamma[2] = {2.783, 3.75};
    double delta[2] = {3.783, 3.75};
    double epsilon[2] = {3.783, 6.25};
    double zeta[2] = {3.783, 8.75};
    double eta[2] = {8.03, 8.75};
    double eta2[2] = {8.03, 9.14};
    double eta3[2] = {10.378, 9.14};
    double theta[2] = {8.03, 6.25};
    double theta2[2] = {10.61, 6.25};
    double giota[2] = {8.03, 3.75};
    double giota2[2] = {10.812, 3.75};
    double x1[2] = {6.783, 5.75};
    double x2[2] = {6.908, 5.75};
    double x3[2] = {6.658, 5.75};
    double x4[2] = {6.533, 5.75};

    // create real path graph
    xyLegend = new QCPCurve(xyPlot->xAxis, xyPlot->yAxis);
    xyLegend->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, QPen(Qt::black, 1.5), QBrush(Qt::white), 15));
    xyLegend->setLineStyle(QCPCurve::lsNone);
    xyLegend->setLayer("abovemain");
    xyLegend->removeFromLegend();
    xyLegend->setVisible(false);

    xyLegend->addData(alpha[0], alpha[1]);
    xyLegend->addData(beta[0], beta[1]);
    xyLegend->addData(gamma[0], gamma[1]);
    xyLegend->addData(delta[0], delta[1]);
    xyLegend->addData(epsilon[0], epsilon[1]);
    xyLegend->addData(zeta[0], zeta[1]);
    xyLegend->addData(eta[0], eta[1]);
    xyLegend->addData(eta2[0], eta2[1]);
    xyLegend->addData(eta3[0], eta3[1]);
    xyLegend->addData(theta[0], theta[1]);
    xyLegend->addData(theta2[0], theta2[1]);
    xyLegend->addData(giota[0], giota[1]);
    xyLegend->addData(giota2[0], giota2[1]);
    xyLegend->addData(x1[0], x1[1]);
    xyLegend->addData(x2[0], x2[1]);
    xyLegend->addData(x3[0], x3[1]);
    xyLegend->addData(x4[0], x4[1]);

    for (int i=0; i<17; i++) {
        nodeLabel[i] = new QCPItemText(xyPlot);
        nodeLabel[i]->setFont(QFont(font().family(), 9));
        nodeLabel[i]->setLayer("abovemain");
        nodeLabel[i]->setVisible(false);
    }

    nodeLabel[0]->setText("A");
    nodeLabel[1]->setText("B");
    nodeLabel[2]->setText("C");
    nodeLabel[3]->setText("D");
    nodeLabel[4]->setText("E");
    nodeLabel[5]->setText("F");
    nodeLabel[6]->setText("G");
    nodeLabel[7]->setText("G2");
    nodeLabel[8]->setText("G3");
    nodeLabel[9]->setText("H");
    nodeLabel[10]->setText("H2");
    nodeLabel[11]->setText("I");
    nodeLabel[12]->setText("I2");
    nodeLabel[13]->setText("X1");
    nodeLabel[14]->setText("X2");
    nodeLabel[15]->setText("X3");
    nodeLabel[16]->setText("X4");

    nodeLabel[0]->position->setCoords(alpha[0], alpha[1]);
    nodeLabel[1]->position->setCoords(beta[0], beta[1]);
    nodeLabel[2]->position->setCoords(gamma[0], gamma[1]);
    nodeLabel[3]->position->setCoords(delta[0], delta[1]);
    nodeLabel[4]->position->setCoords(epsilon[0], epsilon[1]);
    nodeLabel[5]->position->setCoords(zeta[0], zeta[1]);
    nodeLabel[6]->position->setCoords(eta[0], eta[1]);
    nodeLabel[7]->position->setCoords(eta2[0], eta2[1]);
    nodeLabel[8]->position->setCoords(eta3[0], eta3[1]);
    nodeLabel[9]->position->setCoords(theta[0], theta[1]);
    nodeLabel[10]->position->setCoords(theta2[0], theta2[1]);
    nodeLabel[11]->position->setCoords(giota[0], giota[1]);
    nodeLabel[12]->position->setCoords(giota2[0], giota2[1]);
    nodeLabel[13]->position->setCoords(x1[0], x1[1]);
    nodeLabel[14]->position->setCoords(x2[0], x2[1]);
    nodeLabel[15]->position->setCoords(x3[0], x3[1]);
    nodeLabel[16]->position->setCoords(x4[0], x4[1]);

//    qDebug() << "The end";
}

void MainWindow::on_legendButton_clicked()
{
    nodesFlag = !nodesFlag;
    xyLegend->setVisible(nodesFlag);
    for (int i=0; i<17; i++) {
        nodeLabel[i]->setVisible(nodesFlag);
    }
    if(nodesFlag) {
        m_ui->legendButton->setText("Hide Nodes");
    } else {
        m_ui->legendButton->setText("Show Nodes");
    }
    xyPlot->replot();
}
