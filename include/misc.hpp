#pragma once 

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>

#include "graphs.hpp"

namespace misc
{
    /**
     * @brief Table class to contain the dataframe 
     */
    class Table: public std::vector<std::vector<long double>>
    {
        public:
            struct QR
            {
                long double LQ; // lower quartile 
                long double Q1; 
                long double Q2; // median
                long double Q3; 
                long double UQ; // upper quartile 
                std::string toString(){
                    std::string str;
                    str = Table::prd("LQ", 10)
                        + Table::prd("Q1", 10)
                        + Table::prd("Q2", 10)
                        + Table::prd("Q3", 10)
                        + Table::prd("UQ", 10)
                        + "\n";
                    str += "--------------------------------------------- \n";
                    str += Table::prd(LQ, 10)  
                        +  Table::prd(Q1, 10)  
                        +  Table::prd(Q2, 10)  
                        +  Table::prd(Q3, 10)  
                        +  Table::prd(UQ, 10);
                    return str;
                }
            };
        private:
            int checkHeader(std::string head){
                for(int i = 0; i < headers.size(); i++){
                    if(headers[i] == head){
                        return i;
                    }
                }
                return -1;
            }

            std::vector<long double> getCol(std::string headname){
                int j = checkHeader(headname);
                std::vector<long double> a;
                for(int i = 0; i < size(); i++){
                    a.push_back(at(i).at(j));
                }
                return a;                
            }

            std::vector<long double> getAvgs(){
                std::vector<long double> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(getAvg(getCol(headers[j])));
                }
                return a;
            }

            std::vector<long double> getStds(){
                std::vector<long double> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(getStd(getCol(headers[j])));
                }
                return a;             
            }

            std::vector<long double> getVars(){
                std::vector<long double> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(getVar(getCol(headers[j])));
                }
                return a;
            }

            std::vector<QR> getQRs(){
                std::vector<QR> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(getQR(getCol(headers[j])));
                }
                return a;
            }

            std::vector<long double> getSums(){
                std::vector<long double> a;
                for(int j = 0; j < headers.size(); j++){
                    a.push_back(getSum(getCol(headers[j])));
                }
                return a;             
            }

            static std::string center(const string s, const int w) {
                std::stringstream ss, spaces;
                int padding = w - s.size();                 // count excess room to pad
                for(int i=0; i<padding/2; ++i)
                    spaces << " ";
                ss << spaces.str() << s << spaces.str();    // format with padding
                if(padding>0 && padding%2!=0)               // if odd #, add 1 space
                    ss << " ";
                return ss.str();
            }

            static std::string prd(long double x, int width) {
                std::stringstream ss;
                ss << std::fixed << std::left;
                ss.fill(' ');        // fill space around displayed #
                ss.width(width);     // set  width around displayed #
                ss.precision(2); // set # places after decimal
                ss << x;
                return center(ss.str(), width);
            }

            static std::string prd(std::string x, int width) {
                std::stringstream ss;
                ss << std::left;
                ss.fill(' ');        // fill space around displayed #
                ss.width(width);     // set  width around displayed #
                ss << x;
                return center(ss.str(), width);
            }

            void generateRows(){
                rows.clear();
                for(int i = 0; i < size(); i++){
                    rows.push_back("Row-"+std::to_string(i));
                }
            }
            
            void checkSize(){
                col = at(0).size();
                row = size();
            }

            std::string generateLine(int l){
                string line;
                for(int i = 0; i < l; i++){
                    line+="―";
                }
                return line;
            }

            std::vector<std::string> headers;
            std::vector<std::string> rows;
            int row;
            int col;
            int sz = 10;

        public:
            Table(){}
            ~Table(){}

            /**
             * @brief Reads from csv file
             * 
             * @param file 
             * @return true: if read is success   
             * @return false: if read did not complete 
             */
            bool readCSV(std::string filename){
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
                    checkSize();
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
            bool saveCSV(std::string filename)
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
                    checkSize();
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

            int getRow(){
                return size();                
            }

            int getCol(){
                return at(0).size();
            }

            /**
             * @brief Returns colum of certain header 
             * 
             * @param headname 
             * @return std::vector<D>& 
             */
            std::vector<long double> operator[](std::string headname){
                return getCol(headname);
            }

            static std::vector<long double> sortAsc(std::vector<long double> & a){
                std::vector<long double> v_sorted(a.size());
                std::partial_sort_copy(a.begin(), a.end(), 
                v_sorted.begin(), v_sorted.end());
                return v_sorted;
            }

            static long double getMin(std::vector<long double> a){
                return *std::min_element(a.begin(), a.end());
            }

            static long double getMax(std::vector<long double> a){
                return *std::max_element(a.begin(), a.end());
            }

            static long double getSum(std::vector<long double> a){
                return std::accumulate(a.begin(), a.end(), 0);
            }

            static long double getAvg(std::vector<long double> a){
                return getSum(a)/a.size();
            } 

            static long double getVar(std::vector<long double> a){
                long double mean = getAvg(a);
                int N = a.size();
                long double sum = 0;
                for(int i = 0; i < N; i++){
                    sum+=pow((a[i]-mean), 2);
                }
                return (long double) sum/N;            
            }

            static long double getStd(std::vector<long double> a){
                return sqrt(getVar(a));
            }   

            static QR getQR(std::vector<long double> a){
                QR qr; 
                qr.LQ = getMin(a);
                qr.UQ = getMax(a);
                auto a_sorted = sortAsc(a);
                qr.Q1 = a_sorted.at((int) (a_sorted.size())/4);
                qr.Q2 = a_sorted.at((int) (a_sorted.size())/2);
                qr.Q3 = a_sorted.at((int) (3*(a_sorted.size()))/4);
                return qr;
            }

            void show(int r){
                if(rows.empty()){
                    generateRows();
                }
                checkSize();
                std::string line = generateLine(1.2*sz*col);
                for(int i = -1; i < r; i++){
                    for(int j = 0; j < col; j++){
                        if(i == -1){
                            if (j == 0){
                                std::cout << prd("     ", sz) << "│"
                                          << prd(headers[j], sz) << "│";
                            }
                            else if(j != col-1){
                                std::cout << prd(headers[j], sz) << "│";
                            }
                            else{
                                std::cout << prd(headers[j], sz) << "\n";
                                std::cout << line << "\n";
                            }                            
                        }
                        else{
                            if(j == 0){
                                std::cout << prd(rows[i], sz) << "│"
                                          << prd(getCol(headers[j]).at(i), sz) << "│";
                            }
                            else if(j != col-1){
                                std::cout << prd(getCol(headers[j]).at(i), sz) << "│";
                            }
                            else{
                                std::cout << prd(getCol(headers[j]).at(i), sz) << "\n";
                                std::cout << line << "\n";
                            }                           
                        }
                    }
                }
            }

            void show(){
                checkSize();
                show(row);
            }

            Table describeAll(){
                Table t;
                auto avg = getAvgs();
                auto std = getStds();
                auto var = getVars();
                auto qrs = getQRs();
                auto sms = getSums();
                checkSize();
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
                t.checkSize();
                t.sz = 11;
                return t;
            }
            

    };

    /**
     * @brief Simple terminal plot 
     * 
     */
    class Plot
    {
        private:
            size_t height;
            size_t width; 

            long double xmin;
            long double xmax; 
            long double ymin; 
            long double ymax; 

            const size_t cols = 2;
            std::vector<long double> domain;
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
            void setDomain(long double xmn = -10, long double xmx = 10){
                xmin = xmn;
                xmax = xmx;
            }

            /**
             * @brief Set the Range
             * 
             * @param ymn
             * @param ymx
             */
            void setRange(long double ymn = -10, long double ymx = 10){
                ymin = ymn;
                ymax = ymx;
            }

            /**
             * @brief Set the Size of figure
             * 
             * @param h 
             * @param w
             */
            void setSize(int h = 140, int w = 140){
                height = h;
                width = w;

            }

            /**
             * @brief Generates domain to plot function 
             * 
             * @param xmn 
             * @param xmx 
             * @param n number of points
             */
            void generateDomain(long double xmn = -10, long double xmx = 10, int n = 50){
                domain.clear();
                for(long double x = xmn; x < xmax; x+=(long double)(xmx-xmn)/n){
                    domain.push_back(x);
                }
            }

            /**
             * @brief Plots vectors
             * 
             * @param x vector for x
             * @param y vector for y
             */
            void plotVect(std::vector<long double> &x, std::vector<long double> &y)
            {
                if(x.size() != y.size()){
                    std::cerr << "plotVect->Ivalid input \n";
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
                graphoptions aoptions;
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
             * @tparam D 
             * @param fun lambda function 
             */
            template<typename D>
            void plotFun(D fun)
            {
                std::vector<long double> y; 
                for(int i = 0; i < domain.size(); i++){
                    y.push_back(fun(domain[i]));
                }
                plotVect(domain, y);
            }
    };
} 
