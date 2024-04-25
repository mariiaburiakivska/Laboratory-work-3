// Завдання 11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Money {
public:
    string name;
    double money;
    double rate;
    int time;

    
    void setOptions(string n, double m, double r, int t) {
        name = n;
        money = m;
        rate = r;
        time = t;
    }

    Money() {
        setOptions("", 0, 0, 0);
    }

    Money(string n, double m, double r, int t) {
        setOptions(n, m, r, t);
    }

    Money(const Money& other) {
        setOptions(other.name, other.money, other.rate, other.time);
    }

    virtual double getMoney() = 0;

    virtual void print() {
        cout << "Name: " << name << endl;
        cout << "Investment: " << money << endl;
        cout << "Rate(%): " << rate << endl;
        cout << "Years: " << time << endl;
        cout << "Total amount: " << getMoney() << endl;
    }

};

class Deposit: public Money {
public:
    Deposit() : Money() {}

    Deposit(string n, double m, double r, int t) : Money(n, m, r, t) {}

    Deposit(const Deposit& other) : Money(other) {}

    double getMoney() override {
        double s = money * pow((1 + rate / 100), time);
        return s;
    }

    void print() override {
        Money::print();
    }

    void setOptions(string n, double m, double r, int t) {
        Money::setOptions(n, m, r, t);
    }
};

class YearDeposit : public Money {
public:
    int periods; //нарахування на рік

    void setOptions(string n, double m, double r, int t, int p) {
        Money::setOptions(n, m, r, t);
        periods = p;
    }

    YearDeposit() : Money() {
        periods = 1;
    }

    YearDeposit(string n, double m, double r, int t, int p) : Money(n, m, r, t) {
        periods = p;
    }

    YearDeposit(const YearDeposit& other) : Money(other), periods(other.periods) {}

    double getMoney() override {
        double s = money * pow((1 + rate / 100), time*periods);
        return s;
    }

    void print() override {
        cout << "Name: " << name << endl;
        cout << "Investment: " << money << endl;
        cout << "Rate(%): " << rate << endl;
        cout << "Years: " << time << endl;
        cout << "Accruals per year: " << periods << endl;
        cout << "Total amount: " << getMoney() << endl;
    }

};

class MoneyManagement : public Money {
public:
    MoneyManagement() : Money() {}

    MoneyManagement(string n, double m, double r, int t) : Money(n, m, r, t) {}

    MoneyManagement(const MoneyManagement& other) : Money(other) {}

    void add(double amount) {
        money += amount;
    }

    void withdraw(double amount) {
        if (amount <= money) {
            money -= amount;
        }
        else {
            cout << "Too big amount." << endl;
        }
    }

    double getMoney() override {
        double s = money * pow((1 + rate / 100), time);
        return s;
    }
};


int main()
{
    Deposit person1("Pavlo", 1000, 8, 5);
    person1.print();
    cout << endl;

    YearDeposit person2("Petro", 1500, 7, 3, 2);
    person2.print();
    cout << endl;

    MoneyManagement person3("Ivan", 1700, 6, 4);
    person3.print();
    cout << endl;
    person3.withdraw(500);
    cout << "Updated Ivan`s balance:" << endl;
    person3.print();
    cout << endl;


    return 0;
}


