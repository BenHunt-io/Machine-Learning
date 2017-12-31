#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void randomize(char **ptr, int swaps);
void writeToFile(char **ptr);

int main()
{
    cout << "Hello world!" << endl;

    ifstream fin;
    fin.open("train.dat");
    fin.ignore(255, '\n');

    //https://stackoverflow.com/questions/18273370/the-correct-way-to-initialize-a-dynamic-pointer-to-a-multidimensional-array
    char **ptr;
    ptr = new char*[2000];
    for(int i = 0; i<2000; i++){
        ptr[i] = new char[7000];
    }
    string yo = "yo";
    cout << yo[0];
    for(int i = 0; i<2000; i++){
        fin.getline(ptr[i],7000, '\n');
    }

    randomize(ptr,10000);
    writeToFile(ptr);


    return 0;

}


void randomize(char **ptr, int swaps){

    char *temp;
    int randNum1, randNum2;
    srand(time(NULL));
    for(int i = 0; i<swaps; i++){
        randNum1 = rand() % 1000; // 0-999
        randNum2 = rand() % 1000;
        temp = ptr[randNum1];
        ptr[randNum1] = ptr[randNum2];
        ptr[randNum2] = temp;
    }

    for(int i = 0; i<swaps; i++){
        randNum1 = rand() % 1000 + 1000; // 1000-1999
        randNum2 = rand() % 1000 + 1000;
        temp = ptr[randNum1];
        ptr[randNum1] = ptr[randNum2];
        ptr[randNum2] = temp;
    }

}

void writeToFile(char **ptr){

    ofstream fout;
    fout.open("data.dat");


    ofstream foutSplitter[10];

    foutSplitter[0].open("test1.dat");
    foutSplitter[1].open("test2.dat");
    foutSplitter[2].open("test3.dat");
    foutSplitter[3].open("test4.dat");
    foutSplitter[4].open("test5.dat");
    foutSplitter[5].open("not1.dat");
    foutSplitter[6].open("not2.dat");
    foutSplitter[7].open("not3.dat");
    foutSplitter[8].open("not4.dat");
    foutSplitter[9].open("not5.dat");


    for(int i = 0; i<2000; i++){
        fout << ptr[i] << endl;
    }

    // Separate
    for(int i = 0; i<2000; i++){
        if(i%5 == 0){
            foutSplitter[0] << ptr[i] << endl;
            foutSplitter[6] << ptr[i] << endl;
            foutSplitter[7] << ptr[i] << endl;
            foutSplitter[8] << ptr[i] << endl;
            foutSplitter[9] << ptr[i] << endl;
        }
        if(i%5 == 1){
            foutSplitter[1] << ptr[i] << endl;
            foutSplitter[5] << ptr[i] << endl;
            foutSplitter[7] << ptr[i] << endl;
            foutSplitter[8] << ptr[i] << endl;
            foutSplitter[9] << ptr[i] << endl;
        }
        if(i%5 == 2){
            foutSplitter[2] << ptr[i] << endl;
            foutSplitter[5] << ptr[i] << endl;
            foutSplitter[6] << ptr[i] << endl;
            foutSplitter[8] << ptr[i] << endl;
            foutSplitter[9] << ptr[i] << endl;
        }
        if(i%5 == 3){
            foutSplitter[3] << ptr[i] << endl;
            foutSplitter[5] << ptr[i] << endl;
            foutSplitter[6] << ptr[i] << endl;
            foutSplitter[7] << ptr[i] << endl;
            foutSplitter[9] << ptr[i] << endl;
        }
        if(i%5 == 4){
            foutSplitter[4] << ptr[i] << endl;
            foutSplitter[5] << ptr[i] << endl;
            foutSplitter[6] << ptr[i] << endl;
            foutSplitter[7] << ptr[i] << endl;
            foutSplitter[8] << ptr[i] << endl;
        }
    }

}
