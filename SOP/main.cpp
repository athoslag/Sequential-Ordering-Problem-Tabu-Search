#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#define ITERATIONS 30
#define INFINITY 9999999

int iterationCounter = 0;

using namespace std;

struct tabuTuple{
  int a;
  int b;
};

//vector<tuple<int,int>> tabuList;
vector<tabuTuple> tabuList;
int maxSaving;

void printPath(vector<int> path){

    for (unsigned int i = 0; i < path.size(); i++){
        cout << path[i] << " ";
    }
    cout << endl;

}

void printTabuList(){
    cout << "tabuList: ";
    for (unsigned int i = 0; i < tabuList.size(); i++){
        cout << " - <" << tabuList[i].a << ", " << tabuList[i].b << ">";
    }
    cout << endl << endl;
}

void insertTabu(tabuTuple tabu){
    bool found = false;

    for (unsigned int i = 0; i < tabuList.size(); i++){
        if (tabuList[i].a == tabu.a && tabuList[i].b == tabu.b)
            found = true;
    }
    if (!found)
        tabuList.push_back(tabu);
}

// Checks if a vector contains a given node
bool checkNode(vector<int> arr, int seek){
    for (unsigned int i = 0; i < arr.size(); ++i){
        if (arr[i] == seek)
            return true;
    }
    return false;
}

int getCost(vector<vector<int> > weights, vector<int> path){
    int totalCost = 0;

    for (unsigned int i = 0; i < path.size()-1; i++){
        totalCost = totalCost + weights[path[i]-1][path[i+1]-1];
    }
    return totalCost;
}

int getSwapCost (vector<vector<int> > weights, vector<int> path, int a, int b){
    vector<int> auxNodes;
    auxNodes.resize(path.size());

    // compute new path
    for(int i = 0; i <= a; i++){
        auxNodes[i] = path[i];
    }
    for(int i = 0; i < b - a; i++){
        auxNodes[a+i+1] = path[b-i];
    }
    for(unsigned int i = b + 1; i < path.size(); i++){
        auxNodes[i] = path[i];
    }

    // update path
    for(unsigned int i = 0; i < path.size(); i++){
        path[i] = auxNodes[i];
    }

    int cost = getCost(weights, path);

    return cost;
}

int getCostAtoB(vector<vector<int> > weights, vector<int> path, int a, int b){
    int totalCost = 0;

    if (a < b){
        for (int i = a; i < b; i++){
                totalCost = totalCost + weights[path[i]-1][path[i+1]-1];
        }
        return totalCost;
    }
    else{
        for (int i = b; i < a; i++){
                totalCost = totalCost + weights[path[i]-1][path[i+1]-1];
        }
        return totalCost;
    }
}

// Checks if a given path respects the precedence constraints on arch weight matrix
bool isValidPath (vector<vector<int> > weights, vector<int> path){

    vector<int> precedence;
    int node;
    for(unsigned int i = 0; i < path.size()-1; i++){
        precedence.push_back(path[i]);
        node = path[i] - 1;
        for(unsigned int j = 0; j < path.size(); j++){
            if(weights[node][j] == -1 && checkNode(precedence, j+1) == false){
                 //cout << "\nNode " << j+1 << " has to go before " << path[i];
                 return false;
            }
        }
        //cout << "\nNode " << path[i] << " followed by " << path[i+1] << " = ok";
        //cout << "\nArch Cost = " << weights[path[i]-1][path[i+1]-1];
    }
    return true;
}

bool isTabu (int a, int b){
    tabuTuple movement;
    movement.a = a;
    movement.b = b;
    //cout << endl << "Checking tabu... ";
    for(unsigned int i = 0; i < tabuList.size(); i++){
        if ((tabuList[i].a == movement.a) && (tabuList[i].b == movement.b)){
            //cout << "is tabu." << endl;
            return true;
        }
    }
    //cout << "is not tabu." << endl;
    return false;
}

bool isValidMove (vector<vector<int> > weights, vector<int> path, int a, int b){
    vector<int> auxNodes;
    auxNodes.resize(path.size());

    // compute new path
    for(int i = 0; i <= a; i++){
        auxNodes[i] = path[i];
    }
    for(int i = 0; i < b - a; i++){
        auxNodes[a+i+1] = path[b-i];
    }
    for(unsigned int i = b + 1; i < path.size(); i++){
        auxNodes[i] = path[i];
    }

    // update path
    for(unsigned int i = 0; i < path.size(); i++){
        path[i] = auxNodes[i];
    }

    if(isValidPath(weights, path)){
        //cout << endl << "[isValidMove] Path is valid: ";
        //printPath(path);
        return true;
    }else{
        return false;
    }
}

tabuTuple twoOptSearch(vector<vector<int> > weights, vector<int> path){
    /* In each iteration, apply a 2-opt move. That is, find pair of edges
     * (a,a+1) and (b,b+1) such that replacing them with (a,b) and (a+1,b+1)
     * minimizes tour length.
     *
     *       a   b                   a   b
     *  ────→●   ●←────         ────→●───●────→
     *        ╲ ╱
     *         ╳          ==>
     *        ╱ ╲
     *  ←────●   ●────→         ←────●───●←────
     *      b+1 a+1                 b+1 a+1
     */

    int change;
    //int minChange;
    int aMin, bMin, aBad, bBad;
    int oldDistance1;//, oldDistance2;
    int newDistance1;//, newDistance2;

    // repeat until there are not new improvement
   // while(minChange){
    //minChange = 0;
    maxSaving = 0;
    int badResult = 1;
    //int badSaving = 0;
    for(unsigned int a = 1; a < path.size()-3; a++){
        for(unsigned int b = a + 1; b < path.size()-2; b++){
//            oldDistance1 = getCostAtoB(weights, path, a, a+1);
//            oldDistance2 = getCostAtoB(weights, path, b, b+1);
//            newDistance1 = getCostAtoB(weights, path, a, b);
//            newDistance2 = getCostAtoB(weights, path, a+1, b+1);
//            change = newDistance1 + newDistance2 - oldDistance1 - oldDistance2;
            if (isTabu(a, b))
                break;

            oldDistance1 = getCost(weights, path);
            newDistance1 = getSwapCost(weights, path, a, b);
            change = newDistance1 - oldDistance1;
            //cout << "[twoOptSearch] Change: " << change;
            // ERROR: without this small offset there is an infinite loop.
            /*if (change < maxSaving){
                tabuTuple semiTup;
                semiTup.a = a;
                semiTup.b = b;
                insertTabu(semiTup);
            }*/

            if(!(isTabu(a,b)) && change < maxSaving && isValidMove(weights, path, a, b)){
                maxSaving = change;
                aMin = a;
                bMin = b;
                badResult = 0;
            }else{
                if(b-a>3)
                    if(isValidMove(weights, path, a, b) && (!isTabu(a,b))){
                        //badSaving = change;
                        aBad = a;
                        bBad = b;
                }
            }
        }
    }
    tabuTuple tupleAB;
    if(badResult){
        tupleAB.a = aBad;
        tupleAB.b = bBad;
    }else{
        tupleAB.a = aMin;
        tupleAB.b = bMin;
    }
    //cout << "n\[twoOptSearch] returning tuple (a,b): " << tupleAB.a << ", " << tupleAB.b << endl;
    insertTabu(tupleAB);
    return tupleAB;
}

void twoOptMove(vector<int> *path, int a, int b){
    /* - take tour[0] to tour[a] and add them in order to new tour
     * - take tour[a+1] to tour[b] and add them in reverse order to new tour
     * - take tour[b+1] to end and add them in order to new tour
     *
     *       a   b                   a   b
     *  ────→●   ●←────         ────→●───●────→
     *        ╲ ╱
     *         ╳          ==>
     *        ╱ ╲
     *  ←────●   ●────→         ←────●───●←────
     *      b+1 a+1                 b+1 a+1
     */
    vector<int> auxNodes;
    auxNodes.resize(path->size());

    // compute new path
    for(int i = 0; i <= a; i++){
        auxNodes[i] = (*path)[i];
    }
    for(int i = 0; i < b - a; i++){
        auxNodes[a+i+1] = (*path)[b-i];
    }
    for(unsigned int i = b + 1; i < path->size(); i++){
        auxNodes[i] = (*path)[i];
    }

    // update path
    path->clear();
    for(unsigned int i = 0; i < auxNodes.size(); i++){
        path->push_back(auxNodes[i]);
    }
}

// Populates a given vector with a greedy SOP solution, given an arch weight matrix
int generateGreedyInstance(vector<vector<int> > weights, vector<int> *instance, int dimension){

//    pega menor da linha q n -1, que n usado e que n precedence
//    checa pra todos -1 da linha do escolhido se estão usados
//    se algum não, adiciona na lista de precedência e volta pra
//    procurar menor de novo
    instance->push_back(1);
    vector<int> precedence;
    int minWeight, cost = 0; //nextNode,
    int i = 0;
    //int currentNode = 0;
    int found, candidateNode, able;
    for(int k = 1; k < dimension-1; k++){
        minWeight = INFINITY;
        candidateNode = 0;
        found = 0;
        while(found == 0){
            for(int j = 1; j < dimension-1; j++){
                if(weights[i][j] != -1 && (checkNode(*instance, j+1) == false) && (checkNode(precedence, j+1) == false)){
                    if(weights[i][j] < minWeight){
                        minWeight = weights[i][j];
                        candidateNode = j + 1;
                        //cout << "\ncusto " << minWeight;
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
                //cout << "\nAble: " << candidateNode;;
                instance->push_back(candidateNode);
                found = 1;
                precedence.clear();
                i = candidateNode -1;
            }else{
                //cout << "\nUnable: " << candidateNode;;
                minWeight = INFINITY;
                precedence.push_back(candidateNode);
            }
        }
        cost += minWeight;
    }
    instance->push_back(dimension);

    return cost;
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
        return 0;
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
    for(unsigned int i = 0; i < weights.size(); i++) {

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
    vector<int> instancePath;
    vector<int> currentPath;
    int instanceCost = generateGreedyInstance(weights, &instancePath, dimension);
    int currentCost = instanceCost;
    currentPath = instancePath;
    unsigned int maxTabu = instancePath.size()/4;

    cout << "\n**Greedy Instance Generated**\n";

    cout << "Greedy First Instance:\n";
    for(unsigned int i = 0; i < instancePath.size(); i++) {
        cout << instancePath[i] << " ";
        }
    cout << "\nGreedy Instance Cost: " << instanceCost;

    //TABU SEARCH

    int whileControl = 0;

    tabuList.clear();
    while(whileControl != ITERATIONS){
        //maxSaving = -INFINITY;

        tabuTuple maxMove = twoOptSearch(weights, currentPath);
        if(maxMove.a == -1){
            break;
        }

        twoOptMove(&currentPath, maxMove.a, maxMove.b);
        currentCost = getCost(weights, currentPath);
        //currentCost = currentCost + maxSaving;

        insertTabu(maxMove);
        if(tabuList.size() == maxTabu)
            tabuList.erase(tabuList.begin());

        if(currentCost < instanceCost){
            instanceCost = currentCost;
            instancePath = currentPath;
            whileControl = 0;
        }
        else{
            whileControl += 1;
        }
    iterationCounter++;
    }
    cout << endl;
    printTabuList();
    cout << "\n\nStopped at iteration: " << iterationCounter;
    cout << "\nTS Best Found Instance: " << endl;
    printPath(instancePath);
    cout << "TS Best Instance Cost: " << instanceCost;

//    if(isValidPath(weights, path)){
//        cout <<  "\nGG Path";
//    }else{
//        cout << "\nNot GG Path";
//    }
//
//    static const int arr[] = {1,2,8,11,9,5,10,3,6,4,7,12,13,14};
//    //static const int arr[] = {1,2,8,11,9,5,10,3,6,4,7,12,14,13};
//    vector<int> test (arr, arr + sizeof(arr) / sizeof(arr[0]) );
//
//    if(isValidPath(weights, test)){
//        cout <<  "\nGG Path";
//    }else{
//        cout << "\nNot GG Path\n";
//    }

    return 0;
}


