#include "gph_cpp.hpp"
// PyRun_SimpleString(char_array);
// search:  matplotlib.pyplot.plot
gph_cpp::gph_cpp(){

    // command.clear();
    header.append("import matplotlib as mpl\n");
    header.append("import matplotlib.pyplot as plt\n");
    header.append("import numpy as np\n");

    Py_Initialize();
}

gph_cpp::~gph_cpp(){

    Py_Finalize();
}

void gph_cpp::plot(std::vector<double> X, std::vector<double> Y){
    
    std::string command;

    command.append(header);
    command.append("X = np.array(");
    command.append(geraArray(X));
    command.append(")\n");
    command.append("Y = np.array(");
    command.append(geraArray(Y));
    command.append(")\n");
    // command.append();

    command.append("plt.xlabel('X', size = ");
    command.append(std::to_string(X.size()));
    command.append(")\n");
    command.append("plt.ylabel('Y', size = ");
    command.append(std::to_string(Y.size()));
    command.append(")\n");

    command.append("plt.cla()\n");
    command.append("plt.clf()\n");
    command.append("plt.close()\n");

    char char_array[command.length() + 1];
    strcpy(char_array, command.c_str());

    PyRun_SimpleString(char_array);
}

std::string gph_cpp::geraArray(std::vector<double> array){
    
    std::string result;
    std::string tmp;

    result.append("[");
    for(auto it = array.begin(); it!=array.cend(); it++ ){
        // std::stringstream sin(tmp);
        // sin << 
        result.append(std::to_string(*it));
        if(it++ != array.cend()){
            result.append(",");
        }
    }
    result.append("]");
    
    return result;
}