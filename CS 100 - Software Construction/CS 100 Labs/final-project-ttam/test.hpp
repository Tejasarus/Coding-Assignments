#include "account.hpp"
#include "Weather.hpp"
#include "calendar.hpp"
#include <vector>
#include <string>
#include <iostream>
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
TEST(TypicalCalendar, Calendar) 
{
    Calendar test = Calendar("poopy", 13, 13, 13, 13, 13,'p', "test event");
    EXPECT_EQ( "poopy", test.getEventName());
    EXPECT_EQ( 13, test.getEventMonth());
    EXPECT_EQ( 13, test.getEventDay());
    EXPECT_EQ( 13, test.getEventYear());
    EXPECT_EQ( 13, test.getEventHour());
    EXPECT_EQ( 13, test.getEventMin());
    EXPECT_EQ( "PM", test.getDayTime());
    EXPECT_EQ( "test event", test.getEventDesc());
}
TEST(Long, Calendar) 
{
     Calendar test = Calendar("poopyasdfasdfasdfasdfasdfasdfasdfasdfasdf", 123, 132, 123, 123, 123, 'p', "asdfasdfasdfasdfasdfasfhgsdfghsdfghsdfgh event");
    EXPECT_EQ( "poopyasdfasdfasdfasdfasdfasdfasdfasdfasdf", test.getEventName());
    EXPECT_EQ( 123, test.getEventMonth());
    EXPECT_EQ( 132, test.getEventDay());
    EXPECT_EQ( 123, test.getEventYear());
    EXPECT_EQ( 123, test.getEventHour());
    EXPECT_EQ( 123, test.getEventMin());
    EXPECT_EQ( "PM", test.getDayTime());
    EXPECT_EQ( "asdfasdfasdfasdfasdfasfhgsdfghsdfghsdfgh event", test.getEventDesc());
}
TEST(Characters, Calendar) 
{
    Calendar test = Calendar("@#$$%", 123, 132, 123, 123, 123, 'p', "@#$#%#$%$%");
    EXPECT_EQ( "@#$$%", test.getEventName());
    EXPECT_EQ("@#$#%#$%$%", test.getEventDesc());



}

TEST(AllTests, convertJson){
    Weather* wthr = new Weather();
    std::vector<std::string> list;
    list = wthr->convertJson("\"description\":\"rain\"},\"w,\"temp\":74.4,\"mm\"description\":\"rain\"},\"w,\"temp\":74.4,\"mm\"description\":\"rain\"},\"w,\"temp\":74.4,\"mm\"description\":\"rain\"},\"w,\"temp\":74.4,\"mm\"description\":\"rain\"},\"w,\"temp\":74.4,\"mm\"description\":\"rain\"},\"w,\"temp\":74.4,\"mm\"description\":\"rain\"},\"w,\"temp\":74.4,\"mm\"description\":\"rain\"},\"w,\"temp\":74.4,\"mm\"description\":\"rain\"},\"w,\"temp\":74.4,\"m\"description\":\"rain\"},\"w,\"temp\":74.4,\"m\"description\":\"rain\"},\"w,\"temp\":74.4,\"m\"description\":\"rain\"},\"w,\"temp\":74.4,\"m\"description\":\"rain\"},\"w,\"temp\":74.4,\"m\"description\":\"rain\"},\"w,\"temp\":74.4,\"m\"description\":\"rain\"},\"w,\"temp\":74.4,\"m\"description\":\"rain\"},\"w,\"temp\":74.4,\"");

    ASSERT_EQ(list.size(), 28);

    for(int i = 0; i < list.size()/2; i++){
        EXPECT_EQ(list[i], "rain");
        EXPECT_EQ(list[i+14], "74.4");
    }
}

