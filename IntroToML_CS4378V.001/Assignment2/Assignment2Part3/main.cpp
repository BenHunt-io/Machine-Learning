#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "CarData.h"

using namespace std;

void output();
void readInData();
void normalize();
void updateTheta();
double gradientDescent(int index);
double hypothesis(int index);
double predictHypothesis(int index);
double predictTestHypothesis();
void predictValues();
void hardCode();

const int ITERATIONS = 100000;
const double lRate = .001; // Learning Rate
const int n = 5; // Number of feature
const int m = 398; // Number of examples
double features[m][n+1]; // Matrix of features (has y or the target inside)
double Y[m]; // The expected values
double theta[n+1]; // The weights/parameters
const int Y_PREDICT_SIZE = 3;
double YPredict[Y_PREDICT_SIZE];
double testFeatures[Y_PREDICT_SIZE][n+1];
double test[n+1] = {8,307,130,3504,12,1};



double sum;
int runs = 0;
bool significantUpdate = true;


// Predict value is off. Last thing was normalizing the predict (other set) set.
//
int main()
{

    // Initialize Theta
    theta[0] = .1;
    theta[1] = .1;
    theta[2] = .1;
    theta[3] = .1;
    theta[4] = .1;
    theta[5] = .1;



    readInData();
    normalize();
    //output();
    cout << "-Running algorithm-" << endl;
    updateTheta(); // core of the algorithm
    predictValues();

    return 0;

}

void readInData(){

    ifstream fin;
    fin.open("linear_regression_data-1.txt");

    char cm; //read in character
    for(int i = 0; i<m+Y_PREDICT_SIZE; i++){
        for(int j = 0; j<n+1; j++){
            if(j == 0 && i<m){
                fin >> Y[i];
            }
            else if(i>=m){
                if(j==0)
                    fin >> cm;
                else
                    fin >> testFeatures[i-m][j-1];
            }
            else{
                fin >> features[i][j-1];
            }

        }
    }

    for(int i = 0; i<m; i++){
        features[i][n] = 1;
    }
    for(int i = 0; i<Y_PREDICT_SIZE; i++){
        testFeatures[i][n] = 1;
    }



}


void normalize(){

    double max[5];
    double min[5];

    for(int i = 0; i<n; i++){
            max[i] = 0, min[i] = 2147483647;
        for(int j = 0; j<m; j++){
            if(features[j][i] < min[i]){
                min[i] = features[j][i];
            }
            if(features[j][i] > max[i]){
                max[i] = features[j][i];
            }
        }

    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m+Y_PREDICT_SIZE; j++){
            if(j<m){
                features[j][i] = (features[j][i] - min[i]) / (max[i] - min[i]);
            }
            else
                testFeatures[j-m][i] = (testFeatures[j-m][i] - min[i]) / (max[i] - min[i]);
        }


    }

    // For testing to see if my predictions are accurate against known results
    for(int i = 0; i<n; i++){
        test[i] = (test[i] - min[i]) / (max[i] - min[i]);
    }

}

void output(){

    for(int i = 0; i<m; i++){
        cout << i << " ";
        for(int j = 0; j<n+1; j++){
            if(j == 0)
                cout << Y[i] << " ";
                cout << features[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
    for(int i = 0; i<Y_PREDICT_SIZE; i++){
            for(int j = 0; j < n; j++){
               cout << testFeatures[i][j] << " ";
            }
            cout << endl;

    }

}

void predictValues(){

    cout << "Predicted MPG's: " << endl;
    for(int i = 0; i<Y_PREDICT_SIZE; i++){
        cout << i << ": " << predictHypothesis(i) << endl;
    }
    cout << "\nLearned linear function: " << theta[n] << fixed << setprecision(2) << " + " << theta[0] << "*Cylinders + \n"
            << theta[1] << "*Displacement + " << theta[2] << "*Horsepower + " << theta[3] << "*Weight + "
            << theta[4] << "*Acceleration";
    cout << endl;

//    for(int i = 0; i<n+1 ;i++){
//        cout << theta[i] << " ";
//    }

    cout << "Predicted value from the training set 1/398: " << predictTestHypothesis() << endl;
    cout << "Iterations Ran: " + ITERATIONS;


}

void updateTheta(){

    int myCount = 0;
    do{
        // update each theta value
        for(int i = 0; i<n+1; i++){
           theta[i] = gradientDescent(i);
        }

        myCount++;
    }while(myCount < ITERATIONS);

    cout << endl;

}


// index is basically j
double gradientDescent(int index){

    // The other loop I have a it go to size
    double change = 0;
    sum = 0;


    // m - 378 , n = 4
    for(int i = 0; i<m; i++){
        sum += (hypothesis(i) - Y[i])*features[i][index];
    }


    sum = sum/m; // get average


    return theta[index] - lRate*sum;

}

// index is what you would normally think of as i
double hypothesis(int index){

    double prediction = 0;
    for(int i = 0; i<n+1; i++){
        prediction += theta[i]*features[index][i];
    }

    return prediction;
}


double predictHypothesis(int index){

    double prediction = 0;
    for(int i = 0; i < n+1; i++){
        prediction += theta[i]*testFeatures[index][i];
    }

    return prediction;
}

double predictTestHypothesis(){

    double prediction = 0;
    for(int i = 0; i < n+1; i++){
        prediction += theta[i]*test[i];
    }

    return prediction;
}

