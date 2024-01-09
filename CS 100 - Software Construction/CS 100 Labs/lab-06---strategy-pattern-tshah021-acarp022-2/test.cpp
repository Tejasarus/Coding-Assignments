#include "spreadsheet.hpp"
#include "select.hpp"
#include <string>
#include <sstream>
#include "gtest/gtest.h"

#include <iostream>

TEST(fullWord, Select_Contains){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});

    sheet.set_selection(new Select_Contains(&sheet,"First","one"));
    std::stringstream ss;
    sheet.print_selection(ss);
   
    EXPECT_EQ(ss.str(), "one two \n");
}

TEST(AtBeginning, Select_Contains){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Contains(&sheet,"First","un"));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "uno dos \n");
}

TEST(AtEnd, Select_Contains){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Contains(&sheet,"Second","wo"));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \n");
}

TEST(InTheMiddle, Select_Contains){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Contains(&sheet,"First","n"));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \nuno dos \n");
}

TEST(Caps, Select_Contains){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"ONE","caps"});
    sheet.add_row({"one","notcaps"});
    std::stringstream ss;

    sheet.set_selection(new Select_Contains(&sheet,"First","one"));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one notcaps \n");
}

TEST(Blank, Select_Contains){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Contains(&sheet,"First",""));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \nuno dos \n");
}

/////////////////////////////////////////////////////////
//// Tests for Select_Not
///////////////////////////////////////////////////////////

TEST(fullWord, Select_Not){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"First","one")));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "uno dos \n");
}

TEST(AtBeginning, Select_Not){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"First","un")));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \n");
}

TEST(AtEnd, Select_Not){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"Second","wo")));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "uno dos \n");
}

TEST(InTheMiddle, Select_Not){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uo","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"First","n")));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "uo dos \n");
}

TEST(Caps, Select_Not){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"ONE","caps"});
    sheet.add_row({"one","notcaps"});
    std::stringstream ss;

    sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"First","one")));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "ONE caps \n");
}

TEST(BlankSoEmpty, Select_Not){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"First","")));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "");
}

/////////////////////////////////////////////////////////
//// Tests for Select_And
///////////////////////////////////////////////////////////

TEST(doubleContain, Select_And){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_And(new Select_Contains(&sheet,"First","o"), new Select_Contains(&sheet,"First","e")));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \n");
}

TEST(ContainAndNot, Select_And){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_And(new Select_Contains(&sheet,"First","o"), new Select_Not(new Select_Contains(&sheet,"First","u"))));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \n");
}

TEST(DoubleNot, Select_And){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_And(new Select_Not(new Select_Contains(&sheet,"First","z")), new Select_Not(new Select_Contains(&sheet,"First","u"))));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \n");
}

/////////////////////////////////////////////////
//// Tests for Select_Or
//////////////////////////////////////////////////


TEST(doubleContain, Select_Or){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"First","z"), new Select_Contains(&sheet,"First","e")));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \n");
}

TEST(ContainAndNot, Select_Or){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"First","u"), new Select_Not(new Select_Contains(&sheet,"First","u"))));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \nuno dos \n");
}

TEST(DoubleNot, Select_Or){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Or(new Select_Not(new Select_Contains(&sheet,"First","z")), new Select_Not(new Select_Contains(&sheet,"First","u"))));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "one two \nuno dos \n");
}

//////////////////////////////////////////////
//// Tests for print_selection
//////////////////////////////////////////////

TEST(NullSelect, print_selection){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.print_selection(ss);
    EXPECT_EQ(ss.str(), "one two \nuno dos \n");
}

TEST(Empty, print_selection){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second"});
    sheet.add_row({"one","two"});
    sheet.add_row({"uno","dos"});
    std::stringstream ss;

    sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"First","")));

    sheet.print_selection(ss);
    EXPECT_EQ(ss.str(), "");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
