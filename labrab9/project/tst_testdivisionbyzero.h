#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lockcontroller.h>


using namespace testing;

class MockIKeypad : public IKeypad {
public:
    MOCK_METHOD(bool, isActive, ());
    MOCK_METHOD(void, wait, ());
    MOCK_METHOD(PasswordResponse, requestPassword, ());
};

class MockILatch : public ILatch {
public:
    MOCK_METHOD(bool, isActive, ());
    MOCK_METHOD(DoorStatus, open, ());
    MOCK_METHOD(DoorStatus, close, ());
    MOCK_METHOD(DoorStatus, getDoorStatus, ());
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
    EXPECT_FALSE(Door.isDoorOpen());
}

TEST(Lab9, test3){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, getDoorStatus()) .Times(1) .WillOnce (Return(DoorStatus::OPEN));
    EXPECT_TRUE(Door.isDoorOpen());

}

TEST(Lab9, test4){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, open()) .Times(1);
    EXPECT_EQ(Door.unlockDoor(),DoorStatus::OPEN);

}


TEST(Lab9, test5){
   MockILatch ILatch;
   MockIKeypad IKeypad;
   LockController Door(&IKeypad, &ILatch);
   EXPECT_CALL(ILatch, close()) .Times(1) .WillOnce(Return(DoorStatus::CLOSE));
   EXPECT_EQ(Door.lockDoor(),DoorStatus::CLOSE);

}

TEST(Lab9, test6){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, isActive()) .Times(1) .WillOnce(Return(1));
    EXPECT_CALL(IKeypad, isActive()) .Times(1) .WillOnce(Return(1));
    EXPECT_EQ(Door.hardWareCheck(),HardWareStatus::OK);
}

TEST(Lab9, test7){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(nullptr, &ILatch);
    EXPECT_CALL(ILatch, isActive()) .Times(AtLeast(0)) .WillOnce(Return(1));
    EXPECT_CALL(IKeypad, isActive()) .Times(AtLeast(0)) .WillOnce(Return(1));
    EXPECT_EQ(Door.hardWareCheck(),HardWareStatus::ERROR);

}

TEST(Lab9, test8){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    EXPECT_CALL(ILatch, isActive()) .Times(AtLeast(0)) .WillOnce(Return(0));
    EXPECT_CALL(IKeypad, isActive()) .Times(AtLeast(0)) .WillOnce(Return(1));
    EXPECT_EQ(Door.hardWareCheck(),HardWareStatus::ERROR);

}

TEST(Lab9, test9){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse passResp{PasswordResponse::Status::OK,"0000"};
    EXPECT_CALL(IKeypad, requestPassword()) .Times(1) .WillOnce(Return(passResp));
    EXPECT_TRUE(Door.isCorrectPassword());
}

TEST(Lab9, test10){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse passResp{PasswordResponse::Status::OK,"1111"};
    EXPECT_CALL(IKeypad, requestPassword()) .Times(1) .WillOnce(Return(passResp));
    EXPECT_FALSE(Door.isCorrectPassword());
}


TEST(Lab9, test11){
    MockILatch ILatch;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &ILatch);
    PasswordResponse oldPass{PasswordResponse::Status::OK,"0000"};
    PasswordResponse newPass{PasswordResponse::Status::OK,"1111"};
    EXPECT_CALL(IKeypad, requestPassword())
            .Times(2)
            .WillOnce(Return(oldPass))
            .WillOnce(Return(newPass));
            Door.resetPassword();
    EXPECT_CALL(IKeypad, requestPassword()) .Times(1) .WillOnce(Return(newPass));
    EXPECT_TRUE(Door.isCorrectPassword());
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
