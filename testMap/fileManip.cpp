#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_actionOpen_triggered()
{
    QString dir = QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), (dir + "/stationary"), tr("CSV (*.csv)"));
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
    else
    {
        QTextStream in(&file);
        QString line;
        QStringList list;
        std::string str;
        line = in.readLine();
        list = line.split(QLatin1Char(','));
        if(list.size() == ANCHORS+1)
        {
            for (int cidx = 0; cidx < ANCHORS; cidx++)
            {
                str = list[cidx+1].toStdString();
                raw_data[cidx] = std::stod(str) + 0.4;
                test_ranges[cidx] = raw_data[cidx] + offset[cidx];
//                qDebug() << test_ranges[cidx];
            }
        } else {
            qDebug() << "List size = " << list.size();
        }
        clearAll();
        test();
    }
}

//void MainWindow::on_actionOffset_triggered()
//{
//    QString dir = QDir::currentPath();
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), (dir + "/offset"), tr("CSV (*.csv)"));
//    if (!fileName.isEmpty())
//        loadOffsetFile(fileName);
//}

void MainWindow::loadOffsetFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
    else
    {
        QTextStream in(&file);
        QString line;
        QStringList list;
        std::string str;
        line = in.readLine();
        list = line.split(QLatin1Char(','));
        if(list.size() == ANCHORS)
        {
            for (int cidx = 0; cidx < ANCHORS; cidx++)
            {
                str = list[cidx].toStdString();
                offset[cidx] = std::stod(str);
                test_ranges[cidx] = raw_data[cidx] + offset[cidx];
//                qDebug() << test_ranges[cidx];
            }
        } else {
            qDebug() << "List size not expected!";
        }
        clearAll();
        test();
    }
}
