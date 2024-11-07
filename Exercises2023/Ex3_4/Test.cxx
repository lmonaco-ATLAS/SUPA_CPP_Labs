#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "FiniteFunctions.h"
#include "customFunctions.h"

int main(){ 

    //  Read the file with mystery data points and put them into a vector

    std::ifstream input_file("./Outputs/data/MysteryData01440.txt");

    if(!input_file.is_open()){
        std::cout << "Error opening the file with data points" << std::endl;
        return -1;
    }

    std::vector<double> points{};
    double temp{0.0};
    while(input_file.tellg() != -1){
        input_file >> temp;
        points.push_back(temp);
        input_file.seekg(1, input_file.cur);
    }

    const double RMin = - std::ceil(-*std::min_element(points.begin(), points.end())) -2;     //determine the low extreme of the interval from data
    const double RMax = std::ceil(*std::max_element(points.begin(), points.end())) + 2;

    const int Nbins = 100;        // number of histogram bins for plotting data
    const int Ndiv = 100000;       // number of divisions for the integral
    bool isdata = true;

    // Test default function

    FiniteFunction defaultFunc(RMin, RMax, "DefaultFun_Test");
    defaultFunc.integral(Ndiv);

    defaultFunc.plotFunction();
    defaultFunc.plotData(points, Nbins, isdata = true);
    defaultFunc.printInfo();

    std::cout << std::endl;

    // Test gaussianlFunction    - This is the function that fit the data

    double mu = -1; 
    double sigma = 3;
    Gauss gaussFunc(RMin, RMax, mu, sigma);
    gaussFunc.setOutfile("GaussFun_Test");
    gaussFunc.integral(Ndiv);

    gaussFunc.plotFunction();
    gaussFunc.plotData(points, Nbins, isdata = true);
    gaussFunc.printInfo();

    std::cout << std::endl;
    
    // Test CauchyFunction

    double mu1 = -1; 
    double gamma = 2.5;
    Cauchy cauchyFunc(RMin, RMax, mu1, gamma);
    cauchyFunc.setOutfile("CauchyLorentzFun_Test");
    cauchyFunc.integral(Ndiv);

    cauchyFunc.plotFunction();
    cauchyFunc.plotData(points, Nbins, isdata = true);
    cauchyFunc.printInfo();

    std::cout << std::endl;
    
    // Test CrystalFunction

    double mu2 = -1; 
    double sigma2 = 3;
    double n = 15;
    double alpha = 5;
    Crystal crystalFunc(RMin, RMax, mu2, sigma2, n, alpha);
    crystalFunc.setOutfile("NegCrystalBallFun_Test");
    crystalFunc.integral(Ndiv);

    crystalFunc.plotFunction();
    crystalFunc.plotData(points, Nbins, isdata = true);
    crystalFunc.printInfo();

    std::cout << std::endl;

    // Sample data from the gaussian distribution, which is the one that fits the mystery data

    int Nsamples = 1e7;
    std::vector<double> sampledData = gaussFunc.sampleData(Nsamples);
    gaussFunc.plotData(sampledData, Nbins, isdata = false);

    std::cout << std::endl;
    
    return 1;

}