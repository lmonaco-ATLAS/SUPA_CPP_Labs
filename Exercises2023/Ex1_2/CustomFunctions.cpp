//Name: Leonardo Monaco, data of creation: Oct 22, 2024
// This file contains the definition of some custom functions

#include <vector>
#include <string>
#include <numeric>
#include <cmath>
#include <fstream>    //For reading files
#include <iostream>   //cout and cin

std::pair<std::vector<float>, std::vector<float>> FileToVec(std::ifstream& input_file){   // Functions that read the file and print it into two vectors

    std::vector<float> vec1{}, vec2{};
    input_file.seekg(4, input_file.beg);   //skipping the line x,y/n
    float temp{0.f};

    while(input_file.tellg() != -1){

        input_file >> temp;
        vec1.push_back(temp);

        input_file.seekg(1, input_file.cur);

        input_file >> temp;
        vec2.push_back(temp);

    }
    return std::make_pair(std::move(vec1), std::move(vec2));
}

void PrintData(const std::vector<float>& vec1, const std::vector<float>& vec2, int& nlines){     // Functions that print n pairs of data, taking them from vectors

    const int dim = vec1.size();

    if(nlines > dim){
        std::cout << "Warning: you selected a number of data points exceeding the max. Only 5 data points will be printed." << std::endl;
        nlines = 5;
    }

    for (int i=0; i<nlines; i++){
            std::cout << "Element " << i+1 << ": x=" << vec1[i] << "  y=" << vec2[i] << std::endl;
    }
    
    std::cout << std::endl;

}

std::vector<float> AbsValuesCalculation(const std::vector<float>& vec1, const std::vector<float>& vec2){  // Fnction that compute and print the absolute value for each data point, and store it in another vector

    const int dim = vec1.size();
    std::vector<float> absValues(dim, 0.f);

    for(int i=0; i< dim; i++){

        absValues[i]= sqrt(vec1[i]*vec1[i] + vec2[i]*vec2[i]);
        std::cout << "The abs value of the data point [" << i+1 << "] x=" << vec1[i] << ", y=" << vec2[i] << " is: " << absValues[i] << std::endl;

    }
    std::cout << std::endl;
    return absValues;
}

std::string StraightLineFit(const std::vector<float>& vec1, const std::vector<float>& vec2){    //function that computes the straigh line fit, performes chi_squared test, and print and store the results in a string.

    // Lets calculate first the linear fit parameters
    
    const int N = vec1.size();
    
    const float sum_xi = std::accumulate(vec1.begin(), vec1.end(), 0);
    const float sum_yi = std::accumulate(vec2.begin(), vec2.end(), 0);

    float sum_xiyi{0.f};
    float sum_xixi{0.f};
    for (int i=0; i< N; i++){
        sum_xiyi += vec1[i]*vec2[i];
        sum_xixi += vec1[i]*vec1[i];
    }
    const float p = (N*sum_xiyi - sum_xi*sum_yi)/(N*sum_xixi - sum_xi*sum_xi);
    const float q = (sum_xixi*sum_yi - sum_xiyi*sum_xi)/(N*sum_xixi - sum_xi*sum_xi);

    // Lets calculate now the chi_squared

    std::ifstream error_file(std::string("error2D_float.txt"));  //we use the same procedure used for saving data points

    if(!error_file.is_open()){
        std::cout << "Error opening the file with errors on data points" << std::endl;
        exit(1);
    }

    const auto[x_err, y_err] = FileToVec(error_file);           //read the file and write data point errors inside the vectors

    float chi_sq{0.f}, sig_i_sq{0.f}, E_i{0.f};

    for(int i=0; i<N; i++){

        sig_i_sq = pow(y_err[i], 2) + pow(p*x_err[i], 2);          //error propagation
        E_i = p * vec1[i] + q;
        chi_sq += pow(vec2[i]-E_i, 2)/sig_i_sq;

    }
    
    const int NDF = N - 2;

    // Printing and returning the results as a string

    std::cout << "The straight line function, computed using the least squared method, is: y = " << p << " *x + " << q << std::endl;
    std::cout << "The reduced chi squared is: \u03C7^2/NDF = " << chi_sq/NDF << std::endl;

    std::cout << std::endl;

    return std::string("y=" + std::to_string(p) + "*x+" + std::to_string(q) + "\n\u03C7^2/NDF=" + std::to_string(chi_sq/NDF));
}

float SinglePowerComputation(const float& x, int y){       //function that makes the power elevation x^y with y integer.

    if (y==0){
        return 1;
    }
    else{
        y -= 1;
        return x* SinglePowerComputation(x, y);
    }
}

std::vector<float> PowerCalculation(const std::vector<float>& vec1, const std::vector<float>& vec2){  // Function that compute and print the power value x^y for each data point, and store it in another vector

    const int dim = vec1.size();
    std::vector<float> powValues(dim, 0.f);

    for(int i=0; i< dim; i++){
        powValues[i] = SinglePowerComputation(vec1[i], round(vec2[i]));
        std::cout << "The power value of the data point [" << i+1 << "] x=" << vec1[i] << ", y=" << vec2[i] << " is: x^round(y) = " << powValues[i] << std::endl;
    }

    std::cout << std::endl;
    return powValues;
}

void WriteOutData(const std::vector<float>& vec, const std::string& filename){      // function that save a vector into a file called filename

    std::ofstream myOutput;
    myOutput.open(filename);

    if(myOutput.fail()){
        std::cout << "Sorry, couldn't open the output file: " << filename << std::endl;
        exit(1);
    }
    else{
        for (const float& element : vec){
            
            myOutput << element << std::endl;
        }
    }

    myOutput.close();
}

void WriteOutData(const std::string& myString, const std::string& filename){        // function that save a string into a file called filename

    std::ofstream myOutput;
    myOutput.open(filename);

    if(myOutput.fail()){
        std::cout << "Sorry, couldn't open the output file: " << filename << std::endl;
        exit(1);
    }
    else{
        myOutput << myString;
    }

    myOutput.close();
}