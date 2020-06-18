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

<a href="https://github.com/valeti00/labrab/blob/master/labrab5/train.txt">Файл с результатами расчета</a>

<br/>

| Характеристика | Результат  |
|:-:|:-:|
| Общее число выживших | 342  |
| Число выживших из 1 класса | 136 |
| Число выживших из 2 класса | 87 |
| Число выживших из 3 класса | 119 |
| Количество выживших женщин | 233 |
| Количество выживших мужчин | 109 |
| Средний возраст пассажира | 29 |
| Средний возраст женский | 28 |
| Средний возраст мужчин | 31 |
| Штат, в котором село больше 
всего пассажиров: | Southampton |
| Список идентификаторов несовершеннолетних | 8,10,11,15,17,18,20,23,25,27,29,30,32,33,37,40,43,44,46,47,48,49,51,56,<br/>59,60,64,65,66,69,72,77,78,79,83,85,87,88,96,102,108,110,112,115,120,<br/>122,126,127,129,139,141,148,155,157,159,160,164,165,166,167,169,172,<br/>173,177,181,182,183,184,185,186,187,194,197,199,202,206,209,215,221,<br/>224,230,234,236,238,241,242,251,257,261,262,265,267,271,275,278,279,<br/>283,285,296,298,299,301,302,304,305,306,307,308,325,330,331,334,335,<br/>336,341,348,349,352,353,355,359,360,365,368,369,375,376,382,385,387,<br/>389,390,408,410,411,412,414,416,420,421,426,429,432,434,436,445,446,<br/>447,449,452,455,458,460,465,467,469,470,471,476,480,481,482,486,490,<br/>491,496,498,501,503,505,508,512,518,523,525,528,531,532,533,534,536,<br/>539,542,543,548,550,551,553,558,561,564,565,569,574,575,579,585,590,<br/>594,597,599,602,603,612,613,614,619,630,634,635,640,643,644,645,649,<br/>651,654,657,668,670,675,681,684,687,690,692,693,698,710,712,719,721,<br/>722,728,732,733,739,740,741,747,751,752,756,761,765,767,769,774,777,<br/>778,779,781,782,784,788,789,791,792,793,794,803,804,814,816,820,825,<br/>826,827,828,829,831,832,833,838,840,842,845,847,850,851,853,854,860,<br/>864,869,870,876 |

<br/><br/>


Вывод: Все цели и задачи лабораторной работы были выполнены в полном объеме. Были получены навыки в работе с Visual Studio на языке C++ и с языком разметки Markdown. В процессе выполнения лабораторной работы научились работать с тектовыми файлами. Были закреплены навыки работы со структурами.
