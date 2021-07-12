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
    QString TemporaryData,LineTest,LineTest1,TemporaryData1             ,QWer;
    QStringList list;
    int NumPac;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly))){

        while(!file.atEnd()){
            //QString TemporaryData1 = file.readLine(8);
            //file.readLine(8);
            //QString NumPac = file.readLine(3);

           // int NumPac = (file.readLine(3)).toInt(nullptr,16);
           // file.readLine(2);
            LineTest = file.readLine();
            LineTest1 = LineTest.left(LineTest.lastIndexOf(" "));
            TemporaryData1 = LineTest1.left(LineTest1.indexOf("#"));



            //QTextStream Line (&LineTest1);//Именно здесь ошибка, тк я не знаю как ограничить считывание до двух пробелов(идут передtrue/false)

            //QTextStream Line (file.readLine('  '));//Именно здесь ошибка, тк я не знаю как ограничить считывание до двух пробелов(идут передtrue/false)
            //while(!Line.atEnd()){                   //А в нынешней реализации команда преаброзует '  ' в цифровое значение и считывает до него,
                //                int a;
                //                Line >> a;
                //                TemporaryDataMass.push_back(a);
                //                (верх и низ - разные попытки записи)
                //                TemporaryDataMass.push_back((Line.readLine(3)).toInt(nullptr,16));//что является ошибочным, хоть программа и запускается и что-то отрабатывает.
                //                Line.readLine(2);

            //}

            list  = LineTest1.split(" ");
            list.takeFirst();
            list.takeFirst();
            NumPac = list.takeFirst().toInt(nullptr,16);
            list.takeFirst();



            for(auto &i :list){
                TemporaryDataMass.push_back(i.toInt(nullptr,16));
            }

           // file.readLine();
            if(NumPac==0){
                TemporaryData = TemporaryData1;
            }

            for(auto i : TemporaryDataMass){
                Data[TemporaryData].push_back(i);
            }
            TemporaryDataMass.clear();
            QWer+="comboBox ";






        QWer+="\n\nLineTest "+LineTest;
        QWer+="\n\nLineTest1 "+LineTest1;
        QWer+="\n\nTemporaryData1 "+TemporaryData1;
        QWer+="\n\nNumPac "+QString::number(NumPac);
        QWer+="\n\nTemporaryData "+TemporaryData+"\n\nlist ";

        for(auto q : list){
            QWer+=q+" ";
        }
        QWer+="\n\n ";


        for(const auto &i : Data.values()){
            QWer+="Data.values ";
            for(const auto &q : i){
                QWer+=" "+QString::number(q);
            }
               QWer+="\n\n";
               //QWer+=QString::number(i[0+schet])+" "+QString::number(i[1+schet])+" "+QString::number(i[2+schet])
               //       +" "+QString::number(i[3+schet])+" "+QString::number(i[4+schet])+" "+QString::number(i[5+schet])+"\n";
        }
        QWer += "\n";




        }
        file.close();

    }
    for(const auto &i : Data.keys()){

        ui->comboBox->addItem(i);
        QWer+=i+" ";
    }
    ui->textBrowser_2->setText(QWer);
}

