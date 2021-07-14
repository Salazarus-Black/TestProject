#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QMap<QString,QVector<int>> Data;

void MainWindow::on_OpenFileButton_clicked()
{

    QString FileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath(), "*.txt");
    ui->FilePath->setText(FileName);
    QFile file(FileName);

    ui->comboBox->clear();
    ui->widget->clearGraphs();
    Data.clear();

    QVector<int>TemporaryDataMass;
    int kofic;
    QString TemporaryData,LineTest,LineTest1,TemporaryData1,CorrectSignal             ,QWer;
    QStringList list;
    int NumPac;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly))){

        while(!file.atEnd()){

            LineTest = file.readLine();
            LineTest1 = LineTest.left(LineTest.lastIndexOf(" "));
            CorrectSignal = LineTest.right(6).left(4);
            TemporaryData1 = LineTest1.left(LineTest1.indexOf("#"));

            list  = LineTest1.split(" ");
            list.takeFirst();
            list.takeFirst();
            NumPac = list.takeFirst().toInt(nullptr,16);
            kofic = list.takeFirst().toInt(nullptr,16);
            if(CorrectSignal=="True"){
                for(auto &i :list){
                    TemporaryDataMass.push_back(kofic*i.toInt(nullptr,16));
                }

                if(NumPac==0){
                    TemporaryData = TemporaryData1;
                }

                for(auto i : TemporaryDataMass){
                    Data[TemporaryData].push_back(i);
                }
                TemporaryDataMass.clear();
            }



        QWer+="CorrectSignal "+CorrectSignal+" \n";
        QWer+="\n\nLineTest "+LineTest;
        QWer+="\n\nLineTest1 "+LineTest1;
        QWer+="\n\nTemporaryData1 "+TemporaryData1;
        QWer+="\n\nNumPac "+QString::number(NumPac);
        QWer+="\n\nTemporaryData "+TemporaryData+"\n\nlist ";

        for(auto q : list){
            QWer+=q+" ";
        }
        QWer+="\n\n ";


        for(auto &i : Data.values()){
            QWer+="Data.values ";
            for(const auto &q : i){
                QWer+=" "+QString::number(q);
            }
               QWer+="\n\n";
        }
        QWer += "\n";

        }
        file.close();

    }
    QWer+="comboBox ";
    for(auto &i : Data.keys()){

        ui->comboBox->addItem(i);
        QWer+=i+" ";
    }
    ui->textBrowser_2->setText(QWer);
}


void MainWindow::on_DrawGraph_clicked()
{
    QVector<double> SelectedData,SelectedDataTime;
    double counter = 0, MaxElement = 0;
    QString SelectedTime = ui->comboBox->currentText();//для считки что выбрано в combobox
    for (auto i : Data.keys()){
        if(SelectedTime ==i){
            for(auto q : Data[i]){
                SelectedData.push_back(q);
                SelectedDataTime.push_back(counter);
                counter++;
                if(q>MaxElement){
                    MaxElement=q;
                }
            }
        }
    }
    ui->widget->clearGraphs();
    ui->widget->xAxis->setRange(0,SelectedDataTime.size()+5);
    ui->widget->yAxis->setRange(0,MaxElement+5);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(SelectedDataTime,SelectedData);
    ui->widget->replot();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &SelectedTime)
{
    QVector<double> SelectedData,SelectedDataTime;
    double counter = 0, MaxElement = 0;
    //QString SelectedTime = ui->comboBox->currentText();//для считки что выбрано в combobox
    for (auto i : Data.keys()){
        if(SelectedTime ==i){
            for(auto q : Data[i]){
                SelectedData.push_back(q);
                SelectedDataTime.push_back(counter);
                counter++;
                if(q>MaxElement){
                    MaxElement=q;
                }
            }
        }
    }
    ui->widget->clearGraphs();
    ui->widget->xAxis->setRange(0,SelectedDataTime.size()+5);
    ui->widget->yAxis->setRange(0,MaxElement+5);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(SelectedDataTime,SelectedData);
    ui->widget->replot();
}

