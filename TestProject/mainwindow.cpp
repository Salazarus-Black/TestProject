#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QFileDialog>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_OpenFileButton_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath(), "*.txt");
    ui->FilePath->setText(FileName);
    QFile file(FileName);

    ui->comboBox->clear();
    QMap<QString,QVector<int>> Data;
    QVector<int>TemporaryDataMass;
    int kofic;
    QString TemporaryData;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly))){

        while(!file.atEnd()){
            QString TemporaryData1 = file.readLine(8);
            file.readLine(8);
            QString NumPac = file.readLine(3);
            //int NumPac = (file.readLine(3)).toInt(nullptr,16);
            file.readLine(2);
            QTextStream Line (file.readLine('  '));//Именно здесь ошибка, тк я не знаю как ограничить считывание до двух пробелов(идут передtrue/false)
            while(!Line.atEnd()){                   //А в нынешней реализации команда преаброзует '  ' в цифровое значение и считывает до него,
                TemporaryDataMass.push_back((Line.readLine(3)).toInt(nullptr,16));//что является ошибочным, хоть программа и запускается и что-то отрабатывает.
                Line.readLine(2);
            }
            file.readLine();
            if(NumPac=="00"){
                TemporaryData = TemporaryData1;
            }

            for(auto i : TemporaryDataMass){
                Data[TemporaryData].push_back(i);
            }

        }
        for(const auto &i : Data.keys()){

            ui->comboBox->addItem(i);
        }
        QString QWer;
        for(auto i : Data.values()){

            QWer+=QString::number(i[0])+" "+QString::number(i[1])+" "+QString::number(i[2])+"\n";
        }
        ui->textBrowser_2->setText(QWer);
        file.close();
    }
}

