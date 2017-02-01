#ifndef POINTS
#define POINTS

#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
#include <cmath>
#include <math.h>
#include <list>
#include <iostream>
#include <utility>
#include <iostream>
#include <iomanip>

using namespace std;

class Points{
public:
    /*Points();*/
    void insert();
    float distance(pair<int,int> a, pair<int,int> b);
    void findShortestPath();

private:
    int startSize = 20;
    int numOfItems = 0;
    float leastDistance = 1;
    int middleLoc = 0;
    vector<pair<int,int>> myVec;
    vector<pair<int,int>> closePoints;

};


/**
 * @brief Points::insert Retrieves points from a file and adds the pairs to an myVec
 */
void Points::insert(){
    int x = 0, y = 0;

    ifstream input("example.txt");

    pair<int,int> p;

    //reads in data, creates points, and adds to an array
    while(!input.eof()){
        input >> x >> y;
        p = make_pair(x, y);

        // add the pair to the vector
        myVec.push_back(p);
        numOfItems++;
    }
}

/**
 * @brief Points::distance  Find the distance between two points using Distance Formula
 * @param a The first point
 * @param b The second point
 * @return The distance between the points
 */
float Points::distance(pair<int,int> a, pair<int,int> b){
    float x = 0, y = 0, dist = 0;

    x = b.first - a.first;
    y = b.second - a.second;

    x *= x;
    y *= y;

    return dist = sqrt(x + y);
}

/**
 * @brief Points::findShortestPath Goes through the vector of points and finds the points with
 *                the least distance between them, then adds both points to the vector closePoints
 */
void Points::findShortestPath(){
    myVec.pop_back();
    numOfItems--;
    sort(myVec.begin(),myVec.end());

    float dist = 0;
    float leastDist = 1;
    Points p;

    for(unsigned i = 0; i < myVec.size() - 1; i++) {
        dist = distance(myVec[i], myVec[i + 1]);
        if(dist == leastDist){
            closePoints.push_back(myVec[i]);
            closePoints.push_back(myVec[i + 1]);
        }
        else if(dist < leastDist){
            closePoints.clear();
            closePoints.push_back(myVec[i]);
            closePoints.push_back(myVec[i + 1]);

        }
     }

    // Write results to file output.txt
    ofstream output("output_bruteforce.txt");

    output << dist << endl;
    for(unsigned i = 0; i < closePoints.size() - 1; i+=2){
        output << closePoints[i].first << ' ' << closePoints[i].second << ' '
             << closePoints[i + 1].first << ' ' << closePoints[i + 1].second << endl;
    }
    output.close();
}



#endif // POINTS

