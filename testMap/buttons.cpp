#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_comb3Button_clicked()
{
    xyPolygon->data()->clear();
    temp->data()->clear();
    for(int i=0; i<ANCHORS; i++) {
        enabled[i] = 0;
        arrow[i]->setVisible(false);
        xyCircles[i]->data()->clear();
        xyLines[i]->data()->clear();
    }
    if(comb3==-1) {
        comb3=0;
        m_ui->comb3Button->setText("3 Anchors");
        m_ui->comb4Button->setEnabled(true);
        m_ui->comb5Button->setEnabled(true);
        m_ui->comb6Button->setEnabled(true);
        m_ui->testButton->setEnabled(true);
    } else {
        m_ui->comb4Button->setEnabled(false);
        m_ui->comb5Button->setEnabled(false);
        m_ui->comb6Button->setEnabled(false);
        m_ui->testButton->setEnabled(false);
        for(int i=0; i<3; i++) {
            enabled[key3[comb3][i]] = 1;
            xyPolygon->addData(xa[key3[comb3][i]], ya[key3[comb3][i]]);
            arrow[key3[comb3][i]]->end->setCoords(X3[comb3][0], X3[comb3][1]);
            arrow[key3[comb3][i]]->setVisible(losFlag);
            circles(key3[comb3][i]);
            xyCircles[key3[comb3][i]]->setVisible(circlesFlag);
        }
        lines(3, comb3);
        xyPolygon->addData(xa[key3[comb3][0]], ya[key3[comb3][0]]);
        xyPolygon->setVisible(polygonFlag);
        text = QString::number(key3[comb3][0]+1) + QString::number(key3[comb3][1]+1) + QString::number(key3[comb3][2]+1);
        m_ui->comb3Button->setText(text);
        temp->addData(X3[comb3][0],X3[comb3][1]);
        temp->setVisible(targetFlag);
        if(comb3==19) {
            comb3=-1;
        } else {
            comb3++;
        }
    }
    xyPlot->replot();
}

void MainWindow::on_comb4Button_clicked()
{
    xyPolygon->data()->clear();
    temp->data()->clear();
    for(int i=0; i<ANCHORS; i++){
        enabled[i] = 0;
        arrow[i]->setVisible(false);
        xyCircles[i]->data()->clear();
        xyLines[i]->data()->clear();
    }
    if(comb4==-1) {
        comb4=0;
        m_ui->comb4Button->setText("4 Anchors");
        m_ui->comb3Button->setEnabled(true);
        m_ui->comb5Button->setEnabled(true);
        m_ui->comb6Button->setEnabled(true);
        m_ui->testButton->setEnabled(true);
    } else {
        m_ui->comb3Button->setEnabled(false);
        m_ui->comb5Button->setEnabled(false);
        m_ui->comb6Button->setEnabled(false);
        m_ui->testButton->setEnabled(false);
        for(int i=0; i<4; i++) {
            enabled[key4[comb4][i]] = 1;
            xyPolygon->addData(xa[key4[comb4][i]], ya[key4[comb4][i]]);
            arrow[key4[comb4][i]]->end->setCoords(X4[comb4][0], X4[comb4][1]);
            arrow[key4[comb4][i]]->setVisible(losFlag);
            circles(key4[comb4][i]);
            xyCircles[key4[comb4][i]]->setVisible(circlesFlag);
        }
        lines(4, comb4);
        xyPolygon->addData(xa[key4[comb4][0]], ya[key4[comb4][0]]);
        xyPolygon->setVisible(polygonFlag);
        text = QString::number(key4[comb4][0]+1) + QString::number(key4[comb4][1]+1) + QString::number(key4[comb4][2]+1) + QString::number(key4[comb4][3]+1);
        m_ui->comb4Button->setText(text);
        temp->addData(X4[comb4][0],X4[comb4][1]);
        temp->setVisible(targetFlag);
        xyPlot->replot();
        if(comb4==14) {
            comb4=-1;
        } else {
            comb4++;
        }
    }
    xyPlot->replot();
}

void MainWindow::on_comb5Button_clicked()
{
    xyPolygon->data()->clear();
    temp->data()->clear();
    for(int i=0; i<ANCHORS; i++){
        enabled[i] = 0;
        arrow[i]->setVisible(false);
        xyCircles[i]->data()->clear();
        xyLines[i]->data()->clear();
    }
    if(comb5==-1) {
        comb5=0;
        m_ui->comb5Button->setText("5 Anchors");
        m_ui->comb3Button->setEnabled(true);
        m_ui->comb4Button->setEnabled(true);
        m_ui->comb6Button->setEnabled(true);
        m_ui->testButton->setEnabled(true);
    } else {
        m_ui->comb3Button->setEnabled(false);
        m_ui->comb4Button->setEnabled(false);
        m_ui->comb6Button->setEnabled(false);
        m_ui->testButton->setEnabled(false);
        for(int i=0; i<5; i++) {
            enabled[key5[comb5][i]] = 1;
            xyPolygon->addData(xa[key5[comb5][i]], ya[key5[comb5][i]]);
            arrow[key5[comb5][i]]->end->setCoords(X5[comb5][0], X5[comb5][1]);
            arrow[key5[comb5][i]]->setVisible(losFlag);
            circles(key5[comb5][i]);
            xyCircles[key5[comb5][i]]->setVisible(circlesFlag);
        }
        lines(5, comb5);
        xyPolygon->addData(xa[key5[comb5][0]], ya[key5[comb5][0]]);
        xyPolygon->setVisible(polygonFlag);
        text = QString::number(key5[comb5][0]+1) + QString::number(key5[comb5][1]+1) + QString::number(key5[comb5][2]+1) + QString::number(key5[comb5][3]+1) + QString::number(key5[comb5][4]+1);
        m_ui->comb5Button->setText(text);
        temp->addData(X5[comb5][0],X5[comb5][1]);
        temp->setVisible(targetFlag);
        if(comb5==5) {
            comb5=-1;
        } else {
            comb5++;
        }
    }
    xyPlot->replot();
}

void MainWindow::on_comb6Button_clicked()
{
    comb6 = !comb6;
    xyPolygon->data()->clear();
    temp->data()->clear();
    for(int i=0; i<ANCHORS; i++){
        enabled[i] = 0;
        arrow[i]->setVisible(false);
        xyCircles[i]->data()->clear();
        xyLines[i]->data()->clear();
    }
    if(!comb6) {
        m_ui->comb6Button->setText("6 Anchors");
        m_ui->comb3Button->setEnabled(true);
        m_ui->comb4Button->setEnabled(true);
        m_ui->comb5Button->setEnabled(true);
        m_ui->testButton->setEnabled(true);
    } else {
        m_ui->comb3Button->setEnabled(false);
        m_ui->comb4Button->setEnabled(false);
        m_ui->comb5Button->setEnabled(false);
        m_ui->testButton->setEnabled(false);
        xyPolygon->data()->clear();
        temp->data()->clear();
        for(int i=0; i<6; i++) {
            enabled[i] = 1;
            xyPolygon->addData(xa[i], ya[i]);
            arrow[i]->end->setCoords(X6[0], X6[1]);
            arrow[i]->setVisible(losFlag);
            circles(i);
            xyCircles[i]->setVisible(circlesFlag);
        }
        lines(6, 0);
        xyPolygon->addData(xa[0], ya[0]);
        xyPolygon->setVisible(polygonFlag);
        m_ui->comb6Button->setText("123456");
        temp->addData(X6[0],X6[1]);
        temp->setVisible(targetFlag);
    }
    xyPlot->replot();
}

void MainWindow::on_testButton_clicked()
{
    testFlag = !testFlag;
    test3->setVisible(testFlag);
    test4->setVisible(testFlag);
    test5->setVisible(testFlag);
    test6->setVisible(testFlag);
    m_ui->comb3Button->setEnabled(!testFlag);
    m_ui->comb4Button->setEnabled(!testFlag);
    m_ui->comb5Button->setEnabled(!testFlag);
    m_ui->comb6Button->setEnabled(!testFlag);
    xyPolygon->setVisible(false);
    for(int i=0; i<ANCHORS; i++){
        arrow[i]->setVisible(false);
    }
    xyPlot->legend->setVisible(testFlag);
    xyPlot->replot();
    if(testFlag)
        m_ui->testButton->setText("Hide");
    else
        m_ui->testButton->setText("Show");
}

void MainWindow::clearAll()
{
    for(int comb=0; comb<20; comb++) {
        t3->clear();
        keys3->clear();
        values3->clear();
    }
    for(int comb=0; comb<15; comb++) {
        t4->clear();
        keys4->clear();
        values4->clear();
    }
    for(int comb=0; comb<6; comb++) {
        t5->clear();
        keys5->clear();
        values5->clear();
    }
    xyPolygon->data()->clear();
    test6->data()->clear();
    test5->data()->clear();
    test4->data()->clear();
    test3->data()->clear();
    m_ui->testButton->setText("Test");
    for(int i=0; i<ANCHORS; i++){
        arrow[i]->setVisible(false);
        xyLines[i]->data()->clear();
        xyCircles[i]->data()->clear();
    }
    xyPlot->replot();
}

void MainWindow::test()
{
    rawDataFeed.ranges = test_ranges;

    // 6 anchors
    rawDataFeed.anchors = test_enabled;
    append_data(rawDataFeed);

    // 5 anchors
    for(int i=0; i<6; i++) {
        test_enabled[i] = 0;
        rawDataFeed.anchors = test_enabled;
        append_data(rawDataFeed);
        test_enabled[i] = 1;
    }

    // 4 anchors
    for(int i=0; i<6; i++) {
        test_enabled[i] = 0;
        for(int j=i+1; j<6; j++) {
            test_enabled[j] = 0;
            rawDataFeed.anchors = test_enabled;
            append_data(rawDataFeed);
            test_enabled[j] = 1;
        }
        test_enabled[i] = 1;
    }

    // 3 anchors
    for(int i=0; i<6; i++) {
        test_enabled[i] = 0;
        for(int j=i+1; j<6; j++) {
            test_enabled[j] = 0;
            for(int k=j+1; k<6; k++) {
                test_enabled[k] = 0;
                rawDataFeed.anchors = test_enabled;
                append_data(rawDataFeed);
                test_enabled[k] = 1;
            }
            test_enabled[j] = 1;
        }
        test_enabled[i] = 1;
    }
    plot_data();
}

void MainWindow::circles(int anchor)
{
    for(int i=0; i<LENGTH; i++)
    {
        x_circle[i] = xa_real[anchor] + ranges[anchor]*cos(i*2*M_PI/(LENGTH-1));
        y_circle[i] = ya_real[anchor] + ranges[anchor]*sin(i*2*M_PI/(LENGTH-1));
        xyCircles[anchor]->addData(x_circle[i],y_circle[i]);
    }
}

void MainWindow::lines(int group, int comb)
{
    double x,y;
    for(int i=0; i<ANCHORS; i++) {
        xyLines[i]->data()->clear();
    }

    switch(group) {
    case(3) :
        for(int i=0; i<LENGTH; i++)
        {
            x = -5 + i*20/(LENGTH-1);
            for(int j=0; j<2; j++) {
                y = (b3[comb][j] - 2*A3[comb][j][0]*x)/(2*A3[comb][j][1]);
                xyLines[j]->addData(x,y);
            }
        }
        break;
    case(4) :
        for(int i=0; i<LENGTH; i++)
        {
            x = -15 + i*120/(LENGTH-1);
            for(int j=0; j<3; j++) {
                y = (b4[comb][j] - 2*A4[comb][j][0]*x)/(2*A4[comb][j][1]);
                xyLines[j]->addData(x,y);
            }
        }
        break;
    case(5) :
        for(int i=0; i<LENGTH; i++)
        {
            x = -5 + i*20/(LENGTH-1);
            for(int j=0; j<4; j++) {
                y = (b5[comb][j] - 2*A5[comb][j][0]*x)/(2*A5[comb][j][1]);
                xyLines[j]->addData(x,y);
            }
        }
        break;
    case(6) :
        for(int i=0; i<LENGTH; i++)
        {
            x = -5 + i*20/(LENGTH-1);
            for(int j=0; j<5; j++) {
                y = (b6[j] - 2*A6[j][0]*x)/(2*A6[j][1]);
                xyLines[j]->addData(x,y);
            }
        }
        break;
    default :
        break;
    }
}

