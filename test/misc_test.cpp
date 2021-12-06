#include "../include/misc.hpp"
#include "../lib/googletest/googletest/include/gtest/gtest.h"
using namespace misc; 

TEST(misc, plots_fun)
{
	Plot p;
	auto f = [](long double x)->long double{return x*x;};
	p.set_range(-2, 15);
	p.generate_domain(-5, 5, 100);
	p.plot_fun(f);
}

TEST(misc, plot_arr)
{
	Plot p;
	std::vector<long double> x = {-2, -1, 0, 1, 2, 3};
	std::vector<long double> y = {-4, -2, 0, 2, 4, 6};
	p.plot_vect(x, y);
}

TEST(misc, table_read_csv)
{
	Table t;
	ASSERT_TRUE(t.read_csv("homes.csv"));
	ASSERT_TRUE(t.save_csv("test.csv"));
}

TEST(misc, table_header)
{
	Table t;
	t.read_csv("home.csv");
	std::vector<long double> sold = t["Sell"];
	ASSERT_TRUE(t.size() == sold.size());
	for(int i = 0; i < sold.size(); i++){
		ASSERT_TRUE(t.at(i).at(0) == sold[i]);
	}
}

TEST(misc, table_qr_sort_asc)
{
	// to string 
	auto qr = Table::get_qr(
		{5.0, 8.2, 10.3, 10.3, 15.2, 18.2, 23.1});
	Table::QR qr_answer = {5.0, 8.2, 10.3, 18.2, 23.1};
	ASSERT_TRUE(qr_answer.LQ == qr.LQ);
	ASSERT_TRUE(qr_answer.Q1 == qr.Q1);
	ASSERT_TRUE(qr_answer.Q2 == qr.Q2);
	ASSERT_TRUE(qr_answer.Q3 == qr.Q3);
	ASSERT_TRUE(qr_answer.UQ == qr.UQ);
}

TEST(misc, table_mean_std_var_sum)
{
	std::vector<long double> a = {10.0, 8.0, 10.0, 8.0, 8.0, 4.0};  
	ASSERT_DOUBLE_EQ(Table::get_std(a), 2.0);
}

TEST(misc, table_describe_all)
{
	Table t;
	t.read_csv("homes.csv");
	auto t2 = t.describe_all();
	t2.show();
}


TEST(misc, table_show_row)
{
	Table t;
	t.read_csv("homes.csv");
	auto tt = t.get_row(2);
	tt.show();
}

TEST(misc, table_show_col)
{
	Table t;
	t.read_csv("homes.csv");
	auto tt = t.get_col("Sell");
	tt.show();
}

TEST(misc, table_add_col)
{
	Table t;
	t.add_col("x1", {1, 2, 3, 4});
	t.add_col("x2", {5, 6, 7, 8});
	t.add_col("x3", {9, 10, 11, 12});
	t.show();

}

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}