#pragma once 
#include <vector>
#include <iterator>
#include <iostream>
#include <utility>

#include "misc.hpp"
namespace intp
{
    class LinearInterp
    {
        private:
            // original 
            std::vector<long double> x;
            std::vector<long double> y;
            // interpolated only 
            std::vector<long double> x_in;
            std::vector<long double> y_in;
            // original + interpolated 
            std::vector<long double> x_comb;
            std::vector<long double> y_comb;
            int n; // size of original 
            misc::Plot p;

            virtual long double _find_value(long double xx, 
            std::vector<long double> _x, std::vector<long double> _y){
                std::vector<std::pair<long double, long double>> _points;
                for(int i = 0; i < _x.size(); i++){
                    _points.push_back({_x[i], _y[i]});
                }
                std::sort(_points.begin(), _points.end());

                //Define a lambda that returns true if the x value
                //of a point pair is < the caller's x value
                auto lessThan =
                    [](std::pair<double, double> point, double xxx)
                    {return point.first < xxx;};
                
                //Find the first table entry whose value is >= caller's x value
                auto iter =
                    std::lower_bound(_points.cbegin(), _points.cend(), xx, lessThan);
                
                //If the caller's X value is greater than the largest
                //X value in the table, we can't interpolate.
                if(iter == _points.cend()) {
                    return (_points.cend() - 1)->second;
                }
                
                //If the caller's X value is less than the smallest X value in the table,
                //we can't interpolate.
                if(iter == _points.cbegin() && xx <= _points.cbegin()->first) {
                    return _points.cbegin()->second;
                }
                
                //We can interpolate!
                long double upperX = iter->first;
                long double upperY = iter->second;
                long double lowerX = (iter - 1)->first;
                long double lowerY = (iter - 1)->second;
                
                long double deltaY = upperY - lowerY;
                long double deltaX = upperX - lowerX;
                
                long double yy  = lowerY + ((xx - lowerX)/ deltaX) * deltaY;

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
                    throw std::invalid_argument("intp::LinearInterp::load_data -> Size mismatch");
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
                x_in.clear();
                y_in.clear();
            }

            long double find_value(long double xx, bool use_combined = false){
                if(use_combined == true){
                    return _find_value(xx, x_comb, y_comb);
                }
                return _find_value(xx, x, y);
            }

            void reset_interpolated(){
                x_in.clear();
                y_in.clear();
                x_comb = x;
                y_comb = y;
            }

            void plot_all_interpolation(int nn = 400){
                auto dmn = misc::generate_vector(
                misc::Table::get_min(x), misc::Table::get_max(x),
                nn);
                for(int i = 0; i < dmn.size(); i++){
                    find_value(dmn[i]);
                }
                plot_combined_data();
                reset_interpolated();
            }

            void plot_data(){
                p.set_domain(
                std::min(misc::Table::get_min(x)-2.0, (long double) -1.0), 
                std::max(misc::Table::get_max(x)+2.0, (long double) 1.0)
                );
                p.set_range(
                std::min(misc::Table::get_min(y)-2.0, (long double) -1.0), 
                std::max(misc::Table::get_max(y)+2.0, (long double) 1.0)
                );     
                p.set_title("Original data");
                p.set_color(misc::Plot::Color::yellow);
                p.plot_vect(x, y);         
            }

            void plot_interpolated_data(){
                if(!x_in.empty()){
                    p.set_domain(
                    std::min(misc::Table::get_min(x_in)-2.0, (long double) -1.0), 
                    std::max(misc::Table::get_max(x_in)+2.0, (long double) 1.0)
                    );
                    p.set_range(
                    std::min(misc::Table::get_min(y_in)-2.0, (long double) -1.0), 
                    std::max(misc::Table::get_max(y_in)+2.0, (long double) 1.0)
                    ); 
                    p.set_title("Interpolated data");
                    p.set_color(misc::Plot::Color::green);
                    p.plot_vect(x_in, y_in);    
                }             
            }

            void plot_combined_data(){
                p.set_domain(
                std::min(misc::Table::get_min(x_comb)-2.0, (long double) -1.0), 
                std::max(misc::Table::get_max(x_comb)+2.0, (long double) 1.0)
                );
                p.set_range(
                std::min(misc::Table::get_min(y_comb)-2.0, (long double) -1.0), 
                std::max(misc::Table::get_max(y_comb)+2.0, (long double) 1.0)
                );     
                p.set_title("Combined data");
                p.set_color(misc::Plot::Color::blue);
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

            long double get_r_original_data(){
                return misc::Table::get_r(x, y);
            }

            long double get_r_combined_data(){
                return misc::Table::get_r(x_comb, y_comb);
            }    

            friend class PolyInterp;
    };

    class PolyInterp : public LinearInterp
    {
        private:            
            long double _find_value(long double xx, 
            std::vector<long double> _x, std::vector<long double> _y){
                std::vector<std::pair<long double, long double>> _points;
                for(int i = 0; i < _x.size(); i++){
                    _points.push_back({_x[i], _y[i]});
                }
                std::sort(_points.begin(), _points.end());

                //Define a lambda that returns true if the x value
                //of a point pair is < the caller's x value
                auto lessThan =
                    [](std::pair<double, double> point, double xxx)
                    {return point.first < xxx;};
                
                //Find the first table entry whose value is >= caller's x value
                auto iter =
                    std::lower_bound(_points.cbegin(), _points.cend(), xx, lessThan);
                
                //If the caller's X value is greater than the largest
                //X value in the table, we can't interpolate.
                if(iter == _points.cend()) {
                    return (_points.cend() - 1)->second;
                }
                
                //If the caller's X value is less than the smallest X value in the table,
                //we can't interpolate.
                if(iter == _points.cbegin() && xx <= _points.cbegin()->first) {
                    return _points.cbegin()->second;
                }

                // Implementing Lagrange Interpolation 
                long double yy = 0;
                for (int i = 0; i < n; i++){
                    long double m = 1;
                    for (int j = 0; j < n; j++){
                        if (i != j)
                            m = m * (xx - _points[j].first) / (_points[i].first - _points[j].first);
                    }
                    m = m * _points[i].second;
                    yy = yy + m;
                }

                x_comb.push_back(xx);
                y_comb.push_back(yy);
                x_in.push_back(xx);
                y_in.push_back(yy);
                return yy;            
            }
        public:
            PolyInterp(){}
    };   
    
} // namespace Int
