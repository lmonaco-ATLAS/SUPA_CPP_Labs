#include <iostream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include "customFunctions.h"
#include <cmath>
// when calling the constructors, I set a default name for the output files. Then they can be changed if necessary by calling setOutfile method

// --------------Gaussian Function  ------------------------------
Gauss::Gauss(double RMin, double RMax, double mu, double sigma) : FiniteFunction(RMin, RMax, "GaussFun") {
    m_mu=mu; 
    m_sigma=std::abs(sigma);
}; 

double Gauss::callFunction(double x){return std::exp(-0.5*std::pow((x-m_mu)/m_sigma, 2))/(m_sigma*std::sqrt(2*M_PI));};

void Gauss::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "Mean value: " << m_mu << std::endl;
  std::cout << "std deviation: " << m_sigma << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}


// --------------Cauchy Lorentz Function ---------------------
Cauchy::Cauchy(double RMin, double RMax, double mu, double gamma) : FiniteFunction(RMin, RMax, "CauchyLorentzFun") {
    m_mu = mu;
    if (gamma <= 0){
        std::cout << "The value for the gamma parameter of the Cauchy-Lorentz function is not valid" << std::endl;
        exit(1);
    }
    m_gamma = gamma;
};  

double Cauchy::callFunction(double x){return 1/(M_PI*m_gamma*(1+std::pow((x-m_mu)/m_gamma, 2)));};

void Cauchy::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "Mean value: " << m_mu << std::endl;
  std::cout << "gamma: " << m_gamma << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}


// --------------Negative Crystal Ball Function ---------------------
Crystal::Crystal(double RMin, double RMax, double mu, double sigma, double n, double alpha) : FiniteFunction(RMin, RMax, "NegCrystalBallFun") {
    m_mu = mu;
    m_sigma = std::abs(sigma);
    if (n<=1){
        std::cout << "The value for the n parameter of the Crystal Ball function is not valid" << std::endl;
        exit(1);
    }
    m_n = n;
    if (alpha<=0){
        std::cout << "The value for the alpha parameter of the Crystal Ball function is not valid" << std::endl;
        exit(1);
    }
    m_alpha = alpha;
    m_A = std::pow(n/std::abs(alpha),n) * std::exp(-0.5*std::pow(std::abs(alpha),2));
    m_B = n/std::abs(alpha) - std::abs(alpha);
    double C = n * std::exp(-0.5*std::pow(std::abs(alpha),2)) /(std::abs(alpha)*(n-1));
    double D = std::sqrt(0.5*M_PI) * (1 + std::erf(std::abs(alpha)/std::sqrt(2)));
    m_N = 1/(sigma*(C+D));
}; 

double Crystal::callFunction(double x){
    if ((x-m_mu)/m_sigma > -m_alpha){
        return m_N * std::exp(-0.5*std::pow((x-m_mu)/m_sigma, 2));
    }
    if ((x-m_mu)/m_sigma <= -m_alpha){
        return m_N * m_A * std::pow(m_B - (x-m_mu)/m_sigma, -m_n);
    }
};

void Crystal::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "Mean value: " << m_mu << std::endl;
  std::cout << "std deviation: " << m_sigma << std::endl;
  std::cout << "alpha: " << m_alpha << std::endl;
  std::cout << "n: " << m_n << std::endl;
  std::cout << "A: " << m_A << "  B: " << m_B << "  N: " << m_N << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}