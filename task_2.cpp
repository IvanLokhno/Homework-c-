#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
/*
   Реализация магазина (базовый класс) и его сотрудников и товаров (дочерние классы) 
   * Базовый класс:
   * 	Ключевые поля и методы класса:
   * 		Динамически увеличивающийся массив стринговых строк (таким образом, класс неплсокий)
   * 		Статическое поле массив указателей на сотрудников 
   * 		Две чисто виртуальные функции - распределение бюджета и увеличение зарплаты/количества товаров (таким образом, абстрактный класс)
   * 		Переопределенная операция присваивания, которая используется и в дочернем классе сотрудников
   * 		Перегруженный вывод объекта базового класса
   * 		Перегруженная операция индексации                                     
  */                                                             
using namespace std;

const int N=3;

class Employee_1;

class Market{

protected:
	
	int market_index, number_of_notes;
	string *array_of_notes;
	
	static double budget_general, budget_products, budget_employees; //статические поля
	static int number_empl_1;
	
public:	
	
	Market(int a=1){
		market_index=a;
		number_of_notes=0;
		array_of_notes=new string[0];
	}
	
	Market(const Market& a){
		market_index=a.market_index;
		number_of_notes=a.number_of_notes;
		delete [] array_of_notes;
		array_of_notes=new string[number_of_notes];
		for(int i=0;i<number_of_notes;i++)
			array_of_notes[i]=a.array_of_notes[i];
	}
	
	void add_note(){   //добавить запись сотруднику (изменяется динамический массив)
		string *s1;
		
		s1=array_of_notes;
		array_of_notes=new string[number_of_notes+=1];
		for(int i=0;i<number_of_notes-1;i++)
			array_of_notes[i]=s1[i];
		cin>>array_of_notes[number_of_notes-1];
	}
	
	~Market(){
		delete [] array_of_notes;
	}
	
	static Employee_1 **employee_1;  //массив указателей на сотрудников
	
	static void add_money(double x){
		budget_general+=x;
	}
	
	static void distribution_of_budget(double x){	
		int budget_general=budget_products+budget_employees;
		
		budget_products=(budget_general)*x;
		budget_employees=(budget_general)*(1-x);   
	}
	
	static double get_budget(int i){
		switch (i){
			case 1: return budget_general;
			case 2: return budget_employees;
			case 3: return budget_products;
			default:return 0;
		}
	}
	
	virtual int distribution_of_budget_(double x)=0; //чисто виртуальные функции
	virtual void increase_(double x)=0;
	
	void increase(double x){  
		distribution_of_budget_(x);
		increase_(x);
	}
	
	Market& operator=(int a){ //перегруженное присваивание
		market_index=a;
		return *this;
	}
	
	void operator[](int i){   //перегруженное индексирование
		cout<<"Запись номер "<<i<<": "<<array_of_notes[i]<<endl;
	}
	
	friend ostream& operator <<(ostream&, Market&); 
		
};

double Market::budget_employees=100; double Market::budget_products=500; double Market::budget_general=250; int Market::number_empl_1=0;
Employee_1** Market::employee_1=0;


class Employee_1: public Market{
	
	int number, salary, extras; //number - порядковый номер в массиве
	static int base_salary;
	
	Employee_1(int x=base_salary){ //таким образом сотрудники могут создаваться лишь статической функцией данного класса
			salary=x;
			number=number_empl_1;
			extras=0;
		}
public:

	Employee_1(const Employee_1 &a){
		(Market &)*this=(Market &)a;
		number=a.number;
		salary=a.salary;
		extras=a.extras;
		//market_index=a.market_index;
	}
	
	Employee_1& operator=(int a){
		(Market &)*this=a;
		extras=a;
		return *this;
	}
	
	Employee_1& operator=(const Employee_1& a){
		(Market &)*this=(Market &)a;
		salary=a.salary;
		extras=a.extras;
		return *this;
	}
	
	int get_salary()const{
		return salary;
	}
	
	virtual int distribution_of_budget_(double x){
		if(budget_employees<x){
			if(budget_general>x){
				budget_employees+=x;
				budget_general-=x;
				return 0;
			}
			else{
				cout<<"Недостаточно средств на счету"<<endl;
				return 1;
			}
		}
		return 0;
	}

	virtual void increase_(double x){
		if(extras>=N){
			salary+=x;
			budget_employees-=x;
		}
	}
	
	
	static void hire_(int number){
		Employee_1 **ptr;
		
		budget_employees-=base_salary*number;
		ptr=new Employee_1*[number_empl_1+number];
		
		for(int i=0;i<number_empl_1;i++)
			ptr[i]=employee_1[i];
		
		for(int i=0;i<number;i++){
			ptr[number_empl_1]=new Employee_1;
			number_empl_1++;
		}
		
		delete [] employee_1;
		employee_1=ptr;	
	}
	
	static int get_base_salary(){
		return base_salary;
	}
	
	friend ostream& operator <<(ostream&, Employee_1&); 
	
};

int Employee_1::base_salary=10;


class Products: public Market{
	
	int number;
	double price;
	
public:
	
	Products(int numb=10, double price_=5){
		number=numb;
		price=price_;
		budget_products-=price*number;
	}
	
	Products (const Products& a){
		number=a.number;
		price=a.price;	
		market_index=a.market_index;
	}
	
	virtual int distribution_of_budget_(double x){ 
		if(budget_products<x*price){
			if(budget_general>x*price){
				budget_products+=x*price;
				budget_general-=x*price;
				return 0;
			}
			else{
				cout<<"Недостаточно средств на счету"<<endl;
				return 1;
			}
		}
		return 0;
	}
	int get_number()const{ 
		return number;
	}
	
	virtual void increase_(double x){
		budget_products-=x*price;		
		number+=x;
	}
};

ostream& operator<<(ostream& out, Market& empl){
	out<<"Индекс магазина сотрудника: "<<empl.market_index<<endl;	
	return out;
}	

ostream& operator<<(ostream& out, Employee_1& empl){
	out<<"Номер сотрудника: "<<empl.number<<endl;
	out<<"Зарплата сотрудника: "<<empl.salary<<endl;
	out<<"Бонусы сотрудника: "<<empl.extras<<endl;
	out<<"Индекс магазина сотрудника: "<<empl.market_index<<endl;	
	return out;
}	
	
int main(){
	Employee_1::hire_(3);
	Products a;
	int flag=1, i=0, j=0;
	string s1;
	while(flag){
		cout <<endl<<" 1–Добавление заметки для работника (демонстрация перегрузки операции вывода и неплоскости базового класса)"<<endl;
		cout<<" 2–Копирование работников (демонстарция работы кк и перегрузки присваивания в базовом классе)"<<endl;
		cout<<" 3–Вывод бюджета магазина (демоснтарция статического метода базового класса)"<<endl;
		cout<<" 4–Повышение сотрудника (демонстрация абстрактности класса)"<<endl;
		cout<<" 5–Показать сотрудника "<<endl;
		cin>>flag;
			switch(flag){
				case 1: cout<<"Введите, пожалуйста, индекс работника"<<endl;
						cin>>i;
						cout<<"Введите, пожалуйста, запись"<<endl;
						(*Market::employee_1[i]).add_note();
						cout<<"Введите, пожалуйста, запись"<<endl;
						(*Market::employee_1[i]).add_note();
						cout<<endl;
						(*Market::employee_1[i])[0];
						(*Market::employee_1[i])[1];

						break;
						
				case 2:	(*Market::employee_1[0]=5).increase(3);              //для простоты демонстрации копируется сотрудник с индексом 1 из сотрудника с индексом 0
						cout<<"До копирования"<<endl<<*Market::employee_1[1]<<endl;
						(*Market::employee_1[1])=(*Market::employee_1[0]);
						cout<<"После копирования"<<endl<<*Market::employee_1[1];
						(*Market::employee_1[1])[0];
						break;
						
				case 3:	cout<<Market::get_budget(1)<<endl;
						cout<<Market::get_budget(2)<<endl;
						cout<<Market::get_budget(3)<<endl;
						break;
						
				case 4: cout<<"Введите, пожалуйста, индекс работника"<<endl;
						cin>>i;
						(*Market::employee_1[i]=5).increase(2);
						cout<<*Market::employee_1[i];
						break;
						
				case 5:	cout<<"Введите, пожалуйста, индекс работника"<<endl;
						cin>>i;
						cout<<*(Market::employee_1[i]);
						cout<<"Введите, пожалуйста, номер записи"<<endl;
						cin>>j;
						(*Market::employee_1[i])[j];
						break;
				default: flag=0;
			}
		
	};
	
	return 0;
}
	
	
	
