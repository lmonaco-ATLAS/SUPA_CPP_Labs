//Name: Leonardo Monaco, data of creation: Oct 22, 2024
// This file contains the prototypes for the custom functions

#pragma once

std::pair<std::vector<float>, std::vector<float>> FileToVec(std::ifstream& input_file);   // Functions that read the file and print it into two vectors

void PrintData(const std::vector<float>& vec1, const std::vector<float>& vec2, int& nlines);   // Functions that print n pairs of data, taking them from vectors

std::vector<float> AbsValuesCalculation(const std::vector<float>& vec1, const std::vector<float>& vec2);  // Fnction that compute and print the absolute value for each data point, and store it in another vector

std::string StraightLineFit(const std::vector<float>& vec1, const std::vector<float>& vec2);   //function that computes the straigh line fit, performes chi_squared test, print and store the results in a string.

float SinglePowerComputation(const float& x, int y);       //function that makes the power elevation x^y with y integer.

std::vector<float> PowerCalculation(const std::vector<float>& vec1, const std::vector<float>& vec2);   // Function that compute and print the power value x^y for each data point, and store it in another vector

void WriteOutData(const std::vector<float>& vec, const std::string& filename);  // function that save a vector into a file called filename

void WriteOutData(const std::string& myString, const std::string& filename);    // function that save a string into a file called filename