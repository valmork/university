#ifndef CLASS_H
#define CLASS_H
#include <QString>
using namespace std;
//-------------------------------------------------------------------------------------------
class Prod{
    int num;
    QString type;
    double price, mass;
    int countProd;
    Prod *Next, *Prev;
public:
    Prod();
    Prod(int &nn, QString &tn, double &pn, double &mn, int &cn);
    QString GetNum();
    virtual QString GetType();
    QString GetPrice();
    QString GetMass();
    QString GetCountProd();
    virtual ~Prod(){}
    void SetNext(Prod *ProdObj);
    void SetPrev(Prod *ProdObj);
    Prod *GetNext(){return Next;}
    Prod *GetPrev(){return Prev;}
};
// ДОЧЕРНИЙ КЛАСС ТОВАРА - ХЛЕБ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Bread: public Prod{
    QString dough;
    QString additive;
    double sugar;
    QString powder;
    QString form;
    QString roasting;
public:
    Bread(): Prod(){}
    Bread(int &nn, QString &tn, double &pn, double &mn, int &cn, QString &dough_n, QString &additive_n, double &sugar_n, QString &powder_n, QString &form_n, QString &roasting_n): Prod(nn, tn, pn, mn, cn){
        dough = dough_n;
        additive = additive_n;
        sugar = sugar_n;
        powder = powder_n;
        form = form_n;
        roasting = roasting_n;
    }
    QString GetType(){return "Хлеб";}
    QString GetDough(){return dough;}
    QString GetAdditive(){return additive;}
    QString GetSugar(){return QString::number(sugar);}
    QString GetPowder(){return powder;}
    QString GetForm(){return form;}
    QString GetRoasting(){return roasting;}
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ДОЧЕРНИЙ КЛАСС ТОВАРА - КОНДИТЕРСКОЕ ИЗДЕЛИЕ++++++++++++++++++++++++++++++++++++++++++++++
class Pastry: public Prod{
    QString dough;
    QString additive;
    double sugar;
    QString powder;
    QString form;
    QString roasting;
public:
    Pastry(): Prod(){}
    Pastry(int &nn, QString &tn, double &pn, double &mn, int &cn, QString &dough_n, QString &additive_n, double &sugar_n, QString &powder_n, QString &form_n, QString &roasting_n): Prod(nn, tn, pn, mn, cn){
        dough = dough_n;
        additive = additive_n;
        sugar = sugar_n;
        powder = powder_n;
        form = form_n;
        roasting = roasting_n;
    }
    QString GetType(){return "Kондитерское изделие";}
    QString GetDough(){return dough;}
    QString GetAdditive(){return additive;}
    QString GetSugar(){return QString::number(sugar);}
    QString GetPowder(){return powder;}
    QString GetForm(){return form;}
    QString GetRoasting(){return roasting;}
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ДОЧЕРНИЙ КЛАСС ТОВАРА - БУЛОЧНОЕ ИЗДЕЛИЕ++++++++++++++++++++++++++++++++++++++++++++++++++
class Bakery: public Prod{
    QString dough;
    QString additive;
    double sugar;
    QString powder;
    QString form;
    QString roasting;
public:
    Bakery(){}
    Bakery(int &nn, QString &tn, double &pn, double &mn, int &cn, QString &dough_n, QString &additive_n, double &sugar_n, QString &powder_n, QString &form_n, QString &roasting_n): Prod(nn, tn, pn, mn, cn){
        dough = dough_n;
        additive = additive_n;
        sugar = sugar_n;
        powder = powder_n;
        form = form_n;
        roasting = roasting_n;
    }
    QString GetType(){return "Булочное изделие";}
    QString GetDough(){return dough;}
    QString GetAdditive(){return additive;}
    QString GetSugar(){return QString::number(sugar);}
    QString GetPowder(){return powder;}
    QString GetForm(){return form;}
    QString GetRoasting(){return roasting;}
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// СПИСОК ТОВАРОВ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
class ListProd{
    Prod *Head, *Tail;
    int CountProd;
public:
    void AddProd(Prod *NewProd);
    ListProd(){
        Head = Tail = NULL;
        CountProd = 0;
    }
    // Функции добавления
    void AddProd_Pastry(int &nn, QString &tn, double &pn, double &mn, int &cn, QString &dough_n, QString &additive_n, double &sugar_n, QString &powder_n, QString &form_n, QString &roasting_n);
    void AddProd_Bread(int &nn, QString &tn, double &pn, double &mn, int &cn, QString &dough_n, QString &additive_n, double &sugar_n, QString &powder_n, QString &form_n, QString &roasting_n);
    void AddProd_Bakery(int &nn, QString &tn, double &pn, double &mn, int &cn, QString &dough_n, QString &additive_n, double &sugar_n, QString &powder_n, QString &form_n, QString &roasting_n);
    void DeleteProd(int num);
    int GetCount();
    Prod *GetHead(){return Head;}
    Prod *GetTail(){return Tail;}
    void SetCountProd(int CountProd_n);
    void SetHead(Prod* ProdObj) {Head = ProdObj;}
    void SetTail(Prod* ProdObj) {Tail = ProdObj;}
};
//->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->

// КЛАСС МАГАЗИНА-----------------------------------------------------------------------------
class Shop: public ListProd{
    QString ShopName;
    QString ShopAddress;
    int ShopPhone;
    ListProd ListShop;
    Shop *Next;
    Shop *Prev;
public:
    Shop();
    Shop(QString &snn, QString &san, int &spn);
    QString GetShopName();
    QString GetShopAddress();
    QString GetShopPhone();
    QString GetShop();
    void SetNext(Shop *ShopObj){Next = ShopObj;}
    void SetPrev(Shop *ShopObj){Prev = ShopObj;}
    Shop* GetNext() {return Next;}
    Shop* GetPrev() {return Prev;}
};
//--------------------------------------------------------------------------------------------

// СПИСОК Магазинов->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
class ListShop{
    Shop *Head, *Tail;
    int CountShop;
private:
    void AddShop(Shop *NewShop);
public:
    ListShop();
    void AddShop(QString &snn, QString &san, int &spn);
    void DeleteShop(int n);
    int GetCount();
    Shop* GetHead() {return Head;}
    Shop* GetTail() {return Tail;}
    void SetCountShop(int CountShop_n);
    void SetHead(Shop* ShopObj) {Head = ShopObj;}
    void SetTail(Shop* ShopObj) {Tail = ShopObj;}
};
#endif // CLASS_H
