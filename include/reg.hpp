#pragma once
#include <vector> 
#include <iostream>
#include "misc.hpp"
namespace regr
{
    class LinearRegression
    {
        private:
            std::vector<long double> x;
            std::vector<long double> y;
            std::vector<long double> yfit; // fitted values 
            long double m; // slope
            long double c; // y intersept 
            long double r; // corelation coefficient
            long double sumx; // sum of x's
            long double sumy; // sum of y's
            long double sumxx; // sum of x^2
            long double sumxy; // sum of x*y
            long double sumyy; // sum of y*y
            int n; // size of vetors 
            // function 
            long double fun(long double x){
                return (long double)m*x+c;
            }
        public:
            LinearRegression(){};
            ~LinearRegression(){};

            long double get_slope(){return m;}

            long double get_y_intersept(){return c;}

            std::vector<long double> get_fit_data(){return yfit;}

            long double get_r(){
                return r;   
            }

            long double load_data(std::vector<long double> xx, std::vector<long double> yy){
                if(xx.size() != yy.size()){
                    throw std::invalid_argument("Invalid size");
                }
                x = xx;
                y = yy;
                n = xx.size();
                sumx = misc::Table::get_sum(x);
                sumy = misc::Table::get_sum(y);
                sumxx = misc::Table::get_sum(x*x);
                sumxy = misc::Table::get_sum(x*y);
            }

            long double fit_data(){
                m = (n*sumxy-sumx*sumy)/(n*sumxx-sumx*sumx);
                c = (sumy-m*sumx)/n;
                yfit.clear();
                for(int i = 0; i < n; i++){
                    yfit.push_back(fun(x[i]));
                }
                sumyy = misc::Table::get_sum(y*y);
                r = (n*sumxy-(sumx*sumy))/
                (sqrt((n*sumxx-pow(sumx, 2))*(n*sumyy-pow(sumy, 2))));
            }

            void show_equation(){
                std::cout << std::fixed;
                std::cout << std::setprecision(3);
                std::cout << "y = " << m << "⋅" << "x" << " + " << c 
                << "\t r: " << r << "\t r²: " << std::pow(r, 2) << "\n";
            }

            void plot_equation(){
                auto f = [&](long double xx)->long double{return fun(xx);};
                misc::Plot p;
                p.set_domain(
                misc::Table::get_min(x)-2, misc::Table::get_max(x)+2
                );
                p.set_range(
                misc::Table::get_min(yfit)-2, misc::Table::get_max(yfit)+2
                );
                p.generate_domain(
                misc::Table::get_min(x), misc::Table::get_max(x), x.size()+50);
                p.plot_fun(f);
            }

            void plot_original_data(){
                misc::Plot p;
                p.set_domain(
                misc::Table::get_min(x)-2, misc::Table::get_max(x)+2
                );
                p.set_range(
                misc::Table::get_min(y)-2, misc::Table::get_max(y)+2
                );     
                p.plot_vect(x, y);           
            }

            misc::Table get_data(){
                misc::Table t;
                t.add_col("x-data", x);
                t.add_col("y-data", y);
                t.add_col("yfit-data", yfit);
                return t;
            }
    };

    class PolyRegression
    {

    };
} 