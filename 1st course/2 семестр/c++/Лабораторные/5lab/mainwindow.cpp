#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QLineEdit>
#include <QString>
#include<QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (num > 0){
        ui->pushButton_2->setEnabled(1);
    }
}

void MainWindow::on_radioButton_clicked()
{
    ui->lineEdit_2->setEnabled(1);
    ui->lineEdit_3->setEnabled(1);
    ui->lineEdit_4->setEnabled(1);
    ui->lineEdit_5->setEnabled(1);
    ui->lineEdit_6->setEnabled(1);
    ui->lineEdit_7->setEnabled(1);
    ui->label->setEnabled(1);
    ui->label_2->setEnabled(1);
    ui->label_3->setEnabled(1);
    ui->label_4->setEnabled(1);
    ui->label_5->setEnabled(1);
    ui->label_6->setEnabled(1);
    ui->lineEdit_7->text();
    ui->lineEdit_2->text();
    ui->lineEdit_3->text();
    ui->lineEdit_4->text();
    ui->lineEdit_5->text();
    ui->lineEdit_6->text();
    check = 1;
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->lineEdit_2->setEnabled(1);
    ui->lineEdit_3->setEnabled(1);
    ui->lineEdit_4->setEnabled(1);
    ui->lineEdit_5->setEnabled(1);
    ui->lineEdit_7->setEnabled(1);
    ui->lineEdit_7->text();
    ui->lineEdit_2->text();
    ui->lineEdit_3->text();
    ui->lineEdit_4->text();
    ui->lineEdit_5->text();
    ui->lineEdit_6->setEnabled(0);
    ui->lineEdit_6->clear();
    ui->label->setEnabled(1);
    ui->label_2->setEnabled(1);
    ui->label_3->setEnabled(1);
    ui->label_4->setEnabled(1);
    ui->label_5->setEnabled(1);
    ui->label_6->setEnabled(0);
    check = 2;
}

void MainWindow::on_pushButton_clicked()//Начать добавлять++++++
{
    ui->pushButton_3->setEnabled(1);
    ui->radioButton->setEnabled(1);
    ui->radioButton_2->setEnabled(1);
    }

void MainWindow::on_pushButton_2_clicked()//Удалить-------
{
    ui->lineEdit_7->setEnabled(1);
    QString numb_n = ui->lineEdit_7->text();
    ui->pushButton_3->setEnabled(1);
    check = 3;
}

void MainWindow::on_pushButton_3_clicked()//Принять======
{
    if (check == 1 || check == 2){
        if (num != 20){
           int numb_n;
           QString size_n;
           QString weight_n;
           QString price_n;
           QString packcol_n;
           QString taste_n;
           numb_n = ui->lineEdit_7->text().toInt();
           size_n = ui->lineEdit_2->text();
           weight_n = ui->lineEdit_3->text();
           price_n = ui->lineEdit_4->text();
           packcol_n = ui->lineEdit_5->text();
           taste_n = ui->lineEdit_6->text();
           if (check == 1){
               mas[num] = new food(numb_n, size_n, weight_n, price_n, packcol_n, taste_n);
           }
           else{
               mas[num] = new nonfood(numb_n, size_n, weight_n, price_n, packcol_n);
           }
           num++;
           ui->lineEdit_2->setEnabled(0);
           ui->lineEdit_3->setEnabled(0);
           ui->lineEdit_4->setEnabled(0);
           ui->lineEdit_5->setEnabled(0);
           ui->lineEdit_6->setEnabled(0);
           ui->lineEdit_7->setEnabled(0);
           ui->label->setEnabled(0);
           ui->label_2->setEnabled(0);
           ui->label_3->setEnabled(0);
           ui->label_4->setEnabled(0);
           ui->label_5->setEnabled(0);
           ui->label_6->setEnabled(0);
           ui->lineEdit_2->clear();
           ui->lineEdit_3->clear();
           ui->lineEdit_4->clear();
           ui->lineEdit_5->clear();
           ui->lineEdit_6->clear();
           ui->lineEdit_7->clear();
           ui->pushButton_3->setEnabled(0);
           ui->radioButton->setEnabled(0);
           ui->radioButton_2->setEnabled(0);
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Сообщение");
            msgBox.setText("Невозможно больше добавить");
            msgBox.exec();
        }
    }
    if (num > 0){
        ui->pushButton_2->setEnabled(1);
        ui->pushButton_4->setEnabled(1);
    }
    if (check == 3){
        QString numb_n = ui->lineEdit_7->text();
        for (int i = 0; i < num; i++){
            QStringList row = mas[i]->collect();
            if(row.at(0)==numb_n){
                for(int j = i; j < num; j++){
                    mas[j] = mas[j+1];
                }
                num--;
                break;
            }
        }
        ui->lineEdit_7->setEnabled(0);
        ui->lineEdit_7->clear();
        ui->label->setEnabled(0);
        check = 0;
    }
}

void MainWindow::on_pushButton_4_clicked()//Отобразить таблицу????????????
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setRowCount(num);
    for (int i = 0; i < num; i++){
        QStringList row = mas[i]->collect();
        for (int j = 0; j < 7; j++){
            ui->tableWidget->setCellWidget(i, j, new QLabel(row.at(j)));
        }
    }
}
