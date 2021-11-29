#include "../include/reg.hpp"
#include "../lib/googletest/googletest/include/gtest/gtest.h"

using namespace regr; 

TEST(reg, lr_t1)
{
   LinearRegression lr;
   lr.load_data(
      {0, 2, 5, 7},
      {-1, 5, 12, 20});
   lr.fit_data();
   lr.show_equation();
   lr.plot_equation();
   lr.get_data().show();
   lr.plot_original_data();
}


int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}