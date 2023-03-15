#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <sstream>

#include <cmath>

# include <python2.7/Python.h>
# include <python3.8/Python.h>

//g++ main.cpp -o main.bin -g -Wall -lpython2.7 -lm -L/usr/lib/python2.7/config
//g++ main.cpp -o main.bin -g -Wall -lpython3.8 -lm -L/usr/lib/python3.8/config


//#include "matplotlib-cpp-master/matplotlibcpp.h"
// #include "matplotlibcpp.h"

//g++ main.cpp -std=c++11 -I/usr/include/python2.7 -I/usr/lib/python2.7/site-packages/numpy/core/include -lpython2.7 -o main.bin
//g++ main.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7 -o main.bin

// sudo apt-get update
// sudo apt-get install gnuplot
// sudo apt-get install libgnuplot-iostream-dev

// #include "gnuplot-iostream.h"

#define TAM 75

using namespace std;

string ARQ_INPUT;
string ARQ_OUTPUT;


int comparacoes[TAM];
int copias[TAM];
double tempo[TAM];
double media[TAM/5];

void Cal_media(double* vet){

    for(int i=0;i<TAM/5; i++){
        media[i]=(vet[i]+vet[i+15]+vet[i+30]+vet[i+45]+vet[i+60])/5;
    }  

}

void repete(string *command, double* vet, string cor){

    string tmp;
    stringstream sin;

     Cal_media(vet);

    (*command).append("X = np.array([1000,5000,10000,50000,90000,100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000])\n");
    (*command).append("Y = np.array([");
    
    tmp.clear();
    sin.clear();
    sin << media[0];
    sin >> tmp;
    (*command).append(tmp);

    for(int i=1; i < TAM/5; i++){
        (*command).append(",");
        tmp.clear();
        sin.clear();
        sin << media[i];//
        sin >> tmp;
        (*command).append(tmp);    
    }
    (*command).append("])\n");

    (*command).append("plt.plot(X,Y,'-");
    (*command).append(cor);
    (*command).append("')\n");

}

void compara_grafico(){
    ifstream fin("../TP/out/quick1_10.txt");
    string linha;
    int aux1,aux2;
    double temp1[TAM],temp2[TAM],temp3[TAM],temp4[TAM],temp5[TAM];

    for(int i=0;i<TAM;i++){
        getline(fin,linha);
        stringstream sin(linha);
        sin >> aux1 >> aux2 >> temp1[i];
    }
    fin.close();

    fin.open("../TP/out/quick2_10.txt");
    for(int i=0;i<TAM;i++){
        getline(fin,linha);
        stringstream sin(linha);
        sin >> aux1 >> aux2 >> temp2[i];
    }
    fin.close();

    fin.open("../TP/out/quick3_10.txt");
    for(int i=0;i<TAM;i++){
        getline(fin,linha);
        stringstream sin(linha);
        sin >> aux1 >> aux2 >> temp3[i];
    }
    fin.close();

    fin.open("../TP/out/quick4_10.txt");
    for(int i=0;i<TAM;i++){
        getline(fin,linha);
        stringstream sin(linha);
        sin >> aux1 >> aux2 >> temp4[i];
    }
    fin.close();

    fin.open("../TP/out/quick5_10.txt");
    for(int i=0;i<TAM;i++){
        getline(fin,linha);
        stringstream sin(linha);
        sin >> aux1 >> aux2 >> temp5[i];
    }
    fin.close();

    string command;
    string tmp;
    stringstream sin;



    command.clear();

    command.append("import numpy as np\n");
    command.append("import matplotlib.pyplot as plt\n");

    repete(&command,temp1,"ro");// 1
    repete(&command,temp2,"go");// 2
    repete(&command,temp3,"bo");// 3
    repete(&command,temp4,"yo");// 4
    repete(&command,temp5,"ko");// 5
    
    // repete(&command,temp1,"ro");// quick
    // repete(&command,temp2,"go");// merge
    // repete(&command,temp3,"bo");// heap

    command.append("plt.xlabel('Input',size = 12)\n");
    command.append("plt.ylabel('runtime(10^(-2))', size = 12)\n");

    command.append("plt.savefig('out/graph/");
    command.append("tempo_compara_quick");
    command.append(".png')\n");

    if(false){
        command.append("plt.cla()\n");
        command.append("plt.clf()\n");
        command.append("plt.close()\n");
    }

    // cout << (*command) << endl;

    char char_array[command.length() + 1];
    strcpy(char_array, command.c_str());

    PyRun_SimpleString(char_array);

}

void LeArq(){
    ifstream fin(ARQ_INPUT);
    string linha;

    for(int i=0;i<TAM;i++){
        getline(fin,linha);
        stringstream sin(linha);
        sin >> comparacoes[i] >> copias[i] >> tempo[i];
    }
    fin.close();
}

void EscreveArq(){

    string out = "out/media/media_";
    out.append(ARQ_OUTPUT);
    out.append(".txt");

    ofstream fout(out);

    double MedComparacoes=0;
    double MedCopias=0;
    double MedTempo=0;

    for(int i=0; i<TAM; i++){
        MedComparacoes+= comparacoes[i];
        MedCopias+= copias[i];
        MedTempo+= tempo[i]; 
    }

    MedComparacoes = MedComparacoes/TAM;
    MedCopias = MedCopias/TAM;
    MedTempo = MedTempo/TAM; 

    fout << fixed << setprecision(5); // precisão do ponto flutuante

    fout << MedComparacoes << " " << MedCopias << " " << MedTempo << " " << endl;

    fout.close();

}

void body(double *vet, string* command, string tipo,bool limpa){

    string tmp;
    stringstream sin;

    Cal_media(vet);

    (*command).clear();

    (*command).append("import numpy as np\n");
    (*command).append("import matplotlib.pyplot as plt\n");
    (*command).append("X = np.array([1000,5000,10000,50000,90000,100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000])\n");
    (*command).append("Y = np.array([");
    
    tmp.clear();
    sin.clear();
    sin << media[0];
    sin >> tmp;
    (*command).append(tmp);

    for(int i=1; i < TAM/5; i++){
        (*command).append(",");
        tmp.clear();
        sin.clear();
        sin << media[i];//
        sin >> tmp;
        (*command).append(tmp);    
    }
    (*command).append("])\n");

    // if(tipo=="comparacoes"){
    //     (*command).append("plt.plot(X,Y,'-ro')\n");
    // }else if(tipo=="copias"){
    //     (*command).append("plt.plot(X,Y,'-bo')\n");
    // }else if(tipo=="tempo"){
    //     (*command).append("plt.plot(X,Y,'-go')\n");
    // }

    (*command).append("plt.plot(X,Y,'-ro')\n");
    
    // (*command).append("plt.title('SEU TÍTULO LINDO')");
    // (*command).append("plt.xaxis('nome')");
    // (*command).append("plt.xlabel('NOME DO EIXO X')");
    // (*command).append("plt.ylabel('NOME DO EIXO Y')");
    (*command).append("plt.xlabel('Input',size = 12)\n");
    (*command).append("plt.ylabel('runtime(10^(-2))', size = 12)\n");

    (*command).append("plt.savefig('out/graph/");
    (*command).append(ARQ_OUTPUT);
    (*command).append("_");
    (*command).append(tipo);
    (*command).append(".png')\n");

    if(limpa){
        (*command).append("plt.cla()\n");
        (*command).append("plt.clf()\n");
        (*command).append("plt.close()\n");
    }

    // cout << (*command) << endl;

    char char_array[(*command).length() + 1];
    strcpy(char_array, (*command).c_str());

    PyRun_SimpleString(char_array);
}

void GeraGraficos(){
    // gerar os graficos

    string command;
    string tmp;
    stringstream sin;

    double tmp1[TAM];
    double tmp2[TAM];

    for(int i=0;i<TAM; i++){
        tmp1[i] = comparacoes[i];
        tmp2[i] = copias[i];
    }

    
    body(tmp1,&command, "comparacoes",true);
    body(tmp2,&command, "copias",true);
    body(tempo,&command, "tempo",true);


    
}

void Arq_Entrada(){
    

    ifstream fin("entrada.txt");
    string linha;

    

    for(int i=0;i<TAM;i++){
        getline(fin,linha);

        ARQ_INPUT = linha; //"../TP/out/quick1_10.txt"
        cout << ARQ_INPUT << endl;

        linha.erase(linha.begin(),linha.begin()+10);
        linha.erase(linha.cend()-4,linha.cend());
        ARQ_OUTPUT  = linha; //"quick1_10"; 
        cout << ARQ_OUTPUT << endl;


        LeArq();
        EscreveArq();
        GeraGraficos();
    }
    
    
}

int main(){
    
    Py_Initialize();
    // Arq_Entrada();  
    compara_grafico();  
    Py_Finalize();
    
    return 0;
}