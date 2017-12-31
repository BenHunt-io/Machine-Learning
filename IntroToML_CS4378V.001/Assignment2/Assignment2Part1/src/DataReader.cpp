#include <iostream>
#include <fstream>
#include <DataReader.h>
using namespace std;


DataReader::DataReader()
{
    //ctor
}

DataReader::~DataReader()
{
    //dtor
}


void DataReader::read(Plant plantData[]){
    ifstream fin;
    fin.open("iris.txt");
    string line;
    string delimiterComma = ",";
    string delimiterPeriod = ".";
    int a = 5;
    int b = 6;
    int i = 0;
    while(fin >> line){
//        cout << line << endl;
        while(!line.empty()){
            if((line.at(0)) <= 57){ // It's not a number, should be a character (beginning of name()
                string subString = line.substr(0, line.find(delimiterComma));
                plantData[i].sepalLength = (double(((int)*subString.substr(0,line.find(delimiterPeriod)).c_str() + 2) % 10)) +
                                (double(((int)*subString.substr(line.find(delimiterPeriod) + 1 ,line.find(delimiterPeriod)+ 2).c_str() + 2) % 10)) / 10;
//                cout << plantData[i].sepalLength << endl;
                line.erase(0, line.find(delimiterComma)+1);

                subString = line.substr(0, line.find(delimiterComma));
                plantData[i].sepalWidth = (double(((int)*subString.substr(0,line.find(delimiterPeriod)).c_str() + 2) % 10)) +
                                (double(((int)*subString.substr(line.find(delimiterPeriod) + 1 ,line.find(delimiterPeriod)+ 2).c_str() + 2) % 10)) / 10;
//                cout << plantData[i].sepalWidth << endl;
                line.erase(0, line.find(delimiterComma)+1);

                subString = line.substr(0, line.find(delimiterComma));
                plantData[i].petalLength = (double(((int)*subString.substr(0,line.find(delimiterPeriod)).c_str() + 2) % 10)) +
                                (double(((int)*subString.substr(line.find(delimiterPeriod) + 1 ,line.find(delimiterPeriod)+ 2).c_str() + 2) % 10)) / 10;
//                cout << plantData[i].petalLength << endl;
                line.erase(0, line.find(delimiterComma)+1);

                subString = line.substr(0, line.find(delimiterComma));
                plantData[i].petalWidth = (double(((int)*subString.substr(0,line.find(delimiterPeriod)).c_str() + 2) % 10)) +
                                (double(((int)*subString.substr(line.find(delimiterPeriod) + 1 ,line.find(delimiterPeriod)+ 2).c_str() + 2) % 10)) / 10;
//                cout << plantData[i].petalWidth << endl;
                line.erase(0, line.find(delimiterComma)+1);
            }
            else{ // TODO change to be able to work with any format.
                plantData[i].classifcation  = line;
//                cout << plantData[i].classifcation << endl;
                break; // go to next line
            }
        }


//        cout << endl << endl;
        i++;
    }

}
