МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №9<br/> по дисциплине "Программирование"
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

1. Познакомиться с Google Test и Google Mock Framework;
2. Изучить базовые понятия относящийся к тестированию кода;
3. Научиться тестировать классы в среде разработки Qt Creator.

Ход работы

1) Код лабораторной работы:

```cpp

#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lockcontroller.h>


using namespace testing;

class MockIKeypad : public IKeypad {
public:
    MOCK_METHOD(bool, isActive, (), (override));
    MOCK_METHOD(void, wait, (), (override));
    MOCK_METHOD(PasswordResponse, requestPassword, (), (override));
};

class MockILatch : public ILatch {
public:
    MOCK_METHOD(bool, isActive, (), (override));
    MOCK_METHOD(DoorStatus, open, (), (override));
    MOCK_METHOD(DoorStatus, close, (), (override));
    MOCK_METHOD(DoorStatus, getDoorStatus, (), (override));
};


TEST(Lab9, test1){

    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(IKeypad, wait()) .Times(1);
    Door.wait();
}


TEST(Lab9, test2){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, getDoorStatus()) .Times(1) .WillOnce (Return(DoorStatus::CLOSE));
    ASSERT_FALSE(Door.isDoorOpen());
}

TEST(Lab9, test3){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, getDoorStatus()) .Times(1) .WillOnce (Return(DoorStatus::OPEN));
    ASSERT_TRUE(Door.isDoorOpen());

}

TEST(Lab9, test4){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, open()) .Times(1);
    ASSERT_EQ(Door.unlockDoor(),DoorStatus::OPEN);

}


TEST(Lab9, test5){
   MockILatch ILatch;
   MockIKeypad IKeypad;
   LockController Door(&IKeypad, &ILatch);
   EXPECT_CALL(ILatch, close()) .Times(1) .WillOnce(Return(DoorStatus::CLOSE));
   ASSERT_EQ(Door.lockDoor(),DoorStatus::CLOSE);

}

TEST(Lab9, test6){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, isActive()) .Times(1) .WillOnce(Return(1));
    EXPECT_CALL(IKeypad, isActive()) .Times(1) .WillOnce(Return(1));
    ASSERT_EQ(Door.hardWareCheck(),HardWareStatus::OK);
}

TEST(Lab9, test7){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(nullptr, &ILatch);
    EXPECT_CALL(ILatch, isActive()) .Times(AtLeast(0)) .WillOnce(Return(1));
    EXPECT_CALL(IKeypad, isActive()) .Times(AtLeast(0)) .WillOnce(Return(1));
    ASSERT_EQ(Door.hardWareCheck(),HardWareStatus::ERROR);

}

TEST(Lab9, test8){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, isActive()) .Times(AtLeast(0)) .WillOnce(Return(0));
    EXPECT_CALL(IKeypad, isActive()) .Times(AtLeast(0)) .WillOnce(Return(1));
    ASSERT_EQ(Door.hardWareCheck(),HardWareStatus::ERROR);

}

TEST(Lab9, test9){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse PR{PasswordResponse::Status::OK,"0000"};
    EXPECT_CALL(IKeypad, requestPassword()) .Times(1) .WillOnce(Return(PR));
    ASSERT_TRUE(Door.isCorrectPassword());
}

TEST(Lab9, test10){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse PR{PasswordResponse::Status::OK,"1111"};
    EXPECT_CALL(IKeypad, requestPassword()) .Times(1) .WillOnce(Return(PR));
    ASSERT_FALSE(Door.isCorrectPassword());
}


TEST(Lab9, test11){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse Pass1{PasswordResponse::Status::OK,"0000"};
    PasswordResponse Pass2{PasswordResponse::Status::OK,"9876"};
    EXPECT_CALL(IKeypad, requestPassword())
            .Times(3)
            .WillOnce(Return(Pass1))
            .WillOnce(Return(Pass2))
            .WillOnce(Return(Pass2));
    Door.resetPassword();
    ASSERT_TRUE(Door.isCorrectPassword());
}


TEST(Lab9, test12){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse Pass1{PasswordResponse::Status::OK,"0000"};
    PasswordResponse Pass2{PasswordResponse::Status::OK,"9876"};
    PasswordResponse Pass3{PasswordResponse::Status::OK,"1111"};
    EXPECT_CALL(IKeypad, requestPassword()).Times(5)
                .WillOnce(Return(Pass1))
                .WillOnce(Return(Pass2))
                .WillOnce(Return(Pass2))
                .WillOnce(Return(Pass3))
                .WillOnce(Return(Pass3));
    Door.resetPassword();
    Door.resetPassword();
    ASSERT_TRUE(Door.isCorrectPassword());
}


#endif // TST_TESTDIVISIONBYZERO_H



```

При запуске теста возникла 1 ошибка. Это показано на рисунке 1.

![Image of Yaktocat](https://github.com/valeti00/labrab/blob/master/labrab9/qtcreator_3f5kwJ9HVZ.png?raw=true) 
<center>Рис. 1. Ошибка</center>
<br></br>

2) Для того, чтобы исправить данную ошибку нужно было в файле "lockcontroller.cpp" в методе "lockDoor" заменить "open" на "close". Это показано на рисунке 2. 

![Image of Yaktocat](https://github.com/valeti00/labrab/blob/master/labrab9/qtcreator_vXKHTVhtdh.png?raw=true) 
<center>Рис. 2. Метод "lockDoor"</center>
<br></br>

Данная ошибка возникла из-за того что не было вызова метода "Close".

3)В результате все тесты прошли успешно. Это показано на рисунке 3.

![Image of Yaktocat](https://github.com/valeti00/labrab/blob/master/labrab9/qtcreator_NsuugRsNrL.png?raw=true) 
<center>Рис. 3. Результат тестирования</center>
<br></br>

Вывод: Все цели и задачи лабораторной работы были выполнены в полном объеме. Были получены навыки в работе с Visual Studio на языке C++ и с языком разметки Markdown. Научился тестировать классы в среде разработки Qt Creator.
