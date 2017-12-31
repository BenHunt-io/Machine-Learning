 #include <iostream>
 #include <vector>
 #include <cstdlib>
 #include <ctime>
 #include <exception>
 #include <iomanip>
 #include <cmath>
 #include <time.h>
 using namespace std;

 // Composite Datatype to hold x,y values of the data points
 struct Point{
     string name = "";
     double x;
     double y;
 };


 void generateRandomClustersInSet();
 void generateRandomClusters();
 void runRounds();
 int init();
 void initSet(int index, double x, double y);
 Point argMin(int samplePoint);
 double sim(Point dataSetPoint, Point clusterPoint);
 void recalcClusters();
 void run();
 void reassignToClusters();
 void outputResult();
 void runRounds();


 const int SIZE = 8;
 vector<Point> S (SIZE); // set of data samples
 vector<Point> S2 (SIZE);
 vector<Point> C; // c[k] be the vectors for cluster centers;
 vector<Point> A; // set of associate clusters for each data sample
 int k = 0; // number of clusters


 int main()
 {

     srand(time(NULL));

     init();

     return 0;
 }



 int init(){

     initSet(0,2,10);
     initSet(1,2,5);
     initSet(2,8,4);
     initSet(3,5,8);
     initSet(4,7,5);
     initSet(5,6,4);
     initSet(6,1,2);
     initSet(7,4,9);

     S2 = S; // Let S' = S;

     // Print out set
     cout << "Initial Set:" << endl;
     for(int i = 0; i<S.size(); i++){
     cout << S.at(i).x << " " << S.at(i).y << endl;
     }
     cout << endl;


     cout << "Choose starting # of clusters: ";
     cin >> k;
     int choice;
     cout << "Menu: " << endl;
     cout << "1: Generate random cluster centers from within set" << endl;
     cout << "2: Generate random cluster centers with a max of either 10 or 15" << endl;
     cout << "3: Pick from the set" << endl;
     cout << "Enter choice: ";
     cin >> choice;

     switch(choice){

        case 1: generateRandomClustersInSet();
            break;
        case 2: generateRandomClusters();
            break;
        case 3: runRounds();
            break;

     }


     // Print out initial cluster points
     cout << "Initial cluster points:" << endl;
     for(int i = 0; i<k; i++){
        cout << C.at(i).x << " " << C.at(i).y << endl;
     }
     cout << endl;


     for(int i = 0; i<S.size(); i++){
        A.push_back(argMin(i));
     }

     // Print out initial data point cluster assignments
 //     for(int i = 0; i<A.size(); i++){
 //         cout << i << " - " << A.at(i).x <<" " << A.at(i).y << endl;
 //     }

     run(); // recalculates centroids and reassigns datapoints to clusters

     // print out final clustering assignments
     cout << endl;
     cout << "Final clustering assignments: " << endl;
     for(int i = 0; i<A.size(); i++){
        cout << i << " - " << A.at(i).x <<" " << A.at(i).y << endl;
     }

     cout << endl << "Final clustering mean values: " << endl;
     for(int i = 0; i<k; i++){
        cout << fixed << setprecision(2) << C.at(i).x << " " << C.at(i).y << endl;
     }

     outputResult();

 }

 // Initializes the set of data samples
 void initSet(int index, double x, double y){

     S.at(index).x = x;
     S.at(index).y = y;
 }

 // finds the best/closest cluster for a sample/data point
 Point argMin(int dataIndex){

     double mostSimilar = sim(S.at(dataIndex), C.at(0)); // should have smallest value
     double simValue;
     int mostSimilarIndex = 0;
     for(int j = 0; j<k; j++){
         simValue = sim(S.at(dataIndex), C.at(j));
         if(simValue < mostSimilar){
             mostSimilar = simValue;
             mostSimilarIndex = j;
         }
     }

     //cout << "X:" << C.at(mostSimilarIndex).x << " Y:" << C.at(mostSimilarIndex).y << endl;
     return C.at(mostSimilarIndex); // returns the cluster(point) that is the most similar

 }

 // Calculates simularity
 double sim(Point dataSetPoint, Point clusterPoint){

     // return abs(clusterPoint.x - dataSetPoint.x) + abs(clusterPoint.y - dataSetPoint.y);
     return sqrt(pow((clusterPoint.x - dataSetPoint.x), 2)+ pow((clusterPoint.y - dataSetPoint.y),2));
 }


 void run(){

     reassignToClusters();

 }

 void recalcCentroids(){

     for(int i = 0; i<k; i++){
         double meanX = 0, meanY = 0, count = 0;
         for(int j = 0; j<S.size(); j++){
            if(A.at(j).x == C.at(i).x && A.at(j).y == C.at(i).y){
    //          cout << "Match at: " << j << "X: " << S.at(i).x << " Y: " << S.at(i).(y)<< endl;
                 meanX += S.at(j).x;
                 meanY += S.at(j).y;
                 count++;
            }
        }
         // Have to make sure that the centroid needs to be recalculated for the cluster
         if(count > 0){
             //cout << "count > 0: " << i << " " << meanX/count << " " << meanY/count << endl;
             C.at(i).x = meanX/count;
             C.at(i).y = meanY/count;
             C.at(i).name = "Cluster " + i;
          }
    }

 }


 void reassignToClusters(){
     Point a;
     bool change = true;

     recalcCentroids();

     while(change){

         change = false;
         for(int i = 0; i<S.size(); i++){
             a = argMin(i);
             if(a.x != A.at(i).x || a.y != A.at(i).y){
                 A[i].x = a.x;
                 A[i].y = a.y;
                 change = true;
              }
         }
         if(change){
            recalcCentroids();
         }
     }
 }

 void outputResult(){

     cout << "Final Clustering Results: " << endl;
     for(int i = 0; i<k; i++){
         cout << "Cluster " << i << ": {";
         for(int j = 0; j<S.size(); j++){
             if(A.at(j).x == C.at(i).x && A.at(j).y == C.at(i).y){
                cout << "A" <<j<< ",";
             }
         }
         cout << "}" << endl;
     }

 }

 void runRounds(){

     int cluster1, cluster2, cluster3;
     cout << "Cluster 1: ";
     cin >> cluster1;
     cout << "Cluster 2: ";
     cin >> cluster2;
     cout << "Cluster 3: ";
     cin >> cluster3;
     C.push_back(S2.at(cluster1));
     C.push_back(S2.at(cluster2));
     C.push_back(S2.at(cluster3));


 }


 void generateRandomClustersInSet(){

     int j;
     for(int i = 0; i<k; i++){
         j = rand() % S2.size();
         C.push_back(S2.at(j));
         S2.erase(S2.begin() + j);
     }
     cout << endl;


 }

 void generateRandomClusters(){

     int choice;
     cout << "Choose a max:" << endl;
     cout << "1: Max Point is (10,10)" << endl;
     cout << "2: Max Point is (15,15)" << endl;
     cout << "Choice: ";
     cin >> choice;

     Point newPoint;

     switch(choice){

         case 1:
            for (int i = 0; i<k; i++){
                 newPoint.x = rand() % 10;
                 newPoint.y = rand() % 10;
                 C.push_back(newPoint);
            }
            break;
         case 2:
             for (int i = 0; i<k; i++){
                 newPoint.x = rand() % 15;
                 newPoint.y = rand() % 15;
                 C.push_back(newPoint);
            }
            break;
        }



    }




