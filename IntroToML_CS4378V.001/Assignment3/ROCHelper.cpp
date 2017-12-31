#include <iostream>
#include <fstream>


using namespace std;
void getTpFnFpTn(double *tp, double *fn, double *fp, double *tn, int index, string fileName);

int main()

{

    double *tp = new double[18];
    double *fn = new double[18];
    double *fp = new double[18];
    double *tn = new double[18];

    for(int i = 0; i<18; i++){
        tp[i] = 0;
        fn[i] = 0;
        fp[i] = 0;
        tn[i] = 0;
    }


    getTpFnFpTn(tp,fn,fp,tn,0,"../prediction.1");
    getTpFnFpTn(tp,fn,fp,tn,1,"../prediction.3");
    getTpFnFpTn(tp,fn,fp,tn,2,"../prediction.5");
    getTpFnFpTn(tp,fn,fp,tn,3,"../prediction.7");
    getTpFnFpTn(tp,fn,fp,tn,4,"../prediction.9");
    getTpFnFpTn(tp,fn,fp,tn,5,"../prediction1.0");
    getTpFnFpTn(tp,fn,fp,tn,6,"../prediction2.0");
    getTpFnFpTn(tp,fn,fp,tn,7,"../prediction3.0");
    getTpFnFpTn(tp,fn,fp,tn,8,"../prediction4.0");
    getTpFnFpTn(tp,fn,fp,tn,9,"../prediction5.0");
    getTpFnFpTn(tp,fn,fp,tn,10,"../prediction6.0");
    getTpFnFpTn(tp,fn,fp,tn,11,"../prediction7.0");
    getTpFnFpTn(tp,fn,fp,tn,12,"../prediction8.0");
    getTpFnFpTn(tp,fn,fp,tn,13,"../prediction9.0");
    getTpFnFpTn(tp,fn,fp,tn,14,"../prediction10.0");
    getTpFnFpTn(tp,fn,fp,tn,15,"../prediction20.0");
    getTpFnFpTn(tp,fn,fp,tn,16,"../prediction30.0");
    getTpFnFpTn(tp,fn,fp,tn,17,"../prediction40.0");

    for(int i = 0; i<18; i++){
        cout << tp[i] << " " << fn[i] << " " << fp[i] << " " << tn[i] << endl;
    }

    for(int i = 0; i<18; i++){
        cout << "True Positive Rate: " << tp[i]/(tp[i] + fn[i]) << " False Positive rate: " << fp[i]/(fp[i]+tn[i]) << endl;
    }


    return 0;
}

void getTpFnFpTn(double *tp, double *fn, double *fp, double *tn, int index, string fileName){
    ifstream fin;
    fin.open(fileName.c_str());

    char neg;
    string line;
    fin >> neg;
    for(int i = 0; i<300; i++){
        fin >> neg;
        fin >> line;
        if(neg == '-')
            fn[index]++;
        else
            tp[index]++;

         // The
    }

    for(int i = 300; i<600; i++){
        fin >> neg;
        fin >> line;
        if(neg == '-')
            tn[index]++;
        else
            fp[index]++;


    }

}

void getFn(int *fn, string fileName){


}
void getFp(int *fp, string fileName){


}
void getTn(int *tn, string fileName){


}

