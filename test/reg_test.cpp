#include "../include/reg.hpp"
#include "../lib/googletest/googletest/include/gtest/gtest.h"

using namespace regr; 

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}