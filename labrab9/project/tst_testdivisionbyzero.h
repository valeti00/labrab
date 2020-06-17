#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lockcontroller.h>
#include <ILatch.h>
#include <IKeypad.h>

using namespace testing;

class MockILatch: public ILatch{
public:
    MOCK_METHOD(bool, isActive, (), (override));
    MOCK_METHOD(DoorStatus, open,(),(override));
    MOCK_METHOD(DoorStatus, close,(), (override));
    MOCK_METHOD(DoorStatus, getDoorStatus,(),(override));
};

class MockIKeypad: public IKeypad{
public:
   MOCK_METHOD (bool, isActive,(),(override));
   MOCK_METHOD (void, wait,(),(override));
   MOCK_METHOD (PasswordResponse, requestPassword,(),(override));
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
    bool Return=Door.isDoorOpen();
    EXPECT_FALSE(Return);
}

TEST(Lab9, test3){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, getDoorStatus()) .Times(1) .WillOnce (Return(DoorStatus::OPEN));
    bool Return=Door.isDoorOpen();
    EXPECT_TRUE(Return);

}

TEST(Lab9, test4){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, open()) .Times(1);
    DoorStatus Return= Door.unlockDoor();
    EXPECT_EQ(Return,DoorStatus::OPEN);

}


TEST(Lab9, test5){
   MockILatch ILatch;
   MockIKeypad IKeypad;
   LockController Door(&IKeypad, &ILatch);
   EXPECT_CALL(ILatch, close()) .Times(1) .WillOnce(Return(DoorStatus::CLOSE));
   DoorStatus Return= Door.lockDoor();
   EXPECT_EQ(Return,DoorStatus::CLOSE);

}

TEST(Lab9, test6){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, isActive()) .Times(1) .WillOnce(Return(1));
    EXPECT_CALL(IKeypad, isActive()) .Times(1) .WillOnce(Return(1));
    HardWareStatus Return=Door.hardWareCheck();
    EXPECT_EQ(Return,HardWareStatus::OK);
}

TEST(Lab9, test7){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(nullptr, &ILatch);
    EXPECT_CALL(ILatch, isActive()) .Times(AtLeast(0)) .WillOnce(Return(1));
    EXPECT_CALL(IKeypad, isActive()) .Times(AtLeast(0)) .WillOnce(Return(1));
    HardWareStatus Return=Door.hardWareCheck();
    EXPECT_EQ(Return,HardWareStatus::ERROR);

}

TEST(Lab9, test8){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, isActive()) .Times(AtLeast(0)) .WillOnce(Return(0));
    EXPECT_CALL(IKeypad, isActive()) .Times(AtLeast(0)) .WillOnce(Return(1));
    HardWareStatus Return=Door.hardWareCheck();
    EXPECT_EQ(Return,HardWareStatus::ERROR);

}

TEST(Lab9, test9){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse passResp{PasswordResponse::Status::OK,"0000"};
    EXPECT_CALL(IKeypad, requestPassword()) .Times(1) .WillOnce(Return(passResp));
    bool Return=Door.isCorrectPassword();
    EXPECT_TRUE(Return);
}

TEST(Lab9, test10){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse passResp{PasswordResponse::Status::OK,"0100"};
    EXPECT_CALL(IKeypad, requestPassword()) .Times(1) .WillOnce(Return(passResp));
    bool Return=Door.isCorrectPassword();
    EXPECT_FALSE(Return);
}


TEST(Lab9, test11){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse oldPass{PasswordResponse::Status::OK,"0000"};
    PasswordResponse newPass{PasswordResponse::Status::OK,"9876"};
    EXPECT_CALL(IKeypad, requestPassword())
            .Times(2)
            .WillOnce(Return(oldPass))
            .WillOnce(Return(newPass));
            Door.resetPassword();
     EXPECT_CALL(IKeypad, requestPassword()) .Times(1) .WillOnce(Return(newPass));
     bool Return=Door.isCorrectPassword();
      EXPECT_TRUE(Return);
}


TEST(Lab9, test12){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(IKeypad, requestPassword()).Times(Exactly(5))
                .WillOnce(Return(PasswordResponse{PasswordResponse::Status::OK, "0000"}))
                .WillOnce(Return(PasswordResponse{PasswordResponse::Status::OK, "1111"}))
                .WillOnce(Return(PasswordResponse{PasswordResponse::Status::OK, "1111"}));
    Door.resetPassword();
    Door.resetPassword();
    ASSERT_TRUE(Door.isCorrectPassword());
}


#endif // TST_TESTDIVISIONBYZERO_H
