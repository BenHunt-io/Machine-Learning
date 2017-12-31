#include <iostream>
#include <DataReader.h>
#include <cmath>
#include <math.h>
#include <iomanip>
using namespace std;

#include <Plant.h>

const int SIZE = 147;

void normalize(Plant[], Plant[]);
double sim(Plant, Plant); // compare plant similarity
void fillSimMatrix();
void findNearestNeighbors(int k);
void initTestMatrix(int i, double a, double b, double c, double d);
void swapValues(int valToRemove, int newVal, int minIndicies[][SIZE]);
void bubbleSort(double minValues[][SIZE], int minIndicies[][SIZE], int i, int k);
void output(int minIndicies[][SIZE], int k);
const int TEST_SIZE = 3;
Plant pData[SIZE];
double simData[SIZE][SIZE];
Plant testData[TEST_SIZE];

int main()
{
    int k; // neighbors
    DataReader::read(pData); // read data into pData
    initTestMatrix(0, 4.9 ,3.0 ,1.4 ,0.2);
    initTestMatrix(1,4.9,2.4,3.3,1.0);
    initTestMatrix(2,4.9,2.5,4.5,1.7);
    normalize(pData,testData);
//    fillSimMatrix();

    k = 3; // Nearest Neighbors
    findNearestNeighbors(k);
    return 0;
}


void normalize(Plant pData[], Plant testData[]){

    double sepalLengthMax = 7.9;
    double sepalLengthMin = 4.3;
    double sepalWidthMax = 4.4;
    double sepalWidthMin = 2.0;
    double petalLengthMax = 6.9;
    double petalLengthMin = 1.0;
    double petalWidthMax = 2.5;
    double petalWidthMin = 0.1;


    for(int i = 0; i<SIZE; i++){
        pData[i].sepalLength = (pData[i].sepalLength - sepalLengthMin) / (sepalLengthMax - sepalLengthMin);
//        cout << pData[i].sepalLength << endl;
        pData[i].sepalWidth = (pData[i].sepalWidth - sepalWidthMin) / (sepalWidthMax - sepalWidthMin);
//        cout << pData[i].sepalWidth << endl;
        pData[i].petalLength = (pData[i].petalLength - petalLengthMin) / (petalLengthMax - petalLengthMin);
//        cout << pData[i].petalLength << endl;
        pData[i].petalWidth = (pData[i].petalWidth - petalWidthMin) / (petalWidthMax - petalWidthMin);
//        cout << pData[i].petalWidth << endl;
//        cout << endl;
    }

    for(int i = 0; i<TEST_SIZE; i++){
        testData[i].sepalLength = (testData[i].sepalLength - sepalLengthMin) / (sepalLengthMax - sepalLengthMin);
//        cout << testData[i].sepalLength << endl;
        testData[i].sepalWidth = (testData[i].sepalWidth - sepalWidthMin) / (sepalWidthMax - sepalWidthMin);
//        cout << testData[i].sepalWidth << endl;
        testData[i].petalLength = (testData[i].petalLength - petalLengthMin) / (petalLengthMax - petalLengthMin);
//        cout << testData[i].petalLength << endl;
        testData[i].petalWidth = (testData[i].petalWidth - petalWidthMin) / (petalWidthMax - petalWidthMin);
//        cout << testData[i].petalWidth << endl;
//        cout << endl;
    }
}

// using euclidian distance
double sim(Plant plantA, Plant plantB){
    return sqrt( pow((plantB.sepalLength - plantA.sepalLength),2) +
                    pow((plantB.sepalWidth - plantA.sepalWidth),2) +
                    pow((plantB.petalLength - plantA.petalLength),2) +
                    pow((plantB.petalWidth - plantA.petalWidth),2));
}
//
//void fillSimMatrix(){
//
//    for(int i = 0; i<SIZE; i++){
//        for(int j = 0; j<SIZE; j++){
//            simData[i][j] = sim(pData[i], pData[j]);
//        }
//    }
//}

void initTestMatrix(int i, double a, double b, double c, double d){

    testData[i].classifcation = "";
    testData[i].sepalLength = a;
    testData[i].sepalWidth = b;
    testData[i].petalLength = c;
    testData[i].petalWidth = d;
}

void findNearestNeighbors(int k){

    double minValues[TEST_SIZE][SIZE];
    int minIndicies[TEST_SIZE][SIZE];

    for(int i = 0; i<TEST_SIZE; i++){
        for(int j = 0; j<k; j++){
            minValues[i][j] = 10000;
            minIndicies[i][j] = -1;
        }
    }

    for(int i = 0; i<TEST_SIZE; i++){
        for(int j = 0; j<k; j++){
            for(int m = 0; m<SIZE-1; m++){
                if(sim(pData[m], testData[i]) < minValues[i][k-1]){
                    minValues[i][k-1] = sim(pData[m], testData[j]);
                    minIndicies[i][k-1] = m;
                    bubbleSort(minValues, minIndicies, i, k);
                }
            }
        }
    }


    output(minIndicies,k);
}


void bubbleSort(double minValues[][SIZE], int minIndicies[][SIZE], int testDataIndex, int k){

    bool swap = true;
    while(swap){
        for(int i = 0; i<k-1; i++){
            swap = false;
            // Sort minValues matrix in ascending order. Sort minIndices based on how minValues is sorted.
            if(minValues[testDataIndex][i] > minValues[testDataIndex][i+1]){
                    double temp = minValues[testDataIndex][i+1];
                    minValues[testDataIndex][i+1] = minValues[testDataIndex][i];
                    minValues[testDataIndex][i] = temp;

                    int tempInt = minIndicies[testDataIndex][i+1];
                    minIndicies[testDataIndex][i+1] = minIndicies[testDataIndex][i];
                    minIndicies[testDataIndex][i] = tempInt;

                    swap = true;
            }
        }
    }
}

void output(int minIndicies[][SIZE], int k){

    cout << endl << endl << "---- RESULTS ----" << endl << endl;
    for(int i = 0; i < TEST_SIZE; i++){
            cout << "Test Data " << i << ":" << endl;
            cout << testData[i].classifcation << endl;
            cout << testData[i].petalLength << endl;
            cout << testData[i].petalWidth << endl;
            cout << testData[i].sepalLength << endl;
            cout << testData[i].sepalWidth << endl;
            cout << "-------------------------" << endl;

        for(int j = 0; j<k; j++){
            cout << pData[minIndicies[i][j]].classifcation << endl;
            cout << pData[minIndicies[i][j]].petalLength << endl;
            cout << pData[minIndicies[i][j]].petalWidth << endl;
            cout << pData[minIndicies[i][j]].sepalLength << endl;
            cout << pData[minIndicies[i][j]].sepalWidth << endl;
        }
        cout << "-----------------------------" << endl;
        cout << endl;
    }

}

