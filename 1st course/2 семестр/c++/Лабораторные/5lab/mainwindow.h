#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QObject>
#include <QMessageBox>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//---------------------------------------------------------------------------------

class prod{
protected:
    int numb;
    QString size;
    QString weight;
    QString price;
public:
    prod(int numb_n, QString size_n, QString weight_n, QString price_n){
        numb = numb_n;
        size = size_n;
        weight = weight_n;
        price = price_n;
    }
    virtual ~prod(){};
    virtual QStringList collect() = 0;
};

class food: public prod{//Продовольственный++++++++
private:
    QString taste;
    QString packcol;
public:
    food(int numb_n, QString size_n, QString weight_n, QString price_n, QString packcol_n, QString taste_n):prod(numb_n, size_n, weight_n, price_n){
        packcol = packcol_n;
        taste = taste_n;
    }
    ~food(){}
    QStringList collect(){
        QStringList goods;
        QString n = QString::number(numb);
        goods << n << "Продовольственный" << size << weight << price << packcol << taste;
        return goods;
    }
};

class nonfood: public prod{//Непродовольственный+++++++
private:
    QString packcol;
public:
    nonfood(int numb_n, QString size_n, QString weight_n, QString price_n, QString packcol_n):prod(numb_n, size_n, weight_n, price_n){
        packcol = packcol_n;
    }
    ~nonfood(){}
    QStringList collect(){
        QStringList goods;
        QString n = QString::number(numb);
        goods << n << "Непродовольственный" << size << weight << price << packcol << " ";
        return goods;
    }
};

//------------------------------------------------------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    //void on_pushButton_4_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    int num = 0;
    int check = 0;
    prod* mas[20];
};
#endif // MAINWINDOW_H
