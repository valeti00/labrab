МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №5<br/> по дисциплине "Программирование"
<br/>

студента 1 курса группы ИВТ-б-о-192(1)
Тимофеева Тимофея Валерьевича
направления подготовки 09.03.01 "Информатика и вычислительная техника"  
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2020

<br/><br/>


Цель:

1. Научиться работать с текстовыми файлами;
2. Закрепить навыки работы со структурами.

Ход работы:

1) Код лабораторной работы:

  ``` c++
  
  #include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
struct passanger_data {
	int Id;
	bool Survival;
	int Pclass;
	string Name;
	string	Sex;
	int Age;
	int	SibSp;
	int	Parsym;
	int	Ticket;
	string Fare;
	string Cabin;
	string Embarked;
	void set_data(int i, string data) {

		switch (i) {
		case 0:
			Id = atoi(data.c_str());
			break;
		case 1:
			Survival = atoi(data.c_str());
			break;
		case 2:
			Pclass = atoi(data.c_str());
			break;
		case 3:
			Name = data;
			break;
		case 4:
			Name = Name + data;
			break;
		case 5:
			Sex = data;
			break;
		case 6:
			Age = atoi(data.c_str());
			break;
		case 7:
			SibSp = atoi(data.c_str());
			break;
		case 8:
			Parsym = atoi(data.c_str());
			break;
		case 9:
			Ticket = atoi(data.c_str());
			break;
		case 10:
			Fare = data;
			break;
		case 11:
			Cabin = data;
			break;
		case 12:
			Embarked = data;
			break;
		}
		

	}
};

struct DataPassenger {
	int Surv = 0, FirstClass = 0, SecondClass = 0, ThirdClass = 0,
		Female = 0, Male = 0, Age = 0, AgeMale = 0,
		AgeFemale = 0, Cherbourg = 0, Queenstown = 0, Southampton = 0;
	string State = "", Minors = "";
	
};

int main()
{
	DataPassenger urg;
	int i = 0, quantity_male = 0, quantity_surv = 0;
	vector<passanger_data> data_passenger;
	passanger_data temp_data;
	string temp = "";
	ifstream train("train.csv");
	char sym;
	string str;
	while (train.get(sym)) {
		if (sym == '"')continue;

		else if ((sym == ',')) {
			temp_data.set_data(i, temp);
			temp = "";
			i++;
			continue;
		}
		if (sym == '\r') {
			temp_data.set_data(i, temp);
			data_passenger.push_back(temp_data);
			temp = "";
			i = 0;
		}
		temp = temp + sym;
	}

for (int i = 0; i < data_passenger.size(); i++) {
	urg.Surv = urg.Surv + data_passenger[i].Survival;
	if (data_passenger[i].Age > 0) {
		urg.Age += data_passenger[i].Age;
		quantity_surv++;
	}
	if ((data_passenger[i].Age < 18) && (data_passenger[i].Age > 0)) {
		urg.Minors += "," + to_string(data_passenger[i].Id);
	}
	if (data_passenger[i].Embarked == "Southampton") urg.Southampton++;
	if (data_passenger[i].Embarked == "Queenstown") urg.Queenstown++;
	if (data_passenger[i].Embarked == "Cherbourg") urg.Cherbourg++;
	if ((data_passenger[i].Pclass == 1) && (data_passenger[i].Survival == 1)) urg.FirstClass++;
	if ((data_passenger[i].Pclass == 2) && (data_passenger[i].Survival == 1)) urg.SecondClass++;
	if ((data_passenger[i].Pclass == 3) && (data_passenger[i].Survival == 1)) urg.ThirdClass++;
	if ((data_passenger[i].Sex == "female") && (data_passenger[i].Age > 0)) urg.AgeFemale += data_passenger[i].Age;
	if ((data_passenger[i].Sex == "male") && (data_passenger[i].Age > 0)) {
		urg.AgeMale += data_passenger[i].Age;
		quantity_male++;
	}
	if ((data_passenger[i].Sex == "female") && (data_passenger[i].Survival == 1)) urg.Female++;
	if ((data_passenger[i].Sex == "male") && (data_passenger[i].Survival == 1)) urg.Male++;

}
if ((urg.Southampton > urg.Queenstown) && (urg.Southampton > urg.Cherbourg)) urg.State = "Southampton";
else if ((urg.Queenstown > urg.Southampton) && (urg.Queenstown > urg.Cherbourg)) urg.State = "Queenstown";
else urg.State = "Cherbourg";
urg.Minors = urg.Minors.substr(1, urg.Minors.length() - 1);
ofstream out("train.txt", ios::out);
out << "Общее число выживших: " << urg.Surv << endl;
out << "Число выживших из 1 класса: " << urg.FirstClass << endl;
out << "Число выживших из 2 класса: " << urg.SecondClass << endl;
out << "Число выживших из 3 класса: " << urg.ThirdClass << endl;
out << "Количество выживших женщин: " << urg.Female << endl;
out << "Количество выживших мужчин: " << urg.Male << endl;
out << "Средний возраст пассажира: " << urg.Age / quantity_surv << " " << endl;
out << "Средний возраст женщины: " << urg.AgeFemale / (quantity_surv - quantity_male) << " " << endl;
out << "Средний возраст мужчины: " << urg.AgeMale / quantity_male << endl;
out << "Штат, в котором село больше всего пассажиров: " << urg.State << endl;
out << "Список идентификаторов несовершеннолетних: " << urg.Minors << endl;
out.close();
data_passenger.clear();
train.close();

return 0;

}
  
```

