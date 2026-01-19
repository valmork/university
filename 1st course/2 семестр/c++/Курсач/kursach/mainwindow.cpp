#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "class.h"
#include "prod.h"

ListShop *Ls;
int num, num_n, count, countProd, k, kn,  n = 0, s = 0, block, flag, ShopPhone, CurrentItem, EditFlag, index;
double price, mass, sugar;
QString type, powder, dough, additive, form, roasting, ShopName, ShopAddress, ShopInfo, Shop_n, str;
bool stop = false, flag1 = true, NotEmpty = true, SearchFlag = false, EditShop = false;
Prod *P;
Shop *S;

// Реализация товара
QString Prod::GetNum(){return QString::number(num);}
QString Prod::GetType(){return type;}
QString Prod::GetPrice(){return QString::number(price);}
QString Prod::GetMass(){return QString::number(mass);}
QString Prod::GetCountProd(){return QString::number(countProd);}
void Prod::SetNext(Prod *ProdObj){Next = ProdObj;}
void Prod::SetPrev(Prod *ProdObj){Prev = ProdObj;}
Prod::Prod(){}
Prod::Prod(int &nn, QString &tn, double &pn, double &mn, int &cn){
    num = nn; type = tn; price = pn; mass = mn; countProd = cn;
}

void ListProd::AddProd(Prod *NewProd){// ДОБАВИТЬ ТОВАР->+->+->+->+->+->+->+->+->+->+->+->+->+->+->+
    if (CountProd != 0){
        NewProd->SetNext(Head);
        NewProd->SetPrev(Tail);
        Head->SetPrev(NewProd);
        Tail->SetNext(NewProd);
        Head = NewProd;
    }
    else{
        NewProd->SetNext(NewProd);
        NewProd->SetPrev(NewProd);
        Head = Tail = NewProd;
    }
    CountProd++;
}

void ListProd::AddProd_Pastry(int &nn, QString &tn, double &pn, double &mn, int &cn, QString &dough_n, QString &additive_n, double &sugar_n, QString &powder_n, QString &form_n, QString &roasting_n){
    Prod *NewProd = new Pastry(nn, tn, pn, mn, cn, dough_n, additive_n, sugar_n, powder_n, form_n, roasting_n);
    AddProd(NewProd);
}
void ListProd::AddProd_Bread(int &nn, QString &tn, double &pn, double &mn, int &cn, QString &dough_n, QString &additive_n, double &sugar_n, QString &powder_n, QString &form_n, QString &roasting_n){
    Prod *NewProd = new Bread(nn, tn, pn, mn, cn, dough_n, additive_n, sugar_n, powder_n, form_n, roasting_n);
    AddProd(NewProd);
}
void ListProd::AddProd_Bakery(int &nn, QString &tn, double &pn, double &mn, int &cn, QString &dough_n, QString &additive_n, double &sugar_n, QString &powder_n, QString &form_n, QString &roasting_n){
    Prod *NewProd = new Bakery(nn, tn, pn, mn, cn, dough_n, additive_n, sugar_n, powder_n, form_n, roasting_n);
    AddProd(NewProd);
}
void ListProd::DeleteProd(int num){
    Prod *NewProd = Head;
    while(NewProd->GetNum() != QString::number(num)){
        NewProd = NewProd->GetNext();
    }
    if (CountProd != 1){
        NewProd->GetNext()->SetPrev(NewProd->GetPrev());
        NewProd->GetPrev()->SetNext(NewProd->GetNext());
        if (NewProd == Head){
            Head = NewProd->GetNext();
        }
        else if (NewProd == Tail){
            Head = NewProd->GetPrev();
        }
    }
    else{
        Head = Tail = NULL;
    }
    delete NewProd;
    CountProd--;
}
int ListProd::GetCount(){return CountProd;}
void ListProd::SetCountProd(int CountProd_n){CountProd = CountProd_n;}

Shop::Shop(){}
Shop::Shop(QString &snn, QString &san, int &spn){
    ShopName = snn; ShopAddress = san; ShopPhone = spn;
    ListProd();
}
QString Shop::GetShopName(){return ShopName;}
QString Shop::GetShopAddress(){return ShopAddress;}
QString Shop::GetShopPhone(){return QString::number(ShopPhone);}
QString Shop::GetShop(){return ShopName + "\n" + ShopAddress + "\n" + QString::number(ShopPhone);}

void ListShop::AddShop(Shop *NewShop){
    if (CountShop != 0){
        NewShop->SetPrev(Tail);
        NewShop->SetNext(Head);
        Head->SetPrev(NewShop);
        Tail->SetNext(NewShop);
        Head = NewShop;
    }
    else{
        NewShop->SetNext(NewShop);
        NewShop->SetPrev(NewShop);
        Head = Tail = NewShop;
    }
    CountShop++;
}
ListShop::ListShop(){
    Head = Tail = NULL;
    CountShop = 0;
}
void ListShop::AddShop(QString &snn, QString &san, int &spn){
    Shop *NewShop = new Shop(snn, san, spn);
    AddShop(NewShop);
}
void ListShop::DeleteShop(int num){
    int i = 0;
    Shop *NewShop = Tail;
    while (i < num){
        NewShop = NewShop->GetPrev();
        i++;
    }
    if (CountShop != 1){
        NewShop->GetNext()->SetPrev(NewShop->GetPrev());
        NewShop->GetPrev()->SetNext(NewShop->GetNext());
        if (NewShop == Head){ Head = NewShop->GetNext();}
        else if (NewShop == Tail){ Tail = NewShop->GetPrev();}
    }
    else Head = Tail = NULL;
    delete NewShop;
    CountShop--;
}
int ListShop::GetCount() {return CountShop;}
void ListShop::SetCountShop(int CountShop_n) {CountShop = CountShop_n;}






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Ls = new ListShop();
}

MainWindow::~MainWindow()
{
    delete ui;
}
// Проверка номера✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅📞✅

int MainWindow::check_num(int num, int n){
    if (n != 0){
        Shop *Sn = Ls->GetHead();
        for (int i = 0; i < Ls->GetCount(); i++){
            Prod *Pn = Sn->GetHead();
            for (int j = 0; j < Sn->GetCount(); j++){
                if ((Pn->GetNum() == QString::number(num)) && (Pn != P)){
                    //QMessageBox::warning(this, "Ошибка", "Иакой номер уже существует, придумайте другой");
                    return 0;
                }
                Pn = Pn->GetNext();
            }
            Sn = Sn->GetNext();
        }
    }
    return 1;
}

// Проверка названия магазина✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅🏷✅✅🏷

int MainWindow::check_name(QString ShopName, int s)
{
    if (s != 0)
    {
        Shop *Sn = Ls->GetHead();
        for (int i = 0; i < Ls->GetCount(); i++)
        {
            if ((Sn->GetShopName() == ShopName) && (Sn != S))
            {
                QMessageBox::warning(this, "Ошибка", "Данное название уже существует");
                return 0;
            }
            Sn = Sn->GetNext();
        }
    }
    return 1;
}

// Поиск по номеру︎🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞🔍📞

int MainWindow::search_num(int num)
{
    S = Ls->GetHead();
    for (int i = 0; i < Ls->GetCount(); i++){
        P = S->GetHead();
        for (int j = 0; j < S->GetCount(); j++){
            if (P->GetNum() == QString::number(num)){
                return 0;
            }
            P = P->GetNext();
        }
        S = S->GetNext();
    }
    return 0;
}

int MainWindow::search_name(QString name){
    S = Ls->GetHead();
    for (int i = 0; i < Ls->GetCount(); i++){
        if (S->GetShopName() == name){
            return 0;
        }
        S = S->GetNext();
    }
    return 0;
}

// Таблица товаров📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞📑🍞

void MainWindow::table_prod(Shop *Sn, Prod *Pn, int j){
    ui->prod_table_widget->setItem(j, 0, new QTableWidgetItem(Pn->GetNum()));
    ui->prod_table_widget->setItem(j, 1, new QTableWidgetItem(Pn->GetType()));
    ui->prod_table_widget->setItem(j, 2, new QTableWidgetItem(Sn->GetShop()));
    ui->prod_table_widget->setItem(j, 3, new QTableWidgetItem(Pn->GetPrice()));
    ui->prod_table_widget->setItem(j, 4, new QTableWidgetItem(Pn->GetMass()));
    ui->prod_table_widget->setItem(j, 5, new QTableWidgetItem(Pn->GetCountProd()));
    if(Pn->GetType()=="Хлеб"){
        ui->prod_table_widget->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetDough()));
        ui->prod_table_widget->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetAdditive()));
        ui->prod_table_widget->setItem(j, 8, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetSugar()));
        ui->prod_table_widget->setItem(j, 9, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetPowder()));
        ui->prod_table_widget->setItem(j, 10, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetForm()));
        ui->prod_table_widget->setItem(j, 11, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetRoasting()));
    }
    else if(Pn->GetType()=="Kондитерское изделие"){
        ui->prod_table_widget->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetDough()));
        ui->prod_table_widget->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetAdditive()));
        ui->prod_table_widget->setItem(j, 8, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetSugar()));
        ui->prod_table_widget->setItem(j, 9, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetPowder()));
        ui->prod_table_widget->setItem(j, 10, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetForm()));
        ui->prod_table_widget->setItem(j, 11, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetRoasting()));
    }
    else if(Pn->GetType()=="Булочное изделие"){
        ui->prod_table_widget->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetDough()));
        ui->prod_table_widget->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetAdditive()));
        ui->prod_table_widget->setItem(j, 8, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetSugar()));
        ui->prod_table_widget->setItem(j, 9, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetPowder()));
        ui->prod_table_widget->setItem(j, 10, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetForm()));
        ui->prod_table_widget->setItem(j, 11, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetRoasting()));
    }

}
// Таблица товаров для поиска📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎🔍︎📑︎

void MainWindow::table_prod_search(Shop *Sn, Prod *Pn, int j){
    ui->prod_table_search_widget->insertRow(ui->prod_table_search_widget->rowCount());
    ui->prod_table_search_widget->setRowHeight(j, 50);
    ui->prod_table_search_widget->setItem(j, 0, new QTableWidgetItem(Pn->GetNum()));
    ui->prod_table_search_widget->setItem(j, 2, new QTableWidgetItem(Sn->GetShop()));
    ui->prod_table_search_widget->setItem(j, 3, new QTableWidgetItem(Pn->GetPrice()));
    ui->prod_table_search_widget->setItem(j, 4, new QTableWidgetItem(Pn->GetMass()));
    ui->prod_table_search_widget->setItem(j, 5, new QTableWidgetItem(Pn->GetCountProd()));
    if(Pn->GetType()=="Хлеб"){
        ui->prod_table_search_widget->setItem(j, 1, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetType()));
        ui->prod_table_search_widget->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetDough()));
        ui->prod_table_search_widget->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetAdditive()));
        ui->prod_table_search_widget->setItem(j, 8, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetSugar()));
        ui->prod_table_search_widget->setItem(j, 9, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetPowder()));
        ui->prod_table_search_widget->setItem(j, 10, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetForm()));
        ui->prod_table_search_widget->setItem(j, 11, new QTableWidgetItem(dynamic_cast<Bread*>(Pn)->GetRoasting()));
    }
    else if(Pn->GetType()=="Kондитерское изделие"){
        ui->prod_table_search_widget->setItem(j, 1, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetType()));
        ui->prod_table_search_widget->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetDough()));
        ui->prod_table_search_widget->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetAdditive()));
        ui->prod_table_search_widget->setItem(j, 8, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetSugar()));
        ui->prod_table_search_widget->setItem(j, 9, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetPowder()));
        ui->prod_table_search_widget->setItem(j, 10, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetForm()));
        ui->prod_table_search_widget->setItem(j, 11, new QTableWidgetItem(dynamic_cast<Pastry*>(Pn)->GetRoasting()));
    }
    else if(Pn->GetType()=="Булочное изделие"){
        ui->prod_table_search_widget->setItem(j, 1, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetType()));
        ui->prod_table_search_widget->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetDough()));
        ui->prod_table_search_widget->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetAdditive()));
        ui->prod_table_search_widget->setItem(j, 8, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetSugar()));
        ui->prod_table_search_widget->setItem(j, 9, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetPowder()));
        ui->prod_table_search_widget->setItem(j, 10, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetForm()));
        ui->prod_table_search_widget->setItem(j, 11, new QTableWidgetItem(dynamic_cast<Bakery*>(Pn)->GetRoasting()));
    }

}

// Таблица магазинов︎📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑🛒📑

void MainWindow::table_shop(Shop *Sn, int j){
    ui->shop_table_widget->setItem(j, 0, new QTableWidgetItem(Sn->GetShopName()));
    ui->shop_table_widget->setItem(j, 1, new QTableWidgetItem(Sn->GetShopAddress()));
    ui->shop_table_widget->setItem(j, 2, new QTableWidgetItem(Sn->GetShopPhone()));
}

int MainWindow::check_number(QString check){
    for(int i=0; i < check.size(); i++){
        if ((check[i]!='.')&&(!check[i].isDigit())){
            return 0;
        }
    }
    return 1;
}

int MainWindow::check_leter(QString check){
    for (int i = 0; i < check.size(); i++)
    {
        if (!check[i].isLetter()) return 0;
    }
    return 1;
}

void MainWindow::on_bread_radioButton_clicked()
{
    flag = 1;
    ui->prod_dough_label->setDisabled(0);
    ui->prod_dough_line_edit->setDisabled(0);
    ui->prod_additive_label->setDisabled(0);
    ui->prod_additive_line_edit->setDisabled(0);
    ui->prod_sugar_label->setDisabled(1);
    ui->prod_sugar_line_edit->setDisabled(1);
    ui->prod_sugar_line_edit->clear();
    ui->prod_powder_label->setDisabled(1);
    ui->prod_powder_line_edit->setDisabled(1);
    ui->prod_powder_line_edit->clear();
    ui->prod_form_label->setDisabled(1);
    ui->prod_form_line_edit->setDisabled(1);
    ui->prod_form_line_edit->clear();
    ui->prod_roasting_label->setDisabled(1);
    ui->prod_roasting_line_edit->setDisabled(1);
    ui->prod_roasting_line_edit->clear();
}

void MainWindow::on_pastry_radioButton_clicked()
{
    flag = 2;
    ui->prod_sugar_label->setDisabled(0);
    ui->prod_sugar_line_edit->setDisabled(0);
    ui->prod_powder_label->setDisabled(0);
    ui->prod_powder_line_edit->setDisabled(0);
    ui->prod_dough_label->setDisabled(1);
    ui->prod_dough_line_edit->setDisabled(1);
    ui->prod_dough_line_edit->clear();
    ui->prod_additive_label->setDisabled(1);
    ui->prod_additive_line_edit->setDisabled(1);
    ui->prod_additive_line_edit->clear();
    ui->prod_form_label->setDisabled(1);
    ui->prod_form_line_edit->setDisabled(1);
    ui->prod_form_line_edit->clear();
    ui->prod_roasting_label->setDisabled(1);
    ui->prod_roasting_line_edit->setDisabled(1);
    ui->prod_roasting_line_edit->clear();
}

void MainWindow::on_bakery_radioButton_clicked()
{
    flag = 3;
    ui->prod_form_label->setDisabled(0);
    ui->prod_form_line_edit->setDisabled(0);
    ui->prod_roasting_label->setDisabled(0);
    ui->prod_roasting_line_edit->setDisabled(0);
    ui->prod_dough_label->setDisabled(1);
    ui->prod_dough_line_edit->setDisabled(1);
    ui->prod_dough_line_edit->clear();
    ui->prod_additive_label->setDisabled(1);
    ui->prod_additive_line_edit->setDisabled(1);
    ui->prod_additive_line_edit->clear();
    ui->prod_sugar_label->setDisabled(1);
    ui->prod_sugar_line_edit->setDisabled(1);
    ui->prod_sugar_line_edit->clear();
    ui->prod_powder_label->setDisabled(1);
    ui->prod_powder_line_edit->setDisabled(1);
    ui->prod_powder_line_edit->clear();
}

// Добавить магазин➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒➕🛒

void MainWindow::add_shop(){
    if ((!(ui->shop_name_line_edit->text()).size()) || (!check_leter(ui->shop_name_line_edit->text()))){
        QMessageBox::warning(this, "Ошибка", "Введены неверные значения или пустое поле");
        stop = true;
    }
    else{
        if (!ui->shop_address_line_edit->text().size()){
            QMessageBox::warning(this, "Ошибка", "Пустое поле");
            stop = true;
        }
        else{
            if ((!(ui->shop_phone_line_edit->text()).size()) || (!check_number(ui->shop_phone_line_edit->text()))){
                QMessageBox::warning(this, "Ошибка", "Введены неверные значения или пустое поле");
                stop = true;
            }
            else{
                stop = false;
            }
        }
    }
}

void MainWindow::on_shop_add_button_clicked(){
    EditShop = false;
    ui->shop_name_label->setDisabled(0);
    ui->shop_name_line_edit->setDisabled(0);
    ui->shop_address_label->setDisabled(0);
    ui->shop_address_line_edit->setDisabled(0);
    ui->shop_phone_label->setDisabled(0);
    ui->shop_phone_line_edit->setDisabled(0);
    ui->shop_accept_button->setDisabled(0);
    ui->bakery_radioButton->setDisabled(1);
    ui->bread_radioButton->setDisabled(1);
    ui->pastry_radioButton->setDisabled(1);
    ui->prod_num_label->setDisabled(1);
    ui->prod_num_line_edit->setDisabled(1);
    ui->prod_price_label->setDisabled(1);
    ui->prod_price_line_edit->setDisabled(1);
    ui->prod_mass_label->setDisabled(1);
    ui->prod_mass_line_edit->setDisabled(1);
    ui->prod_sugar_label->setDisabled(1);
    ui->prod_sugar_line_edit->setDisabled(1);
    ui->prod_powder_label->setDisabled(1);
    ui->prod_powder_line_edit->setDisabled(1);
    ui->prod_form_label->setDisabled(1);
    ui->prod_form_line_edit->setDisabled(1);
    ui->prod_roasting_label->setDisabled(1);
    ui->prod_roasting_line_edit->setDisabled(1);
    ui->prod_count_label->setDisabled(1);
    ui->prod_count_line_edit->setDisabled(1);
    ui->prod_dough_label->setDisabled(1);
    ui->prod_dough_line_edit->setDisabled(1);
    ui->prod_additive_label->setDisabled(1);
    ui->prod_additive_line_edit->setDisabled(1);
    ui->prod_accept_button->setDisabled(1);
    ui->prod_selectshop_label->setDisabled(1);
    ui->prod_selectshop_combobox->setDisabled(1);
    ui->prod_searchtype_combobox->setDisabled(1);
    ui->prod_num_label_2->setDisabled(1);
    ui->prod_numsearch_line_edit->setDisabled(1);
    ui->prod_type_label->setDisabled(1);
    ui->prod_typesearch_line_edit->setDisabled(1);
    ui->prod_searchaccept_button->setDisabled(1);
    ui->prod_search_button->setDisabled(1);
    ui->prod_add_button->setDisabled(1);
    ui->prod_num_line_edit->clear();
    ui->prod_price_line_edit->clear();
    ui->prod_mass_line_edit->clear();
    ui->prod_count_line_edit->clear();
    ui->prod_dough_line_edit->clear();
    ui->prod_additive_line_edit->clear();
    ui->prod_sugar_line_edit->clear();
    ui->prod_powder_line_edit->clear();
    ui->prod_form_line_edit->clear();
    ui->prod_roasting_line_edit->clear();
    ui->shop_del_button->setDisabled(0);
    ui->prod_add_button->setDisabled(0);
    ui->prod_del_button->setDisabled(0);

    ui->prod_table_widget->show();
}

void MainWindow::on_shop_accept_button_clicked()
{
    if (EditShop == false){
        add_shop();
        if (stop == false){
            ShopName = ui->shop_name_line_edit->text();
            ShopAddress = ui->shop_address_line_edit->text();
            ShopPhone = ui->shop_phone_line_edit->text().toInt();
            if (check_name(ShopName, s) != 1){
                stop = true;
            }
            else{
                Ls->AddShop(ShopName, ShopAddress, ShopPhone);
                ui->prod_selectshop_combobox->addItem(ShopName);
                Shop *Sn = Ls->GetHead();
                ui->shop_table_widget->insertRow(ui->shop_table_widget->rowCount());
                table_shop(Sn, s);
                s++;
                ui->shop_name_label->setDisabled(1);
                ui->shop_name_line_edit->setDisabled(1);
                ui->shop_name_line_edit->clear();
                ui->shop_address_label->setDisabled(1);
                ui->shop_address_line_edit->setDisabled(1);
                ui->shop_address_line_edit->clear();
                ui->shop_phone_label->setDisabled(1);
                ui->shop_phone_line_edit->setDisabled(1);
                ui->shop_phone_line_edit->clear();
                ui->shop_accept_button->setDisabled(1);
            }
        }
        else{
            stop = true;
        }

    }
    else if (EditShop == true){
        add_shop();
        if (stop == false){
            ShopName = ui->shop_name_line_edit->text();
            ShopAddress = ui->shop_address_line_edit->text();
            ShopPhone = ui->shop_phone_line_edit->text().toInt();
            Shop *Sn = new Shop(ShopName, ShopAddress, ShopPhone);
            if (Ls->GetCount() != 1){
                S->GetPrev()->SetNext(Sn);
                S->GetNext()->SetPrev(Sn);
                Sn->SetNext(S->GetNext());
                Sn->SetPrev(S->GetPrev());
            }
            else{
                Sn->SetNext(Sn);
                Sn->SetPrev(Sn);
            }
            if (Ls->GetHead() == S){
                Ls->SetHead(Sn);
            }
            if (Ls->GetTail() == S){
                Ls->SetTail(Sn);
            }
            table_shop(Sn, CurrentItem);
            Sn->SetCountProd(S->GetCount());
            Sn->SetHead(S->GetHead());
            Sn->SetTail(S->GetTail());
            Prod *Pn = Sn->GetHead(), *C = S->GetHead();
            for (int i = 0; i < Sn->GetCount(); i++){
                Pn->SetNext(C->GetNext());
                Pn->SetPrev(C->GetPrev());
                Pn = Pn->GetNext();
                C = C->GetNext();
            }
            for (int i = 0; i < n; i++){
                QString name1 = ui->shop_table_widget->item(i, 2)->text();
                if (name1 == S->GetShop()) ui->prod_table_widget->setItem(i, 2, new QTableWidgetItem(Sn->GetShop()));
            }
            int x = 0;
            Shop *sn = Ls->GetTail();
            while(sn != Sn){
                x++;
                sn = sn->GetPrev();
            }
            ui->prod_selectshop_combobox->setItemText(x, ShopName);
        }
        else{
            stop = false;
            QMessageBox::warning(this, "Ошибка", "Неверное значение");
        }
        ui->shop_name_line_edit->clear();
        ui->shop_address_line_edit->clear();
        ui->shop_phone_line_edit->clear();
        ui->shop_name_line_edit->setDisabled(1);
        ui->shop_address_line_edit->setDisabled(1);
        ui->shop_phone_line_edit->setDisabled(1);
    }
    if(Ls->GetCount()!=0){
        ui->shop_del_button->setDisabled(0);
        ui->shop_edit_button->setDisabled(0);
        ui->prod_add_button->setDisabled(0);
        ui->prod_del_button->setDisabled(0);
    }
    else{
        ui->shop_edit_button->setDisabled(1);
        ui->shop_del_button->setDisabled(1);
        ui->prod_add_button->setDisabled(1);
    }
}

void MainWindow::on_shop_edit_button_clicked()//Изменение товара
{
    EditShop = true;
    ui->shop_name_line_edit->setDisabled(0);
    ui->shop_address_line_edit->setDisabled(0);
    ui->shop_phone_line_edit->setDisabled(0);
    QItemSelectionModel *selectionModel = ui->shop_table_widget->selectionModel();
        if (selectionModel->hasSelection()){
            CurrentItem = ui->shop_table_widget->currentRow();
            ui->shop_name_line_edit->setText(ui->shop_table_widget->item(CurrentItem, 0)->text());
            ui->shop_address_line_edit->setText(ui->shop_table_widget->item(CurrentItem, 1)->text());
            ui->shop_phone_line_edit->setText(ui->shop_table_widget->item(CurrentItem, 2)->text());
            search_name(ui->shop_table_widget->item(CurrentItem, 0)->text());
            ui->shop_accept_button->setDisabled(0);
        }
        else{
            QMessageBox::warning(this, "Ошибка", "Магазин не выбран");
        }
}

// Удаление магазина❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒❌🛒

void MainWindow::on_shop_del_button_clicked()
{
    QItemSelectionModel *selectionModel = ui->shop_table_widget->selectionModel();
    if (selectionModel->hasSelection()){
        CurrentItem = ui->shop_table_widget->currentRow();
        ui->shop_table_widget->removeRow(CurrentItem);
        s--;
        ui->prod_selectshop_combobox->removeItem(CurrentItem);
        int x = 0;
        Shop *Sn = Ls->GetTail();
        while (x != CurrentItem){
            Sn = Sn->GetPrev();
            x++;
        }
        for (int i = 0; i < n; i++){
            if (ui->prod_table_widget->item(i, 2)->text()==Sn->GetShop()){
                ui->prod_table_widget->removeRow(i);
                i--;
                n--;
            }
        }
        Ls->DeleteShop(CurrentItem);
    }
    else{
        QMessageBox::warning(this, "Ошибка", "Магазин не выбран");
    }
    if(Ls->GetCount()!=0){
        ui->shop_del_button->setDisabled(0);
        ui->prod_add_button->setDisabled(0);
        ui->prod_del_button->setDisabled(0);
        ui->prod_table_widget->show();
    }
    else{
        ui->shop_del_button->setDisabled(1);
        ui->prod_add_button->setDisabled(1);
        ui->prod_del_button->setDisabled(1);
        ui->prod_search_button->setDisabled(1);
        ui->prod_searchtype_combobox->setDisabled(1);
        ui->prod_typesearch_line_edit->setDisabled(1);
        ui->prod_searchaccept_button->setDisabled(1);
        ui->prod_type_label->setDisabled(1);
        ui->prod_table_widget->show();
    }
}

// Добавить товар➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕🍞➕

void MainWindow::add_prod()
{
    SearchFlag = 0;
    EditFlag = 0;
    //QMessageBox::warning(this, "Ошибка", "QString::number(num_n)");
    // Проверка на заполненность полей----------
    if((( ui->prod_num_line_edit->text()).size() == 0) || (( ui->prod_price_line_edit->text()).size() == 0)
            || (( ui->prod_mass_line_edit->text()).size() == 0) || (( ui->prod_count_line_edit->text()).size() == 0)){
        NotEmpty = false;
        if (NotEmpty == false){
            QMessageBox::warning(this, "Ошибка", "Должны быть заполнены все поля");
            ui->prod_accept_button->setDisabled(1);
        }
        NotEmpty = true;
    }
    else{
        num = ui->prod_num_line_edit->text().toInt();
        price = ui->prod_price_line_edit->text().toDouble();
        mass = ui->prod_mass_line_edit->text().toDouble();
        countProd = ui->prod_count_line_edit->text().toInt();
    }


    if (flag == 1){// Если выбран хлеб
        if ((((ui->prod_dough_line_edit->text()).size() == 0) || (( ui->prod_additive_line_edit->text()).size() == 0)) && (NotEmpty == true)){
            {
                QMessageBox::warning(this, "Ошибка", "Должны быть заполнены все поля");
                stop = true;
               // ui->prod_accept_button->setDisabled(1);
           }
        }
        else{
            stop = false;
            dough = ui->prod_dough_line_edit->text();
            additive = ui->prod_additive_line_edit->text();
        }
        k = ui->prod_selectshop_combobox->currentIndex();
    }
    else if (flag == 2){// Если выбраны кондитерские изделия
        if (((( ui->prod_sugar_line_edit->text()).size() == 0) || (( ui->prod_powder_line_edit->text()).size() == 0)) && (NotEmpty == true)){
            QMessageBox::warning(this, "Ошибка", "Должны быть заполнены все поля");
            stop = true;
            //ui->prod_accept_button->setDisabled(1);
        }
        else{
            stop = false;
            sugar = ui->prod_sugar_line_edit->text().toDouble();
            powder = ui->prod_powder_line_edit->text();
        }
        k = ui->prod_selectshop_combobox->currentIndex();
    }
    else if (flag == 3){// Если выбрана выпечка
        if (((( ui->prod_form_line_edit->text()).size() == 0) || (( ui->prod_roasting_line_edit->text()).size() == 0)) && (NotEmpty == true)){
            QMessageBox::warning(this, "Ошибка", "Должны быть заполнены все поля");
            stop = true;
            //ui->prod_accept_button->setDisabled(1);
        }
        else{
            stop = false;
            form = ui->prod_form_line_edit->text();
            roasting = ui->prod_roasting_line_edit->text();
        }
        k = ui->prod_selectshop_combobox->currentIndex();
    }
    // Проверка на введенные цифры, повторяющиеся номера и буквы------
    if (stop == false){
        if((!check_number(ui->prod_num_line_edit->text())) || (!check_number(ui->prod_count_line_edit->text()))
                || (!check_number(ui->prod_price_line_edit->text())) || (!check_number(ui->prod_mass_line_edit->text()))
                || (!check_number(ui->prod_sugar_line_edit->text()))){
            QMessageBox::warning(this, "Ошибка", "Введены неверные значения");
            stop = true;
            //ui->prod_accept_button->setDisabled(1);
        }
        else{
            stop = false;
        }
    }
    if (stop == false){
        num_n = ui->prod_num_line_edit->text().toInt();
        if (!check_num(num_n, n)){
            stop = true;
            QMessageBox::warning(this, "Ошибка", "Такой номер уже существует");
            stop = true;
            //ui->prod_accept_button->setDisabled(1);
        }
        else{
            stop = false;
        }
    }
    if (stop == false){
        if ((!check_leter(ui->prod_form_line_edit->text())) || (!check_leter(ui->prod_roasting_line_edit->text()))
                || (!check_leter(ui->prod_dough_line_edit->text())) || (!check_leter(ui->prod_additive_line_edit->text()))){
            QMessageBox::warning(this, "Ошибка", "Введены неверные значения");
            stop = true;
            ui->prod_accept_button->setDisabled(1);
        }
        else{
            stop = false;
            ui->prod_accept_button->setDisabled(1);
        }
    }



}

void MainWindow::on_prod_add_button_clicked(){
    if (Ls->GetCount() !=0){
        EditFlag = 0;
        flag = 1;
        ui->bakery_radioButton->setDisabled(0);
        ui->bread_radioButton->setDisabled(0);
        ui->pastry_radioButton->setDisabled(0);
        ui->prod_num_label->setDisabled(0);
        ui->prod_num_line_edit->setDisabled(0);
        ui->prod_price_label->setDisabled(0);
        ui->prod_price_line_edit->setDisabled(0);
        ui->prod_mass_label->setDisabled(0);
        ui->prod_mass_line_edit->setDisabled(0);
        ui->prod_count_label->setDisabled(0);
        ui->prod_count_line_edit->setDisabled(0);
        ui->prod_dough_label->setDisabled(0);
        ui->prod_dough_line_edit->setDisabled(0);
        ui->prod_additive_label->setDisabled(0);
        ui->prod_additive_line_edit->setDisabled(0);
        ui->prod_add_button->setDisabled(1);
        ui->prod_accept_button->setDisabled(0);
        ui->prod_selectshop_label->setDisabled(0);
        ui->prod_selectshop_combobox->setDisabled(0);
        ui->shop_name_label->setDisabled(1);
        ui->shop_name_line_edit->setDisabled(1);
        ui->shop_address_label->setDisabled(1);
        ui->shop_address_line_edit->setDisabled(1);
        ui->shop_phone_label->setDisabled(1);
        ui->shop_phone_line_edit->setDisabled(1);
        ui->shop_accept_button->setDisabled(1);
        ui->prod_search_button->setDisabled(1);
        ui->prod_del_button->setDisabled(1);
        ui->prod_table_widget->show();
    }
    else{
        QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар, возможно, нет ни одного магазина");
    }

}

void MainWindow::on_prod_accept_button_clicked()
{
    if ((EditFlag == 0) && (SearchFlag == false)){
        add_prod();
        if ((stop != true) && (flag == 1)){
            int x = 0;
            Shop *Sn = Ls->GetTail();
            while (x!=k){
                Sn = Sn->GetPrev();
                x++;
            }
            //QMessageBox::warning(this, "Ошибка", "proverka");
            Sn->AddProd_Bread(num, type, price, mass, countProd, dough, additive, sugar, powder, form, roasting);
            Prod *Pn = Sn->GetHead();
            ui->prod_table_widget->insertRow(ui->prod_table_widget->rowCount());
            ui->prod_table_widget->setRowHeight(n, 50);
            table_prod(Sn, Pn, n);
            //table_prod_search(Sn, Pn, n);
            n++;
        }

        if ((stop != true) && (flag == 2)){
            int x = 0;
            Shop *Sn = Ls->GetTail();
            while (x!=k){
                Sn = Sn->GetPrev();
                x++;
            }
            Sn->AddProd_Pastry(num, type, price, mass, countProd, dough, additive, sugar, powder, form, roasting);
            Prod *Pn = Sn->GetHead();
            ui->prod_table_widget->insertRow(ui->prod_table_widget->rowCount());
            ui->prod_table_widget->setRowHeight(n, 50);
            table_prod(Sn, Pn, n);
            //table_prod_search(Sn, Pn, n);
            n++;
        }

        if ((stop != true) && (flag == 3)){
            int x = 0;
            Shop *Sn = Ls->GetTail();
            while (x!=k){
                Sn = Sn->GetPrev();
                x++;
            }
            Sn->AddProd_Bakery(num, type, price, mass, countProd, dough, additive, sugar, powder, form, roasting);
            Prod *Pn = Sn->GetHead();
            ui->prod_table_widget->insertRow(ui->prod_table_widget->rowCount());
            ui->prod_table_widget->setRowHeight(n, 50);
            table_prod(Sn, Pn, n);
            //table_prod_search(Sn, Pn, n);
            n++;
        }

        if (stop == false){
            ui->bakery_radioButton->setDisabled(1);
            ui->bread_radioButton->setDisabled(1);
            ui->pastry_radioButton->setDisabled(1);
            ui->prod_num_label->setDisabled(1);
            ui->prod_num_line_edit->setDisabled(1);
            ui->prod_price_label->setDisabled(1);
            ui->prod_price_line_edit->setDisabled(1);
            ui->prod_mass_label->setDisabled(1);
            ui->prod_mass_line_edit->setDisabled(1);
            ui->prod_sugar_label->setDisabled(1);
            ui->prod_sugar_line_edit->setDisabled(1);
            ui->prod_powder_label->setDisabled(1);
            ui->prod_powder_line_edit->setDisabled(1);
            ui->prod_form_label->setDisabled(1);
            ui->prod_form_line_edit->setDisabled(1);
            ui->prod_roasting_label->setDisabled(1);
            ui->prod_roasting_line_edit->setDisabled(1);
            ui->prod_count_label->setDisabled(1);
            ui->prod_count_line_edit->setDisabled(1);
            ui->prod_dough_label->setDisabled(1);
            ui->prod_dough_line_edit->setDisabled(1);
            ui->prod_additive_label->setDisabled(1);
            ui->prod_additive_line_edit->setDisabled(1);
            ui->prod_add_button->setDisabled(0);
            ui->prod_accept_button->setDisabled(1);
            ui->prod_num_line_edit->clear();
            ui->prod_price_line_edit->clear();
            ui->prod_mass_line_edit->clear();
            ui->prod_count_line_edit->clear();
            ui->prod_dough_line_edit->clear();
            ui->prod_additive_line_edit->clear();
            ui->prod_sugar_line_edit->clear();
            ui->prod_powder_line_edit->clear();
            ui->prod_form_line_edit->clear();
            ui->prod_roasting_line_edit->clear();
            ui->prod_selectshop_label->setDisabled(1);
            ui->prod_selectshop_combobox->setDisabled(1);
            ui->prod_table_widget->show();
            ui->prod_del_button->setDisabled(0);
            ui->prod_search_button->setDisabled(0);
            num = 0; price = 0; mass = 0; countProd = 0; dough = ""; additive = ""; sugar = 0; powder = ""; form = ""; roasting = "";
        }
    }
    else if ((EditFlag == 0) && (SearchFlag == 1)){
        ui->prod_table_widget->show();
        ui->prod_add_button->setDisabled(0);
        ui->prod_del_button->setDisabled(0);
        ui->prod_search_button->setDisabled(0);
        SearchFlag = 0;
    }
}



// Удаление товара❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌🍞❌
void MainWindow::on_prod_del_button_clicked()
{
    QItemSelectionModel *selectionModel = ui->prod_table_widget->selectionModel();
    if (selectionModel->hasSelection()){
        CurrentItem = ui->prod_table_widget->currentRow();
        num = ui->prod_table_widget->item(CurrentItem, 0)->text().toInt();
        ShopInfo = ui->prod_table_widget->item(CurrentItem, 2)->text();
        ui->prod_table_widget->removeRow(CurrentItem);
        Shop *Sn = Ls->GetTail();
        for (int i = 0; i < Ls->GetCount(); i++){
            if (Sn->GetShop()== ShopInfo){
                Sn->DeleteProd(num);
                break;
            }
            Sn->GetPrev();
        }
        n--;
    }
    else{
        QMessageBox::warning(this, "Ошибка", "Товар для удаления не выбран. Что вы собираетесь удалять:");
    }
}

// Поиск товара🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞🔍🍞
void MainWindow::on_prod_search_button_clicked()
{
    if (Ls->GetCount() !=0){
        ui->prod_search_button->setDisabled(0);
        ui->prod_searchtype_combobox->setDisabled(0);
        ui->prod_searchaccept_button->setDisabled(0);
        ui->prod_typesearch_line_edit->setDisabled(0);
        ui->prod_type_label->setDisabled(0);
        ui->prod_numsearch_line_edit->setDisabled(0);
        ui->prod_num_label_2->setDisabled(0);
        ui->prod_selectshop_combobox->setDisabled(0);
        ui->prod_selectshop_label->setDisabled(0);
        ui->prod_selectshop_combobox->setDisabled(0);
        ui->prod_selectshop_label->setDisabled(0);
    }
}

void MainWindow::on_prod_searchaccept_button_clicked()
{
    SearchFlag = true;
    int n_n = n;
    for(int i = 0; i < n_n; i++){
        ui->prod_table_search_widget->removeRow(i);
        i--; n_n--;
    }
    int f = 0;
    if (ui->prod_searchtype_combobox->currentIndex()==0){
        Shop *Sn = Ls->GetTail();
        for (int i = 0; i < Ls->GetCount(); i++){
            Prod *Pn = Sn->GetTail();
            for(int j = 0; j < Sn->GetCount(); j++){
                if (Pn->GetNum() == ui->prod_numsearch_line_edit->text()){
                    table_prod_search(Sn, Pn, f);
                    f++;
                }
                Pn = Pn->GetPrev();
            }
            Sn = Sn->GetPrev();
        }
        f = 0;
    }
    else if (ui->prod_searchtype_combobox->currentIndex()==1){
        Shop *Sn = Ls->GetTail();
        for (int i = 0; i < Ls->GetCount(); i++){
            Prod *Pn = Sn->GetTail();
            for(int j = 0; j < Sn->GetCount(); j++){
                if (Pn->GetType() == ui->prod_typesearch_line_edit->text()){
                    table_prod_search(Sn, Pn, f);
                    f++;
                }
                Pn = Pn->GetPrev();
            }
            Sn = Sn->GetPrev();
        }
        f = 0;
    }
    else if (ui->prod_searchtype_combobox->currentIndex() == 2)
        {
            int l = 0;
            Shop *Sn = Ls->GetTail();
            k = ui->prod_selectshop_combobox->currentIndex();
            while(l != k)
            {
                Sn = Sn->GetPrev();
                l++;
            }
            Prod *Pn = Sn->GetTail();
            {
                for (int i = 0; i < Sn->GetCount(); i++)
                {
                    table_prod_search(Sn, Pn, f);
                    f++;
                    Pn = Pn->GetPrev();
                }
            }
            f = 0;
        }
    else{
        QMessageBox::warning(this, "Ошибка", "Не удалось ничего найти");
    }
    ui->prod_searchtype_combobox->setDisabled(1);
    ui->prod_searchaccept_button->setDisabled(1);
    ui->prod_typesearch_line_edit->setDisabled(1);
    ui->prod_type_label->setDisabled(1);
    ui->prod_numsearch_line_edit->setDisabled(1);
    ui->prod_num_label_2->setDisabled(1);
    ui->prod_selectshop_combobox->setDisabled(1);
    ui->prod_selectshop_label->setDisabled(1);
    ui->prod_selectshop_combobox->setDisabled(1);
    ui->prod_selectshop_combobox->setDisabled(1);
    ui->prod_selectshop_label->setDisabled(1);
    ui->prod_selectshop_label->setDisabled(1);
    ui->prod_typesearch_line_edit->clear();
    ui->prod_numsearch_line_edit->clear();
    ui->prod_table_widget->hide();
    ui->prod_accept_button->setDisabled(0);
    ui->prod_add_button->setDisabled(1);
    ui->prod_del_button->setDisabled(1);
    ui->prod_search_button->setDisabled(1);
}

void MainWindow::write_n(QString str_n){
    QFile file(str_n);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        Shop *Sn = Ls->GetTail();
        for (int i = 0; i < Ls->GetCount(); i++){
            out << Sn->GetShopName() << "|"
                << Sn->GetShopPhone() << "|"
                << Sn->GetShopAddress() << "|" << endl;
            Prod *Pn = Sn->GetTail();
            for (int j = 0; j < Sn->GetCount(); j++){
                out << ' ' << Pn->GetNum() << "|"
                    << Pn->GetType() << "|"
                    << Pn->GetPrice() << "|"
                    << Pn->GetMass() << "|";
                if (Pn->GetType() == "Хлеб"){
                    out << dynamic_cast<Bread*>(Pn)->GetDough() << "|"
                        << dynamic_cast<Bread*>(Pn)->GetAdditive() << "|" << endl;
                }
                else if (Pn->GetType() == "Kондитерское изделие"){
                    out << dynamic_cast<Pastry*>(Pn)->GetSugar() << "|"
                        << dynamic_cast<Pastry*>(Pn)->GetPowder() << "|" << endl;
                }
                else if (Pn->GetType() == "Булочное изделие"){
                    out << dynamic_cast<Bakery*>(Pn)->GetForm() << "|"
                        << dynamic_cast<Bakery*>(Pn)->GetRoasting() << "|" << endl;
                }
                Pn->GetPrev();
            }
            Sn = Sn->GetPrev();
        }
    }
    else{
        QMessageBox::warning(this, "Ошибка", "Невозможно открыть файл");
    }
}

void MainWindow::on_actionCreate_triggered()
{
    if (!str.isNull()){
        for (int i = n-1; i>= 0; i--){
            ui->prod_table_widget->removeRow(i);
        }
        n = 0;
        for (int i = s-1; i>=0; i--){
            ui->shop_table_widget->removeRow(i);
            ui->prod_searchtype_combobox->removeItem(i);
            Ls->DeleteShop(i);
        }
        s = 0;
    }
    else QMessageBox::warning(this, "Ошибка", "Файл не сохранен");
}


void MainWindow::on_actionOpen_triggered()
{
    on_actionCreate_triggered();
    QString Z, z;
    int row1 = 0, column = 0, row = 0;
    QString selFilter = "All files (*.*)";
    str = QFileDialog::getOpenFileName(this, "Open file", QDir::currentPath(), "Text files (*.txt);;All files (*.*)",&selFilter);
    QFile file(str);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd()){
            Z = in.readLine();
            if(Z[0] != ' '){
                ui->shop_table_widget->insertRow(ui->shop_table_widget->rowCount());
                for (int i = 0; i < Z.size(); i++){
                    if((Z[i] == "|")){
                        ui->shop_table_widget->setItem(row1, column, new QTableWidgetItem(z));
                        column++;
                        z.clear();
                    }
                    else z += Z[i];
                }
                ui->shop_table_widget->setItem(row1, column, new QTableWidgetItem(z));
                //index = ui->shop_table_widget->item(row1, 1)->text().toInt();
                ShopName = ui->shop_table_widget->item(row1, 0)->text();
                ShopAddress = ui->shop_table_widget->item(row1, 1)->text();
                ShopPhone = ui->shop_table_widget->item(row1, 2)->text().toInt();
                Ls->AddShop(ShopName, ShopAddress, ShopPhone);
                ui->prod_selectshop_combobox->addItem(ShopName);
                s++;
                column = 0;
                row1++;
                z.clear();
            }
            else{
                QMessageBox::warning(this, "dsf", "sdg");
                ui->prod_table_widget->insertRow(ui->prod_table_widget->rowCount());
                ui->prod_table_widget->setRowHeight(row, 50);
                for (int i = 1; i < Z.size(); i++){
                    if ((Z[i]) == '|'){
                        ui->prod_table_widget->setItem(row, column, new QTableWidgetItem(z));
                        if (column == 2){
                            if (ui->prod_table_widget->item(row, 1)->text() == "Хлеб") column++;
                            if (ui->prod_table_widget->item(row, 1)->text() == "Kондитерское изделие") column++;
                            if (ui->prod_table_widget->item(row, 1)->text() == "Булочное изделие") column++;
                        }
                        if (column == 3){
                            ui->prod_table_widget->setItem(row, 2, new QTableWidgetItem(Ls->GetHead()->GetShop()));
                            column++;
                        }
                        column++;
                        if (column > 3) i = Z.size();
                        z.clear();
                    }
                    else z += Z[i];
                }
                ui->prod_table_widget->setItem(row, column, new QTableWidgetItem(z));
                z.clear();
                QString type_n = ui->prod_table_widget->item(row, 1)->text();
                if (type_n == "Хлеб"){
                    num = ui->prod_table_widget->item(row, 0)->text().toInt();
                    price = ui->prod_table_widget->item(row, 3)->text().toDouble();
                    mass = ui->prod_table_widget->item(row, 4)->text().toDouble();
                    countProd = ui->prod_table_widget->item(row, 5)->text().toInt();
                    dough = ui->prod_table_widget->item(row, 6)->text();
                    additive = ui->prod_table_widget->item(row, 7)->text();
                    sugar = ui->prod_table_widget->item(row, 8)->text().toDouble();
                    powder = ui->prod_table_widget->item(row, 9)->text().toDouble();
                    form = ui->prod_table_widget->item(row, 10)->text();
                    roasting = ui->prod_table_widget->item(row, 11)->text();
                    Shop *Sn = Ls->GetTail();
                    ShopInfo =  ui->prod_table_widget->item(row, 2)->text();
                    int x = 0;
                    while (x != Ls->GetCount()){
                        if (Sn->GetShop() == ShopInfo) break;
                        x++;
                        Sn = Sn->GetPrev();
                    }
                    Sn->AddProd_Bread(num, type, price, mass, countProd, dough, additive, sugar, powder, form, roasting);
                    n++;
                }
                else if (type_n == "Kондитерское изделие"){
                    num = ui->prod_table_widget->item(row, 0)->text().toInt();
                    price = ui->prod_table_widget->item(row, 3)->text().toDouble();
                    mass = ui->prod_table_widget->item(row, 4)->text().toDouble();
                    countProd = ui->prod_table_widget->item(row, 5)->text().toInt();
                    dough = ui->prod_table_widget->item(row, 6)->text();
                    additive = ui->prod_table_widget->item(row, 7)->text();
                    sugar = ui->prod_table_widget->item(row, 8)->text().toDouble();
                    powder = ui->prod_table_widget->item(row, 9)->text().toDouble();
                    form = ui->prod_table_widget->item(row, 10)->text();
                    roasting = ui->prod_table_widget->item(row, 11)->text();
                    Shop *Sn = Ls->GetTail();
                    ShopInfo =  ui->prod_table_widget->item(row, 2)->text();
                    int x = 0;
                    while (x != Ls->GetCount()){
                        if (Sn->GetShop() == ShopInfo) break;
                        x++;
                        Sn = Sn->GetPrev();
                    }
                    Sn->AddProd_Pastry(num, type, price, mass, countProd, dough, additive, sugar, powder, form, roasting);
                    n++;
                }
                else if (type_n == "Булочное изделие"){
                    num = ui->prod_table_widget->item(row, 0)->text().toInt();
                    price = ui->prod_table_widget->item(row, 3)->text().toDouble();
                    mass = ui->prod_table_widget->item(row, 4)->text().toDouble();
                    countProd = ui->prod_table_widget->item(row, 5)->text().toInt();
                    dough = ui->prod_table_widget->item(row, 6)->text();
                    additive = ui->prod_table_widget->item(row, 7)->text();
                    sugar = ui->prod_table_widget->item(row, 8)->text().toDouble();
                    powder = ui->prod_table_widget->item(row, 9)->text().toDouble();
                    form = ui->prod_table_widget->item(row, 10)->text();
                    roasting = ui->prod_table_widget->item(row, 11)->text();
                    Shop *Sn = Ls->GetTail();
                    ShopInfo =  ui->prod_table_widget->item(row, 2)->text();
                    int x = 0;
                    while (x != Ls->GetCount()){
                        if (Sn->GetShop() == ShopInfo) break;
                        x++;
                        Sn = Sn->GetPrev();
                    }
                    Sn->AddProd_Bakery(num, type, price, mass, countProd, dough, additive, sugar, powder, form, roasting);
                    n++;
                }
                row++;
                column = 0;
            }
        }
        file.close();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (!str.isNull()){
        QFile file(str);
        file.open(QFile::WriteOnly|QFile::Truncate);
        file.close();
        write_n(str);
    }
    else QMessageBox::warning(this, "Ошибка", "Нечего открывать");
}

void MainWindow::on_actionSave_Us_triggered()
{
    QString selFilter = "All files (*.*)";
    QString str1 = QFileDialog::getSaveFileName(this, "Save file", QDir::currentPath(),
    "Text files (*.txt);;All files (*.*)", &selFilter);
    write_n(str1);
    str = str1;
}



















