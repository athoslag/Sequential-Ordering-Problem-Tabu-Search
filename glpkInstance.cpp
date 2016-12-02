#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;
static int infinito = -1;

int main(){

    string shit;
    //le 7 linhas inuteis de informaçao
    for(int i=0; i<7; i++){
        getline(cin, shit);
    }

    int tam;
    cin >> tam;
    int custo[tam][tam];
    int precedencia[tam][tam];

    int c;
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            cin >> c;
            if(c== -1){
                custo[i][j] = infinito;
                precedencia[j][i] = 1;
            }else{
                custo[i][j] = c;
                precedencia[j][i] = 0;
            }          

        }
    }    
    
    cout << "data;" << endl;
    cout << "set N:= " ;
    for(int i=0; i<tam; i++){
        cout << i << " "; 
    }
    cout << ";" << endl;

    cout << "set C:= " ;
    for(int i=1; i<tam-1; i++){
        cout << i << " "; 
    }
    cout << ";" << endl;

    cout << "param G:= 100000;" << endl;
    cout << "param c:" << endl;
    for(int i=0; i<tam; i++){
        cout << i << " "; 
    }
    cout << ":=" << endl;

    for(int i=0; i<tam; i++){
        cout << i << " "; 
        for(int j=0; j<tam; j++){
                cout << custo[i][j] << " "; 
        }
        cout << endl;
    }
    cout << ";" << endl;
    cout << "param p:" << endl;
    for(int i=0; i<tam; i++){
        cout << i << " "; 
    }
    cout << ":=" << endl;
    for(int i=0; i<tam; i++){
        cout << i << " "; 
        for(int j=0; j<tam; j++){
                cout << precedencia[i][j] << " "; 
        }
        cout << endl;
    }
    cout << ";" << endl;
    cout << "end:";






















    return 0;
}
