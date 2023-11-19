#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "someFunctions.h"
using namespace boost::numeric::ublas;

class environment{
    public:
        float wavelength { 1 };
        int n_dipoles { 10 };
        float area_width { 10 };
        int points_per_wavelength { 6 };
        float fraction_of_max_alpha { 1 };

        int n_pixels() const {
            return static_cast<int>((area_width / wavelength) * points_per_wavelength);
        } 
        float wavevector() const {
            return 2 * M_PI / wavelength;
        }
        float wavevector_squared() const {
            return wavevector() * wavevector();
        }
        float x_start() const {
            return -1 * area_width / 2;
        }
        std::vector<float> grid_points_1D() const {
            std::vector<float> grid_points = linspace(x_start(), x_start()+area_width, n_pixels());
            return grid_points;
        }
        matrix<float> x_mesh() const {            
            return x_meshgrid(grid_points_1D());
        }
        matrix<float> y_mesh() const {
            return y_meshgrid(grid_points_1D());
        }
        std::complex<double> alpha() const {
            return calculate_polarizability(fraction_of_max_alpha, wavevector_squared());
        }
        int n_sources() const {
            return static_cast<int>((area_width / wavelength)*4);
        }
        int n_detectors() const {
            return static_cast<int>((area_width / wavelength)*4);
        }
        matrix<float> x_sources() const{
            matrix<float> x_s (n_sources(),1);
            float x_0 = x_start();
            for (int i=0; i<x_s.size1(); ++i)
                x_s(i,0) = x_0;
            return x_s;
        }
        matrix<float> y_sources() const{
            matrix<float> y_s (n_sources(),1);
            std::vector<float> grid_points = grid_points_1D();
            for (int i=0; i<y_s.size1(); ++i)
                y_s(i,0) = grid_points[i];
            return y_s;
        }

        matrix<float> x_detectors() const{
            matrix<float> x_d (n_detectors(),1);
            float x_0 = -1 * x_start();
            for (int i=0; i<x_d.size1(); ++i)
                x_d(i,0) = x_0;
            return x_d;
        }
        matrix<float> y_detectors() const{
            matrix<float> y_d (n_detectors(),1);
            std::vector<float> grid_points = grid_points_1D();
            for (int i=0; i<y_d.size1(); ++i)
                y_d(i,0) = grid_points[i];
            return y_d;
        }
};

#endif