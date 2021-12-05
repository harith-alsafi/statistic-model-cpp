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
            std::cout << "[6] Interpolation on loaded CSV \n";
            std::cout << "[7] Exit \n";
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "Enter your choice: ";    
            std::cin >> choice;
            std::cout << "------------------------------------------------------- \n";
            check_choice(7, choice);
        }

        void load_csv(){
            std::cout << "Enter CSV file name (with .csv extension): ";
            
            std::cin >> filename;
            if(!table.read_csv(filename)){
                std::cout << "File: " + filename + " could not be open \n";
                menu_state = State::error_csv;
            }
            std::cout << "File: " + filename + " was loaded \n";
            menu_state = State::running;
        }

        bool check_errors(){
            if(menu_state != State::error_csv){
                return true;
            }
            std::cout << "No CSV file was loaded please try again \n";
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
                auto vcol = table[colname];
                if(vcol.empty()){
                    std::cout << "Wrong column name, please try again \n ";
                }

            }
            else if (choice == 4){

            }
            else if(choice == 5){
                menu_state = State::running;
                choice = 0;
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

    public:
        Menu(){
            menu_state = running;
            choice = 0;
        }

        void run(){
            while(menu_state != exit)
            {
                main_options();

                if(choice == 1)
                {
                    load_csv();
                }

                if(check_errors()){
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
                        while(menu_state == State::regression)
                        {

                        }
                    }

                    else if (choice == 5)
                    {
                        while(menu_state == State::interpolation)
                        {

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
