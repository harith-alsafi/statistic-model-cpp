#pragma once
#include "intp.hpp"
#include "misc.hpp"
#include "regr.hpp"

class Menu
{
    private:
        enum State
        {
            running,
            exit,
            error_csv,
            error_unloaded_data,
            show_data,
            regression,
            interpolation
        };

        State menu_state;
        
        misc::Table table;
        misc::Plot plt;

        regr::LinearRegression lr;
        regr::PolyRegression pr;

        intp::LinearInterp lip;
        intp::PolyInterp pip;

        int choice;
        std::string filename;
        bool linear_intp;
        bool linear_reg;

        void check_choice(int max, int ch){
            if(ch > max || ch < 1){
                std::cout << 
                "Choice " + to_string(ch) + " doesn't exist, please try again \n"; 
            }
        }

        void main_options(){
            std::cout << "―――――――――――――――――――――Main Window―――――――――――――――――――――――― \n";
            std::cout << "[1] Load CSV file \n";
            std::cout << "[2] Show data of loaded CSV \n";
            std::cout << "[3] Statistical analysis of all columns in loaded CSV \n";
            std::cout << "[4] Regression on loaded CSV \n";
            std::cout << "[5] Interpolation on loaded CSV \n";
            std::cout << "[6] Save CSV file \n";
            std::cout << "[7] Go back \n";
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "Enter your choice: ";    
            std::cin >> choice;
            std::cout << "------------------------------------------------------- \n";
            check_choice(7, choice);
        }

        void load_csv(){
            std::cout <<"Pre-existing csv files (Note: all options will work with any csv file): \n ";
            std::cout <<"statistics.csv [for all options] \n ";
            std::cout <<"regression.csv [shows true demonstration of regression] \n ";
            std::cout <<"interpolation.csv [shows true demonstration of interpolation] \n ";
            std::cout << "----------------------------------------------------------------------- \n";
            std::cout << "Enter CSV file name (with .csv extension): ";
            
            std::cin >> filename;
            if(!table.read_csv(filename)){
                std::cout << "File: " + filename + " could not be open \n";
                menu_state = State::error_csv;
                return;
            }
            std::cout << "File: " + filename + " was loaded \n";
            menu_state = State::running;
        }

        bool check_csv_errors(){
            if(menu_state != State::error_csv){
                return true;
            }
            std::cout << "No CSV file was loaded please try again \n";
            return false;
        }

        bool check_unloaded_errors(){
            if(menu_state != State::error_unloaded_data){
                return true;
            }
            std::cout << "No data was loaded please try again \n";
            return false;
        }

        void show_data_options(){
            menu_state = State::show_data;
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "[1] Show all data \n";
            std::cout << "[2] Show n-rows \n";
            std::cout << "[3] Show specefic column \n";
            std::cout << "[4] Show specefic row \n";
            std::cout << "[5] Go back \n";
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "Enter your choice: ";    
            std::cin >> choice;
            std::cout << "------------------------------------------------------- \n";
            if(choice == 1){
                table.show();
            }
            else if(choice == 2){
                int n = 0;
                std::cout << "Enter number of rows: ";
                std::cin >> n; 
                if( n >= table.size() || n < 0){
                    std::cout << "Invalid number of rows, please try again \n ";
                    menu_state = State::show_data;
                    return;
                }
                table.show(n);
            }
            else if(choice == 3){
                std::string colname;
                std::cout << "Enter column name: ";
                std::cin >> colname;
                misc::Table vcol = table.get_col(colname);
                if(vcol.empty()){
                    std::cout << "Wrong column name, please try again \n ";
                    return;
                }
                vcol.show();
            }
            else if (choice == 4){
                int rownum;
                std::cout << "Enter row number: ";
                std::cin >> rownum;
                misc::Table vrow = table.get_row(rownum);
                if(vrow.empty()){
                    std::cout << "Wrong row number, please try again \n ";
                    return;
                }
                vrow.show();
            }
            else if(choice == 5){
                menu_state = State::running;
                choice = 0;
                return;
            }
            check_choice(5, choice);
        }

        void save_csv(){
            std::string outname;
            std::cout << "Enter file name: ";
            std::cin >> outname;
            if(!table.save_csv(outname)){
                menu_state = State::running;
                std::cout << "Error in saving the file \n";
                return; 
            }
            std::cout << "File saved! \n";
        }

        void show_poly_lin(std::string str){
            std::cout << "[1] Linear "+str+" \n";
            std::cout << "[2] Polynomial "+str+" \n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
        }

        void show_regression_options(){
            menu_state = State::regression;
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "[1] Load and fit the data \n";
            std::cout << "[2] Show and plot equation \n";
            std::cout << "[3] Show the table \n";
            std::cout << "[4] Go back \n";
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "Enter your choice: ";    
            std::cin >> choice;
            std::cout << "------------------------------------------------------- \n";
            if(choice == 1){
                table.show_header();
                std::string colname;
                std::cout << "Chose column name for x-data: ";
                std::cin >> colname;
                std::vector<long double> x = table[colname];
                if(x.empty()){
                    std::cout << "Wrong column name, please try again \n ";
                    menu_state = State::error_unloaded_data;
                    return;
                }
                std::cout << "Chose column name for y-data: ";
                std::cin >> colname;
                std::vector<long double> y = table[colname];
                if(y.empty()){
                    std::cout << "Wrong column name, please try again \n ";
                    menu_state = State::error_unloaded_data;
                    return;
                } 
                show_poly_lin("regression");
                if(choice == 1){
                    linear_reg = true;
                    lr.load_data(x, y);
                    lr.fit_data();   
                    std::cout << "Data is fitted correctly \n ";
                    return;
                }
                else if(choice == 2){
                    linear_reg = false;
                    pr.load_data(x, y);
                    int n;
                    std::cout << "Enter dgree of equation (ex: 2 will give a max x²): ";
                    std::cin >> n;
                    pr.set_degree(n);
                    pr.fit_data();   
                    std::cout << "Data is fitted correctly \n ";
                    return;
                }
                check_choice(2, choice);
            }
            if(check_unloaded_errors()){
                if(choice == 2){
                    if(linear_reg){
                        lr.show_equation();
                        lr.plot_data();
                        lr.plot_equation();
                    }
                    else{
                        pr.show_equation();
                        pr.plot_data();
                        pr.plot_equation();                     
                    }
                }
                else if (choice == 3){
                    if(linear_reg){
                        lr.get_data().show();
                    }
                    else{
                        pr.get_data().show();
                    }
                }
            }
            if(choice == 4){
                menu_state = State::running;
                choice = 0;
                return;
            }
            check_choice(4, choice);                  
        }

        void show_interpolation_option(){
            menu_state = State::interpolation;
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "[1] Load the data \n";
            std::cout << "[2] Predict using x input \n";
            std::cout << "[3] Plot all possible interpolations \n";
            std::cout << "[4] Show table with all data from option[2] \n";
            std::cout << "[5] Go back \n";
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "Enter your choice: ";    
            std::cin >> choice;
            std::cout << "------------------------------------------------------- \n";
            if(choice == 1){
                table.show_header();
                std::string colname;
                std::cout << "Chose column name for x-data: ";
                std::cin >> colname;
                std::vector<long double> x = table[colname];
                if(x.empty()){
                    std::cout << "Wrong column name, please try again \n";
                    menu_state = State::error_unloaded_data;
                    return;
                }
                std::cout << "Chose column name for y-data: ";
                std::cin >> colname;
                std::vector<long double> y = table[colname];
                if(y.empty()){
                    std::cout << "Wrong column name, please try again \n";
                    menu_state = State::error_unloaded_data;
                    return;
                } 
                show_poly_lin("interpolation");
                if(choice == 1){
                    linear_intp = true;
                    lip.load_data(x, y);
                    std::cout << "Data is fitted correctly \n";
                    return;
                }
                else if(choice == 2){
                    linear_intp = false;
                    pip.load_data(x, y);
                    std::cout << "Data is fitted correctly \n";
                    return;
                }
                check_choice(2, choice);
            }
            if(check_unloaded_errors()){
                if(choice == 2){
                    long double xx;
                    std::cout << "Enter x-value: ";
                    std::cin >> xx;
                    if(linear_intp){
                        xx = lip.find_value(xx);
                    }
                    else{
                        xx = pip.find_value(xx);
                    }
                    std::cout << "Predicted y-value: " << xx << "\n";
                }
                else if (choice == 3){
                    if(linear_intp){
                        lip.plot_data();
                        lip.plot_all_interpolation();
                    }
                    else{
                        std::cout << "hile \n";
                        pip.plot_data();
                        pip.plot_all_interpolation();
                    }
                }
                else if(choice == 4){
                    if(linear_intp){
                        lip.get_interpolated_data().show();
                    }
                    else{
                        pip.get_interpolated_data().show();
                    }
                }
            }
            if(choice == 5){
                menu_state = State::running;
                choice = 0;
                return;
            }
            check_choice(4, choice); 
        }

    public:
        Menu(){
            menu_state = running;
            choice = 0;
            linear_intp = true;
            linear_reg = true;
        }

        void run(){
            while(menu_state != exit)
            {
                main_options();

                if(choice == 1)
                {
                    load_csv();
                }

                if(check_csv_errors()){
                    if(choice == 2)
                    {
                        show_data_options();
                        while (menu_state == State::show_data)
                        {
                            show_data_options();
                        }
                    }

                    
                    if (choice == 3)
                    {
                        table.describe_all().show();
                    }
                    
                    else if (choice == 4)
                    {
                        show_regression_options();
                        while(menu_state == State::regression)
                        {
                            show_regression_options();
                        }
                    }

                    else if (choice == 5)
                    {
                        show_interpolation_option();
                        while(menu_state == State::interpolation)
                        {
                            show_interpolation_option();
                        }
                    }
                    else if (choice == 6)
                    {
                        save_csv();
                    }
                }

                if (choice == 7)
                {
                    menu_state = State::exit;
                }

            }
        }

};
