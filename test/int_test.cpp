#include "../include/intp.hpp"
#include "../lib/googletest/googletest/include/gtest/gtest.h"

using namespace intp; 



TEST(intp, linear_data_test)
{
   std::vector<long double> x = {7.5, 1.5, 0.5, 3.5};
   std::vector<long double> y = {32.0, 20.0, 10.0, 28.0};

   LinearInterp lip;
   lip.load_data(x, y);

   ASSERT_DOUBLE_EQ(lip.find_value(2.5), 24.0);
   ASSERT_DOUBLE_EQ(lip.find_value(5.5), 30.0);
   ASSERT_DOUBLE_EQ(lip.find_value(1.0), 15.0);
}


TEST(intp, linear_show_plots)
{
   std::vector<long double> x = {7.5, 1.5, 0.5, 3.5};
   std::vector<long double> y = {32.0, 20.0, 10.0, 28.0};

   LinearInterp lip;
   lip.load_data(x, y);

   lip.find_value(2.5);
   lip.find_value(5.5);
   lip.find_value(1.0);

   lip.plot_data();
   lip.plot_combined_data();
   lip.plot_interpolated_data(); 
}

TEST(intp, linear_show_table)
{
   std::vector<long double> x = {7.5, 1.5, 0.5, 3.5};
   std::vector<long double> y = {32.0, 20.0, 10.0, 28.0};

   LinearInterp lip;
   lip.load_data(x, y);

   lip.find_value(2.5);
   lip.find_value(5.5);
   lip.find_value(1.0);

   lip.get_original_data().show();
   std::cout << "\n";
   lip.get_combined_data().show();
   std::cout << "\n";
   lip.get_interpolated_data().show(); 
}



int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}