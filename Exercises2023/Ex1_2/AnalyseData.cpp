//Name: Leonardo Monaco, data of creation: Oct 22, 2024

#include <iostream>   //cout and cin
#include <fstream>    //For reading files
#include <vector>
#include <string>

#include "CustomFunctions.h"

int main(){
    
    std::ifstream input_file("input2D_float.txt");

    if(!input_file.is_open()){
        std::cout << "Error opening the file with data points" << std::endl;
    }
    else{

        const auto[x_val, y_val] = FileToVec(input_file);       //read the file and write data points inside the vectors

        int command{0};
        bool go{false};

        do{
            go = true;
            std::cout << "Press: 1 to print data points; 2 for abs values; 3 for straight line fit; 4 for x^y calculation; 5 to exit. Your choice: ";
            std::cin >> command;
            std::cout << std::endl;

            switch(command){
                case 1: {
                    int nlines{0};
                    std::cout << "Insert the number of data points that you want to print:";
                    std::cin >> nlines;
                    PrintData(x_val, y_val, nlines);
                    break;
                }
                case 2: {
                    const std::vector<float> absValues = AbsValuesCalculation(x_val, y_val);
                    WriteOutData(absValues, std::string("AbsValues.txt"));
                    break;
                }
                case 3: {
                    const std::string StraightFit = StraightLineFit(x_val, y_val);
                    WriteOutData(StraightFit, std::string("StrightLineFit.txt"));
                    break;
                }
                case 4: {
                    const std::vector<float> powValues = PowerCalculation(x_val, y_val);
                    WriteOutData(powValues, std::string("PowValues.txt"));
                    break;
                }
                case 5: {
                    go=false;
                    break;
                }
                default: {
                    std::cout << "You didn't choose a valid command. Retry." << std::endl;
                    std::cout << std::endl;
                    break;
                }
            }
        }while(go);
    }

    return 0;


}