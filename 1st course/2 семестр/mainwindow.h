#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Prod{
protected:
    QString type;
    QString price;
    QString mass;
    QString count;
    Prod *Next, *Prev;
public:
    Prod(){}
    Prod(QString &tn, QString &pn, QString &mn, QString &cn){
        type = tn; price = pn; mass = mn; count = cn;
    }
    virtual ~Prod(){}
};
class Pastry: public Prod{
protected:
    QString sugar;
    QString powder;
public:
    Pastry(): Prod(){}
    Pastry(QString tn, QString &pn, QString &mn, QString &cn, QString &sugar_n, QString &powder_n): Prod(tn, pn, mn, cn){
        sugar = sugar_n; powder = powder_n;
    }
};
class Bread: public Prod{
protected:
    QString dough;
    QString additive;
public:
    Bread(): Prod(){}
    Bread(QString tn, QString &pn, QString &mn, QString &cn, QString &dough_n, QString &additive_n): Prod(tn, pn, mn, cn){
        dough = dough_n; additive = additive_n;
    }
};
class Bakery: public Prod{
protected:
    QString form;
    QString roasting;
public:
    Bakery(){}
    Bakery(QString tn, QString &pn, QString &mn, QString &cn, QString &form_n, QString &roasting_n): Prod(tn, pn, mn, cn){
        form = form_n; roasting = roasting_n;
    }
};