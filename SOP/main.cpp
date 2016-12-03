#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Checks if a vector contains a given node
bool checkNode(vector<int> arr, int seek)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == seek)
            return true;
    }
    return false;
}

// Populates a given vector with a greedy SOP solution, given an arch weight matrix
int generateGreedyInstance(vector<vector<int> > weights, vector<int> *instance, int dimension){

//    pega menor da linha q n -1, que n usado e que n precedence
//    checa pra todos -1 da linha do escolhido se estão usados
//    se algum não, adiciona na lista de precedência e volta pra
//    procurar menor de novo
    instance->push_back(1);
    vector<int> precedence;
    int minWeight, nextNode, cost = 0;
    int i = 0;
    int currentNode = 0;
    int found, candidateNode, able;
    for(int k = 1; k < dimension-1; k++){
        minWeight = 5000000;
        candidateNode = 0;
        found = 0;
        while(found == 0){
            for(int j = 1; j < dimension-1; j++){
                if(weights[i][j] != -1 && (checkNode(*instance, j+1) == false) && (checkNode(precedence, j+1) == false)){
                    if(weights[i][j] < minWeight){
                        minWeight = weights[i][j];
                        candidateNode = j + 1;
                        cout << "\ncusto " << minWeight;
                    }
                }
            }
            int n = candidateNode - 1;
            able = 1;

            for(int j = 1; j < dimension-1; j++){
                if(weights[n][j] == -1 && checkNode(*instance, j+1) == false){
                    able = 0;
                    break;
                }
            }
            if(able){
                cout << "\nAble: " << candidateNode;;
                instance->push_back(candidateNode);
                found = 1;
                precedence.clear();
                i = candidateNode -1;
            }else{
                cout << "\nUnable: " << candidateNode;;
                minWeight = 5000000;
                precedence.push_back(candidateNode);
            }
        }
        cost += minWeight;
    }
    instance->push_back(dimension);

    return cost;
}

// Checks if a given path respects the precedence constraints on arch weight matrix
bool isValidPath (vector<vector<int> > weights, vector<int> path){

    vector<int> precedence;
    int node;
    for(int i = 0; i < path.size()-1; i++){
        precedence.push_back(path[i]);
        node = path[i] - 1;
        for(int j = 0; j < path.size(); j++){
            if(weights[node][j] == -1 && checkNode(precedence, j+1) == false){
                 cout << "\nNode " << j+1 << " has to go before " << path[i];
                 return false;
            }
        }
        cout << "\nNode " << path[i] << " followed by " << path[i+1] << " = ok";
        cout << "\nArch Cost = " << weights[path[i]-1][path[i+1]-1];
    }
    return true;
}

int main(int argc, const char * argv[]) {
    // insert code here...

    ifstream file;
    int dimension;
    string buffer;
    string fileToBeOpened;

    cout << "Choose the file >> ";
    cin >> fileToBeOpened;

    file.open(fileToBeOpened.c_str());

    if(file) {

        cout << "Opened file" << endl;
    } else {

        cout << "File error" << endl;
    }

    getline(file, buffer);
    getline(file, buffer);
    getline(file, buffer);
    getline(file, buffer);
    getline(file, buffer);
    getline(file, buffer);
    getline(file, buffer);

    file >> dimension;

    vector<vector<int> > weights(dimension);

    // Populates arch weight matrix from given file
    for(int i = 0; i < weights.size(); i++) {

        weights[i].resize(dimension);
    }

    for(int i = 0; i < dimension; i++) {

        for(int j = 0; j < dimension; j++) {

            file >> weights[i][j];
        }
    }

    // Prints arch weight matrix on screen
    for(int i = 0; i < dimension; i++) {

        for(int j = 0; j < dimension; j++) {

            cout << weights[i][j] << " ";
        }

        cout << endl;
    }
    vector<int> path;
    int instanceCost = generateGreedyInstance(weights, &path, dimension);

    cout << "\nGreedy Instance Generated\n";

    cout << "First Instance:\n";
    for(int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
        }
    cout << "\nInstance Cost: " << instanceCost;

    if(isValidPath(weights, path)){
        cout <<  "\nGG Path";
    }else{
        cout << "\nNot GG Path";
    }

    static const int arr[] = {1,2,8,11,9,5,10,13,3,6,4,7,12,14};
    //static const int arr[] = {1,2,8,11,9,5,10,3,6,4,7,12,14,13};
    vector<int> test (arr, arr + sizeof(arr) / sizeof(arr[0]) );

    if(isValidPath(weights, test)){
        cout <<  "\nGG Path";
    }else{
        cout << "\nNot GG Path";
    }

    return 0;
}
