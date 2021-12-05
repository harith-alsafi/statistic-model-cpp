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
            error_csv
        };

        State menu_state;
        
        misc::Table table;
        misc::Plot plt;

        regr::LinearRegression lr;
        regr::PolyRegression pr;

        intp::LinearInterp lip;
        intp::PolyInterp pip;

        int choice;

        void check_choice(int min, int max, int ch){
            if(ch > max || ch < min){
                std::cout << 
                "Choice " + to_string(ch) + " doesn't exist, please try again \n"; 
            }
        }

        void main_options(int &ch){
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "[1] Load CSV file \n";
            std::cout << "[2] Show data of loaded CSV \n";
            std::cout << "[3] Statistical analysis of all columns in loaded CSV \n";
            std::cout << "[4] Regression on loaded CSV \n";
            std::cout << "[5] Interpolation on loaded CSV \n";
            std::cout << "[6] Exit \n";
            std::cout << "――――――――――――――――――――――――――――――――――――――――――――――――――――――― \n";
            std::cout << "Enter your choice: ";    
            std::cin >> ch;
            std::cout << "------------------------------------------------------- \n";
            check_choice(1, 6, ch);
        }

        void load_csv(){
            std::cout << "Enter CSV file name (with .csv extension): ";
            std::string name;
            std::cin >> name;
            if(!table.read_csv(name)){
                std::cout << "File: " + name + " could not be open \n";
                menu_state = State::error_csv;
            }
            std::cout << "File: " + name + " was loaded \n";
            menu_state = State::running;
        }

        void check_errors(){

        }

    public:
        Menu(){
            menu_state = running;
            choice = 0;
        }

        void run(){
            while(menu_state != exit)
            {
                main_options(choice);

                if(choice == 1)
                {

                }
                
                else if (choice == 2)
                {

                }
                
                else if (choice == 3)
                {

                }
                
                else if (choice == 4)
                {

                }

                else if (choice == 5)
                {

                }

                else if (choice == 6)
                {
                    menu_state = State::exit;
                }
            }
        }

};
