#include <iostream>
#include <random>

int main(int argc, char *argv[]){       
    
    double radius = std::stod(argv[1]);
    int n_random = std::stoi(argv[2]);

    double x{0.0};    // x coordinate of the point. It spans between 0 and 2*radius
    double y{0.0};    // y coordinate of the point. It spans between 0 and 2*radius
    int count{0};     // number of points that fall inside the circle centered in (1*radius, 1*radius)
    double d{0.0};    // distance of the point from the center of the circle
    std::random_device rd;
    std::mt19937 mtEngine{rd()};
    std::uniform_real_distribution<double> uniformPDF{0, 2*radius};
    for(int i=0; i<n_random; i++){
        x = uniformPDF(mtEngine);
        y = uniformPDF(mtEngine);
        d = std::sqrt((x-radius)*(x-radius) + (y-radius)*(y-radius));
        if (d <= radius){
            count ++;
        }
    }
    std::cout << count << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);
    std::cout << "The value of pi is: " << (static_cast<double>(count) /n_random)*4 << std::endl << std::endl;

}