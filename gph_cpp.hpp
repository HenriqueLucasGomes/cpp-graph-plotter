#ifndef GPH_CPP
#define GPH_CPP


#include <string>
#include <sstream>
#include <vector>
#include <string.h>
// #include <iostream>

// python
# include <python2.7/Python.h>
# include <python3.8/Python.h>

class gph_cpp
{
private:
    std::string header;
    // std::vector<double> X;
    // std::vector<double> Y;

public:
    gph_cpp();
    void plot(std::vector<double> X, std::vector<double> Y);
    std::string geraArray(std::vector<double> array);
    ~gph_cpp();
};



#endif