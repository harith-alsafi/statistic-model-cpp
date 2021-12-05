#include "../include/regr.hpp"
#include "../lib/googletest/googletest/include/gtest/gtest.h"

using namespace regr; 

TEST(reg, lr_showing)
{
   LinearRegression lr;
   lr.load_data(
      {0, 2, 5, 7},
      {-1, 5, 12, 20});
   lr.fit_data();
   lr.show_equation();
   lr.plot_equation();
   lr.get_data().show();
   lr.plot_data();
}

TEST(reg, lr_values)
{
   LinearRegression lr;
   lr.load_data(
      {0, 2, 5, 7},
      {-1, 5, 12, 20});
   lr.fit_data();
   ASSERT_DOUBLE_EQ(round(lr.get_original_r(), 4), 0.9945);
   ASSERT_DOUBLE_EQ(round(lr.get_slope(), 3), 2.897);
   ASSERT_DOUBLE_EQ(round(lr.get_y_intersept(), 3), -1.138);

}

TEST(reg, pr_showing)
{
   PolyRegression pr;

   
}

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}