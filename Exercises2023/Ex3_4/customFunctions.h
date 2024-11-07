# include <iostream>
#include "FiniteFunctions.h"

#pragma once

class Gauss : public FiniteFunction{

    public:

        Gauss(double RMin, double RMax, double mu, double sigma);     

        void printInfo(); 
        double callFunction(double x); 

    private:

        double m_mu{0.0};
        double m_sigma{0.0};

};

class Cauchy : public FiniteFunction{

    public:

        Cauchy(double RMin, double RMax, double mu, double gamma);     

        void printInfo(); 
        double callFunction(double x); 

    private:

        double m_mu{0.0};
        double m_gamma{0.0};

};

class Crystal : public FiniteFunction{

    public:

        Crystal(double RMin, double RMax, double mu, double sigma, double n, double alpha);    
        
        void printInfo(); 
        double callFunction(double x); 

    private:

        double m_mu{0.0};
        double m_sigma{0.0};
        double m_n{0.0};
        double m_alpha{0.0};
        double m_A{0.0};
        double m_B{0.0};
        double m_N{0.0};

};
