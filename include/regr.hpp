#pragma once
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
            long double sumx; // sum of x's
            long double sumy; // sum of y's
            long double sumxx; // sum of x^2
            long double sumxy; // sum of x*y
            int n; // size of vetors 
            misc::Plot p;
            // function 
            virtual long double fun(long double xx){
                return (long double)m*xx+c;
            }
        
        public:
            LinearRegression(){}

            long double get_slope(){return m;}

            long double get_y_intersept(){return c;}

            std::vector<long double> get_fit_data(){return yfit;}

            long double get_original_r(){return misc::Table::get_r(x, y);}

            long double get_fitted_r(){return misc::Table::get_r(x, yfit);}

            long double load_data(std::vector<long double> xx, std::vector<long double> yy){
                if(xx.size() != yy.size()){
                    throw std::invalid_argument("regr::LinearRegression::load_data -> Size mismatch");
                }
                if (xx.size() == 0 || yy.size() == 0) {
                    throw std::invalid_argument( "regr::LinearRegression::load_data -> Input is size = 0" );
                }
                x = xx;
                y = yy;
                n = xx.size();
                sumx = misc::Table::get_sum(x);
                sumy = misc::Table::get_sum(y);
                sumxx = misc::Table::get_sum(x*x);
                sumxy = misc::Table::get_sum(x*y);
            }

            virtual void fit_data(){
                m = (n*sumxy-sumx*sumy)/(n*sumxx-sumx*sumx);
                c = (sumy-m*sumx)/n;
                yfit.clear();
                for(int i = 0; i < n; i++){
                    yfit.push_back(fun(x[i]));
                }
            }

            virtual void show_equation(){
                std::cout << std::fixed;
                std::cout << std::setprecision(3);
                std::cout << "y = " << m << "⋅" << "x" << " + " << c << "\n"
                << "r: " << get_original_r() << "    r²: " 
                << std::pow(get_original_r(), 2) << "\n";
            }

            void plot_equation(int nn=500){
                auto f = [&](long double xx)->long double{return fun(xx);};
                p.set_domain(
                std::min(misc::Table::get_min(x)-2.0, (long double) -1.0), 
                std::max(misc::Table::get_max(x)+2.0, (long double) 1.0)
                );
                p.set_range(
                std::min(misc::Table::get_min(y)-2.0, (long double) -1.0), 
                std::max(misc::Table::get_max(y)+2.0, (long double) 1.0)
                );
                p.generate_domain(
                std::min(misc::Table::get_min(x)-2.0, (long double) -1.0), 
                std::max(misc::Table::get_max(x)+2.0, (long double) 1.0),
                x.size()+nn
                );
                p.set_title("Regression equation with " + to_string(nn) + " data points");
                p.set_color(misc::Plot::Color::blue);
                p.plot_fun(f);
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

                p.set_title("Predicted data from original x-input");
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
            std::vector<long double> coeff;

            long double fun(long double xx){
                long double sm = 0;
                for(int i = 0; i < coeff.size(); i++){
                    sm += coeff[i]*pow(xx, i);
                }
                return sm;
            }
            
            int degree; 

            std::string get_power(int i){
                const std::vector<std::string> powers = 
                {"", "", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹"};
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

            void set_degree(int deg = 2){
                degree = deg;
            }

            void show_equation(){ 
                std::cout << std::fixed;
                std::cout << std::setprecision(3);
                if(!coeff.empty()){
                    std::cout << "y = ";
                    for(int i = coeff.size()-1; i >= 0; i--){
                        if(i != 0){
                            std::cout << coeff[i] << get_power(i) << " + ";
                        }
                        else{
                            std::cout << coeff[i] << get_power(i);
                        }
                    }
                    std::cout << "\n";
                    std::cout << "r: " << get_original_r() << "    r²: " 
                    << std::pow(get_original_r(), 2) << "\n";
                }
            }

            void fit_data(){   
                int i,j,k;
                //Array that will store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
                double X[2*degree+1];                        
                for (i = 0; i < 2*degree+1; i++){
                    X[i]=0;
                    //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
                    for (j=0;j<n;j++){
                        X[i]=X[i]+pow(x[j],i);
                    }
                }
                //B is the Normal matrix(augmented) that will store the equations, 'a' is for value of the final coefficients
                double B[degree+1][degree+2],a[degree+1];
                 //Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix            
                for (i = 0; i <= degree; i++){
                    for (j=0;j<=degree;j++){
                        B[i][j]=X[i+j];
                    }
                }
                //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
                double Y[degree+1];
                //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)                    
                for (i = 0; i < degree+1; i++){    
                    Y[i]=0;
                    for (j = 0; j < n; j++){
                        Y[i]=Y[i]+pow(x[j],i)*y[j];
                    }       
                }
                 //load the values of Y as the last column of B(Normal Matrix but augmented)
                for (i = 0; i <= degree; i++){
                    B[i][degree+1]=Y[i];               
                }
                //n is made n+1 because the Gaussian Elimination part below was for n equations, but here n is the degree of polynomial and for n degree we get n+1 equations 
                degree=degree+1; 
                 //From now Gaussian Elimination starts(can be ignored) to solve the set of linear equations (Pivotisation)               
                for (i = 0; i < degree; i++){
                    for (k = i+1; k < degree; k++){
                       if (B[i][i]<B[k][i]){
                            for (j = 0; j <= degree; j++){
                                double temp=B[i][j];
                                B[i][j]=B[k][j];
                                B[k][j]=temp;
                            }
                       }
                    }
                }

                //loop to perform the gauss elimination
                for (i = 0; i < degree-1; i++) {
                    for (k= i+1; k < degree; k++){
                        double t=B[k][i]/B[i][i];
                        //make the elements below the pivot elements equal to zero or elimnate the variables
                        for (j = 0; j <= degree; j++){
                            B[k][j]=B[k][j]-t*B[i][j];
                        }            
                    }
                }  

                //back-substitution
                for (i = degree-1; i >= 0; i--){                        
                     //make the variable to be calculated equal to the rhs of the last equation
                    a[i]=B[i][degree];               
                    for (j = 0; j < degree; j++){
                        if (j!=i){
                            //then subtract all the lhs values except the coefficient of the variable whose value is being calculated
                            a[i]=a[i]-B[i][j]*a[j];
                        }
                    }
                    //now finally divide the rhs by the coefficient of the variable to be calculated
                    a[i]=a[i]/B[i][i];            
                }
                coeff.clear();
                for(i = 0; i < degree; i++){
                    coeff.push_back(a[i]);
                }    
                yfit.clear();
                for(int i = 0; i < n; i++){
                    yfit.push_back(fun(x[i]));
                }        
            }
    };
} 