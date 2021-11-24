#include "../include/misc.hpp"
#include "../lib/googletest/googletest/include/gtest/gtest.h"
using namespace misc; 

TEST(misc, plots_fun)
{
	Plot p;
	auto f = [](long double x)->long double{return x*x;};
	p.setRange(-2, 15);
	p.generateDomain(-5, 5, 100);
	p.plotFun(f);
}

TEST(misc, plot_arr)
{
	Plot p;
	std::vector<long double> x = {-2, -1, 0, 1, 2, 3};
	std::vector<long double> y = {-4, -2, 0, 2, 4, 6};
	p.plotVect(x, y);
}

TEST(misc, table_read_csv)
{
	Table t;
	ASSERT_TRUE(t.readCSV("homes.csv"));
	ASSERT_TRUE(t.saveCSV("test.csv"));
}


int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}