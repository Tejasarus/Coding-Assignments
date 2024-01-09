#include "account.hpp"
#include "gtest/gtest.h"

TEST(Regular_Account_Info, Account) 
{
    Account t = Account("Username", "Password");
    EXPECT_EQ("Password",t.get_password());
    EXPECT_EQ("Username", t.get_username());
}
TEST(Nothing, Account) 
{
    Account t = Account("", "");
    EXPECT_EQ("",t.get_password());
    EXPECT_EQ("", t.get_username());
}
TEST(Characters, Account) 
{
    Account t = Account("#$%@!", ")(*&&^");
    EXPECT_EQ(")(*&&^",t.get_password());
    EXPECT_EQ("#$%@!", t.get_username());
}