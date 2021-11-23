#include "../include/int.hpp"
#include "../lib/googletest/googletest/include/gtest/gtest.h"

using namespace intp; 

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}