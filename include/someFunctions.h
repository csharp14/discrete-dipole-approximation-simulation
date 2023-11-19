#ifndef SOMEFUNCTIONS_H
#define SOMEFUNCTIONS_H

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <numeric>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <tuple>
#include <complex>

/* Here are some methods that will come in handy. */

// Function to create a vector containing a range from vec_start to vec_end with num_elements number of elements.
template<typename T>
std::vector<float> linspace(T vec_start, T vec_end, int num_elements){
    std::vector<float> linspaced;

    float start = static_cast<float>(vec_start);
    float end = static_cast<float>(vec_end);
    float num = static_cast<float>(num_elements);

    if (num_elements == 0) { return linspaced; }
    if (num_elements == 1) { 
        linspaced.push_back(start);
        return linspaced;
    }

    float delta = (end - start) / (num_elements - 1);

    for(int i=0; i < num_elements-1; ++i)
    {
        linspaced.push_back(start + delta * i);
    }
    linspaced.push_back(end);
    return linspaced;
}

// Function to print out a vector to the terminal
void print_vector(std::vector<float> vec)
{
  std::cout << "size: " << vec.size() << std::endl;
  for (float d : vec)
    std::cout << d << " ";
  std::cout << std::endl;
}

// Function to create a 2D meshgrid given a 1D vector 
using namespace boost::numeric::ublas;
matrix<float> x_meshgrid(std::vector<float> x_vec){
    matrix<float> x_mesh (x_vec.size(),x_vec.size());
    for (int i=0; i<x_vec.size(); ++i)
    {
        for (int j=0; j<x_vec.size(); ++j)
        {x_mesh(j,i) = x_vec[i];}
    }
    return x_mesh;
}

// Function to create a 2D meshgrid given a 1D vector 
matrix<float> y_meshgrid(std::vector<float> y_vec){
    matrix<float> y_mesh (y_vec.size(),y_vec.size());
    for (int i=0; i<y_vec.size(); ++i)
    {
        for (int j=0; j<y_vec.size(); ++j)
        {y_mesh(i,j) = y_vec[i];}
    }
    return y_mesh;
}

// Function to calculate polarizability alpha
std::complex<float> calculate_polarizability(float fraction_of_max_alpha, float wavevector_sq){
    std::complex<float> alpha;
    float alpha_mod, alpha_arg;
    alpha_mod = (4 / wavevector_sq)*fraction_of_max_alpha;
    alpha_arg = asin(0.25*alpha_mod*wavevector_sq);
    alpha = std::polar(alpha_mod,alpha_arg);
    // std::cout << "Alpha_mod: " << alpha_mod << std::endl;
    // std::cout << "Alpha_arg: " << alpha_arg << std::endl;
    // std::cout << "Alpha: " << alpha << std::endl;
    return alpha;
}

#endif