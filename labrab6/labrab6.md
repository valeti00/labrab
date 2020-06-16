МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №6<br/> по дисциплине "Программирование"
<br/>

студента 1 курса группы ИВТ-б-о-192
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

Закрепить навыки разработки многофайловыx приложений;
Изучить способы работы с API web-сервиса;
Изучить процесс сериализации/десериализации данных.

Ход работы

1. Подготовка серверной части.

2. Подготовка к работе с сервисом openweathermap.org

3. Подготовка клиента для получения информации от openweathermap.org.

4. Подготовка к работе с JSON.

5. Подготовка шаблона виджета

6. Сборка итогового проекта

1) Для выполнения заданий нужно было с серивиса openweathermap.org получить API ключ.<br></br> 
Сам API ключ: "33b542b29e9846ba11f480646a553e7d".

2) Код выполненной лабараторной работы:

```cpp
        #include <iostream>
        #include <httplib/httplib.h>
        #include <nlohmann/json.hpp>
        #include <string>

    
        using namespace std;
        using namespace httplib;
        using json = nlohmann::json;

        void replace(string& str, const string from, string  to, int key)
        {
	        switch (key)
	        {
	        case 1: to = to.substr(1, 10); break;
	        case 2: to = to.substr(1, 3); break;
	        }
	        int start_pos = str.find(from);
	        if (start_pos == string::npos) return;

	        str.replace(start_pos, from.length(), to);
        }

        void gen_response(const Request& req, Response& res)
        {
	        string pogoda;
	        Client sevice("api.openweathermap.org", 80);
	        auto result = sevice.Get("/data/2.5/forecast?id=693805&units=metric&APPID=33b542b29e9846ba11f480646a553e7d&units=metric");
	        json j;
	        if (result && result->status == 200) j = json::parse(result->body);

	        ifstream stream("Weather.html");
	        getline(stream, pogoda, '\0');
	        stream.close();

	        replace(pogoda, "{city.name}", j["city"]["name"].dump(), 1);
	        for (int i = 0; i < 5; i++)
	        {

		        int temp = j["list"][0]["dt"];
		        for (int i = 0; i < 40; i++) 
		        {
			        if (j["list"][i]["dt"] >= temp)
			        {
				        replace(pogoda, "{list.dt}", j["list"][i]["dt_txt"].dump(), 1);
				        replace(pogoda, "{list.weather.icon}", j["list"][i]["weather"][0]["icon"].dump(), 2);
				        replace(pogoda, "{list.main.temp}", j["list"][i]["main"]["temp"].dump(), 0);
				        temp += 86400;
			        }
		        }
	        }

	        res.set_content(pogoda, "text/html");
        }       


        int main()
        {
        	Server svr;
	        svr.Get("/", gen_response);
	        svr.listen("localhost", 3000);
        }
```
3) Выполненная лабораторная работа показана на рисунке 1.

![Image of Yaktocat](https://github.com/valeti00/labrab/blob/master/labrab6/chrome_tkDoUt0IZD.png?raw=true) 
<center>Рис. 1. Погода</center>
<br></br>

Вывод: Все цели и задачи лабораторной работы были выполнены в полном объеме. Были получены навыки в работе с Visual Studio на языке C++ и с языком разметки Markdown. Были получены навыки работы с Json. 
