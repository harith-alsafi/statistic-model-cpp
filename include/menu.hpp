/**
 * @file menu.hpp
 * @author Harith Al-Safi
 * @brief 
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include "intp.hpp"
#include "misc.hpp"
#include "regr.hpp"

/**
 * @brief Class for the main menu 
 * 
 */
class Menu
{
    private:
        /**
         * @brief State of the program 
         * 
         */
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

        /**
         * @brief The menu state 
         * 
         */
        State menu_state;
        
        /**
         * @brief Table object 
         * 
         */
        misc::Table table;

        /**
         * @brief Plot object 
         * 
         */
        misc::Plot plt;

        /**
         * @brief Linear regression object 
         * 
         */
        regr::LinearRegression lr;

        /**
         * @brief Polynomial regression object 
         * 
         */
        regr::PolyRegression pr;

        /**
         * @brief Linear interpolation object 
         * 
         */
        intp::LinearInterp lip;

        /**
         * @brief Polynomial interpolation object 
         * 
         */
        intp::PolyInterp pip;

        /**
         * @brief Used to get the choice of the user 
         * 
         */
        int choice;

        /**
         * @brief Gets the loaded file name 
         * 
         */
        std::string filename;

        std::vector<long double> x;
        std::vector<long double> y;

        /**
         * @brief Specifies if the methods will be linear or polynomial, for interpolation 
         * 
         */
        bool linear_intp;

        /**
         * @brief Specifies if the methods will be linear or polynomial, for regression
         * 
         */
        bool linear_reg;

        /**
         * @brief Checks the choices 
         * 
         * @param max 
         * @param ch 
         */
        void check_choice(int max, int ch){
            if(ch > max || ch < 1){
                std::cout << 
                "This choice doesn't exist, please try again \n"; 
            }
            if(cin.fail()){
                cout << "\n";
                cin.clear();
                std::string ignoreLine; //read the invalid input into it
                std::getline(cin, ignoreLine); //read the line till next space
                return;
            }
        }

        /**
         * @brief Showcase main options 
         * 
         */
        void main_options(){
            std::cout << "―――――――――――――――――――――Option 2―――――――――――――――――――――――― \n";
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

        /**
         * @brief load csv options 
         * 
         */
        void load_csv(){
            std::cout <<"Pre-existing csv files (Note: all options will work with any csv file): \n";
            std::cout <<"statistics.csv [for all options] \n";
            std::cout <<"regression.csv [shows true demonstration of regression] \n";
            std::cout <<"interpolation.csv [shows true demonstration of interpolation] \n";
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

        /**
         * @brief Checks if csv was loaded correctly 
         * 
         * @return true 
         * @return false 
         */
        bool check_csv_errors(){
            if(filename.empty()){
                menu_state = State::error_csv;
                std::cout << "No CSV file was loaded please try again \n";
                return false;
            }
            if(menu_state != State::error_csv){
                return true;
            }
            std::cout << "No CSV file was loaded please try again \n";
            return false;
        }

        /**
         * @brief Checks if data was loaded correctly 
         * 
         * @return true 
         * @return false 
         */
        bool check_unloaded_errors(){
            if(x.empty() || y.empty()){
                std::cout << "No data was loaded please try again \n";
                return false;
            }
            if(menu_state != State::error_unloaded_data){
                return true;
            }
            std::cout << "No data was loaded please try again \n";
            return false;
        }

        /**
         * @brief show data options 
         * 
         */
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

        /**
         * @brief save csv options 
         * 
         */
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

        /**
         * @brief Polynomial or linear option 
         * 
         * @param str 
         */
        void show_poly_lin(std::string str){
            std::cout << "[1] Linear "+str+" \n";
            std::cout << "[2] Polynomial "+str+" \n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
        }

        /**
         * @brief Show the regression option 
         * 
         */
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
                x = table[colname];
                if(x.empty()){
                    std::cout << "Wrong column name, please try again \n ";
                    menu_state = State::error_unloaded_data;
                    return;
                }
                std::cout << "Chose column name for y-data: ";
                std::cin >> colname;
                y = table[colname];
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

        /**
         * @brief Show interpolation options 
         * 
         */
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
                x = table[colname];
                if(x.empty()){
                    std::cout << "Wrong column name, please try again \n";
                    menu_state = State::error_unloaded_data;
                    return;
                }
                std::cout << "Chose column name for y-data: ";
                std::cin >> colname;
                y = table[colname];
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

        /**
         * @brief Construct a new Menu object
         * 
         */
        Menu(){
            menu_state = running;
            choice = 0;
            linear_intp = true;
            linear_reg = true;
        }

        /**
         * @brief Destroy the Menu object
         * 
         */
        ~Menu(){}

        /**
         * @brief Main run method 
         * 
         */
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
