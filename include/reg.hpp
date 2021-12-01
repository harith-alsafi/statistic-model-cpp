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
            long double fun(long double xx){
                return (long double)m*xx+c;
            }
            void calculate_r(){
                r = (n*sumxy-(sumx*sumy))/
                (sqrt((n*sumxx-pow(sumx, 2))*(n*sumyy-pow(sumy, 2))));
            }
        
        public:
            LinearRegression(){}


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
                calculate_r();
            }

            void show_equation(){
                std::cout << std::fixed;
                std::cout << std::setprecision(3);
                std::cout << "y = " << m << "⋅" << "x" << " + " << c << "\n"
                << "r: " << r << "    r²: " << std::pow(r, 2) << "\n";
            }

            void plot_equation(int nn=100){
                auto f = [&](long double xx)->long double{return fun(xx);};
                misc::Plot p;
                p.set_domain(
                misc::Table::get_min(x)-2, misc::Table::get_max(x)+2
                );
                p.set_range(
                misc::Table::get_min(yfit)-2, misc::Table::get_max(yfit)+2
                );
                p.generate_domain(
                misc::Table::get_min(x), misc::Table::get_max(x), x.size()+nn);
                p.set_title("Equation with " + to_string(nn) + " data points");
                p.set_color(misc::Plot::Color::blue);
                p.plot_fun(f);
            }

            void plot_data(){
                misc::Plot p;
                p.set_domain(
                misc::Table::get_min(x)-2, misc::Table::get_max(x)+2
                );
                p.set_range(
                misc::Table::get_min(y)-2, misc::Table::get_max(y)+2
                );     

                p.set_title("Original data");
                p.set_color(misc::Plot::Color::yellow);
                p.plot_vect(x, y);         

                p.set_title("Fitted data");
                p.set_color(misc::Plot::Color::green);
                p.plot_vect(x, yfit);           
            }

            misc::Table get_data(){
                misc::Table t;
                t.add_col("x-data", x);
                t.add_col("y-data", y);
                t.add_col("yfit-data", yfit);
                return t;
            }
            friend class PolyRegression; 
    };

    class PolyRegression: public LinearRegression
    {
        private:   
            using LinearRegression::get_y_intersept;
            using LinearRegression::get_slope;

            long double fun(long double xx){
                long double sm = 0;
                for(int i = 0; i < coef.size(); i++){
                    sm += coef[i]*pow(xx, i);
                }
                return sm;
            }

            std::vector<long double> coef;
            int degree; 
            const std::vector<std::string> powers = 
            {"", "", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹"};

            std::string get_power(int i){
                std::string str;
                if(i > 9){
                    while (i > 0)
                    {
                        int digit = i%10;
                        i /= 10;
                        str += powers[i];
                    }
                }
                else if(i == 0){
                    return "";
                }
                else{
                    str = powers[i];
                }
                return "⋅x"+str;
            }


        public:
            PolyRegression(){}

            void set_degree(int deg = 3){
                degree = deg;
            }

            void show_equation(){ 
                std::cout << std::fixed;
                std::cout << std::setprecision(3);
                std::cout << "y = ";
                for(int i = coef.size()-1; i >= 0; i--){
                    if(i != 0){
                        std::cout << coef[i] << get_power(i) << " + ";
                    }
                    else{
                        std::cout << coef[i] << get_power(i);
                    }
                }
                std::cout << "\n";
                std::cout << "r: " << r << "    r²: " << std::pow(r, 2) << "\n";
            }

    };
} 