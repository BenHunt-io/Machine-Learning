#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

struct Point{
    double x = 0;
    double y = 0;
};

struct MergedCluster{
    int cluster1;
    int cluster2;
};

struct ClusterContents{

    vector<Point> cluster;

};

int menu();
void initDisplay();
void displayActiveClusters();
void displayActiveClusters();
void displaySimilarityMatrix();
void displayClusterContents();
void init();
void initSet(int index, double x, double y);
double sim(Point firstPt, Point secondPt); // finds similarity between 2 points
double simSL(int i, int m, int j);
double simCL(int i, int m, int j);
double simCen(int i, int m, int j);
MergedCluster argMax();
void run();
void sl();
void cen();
void cl();

const int SIZE = 12;
Point S[SIZE];
double similarity[SIZE][SIZE]; // Holds all the distances between sample points and each cluster.
ClusterContents clusterContents[SIZE];
MergedCluster clusterHistory[SIZE];
int activeClusters[SIZE];

int main()
{

    init();
    initDisplay();
    run();

}


void init(){

    initSet(0,2,2);
    initSet(1,3.01,2);
    initSet(2,4.02,2);
    initSet(3,5.03,2);
    initSet(4,6.04,2);
    initSet(5,7.05,2);
    initSet(6,2,3.5);
    initSet(7,3.01,3.5);
    initSet(8,4.02,3.5);
    initSet(9, 5.03,3.5);
    initSet(10,6.04,3.5);
    initSet(11,7.05,3.5);


    for(int i = 0; i<SIZE; i++){
        clusterContents[i].cluster.push_back(S[i]);
        for(int j = 0; j<SIZE; j++){
            similarity[i][j] = sim(S[i], S[j]);
        }
        activeClusters[i] = 1;
    }

}


void run(){

    double similarityResult;
    int choice;
    choice = menu();
    for(int i = 0; i<SIZE-1; i++){

        clusterHistory[i] = argMax(); // append cluster history, argmax returns index of two most similar clusters

        //Update clusterContents, Update cluster contents right after argmax. Because you are going to add up the contents to calculate
        // the centroid in the cen function
        // You do this so that I has both I and M points in it before you add them up.'
        //
        int size = clusterContents[clusterHistory[i].cluster2].cluster.size();
        for(int f = 0; f<size; f++){
            clusterContents[clusterHistory[i].cluster1].cluster.push_back(clusterContents[clusterHistory[i].cluster2].cluster.at(f));
            // 2 clusters are getting merged. i and m. I'm adding the points from m into i before I call the cen functiont I
            // don't use m in the cen function.
            // i and m are coming from the most recent cluster history (argmax)
            // clusterHistory is not the same. Cluster contents holds the
        }


        // You merge i and m, so what you are trying to return is the distance from the centroid of those two clusters and j.
        // i now has all the points of both i and m, because you did that clusterContents update before centroid.
        for(int j = 0; j < SIZE; j++){


            if(clusterHistory[i].cluster1 != j && clusterHistory[i].cluster2 != j){
                switch(choice){
                    case 1: similarityResult = simSL(clusterHistory[i].cluster1,clusterHistory[i].cluster2,j);
                        break;
                    case 2: similarityResult = simCL(clusterHistory[i].cluster1,clusterHistory[i].cluster2,j);
                        break;
                    case 3: similarityResult = simCen(clusterHistory[i].cluster1,clusterHistory[i].cluster2,j);
                        break;
                }
                similarity[clusterHistory[i].cluster1][j] = similarityResult;
                similarity[j][clusterHistory[i].cluster1] = similarityResult;
            }
        }

        activeClusters[clusterHistory[i].cluster2] = 0;
        displayClusterContents();
        displayActiveClusters();
        displaySimilarityMatrix();


    }

    cout << "Cluster History: " << endl;
    for(int i = 0; i<SIZE-1; i++){
        cout <<clusterHistory[i].cluster1 <<"->" << clusterHistory[i].cluster2 << " ";
    }
    cout << endl << endl;




}


double simSL(int i, int m, int j){

    if(similarity[m][j] < similarity[i][j]){
        return similarity[m][j];
    }
    return similarity[i][j];
}

double simCL(int i, int m, int j){

    if(similarity[m][j] > similarity[i][j]){
        return similarity[m][j];
    }
    return similarity[i][j];
}

// The index of the recently merged active cluster is index i that is passed in.
// With that index and the contents of that cluster in the clusterContents array the function
// will calculate the new centroid and then calculate the similarity of that centroid to the rest.
// But it will do it one at a time, via the j index that is passed in.
double simCen(int i, int m, int j){

    // Only need i and j, because i has the newly merged cluster and it's point contents. Because I updated the clusterContents right after
    // argmax. I sum all the points in the newly merged cluster and then sum up all the points in the cluster I'm basically comparing it to.
    //  Cluster i has cluster m inside of it.
    Point iPoint;
    Point jPoint;

    for(int k = 0; k<clusterContents[i].cluster.size(); k++){
        iPoint.x += clusterContents[i].cluster.at(k).x;
        iPoint.y += clusterContents[i].cluster.at(k).y;
    }

    for(int k = 0; k<clusterContents[j].cluster.size(); k++){
        jPoint.x += clusterContents[j].cluster.at(k).x;
        jPoint.y += clusterContents[j].cluster.at(k).y;
    }

    iPoint.x = iPoint.x / (clusterContents[i].cluster.size());
    iPoint.y = iPoint.y / (clusterContents[i].cluster.size());

    jPoint.x = jPoint.x / clusterContents[j].cluster.size();
    jPoint.y = jPoint.y / clusterContents[j].cluster.size();

    return sim(iPoint,jPoint);

}



void initSet(int index, double x, double y){

        S[index].x = x;
        S[index].y = y;
}


// Returns the most similar 2 clusters as a MergedCluster
MergedCluster argMax(){

    MergedCluster mergedCluster;

    double mostSimilar = 10000;
    int cluster1; // index of 1 of the 2 clusters with the most similarity
    int cluster2; // index of 1 of the 2 clusters with the most similarity
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(mostSimilar > similarity[i][j] && activeClusters[i] && activeClusters[j] &&
               similarity[i][j] != 0){
                cout << "   Found min: " << similarity[i][j] << " "<<  i << " " << j <<" " << mostSimilar;
                mostSimilar = similarity[i][j];
                mergedCluster.cluster1 = i;
                mergedCluster.cluster2 = j;
            }
        }
    }
    cout << endl;

    cout << endl << "Merged Cluster: (" << mergedCluster.cluster1 << "," << mergedCluster.cluster2
        << ") with a similarity(distance) of: " << similarity[mergedCluster.cluster1][mergedCluster.cluster2] <<  endl;
    return mergedCluster;
}


double sim(Point firstPt, Point secondPt){

    return sqrt(pow((secondPt.x - firstPt.x),2) + pow((secondPt.y - firstPt.y),2));
}

void displayActiveClusters(){

    cout << "Active clusters: ";
    for(int i = 0; i<SIZE; i++){
        cout << activeClusters[i] << " ";
    }
    cout << endl;

}

void displaySimilarityMatrix(){

    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            cout << fixed << setprecision(2) << "  " << similarity[i][j];
        }
    cout << endl;
    }
    cout << endl << endl;

}

void displayClusterContents(){

    for(int m = 0; m<SIZE; m++){
        if(activeClusters[m]){
            cout << "Cluster " << m << ": ";
            for(int k = 0; k<clusterContents[m].cluster.size(); k++){
                cout << "(" << clusterContents[m].cluster.at(k).x << "," <<  clusterContents[m].cluster.at(k).y << ")";
                if((k+1)<clusterContents[m].cluster.size())
                    cout << " , ";
            }
            cout << endl;
        }
    }

}


int menu(){

    int choice;
    cout << "Choose a HAC clustering algorithm: " << endl;
    cout << "1: Single Linkage" << endl;
    cout << "2: Complete Linkage" << endl;
    cout << "3: Centroid Linkage" << endl;
    cout << "Choice: ";
    cin >> choice;
    return choice;



}

void initDisplay(){
    cout << "Data Set: " << endl;
    for(int i = 0; i<SIZE; i++){
        cout << i << ": " << S[i].x << " " << S[i].y << " " << endl;
    }
    cout << endl;
    cout << "Initial similarity cluster: " << endl;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            cout << fixed << setprecision(2) << fixed << setw(5) <<  similarity[i][j];
        }
        cout << endl;
    }

    cout << endl;
    displayClusterContents();
    cout << endl;
    displayActiveClusters();
    cout << endl;

    cout << "------------------ Starting HAC Algorithm -----------------------" << endl;
}

/////////////////////////////////// Revelations ///////////////////////////////////////
 // i/j in the sim 2d array was not suppose to be the for loop counters
// They should be clusterHistory.[i].cluster 1 (and 2). That correlates to the rows being updated. I was
// updatng the wrong rows and columns in the sim matrix
// because the sim function is sim(i,m,j) I was getting that mixed up with my loop. Because my loop is i and j
// On the notes the loops are like k and p or something, so i and j don't get mixed up


