#pragma once 
#include <vector>
#include <iterator>
#include <iostream>
#include "misc.hpp"
namespace intp
{
    class LinearInterp
    {
        private:
            std::vector<long double> x;
            std::vector<long double> y;
            std::vector<long double> x_in;
            std::vector<long double> y_in;
            std::vector<long double> x_comb;
            std::vector<long double> y_comb;
            int n; // size 

            long double _find_value(long double xx, 
            std::vector<long double> _x, std::vector<long double> _y){
                auto lessThan =
                    [](long double x1, long double x2)
                    ->bool{return x1 < x2;};

                //Find the first table entry whose value is >= caller's x value
                auto iter = std::lower_bound(_x.cbegin(), _x.cend(), xx, lessThan);

                //If the caller's X value is greater than the largest
                //X value in the table, we can't interpolate.
                if(iter == _x.cend()) {
                    return _y.at(_x.size()-1);
                }
                
                //If the caller's X value is less than the smallest X value in the table,
                //we can't interpolate.
                if(iter == _x.cbegin() && xx <= _x.at(0)) {
                    return _y.at(0);
                }
                auto indxL = std::distance
                <std::vector<long double>::const_iterator>(_x.begin(), iter);
                auto indxU = std::distance
                <std::vector<long double>::const_iterator>(_x.begin(), (iter-1));
                
                //We can interpolate!
                long double upperX = _x[indxL];
                long double upperY = _y[indxL];
                long double lowerX = _x[indxU];
                long double lowerY = _y[indxU];
                
                long double deltaY = upperY - lowerY;
                long double deltaX = upperX - lowerX;
                
                long double yy = lowerY + ((xx - lowerX)/ deltaX) * deltaY;
                x_comb.push_back(xx);
                y_comb.push_back(yy);
                x_in.push_back(xx);
                y_in.push_back(yy);
                return yy;
            }
        public:
            LinearInterp(){}

            void load_data(std::vector<long double> xx, std::vector<long double> yy){
                if(xx.size() != yy.size()){
                    throw std::invalid_argument("Invalid size");
                }
                x = xx;
                y = yy;
                x_comb = xx;
                y_comb = yy;
                n = xx.size();
                // checking validty of points 
                const long double EPSILON{1.0E-8};
                for(std::size_t i=1; i< n; ++i) {
                    long double deltaX{std::abs(x[i] - x[i-1])};
                    if(deltaX < EPSILON ) {
                        std::string err{"Potential Divide By Zero: Points " +
                            std::to_string(i-1) + " And " +
                            std::to_string(i) + " Are Too Close In Value"};
                        throw std::range_error(err);
                    }
                }
                std::sort(x.begin(), x.end());
                std::sort(y.begin(), y.end());
                x_in.clear();
                y_in.clear();
            }

            long double find_value(long double xx, bool use_combined = false){
                if(use_combined == true){
                    return _find_value(xx, x_comb, y_comb);
                }
                return _find_value(xx, x, y);
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

                p.set_domain(
                misc::Table::get_min(x_in)-2, misc::Table::get_max(x_in)+2
                );
                p.set_range(
                misc::Table::get_min(y_in)-2, misc::Table::get_max(y_in)+2
                );  
                p.set_title("Interpolated data");
                p.set_color(misc::Plot::Color::green);
                p.plot_vect(x_in, y_in);           
            }

            void plot_combined_data(){
                misc::Plot p;
                p.set_domain(
                misc::Table::get_min(x_comb)-2, misc::Table::get_max(x_comb)+2
                );
                p.set_range(
                misc::Table::get_min(y_comb)-2, misc::Table::get_max(y_comb)+2
                );     
                p.set_title("Combined data");
                p.set_color(misc::Plot::Color::yellow);
                p.plot_vect(x_comb, y_comb);                   
            }

            misc::Table get_original_data(){
                misc::Table t;
                t.add_col("x-data", x);
                t.add_col("y-data", y);
                return t;
            }

            misc::Table get_interpolated_data(){
                misc::Table t;
                t.add_col("x-data", x_in);
                t.add_col("y-interpolated-data", y_in);
                return t;
            }

            misc::Table get_combined_data(){
                misc::Table t;
                t.add_col("x-data", x_comb);
                t.add_col("y-data", y_comb);
                return t;
            }       
    };

    class PolyInterp
    {

    };   
    
} // namespace Int
