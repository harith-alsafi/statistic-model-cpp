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
   std::vector<long double> x = {6.0, 2.0, 1.0, 5.0, 4.0, 3.0};
   std::vector<long double> y = {3.0, 3.0, 2.0, 1.0, -2.0, 1.0};

   LinearInterp lip;
   lip.load_data(x, y);

   lip.plot_data();
   lip.plot_combined_data();
   lip.plot_interpolated_data(); 
   lip.plot_all_interpolation();
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

TEST(intp, poly_data_test)
{
   std::vector<long double> x = {5.0, 7.0, 11.0, 13.0, 17.0};
   std::vector<long double> y = {150.0, 392.0, 1452.0, 2366.0, 5202.0 };

   PolyInterp pip;
   pip.load_data(x, y);


   ASSERT_DOUBLE_EQ(pip.find_value(9.0), 810.0);
}

TEST(intp, poly_plots)
{
   misc::Table t;
   t.read_csv("homes.csv");

   std::vector<long double> x = {6.0, 2.0, 1.0, 5.0, 4.0, 3.0, 7.0, 8.0, 9.0};
   std::vector<long double> y = {3.0, 3.0, 2.0, 1.0, -2.0, 1.0, 3.5, 4.5, 3.0};

   PolyInterp pip;
   pip.load_data(x, y);
   pip.plot_data();
   pip.plot_all_interpolation();
}

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}