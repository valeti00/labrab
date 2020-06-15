МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №3<br/> по дисциплине "Программирование"
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

Закрепить навыки разработки программ использующих операторы цикла;
Закрепить навыки разработки программ использующих массивы;
Освоить методы подключения сторонних библиотек.


Ход работы

Исходный ключ: ``` 00r 00b 00g 01r 01b 01g 10r 10b ``` 

Изображение:

![Image of Yaktocat](https://raw.githubusercontent.com/valeti00/labrab/master/labrab3/pict/pic7.bmp) 
<center>Рис. 1. Исходное изображение</center>
<br/><br/>

Код: 
```cpp
    #include <iostream>
    #include<string>
    #include "libbmp.h"
    #include<fstream>
    using namespace std;

    int8_t defcolor(int& x, int& y, BmpImg& img) {
	    static int8_t count = 1;
	    if (count == 1) {
		    count = 2;
		    return img.red_at(x, y);
	    }
	    else if (count == 2) {
		    count = 3;
		    return img.blue_at(x, y);
	    }
	    count = 1;
	    return img.green_at(x, y);
    };
    int main()
    {
	    string viv;
	    int8_t text = 0;
	    BmpImg img;
	    int8_t bit = 0;
	    if (img.read("pic7.bmp") != BMP_OK)
	    return 0; 
	    for (int x = 0; x <= img.get_width() - 1; x++)
	    {
		    for (int y = 0; y <= img.get_height() - 1; y++)
		    {
			    for (int rbg = 0; rbg < 3; rbg++) {
				    text = (text << 1) | (defcolor(x, y, img) & 1); bit++;
				    if (bit == 8) {
					    if ((text & 255) == '\0') {
						    cout << viv;
						    return 0;
					    }
					    viv = viv + static_cast<char>(text); bit = 0;
					    text = 0;
				    }
			    }
		    }
	    }
	    return 0;
    }
```

Результатом декодирования является данный текст:

![Image of Yaktocat](https://github.com/valeti00/labrab/blob/master/labrab3/pict/VsDebugConsole_R92nJIPoYh.png?raw=true) 
<center>Рис. 2. Декодированное изображение</center>
<br/><br/>


Вывод: Все цели и задачи лабораторной работы были выполнены в полном объеме. Были получены навыки в работе с Visual Studio на языке C++ и с языком разметки Markdown. Получены навыки работы с побитовыми операторами.
