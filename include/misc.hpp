#pragma once 
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
/**
 * @file misc.hpp
 * @author Harith Al-Safi
 * @brief 
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <algorithm>
#include <numeric>
#include "graphs.hpp"

/**
 * @brief Operator to multiply two vectors 
 * 
 * @tparam TYPE 
 * @param first 
 * @param second 
 * @return std::vector<TYPE> 
 */
template<typename TYPE>
std::vector<TYPE> operator *(std::vector<TYPE> first, std::vector<TYPE> second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<TYPE> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]*second[i]);
    }
    return temp;
}

/**
 * @brief Overloads the round function 
 * 
 * @tparam TYPE 
 * @param a the value itself
 * @param dp number of decimal places
 * @return TYPE 
 */
template<typename TYPE>
TYPE round(TYPE a, int dp = 0){
    if(a < TYPE(0)){
        return TYPE((int)(a*pow(10, dp)-.5)/pow(10, dp));
    }
    return TYPE((int)(a*pow(10, dp)+.5)/pow(10, dp));
}


namespace misc
{
    /**
     * @brief Genarate vector from min, max andn number of points
     * 
     * @tparam TYPE 
     * @param mn min val
     * @param mx max val
     * @param n number of points
     * @return std::vector<TYPE> 
     */
    template<typename TYPE>
    std::vector<TYPE> generate_vector(TYPE mn, TYPE mx, int n){
        std::vector<TYPE> v;
        for(TYPE i = mn; i <= mx; i+=(TYPE)(mx-mn)/n){
            v.push_back(i);
        }
        return v;
    }

    /**
     * @brief Table class to contain the dataframe 
     */
    class Table: public std::vector<std::vector<long double>>
    {
        public:

            /**
             * @brief Struct to contain the quartile range 
             * 
             */
            struct QR
            {
                long double LQ; // lower quartile 
                long double Q1; 
                long double Q2; // median
                long double Q3; 
                long double UQ; // upper quartile 
            };
        private:

            /**
             * @brief Checks the header and returns index
             * 
             * @param head 
             * @return int 
             */
            int check_header(std::string head){
                for(int i = 0; i < headers.size(); i++){
                    if(headers[i] == head){
                        return i;
                    }
                }
                return -1;
            }

            /**
             * @brief Get the col vector based on header name
             * 
             * @param headname 
             * @return std::vector<long double> 
             */
            std::vector<long double> get_col_(std::string headname){
                int j = check_header(headname);
                std::vector<long double> a;
                if(j >= 0){
                    for(int i = 0; i < size(); i++){
                        a.push_back(at(i).at(j));
                    }
                }
                return a;  
            }

            /**
             * @brief Get the return average of all colums in vector 
             * 
             * Used in describe_all()
             * 
             * @return std::vector<long double> 
             */
            std::vector<long double> get_avgs(){
                std::vector<long double> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(get_avg(get_col_(headers[j])));
                }
                return a;
            }

            /**
             * @brief Get the return std of all colums in vector 
             * 
             * Used in describe_all()
             * 
             * @return std::vector<long double> 
             */
            std::vector<long double> get_stds(){
                std::vector<long double> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(get_std(get_col_(headers[j])));
                }
                return a;             
            }

            /**
             * @brief Get the return variance of all colums in vector 
             * 
             * Used in describe_all()
             * 
             * @return std::vector<long double> 
             */            
            std::vector<long double> get_vars(){
                std::vector<long double> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(get_var(get_col_(headers[j])));
                }
                return a;
            }

            /**
             * @brief Get the return quartile range of all colums in vector 
             * 
             * Used in describe_all()
             * 
             * @return std::vector<long double> 
             */
            std::vector<QR> get_qrs(){
                std::vector<QR> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(get_qr(get_col_(headers[j])));
                }
                return a;
            }

            /**
             * @brief Get the return sums of all colums in vector 
             * 
             * Used in describe_all()
             * 
             * @return std::vector<long double> 
             */
            std::vector<long double> get_sums(){
                std::vector<long double> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(get_sum(get_col_(headers[j])));
                }
                return a;             
            }

            /**
             * @brief Re-centers a string based on given width 
             * 
             * @param s 
             * @param w 
             * @return std::string 
             */
            static std::string center(const string s, const int w) {
                std::stringstream ss, spaces;
                int padding = w - s.size(); // count excess room to pad
                for(int i=0; i<padding/2; ++i)
                    spaces << " ";
                ss << spaces.str() << s << spaces.str(); // format with padding
                if(padding>0 && padding%2!=0) // if odd #, add 1 space
                    ss << " ";
                return ss.str();
            }

            /**
             * @brief converts double to a string with white space 
             * 
             * @param x 
             * @param width 
             * @return std::string 
             */
            static std::string prd(long double x, int width) {
                std::stringstream ss;
                ss << std::fixed << std::left;
                ss.fill(' '); // fill space around displayed #
                ss.width(width); // set  width around displayed #
                ss.precision(2); // set # places after decimal
                ss << x;
                return center(ss.str(), width);
            }

            /**
             * @brief Gives spacing to a string 
             * 
             * @param x 
             * @param width 
             * @return std::string 
             */
            static std::string prd(std::string x, int width) {
                std::stringstream ss;
                ss << std::left;
                ss.fill(' '); // fill space around displayed #
                ss.width(width); // set  width around displayed #
                ss << x;
                return center(ss.str(), width);
            }

            /**
             * @brief Generates row names 
             * 
             */
            void generate_rows(){
                rows.clear();
                for(int i = 0; i < size(); i++){
                    rows.push_back("Row-"+std::to_string(i));
                }
            }
            
            /**
             * @brief Checks size of current class
             * 
             */
            void check_size(){
                if(empty()){
                    row = 0;
                    col = 0;
                    return;
                }
                col = at(0).size();
                row = size();
            }

            /**
             * @brief Generates line to seperate rows 
             * 
             * @param l 
             * @return std::string 
             */
            std::string generate_line(int l){
                std::string line;
                for(int i = 0; i < l; i++){
                    line+="―";
                }
                return line;
            }

            std::vector<std::string> headers;
            std::vector<std::string> rows;
            int row;
            int col;
            int sz = 10; // size for 

        public:
            /**
             * @brief Construct a new Table object
             * 
             */
            Table(){}

            /**
             * @brief Destroy the Table object
             * 
             */
            ~Table(){}

            /**
             * @brief Reads from csv file
             * 
             * @param file 
             * @return true: if read is success   
             * @return false: if read did not complete 
             */
            bool read_csv(std::string filename){
                ifstream file(filename);
                if(file.is_open()){
                    clear();
                    headers.clear();

                    // col name
                    string line, colname;
                    getline(file, line);

                    stringstream ss(line);
                    while(getline(ss, colname, ',')){
                        headers.push_back(colname);
                    }

                    // data 
                    long double val;
                    while(std::getline(file, line))
                    {
                        // Create a stringstream of the current line
                        std::stringstream ss(line);
                        
                        std::vector<long double> r;
                        while(ss >> val){
                            r.push_back(val);
                            
                            // If the next token is a comma, ignore it and move on
                            if(ss.peek() == ',') ss.ignore();
                        }
                        push_back(r);
                    }
                    check_size();
                    file.close();
                    return true;
                }
                file.close();
                return false;
            }

            /**
             * @brief Reads from csv file
             * 
             * @param file 
             * @return true: if read is success   
             * @return false: if read did not complete 
             */
            bool save_csv(std::string filename)
            {
                ofstream file(filename);
                if(file.is_open()){
                    for(int i = 0; i < headers.size(); i++){
                        if(i != headers.size()-1){
                            file << headers[i] << ",";
                        }
                        else{
                            file << headers[i] << "\n";
                        }
                    }
                    check_size();
                    for(int i = 0; i < row; i++){
                        for(int j = 0; j < col; j++){
                            if(j != col-1){
                                file << at(i).at(j) << ",";
                            }
                            else if (j == col-1){
                                file << at(i).at(j) << "\n";
                            }
                        }
                    }
                    file.close();
                    return true;
                }
                file.close();
                return false;
            }

            /**
             * @brief Get the row size object
             * 
             * @return int 
             */
            int get_row_size(){
                return size();                
            }

            /**
             * @brief Get the col size object
             * 
             * @return int 
             */
            int get_col_size(){
                return at(0).size();
            }

            /**
             * @brief Returns colum of certain header 
             * 
             * @param headname 
             * @return std::vector<TYPE>& 
             */
            std::vector<long double> operator[](std::string headname){
                return get_col_(headname);
            }

            /**
             * @brief Sorts data ascending 
             * 
             * @param a 
             * @return std::vector<long double> 
             */
            static std::vector<long double> sort_asc(std::vector<long double> & a){
                std::vector<long double> v_sorted(a.size());
                std::partial_sort_copy(a.begin(), a.end(), 
                v_sorted.begin(), v_sorted.end());
                return v_sorted;
            }

            /**
             * @brief Get the min value of vector 
             * 
             * @param a 
             * @return long double 
             */
            static long double get_min(std::vector<long double> a){
                return *std::min_element(a.begin(), a.end());
            }

            /**
             * @brief Get the max value of vector 
             * 
             * @param a 
             * @return long double 
             */
            static long double get_max(std::vector<long double> a){
                return *std::max_element(a.begin(), a.end());
            }

            /**
             * @brief Get the sum of vector 
             * 
             * @param a 
             * @return long double 
             */
            static long double get_sum(std::vector<long double> a){
                return std::accumulate(a.begin(), a.end(), 0);
            }

            /**
             * @brief Get the avg of vector 
             * 
             * @param a 
             * @return long double 
             */
            static long double get_avg(std::vector<long double> a){
                return get_sum(a)/a.size();
            } 

            /**
             * @brief Get the variance of vector 
             * 
             * @param a 
             * @return long double 
             */
            static long double get_var(std::vector<long double> a){
                long double mean = get_avg(a);
                int N = a.size();
                long double sum = 0;
                for(int i = 0; i < N; i++){
                    sum+=pow((a[i]-mean), 2);
                }
                return (long double) sum/N;            
            }

            /**
             * @brief Get the standard diviation of vector 
             * 
             * @param a 
             * @return long double 
             */
            static long double get_std(std::vector<long double> a){
                return sqrt(get_var(a));
            }   

            /**
             * @brief Get the quartile range of a vector 
             * 
             * @param a 
             * @return QR 
             */
            static QR get_qr(std::vector<long double> a){
                QR qr; 
                qr.LQ = get_min(a);
                qr.UQ = get_max(a);
                auto a_sorted = sort_asc(a);
                qr.Q1 = a_sorted.at((int) (a_sorted.size())/4);
                qr.Q2 = a_sorted.at((int) (a_sorted.size())/2);
                qr.Q3 = a_sorted.at((int) (3*(a_sorted.size()))/4);
                return qr;
            }

            /**
             * @brief Get the relation coefficient of two vectors 
             * 
             * @param _x 
             * @param _y 
             * @return long double 
             */
            static long double get_r(
            std::vector<long double> _x, std::vector<long double> _y){
                if(_x.size() != _y.size()){
                    throw std::invalid_argument("misc::Table::get_r -> Size mismatch");
                }
                long double sumx = misc::Table::get_sum(_x);
                long double sumy = misc::Table::get_sum(_y);
                long double sumxx = misc::Table::get_sum(_x*_x);
                long double sumxy = misc::Table::get_sum(_x*_y);
                long double sumyy = misc::Table::get_sum(_y*_y);
                return (_x.size()*sumxy-(sumx*sumy))/
                (sqrt((_x.size()*sumxx-pow(sumx, 2))*(_x.size()*sumyy-pow(sumy, 2))));
            }

            /**
             * @brief Shows a certain number of rows in table 
             * 
             * @param r 
             */
            void show(int r){
                if(rows.empty()){
                    generate_rows();
                }
                check_size();
                std::string line;
                if(col == 1){
                    line = generate_line((std::pow(2, 1/col)+0.2)*sz*col);
                }
                else{
                    line = generate_line((std::pow(1.05, 1/col)+1.9/col)*sz*col);
                }
                for(int i = -1; i < r; i++){
                    for(int j = 0; j < col; j++){
                        // to print header 
                        if(i == -1){
                            if (j == 0 && col > 1){
                                std::cout << prd("     ", sz) << "│"
                                          << prd(headers[j], sz) << "│";
                            }
                            else if(j == 0 && col == 1){
                                std::cout << prd("     ", sz) << "│"
                                          << prd(headers[j], sz) << "\n";    
                                std::cout << line << "\n";                            
                            }
                            else if(j != col-1){
                                std::cout << prd(headers[j], sz) << "│";
                            }
                            else{
                                std::cout << prd(headers[j], sz) << "\n";
                                std::cout << line << "\n";
                            }                            
                        }
                        // printing values 
                        else{
                            // row name + val
                            if(j == 0 && col > 1){
                                std::cout << prd(rows[i], sz) << "│"
                                          << prd(get_col_(headers[j]).at(i), sz) << "│";
                            }
                            else if(j == 0 && col == 1){
                                std::cout << prd(rows[i], sz) << "│"
                                          << prd(get_col_(headers[j]).at(i), sz) << "│" << "\n";
                                std::cout << line << "\n";
                            }
                            else if(j != col-1){
                                std::cout << prd(get_col_(headers[j]).at(i), sz) << "│";
                            }

                            else{
                                std::cout << prd(get_col_(headers[j]).at(i), sz) << "\n";
                                std::cout << line << "\n";
                            }                           
                        }
                    }
                }
            }

            /**
             * @brief shows all of the table 
             * 
             */
            void show(){
                check_size();
                show(row);
            }

            /**
             * @brief Statistical summary of all colums in table 
             * 
             * @return Table 
             */
            Table describe_all(){
                Table t;
                auto avg = get_avgs();
                auto std = get_stds();
                auto var = get_vars();
                auto qrs = get_qrs();
                auto sms = get_sums();
                check_size();
                // loading row names
                for(int i = 0; i < col; i++){
                    t.rows.push_back(headers[i]);
                }
                // loading col names 
                t.headers.push_back("Mean");
                t.headers.push_back("STD");
                t.headers.push_back("VAR");
                t.headers.push_back("Min");
                t.headers.push_back("Q1");
                t.headers.push_back("Q2");
                t.headers.push_back("Q3");
                t.headers.push_back("Max");
                t.headers.push_back("IQR");
                t.headers.push_back("Sum");
    
                // loading values 
                t.row = t.rows.size();
                t.col = t.headers.size();
                for(int i = 0; i < t.row; i++){
                    std::vector<long double> rr;
                    rr.push_back(avg[i]);
                    rr.push_back(std[i]);
                    rr.push_back(var[i]);
                    rr.push_back(qrs[i].LQ);
                    rr.push_back(qrs[i].Q1);
                    rr.push_back(qrs[i].Q2);
                    rr.push_back(qrs[i].Q3);
                    rr.push_back(qrs[i].UQ); 
                    rr.push_back(qrs[i].Q3-qrs[i].Q1);  
                    rr.push_back(sms[i]);         
                    t.push_back(rr);
                }
                t.check_size();
                t.sz = 11;
                return t;
            }
            
            /**
             * @brief Get the row as table 
             * 
             * @param r 
             * @return Table 
             */
            Table get_row(int r){
                Table t; 
                t.push_back(at(r));
                t.headers = headers;
                if(rows.empty()){
                    generate_rows();
                }
                t.rows.push_back(rows[r]);
                return t;
            }

            /**
             * @brief Get the col as table 
             * 
             * @param name 
             * @return Table 
             */
            Table get_col(std::string name){
                Table t;
                auto a = get_col_(name);
                for(int i = 0; i < a.size(); i++){
                    t.push_back({a[i]});
                }
                if(rows.empty()){
                    generate_rows();
                }
                t.headers.push_back(headers[check_header(name)]);
                return t;
            }

            /**
             * @brief Adds new colum 
             * 
             * @param col_name 
             * @param col_data 
             * @return true 
             * @return false 
             */
            bool add_col(std::string col_name, std::vector<long double> col_data){
                check_size();
                if((col_data.size() != row && row != 0) || col_data.empty()){
                    return false;
                }
                headers.push_back(col_name);
                for(int i = 0; i < col_data.size(); i++){
                    if(row == 0){
                        push_back({col_data[i]});
                    }
                    else{
                        at(i).push_back(col_data[i]);
                    }
                }
                return true;
            }

            /**
             * @brief Shows headers only 
             * 
             */
            void show_header(){
                show(0);
            }
    };

    /**
     * @brief Encapsulates graph.hpp (https://github.com/tdulcet/Tables-and-Graphs) 
     * 
     */
    class Plot
    {
        public:
            /**
             * @brief Colors for plots 
             * 
             */
            enum Color
            {
                red = 10,
                green = 11,
                yellow = 12,
                purple = 14,
                blue = 15,
                white = 16
            };

        private:
            size_t height;
            size_t width; 

            long double xmin;
            long double xmax; 
            long double ymin; 
            long double ymax; 

            const size_t cols = 2;
            std::vector<long double> domain;
            graphoptions aoptions;
            Color c;
            std::string title;

        public:
            /**
             * @brief Construct a new Plot object
             * 
             * @param h height
             * @param w width
             * @param xmn min x
             * @param xmx max x
             * @param ymn min y
             * @param ymx max y
             */
            Plot(int h = 145, int w = 145, 
                long double xmn = -10, long double xmx = 10,
                long double ymn = -10, long double ymx = 10): 
                height(h), width(w), 
                xmin(xmn), xmax(xmx), 
                ymin(ymn), ymax(ymx){}

            /**
             * @brief Set the Domain 
             * 
             * @param xmn 
             * @param xmx 
             */
            void set_domain(long double xmn = -10, long double xmx = 10){
                xmin = xmn;
                xmax = xmx;
            }

            /**
             * @brief Set the Range
             * 
             * @param ymn
             * @param ymx
             */
            void set_range(long double ymn = -10, long double ymx = 10){
                ymin = ymn;
                ymax = ymx;
            }

            /**
             * @brief Set the Size of figure
             * 
             * @param h 
             * @param w
             */
            void set_size(int h = 140, int w = 140){
                height = h;
                width = w;

            }

            /**
             * @brief Set the color 
             * 
             * @param cc 
             */
            void set_color(Color cc = Color::blue){
                c = cc;
            }

            /**
             * @brief Set the title 
             * 
             * @param tt 
             */
            void set_title(std::string tt){
                title = tt;
            }

            /**
             * @brief Generates domain 
             * 
             * @param n 
             */
            void generate_domain(int n = 50){
                generate_domain(xmin, xmax, n);
            }

            /**
             * @brief Generates domain to plot function 
             * 
             * @param xmn 
             * @param xmx 
             * @param n number of points
             */
            void generate_domain(long double xmn, long double xmx, int n){
                domain = generate_vector(xmn, xmx, n);
            }

            /**
             * @brief Plots vectors
             * 
             * @param x vector for x
             * @param y vector for y
             */
            void plot_vect(std::vector<long double> &x, std::vector<long double> &y)
            {
                if(x.size() != y.size()){
                    std::cerr << x.size() << "\t" << y.size() << "\n";
                    std::cerr << "misc::Plot::plot_vect-> Size mismatch \n";
                    return;
                }
                long double **array;
                array = new long double *[x.size()];                
                for (unsigned int i = 0; i < x.size(); ++i){
                    array[i] = new long double[cols];
                }
                for (unsigned int i = 0; i < x.size(); ++i){
                    for (unsigned int j = 0; j < cols; ++j){
                        // x
                        if (j == 0){
                            array[i][j] = x[i];
                        }
                        // y 
                        else{
                            array[i][j] = y[i];
                        }
                    }
                }
                aoptions.color = c;
                std::cout << 
                colors[c] 
                << title << "\n"
                << colors[Color::white];
                graph(height, width, xmin, xmax, ymin, ymax, x.size(), array, aoptions);
                if(array != NULL){
                    for (unsigned int i = 0; i < x.size(); ++i){
                        delete[] array[i];
                    }
                    delete[] array;
                }
            }

            /**
             * @brief Plots function 
             * 
             * @tparam LAMBDA 
             * @param fun lambda function 
             */
            template<typename LAMBDA>
            void plot_fun(LAMBDA fun)
            {
                std::vector<long double> y; 
                for(int i = 0; i < domain.size(); i++){
                    y.push_back(fun(domain[i]));
                }
                plot_vect(domain, y);
            }
    };
} 
