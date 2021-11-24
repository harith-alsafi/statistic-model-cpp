#pragma once 

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "graphs.hpp"
namespace misc
{
    /**
     * @brief Table class to contain the dataframe 
     */
    class Table: public std::vector<std::vector<long double>>
    {
        struct QR
        {
            long double LQ; // lower quartile 
            long double Q1; 
            long double Q2; // median
            long double Q3; 
            long double UQ; // upper quartile 
            long double IQR = Q3-Q1; // interquartile range
        };
        protected:
            int checkHeader(std::string head){
                for(int i = 0; i < headers.size(); i++){
                    if(headers[i] == head){
                        return i;
                    }
                }
                return -1;
            }

            std::vector<long double> getAvgs(){

            }

            std::vector<long double> getStds(){
                
            }

            std::vector<long double> getVars(){
                
            }

            std::vector<QR> getQRs(){
                
            }


        private:
            std::vector<std::string> headers;
            int row;
            int col;

        public:
            Table(){}

            void checkSize(){
                col = at(0).size();
                row = size();
            }

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
                    return true;
                }
                file.close();
                return false;
            }

            /**
             * @brief Returns colum of certain header 
             * 
             * @param headname 
             * @return std::vector<D>& 
             */
            std::vector<long double>& operator[](std::string headname){
                int i = checkHeader(headname);
                return at(i);
            }

            long double getMin(std::vector<long double>& a){

            }

            long double getMax(std::vector<long double>& a){
                
            }

            long double getAvg(std::vector<long double>& a){

            } 

            long double getStd(std::vector<long double>& a){

            }

            long double getVar(std::vector<long double>& a){

            }



            QR getQR(std::vector<long double>& a){

            }

            void show(){

            }

            Table describeAll(){
                Table t;
                t.headers.push_back("Colum Name");
                t.headers.push_back("Average");
                t.headers.push_back("Standard diviation");
                t.headers.push_back("Variance");
                t.headers.push_back("IQR");
                t.col = headers.size();
                t.row = col;
                



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
