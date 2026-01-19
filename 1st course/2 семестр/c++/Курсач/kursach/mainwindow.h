#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <bits/stdc++.h>
#include <QMainWindow>
#include <QStackedWidget>
#include <QSpinBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include <class.h>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int check_num(int num, int n);
    int search_num(int num);
    void table_prod(Shop *Sn, Prod *Pn, int j);
    void table_prod_search(Shop *Sn, Prod *Pn, int j);
    void table_shop(Shop *Sn, int j);
    int check_number(QString check);
    int check_name(QString ShopName, int s);
    int check_leter(QString check);
    int search_name(QString name);
    void add_prod();
    void add_shop();
    void write_n(QString str_n);
private slots:
    void on_shop_add_button_clicked();

    void on_prod_add_button_clicked();

    void on_prod_accept_button_clicked();

    void on_bread_radioButton_clicked();

    void on_pastry_radioButton_clicked();

    void on_bakery_radioButton_clicked();

    void on_shop_accept_button_clicked();

    void on_prod_del_button_clicked();

    void on_shop_del_button_clicked();

    void on_prod_search_button_clicked();

    void on_prod_searchaccept_button_clicked();

    void on_actionCreate_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_Us_triggered();

    void on_shop_edit_button_clicked();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
