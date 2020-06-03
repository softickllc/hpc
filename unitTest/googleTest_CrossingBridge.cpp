#include <limits.h>
#include <gtest/gtest.h>
#include "CrossBridgeTest.cpp"

//Test1: Read Yaml
TEST(ReadYamlTest,readYamlvalid){
    ReadYAML testYamlData;
    EXPECT_EQ(1,testYamlData.readYaml());
}


//Test2: get the Minimum crossing time

TEST(MinCrossingTimeTest,singleBridge){
    CrossingBridge testMinTime(0.0);
    EXPECT_EQ(25,testMinTime.get_minimum_crossing_time(5,{ 1, 2, 5, 10, 12 }));
    EXPECT_EQ(17,testMinTime.get_minimum_crossing_time(4,{ 1, 2, 5, 10 }));
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
