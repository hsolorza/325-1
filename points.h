#ifndef POINTS_H
#define POINTS_H

#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
#include <cmath>
#include <math.h>
#include <list>
#include <iostream>
#include <utility>
#include <iomanip>
#include <fstream>

using namespace std;

class Points{
public:

    void insert();
    float distance(pair<int,int> a, pair<int,int> b);
    void findShortestPath();
    void outputToFile(vector<pair<int,int>> v);
    float closestPair(vector<pair<int, int> > v);
    float closestCrossPair(vector<pair<int,int>> mY, float S);

private:
    float dist = 0, leastDist = 1;
    int middleLoc = 0, numOfItems = 0;
    float S1, S2;

    vector<pair<int,int>> myVec;
    vector<pair<int,int>> closePoints;
    vector<pair<int,int>> pointsFromL;
};

/**
 * @brief Points::pairCompare  Sort helper that sorts pairs by their x
 * @param a The first pair
 * @param b The second pair
 * @return A bool if the second pair is the biggest
 */
static bool pairCompare(pair<int, int> a, pair<int, int> b){
    return a.first < b.first;
}


/**
 * @brief Points::insert Retrieves points from a file and adds the pairs to myVec
 */
void Points::insert(){

    ifstream input("example.txt");

    pair<int,int> p;
    int x = 0, y = 0;

    //reads in data, creates points, and adds to an array
    while(!input.eof()){
        input >> x >> y;
        p = make_pair(x, y);

        // add the pair to the vector
        myVec.push_back(p);
        numOfItems++;
    }
    myVec.pop_back();
    numOfItems--;
    float result = closestPair(myVec);

    cout << "the result: " << result << endl;

}


/**
 * @brief Points::closestPair Find the closest pairs using the Closest Pair Algorithm
 * @param myVec Full vector of all the points
 * @return The least distance?
 */
float Points::closestPair(vector<pair<int,int>> v){
    vector<pair<int,int>> leftHalf;
    vector<pair<int,int>> rightHalf;

    cout << "I went in closestPair! " << endl;
    if(v.size() <= 3){
        for(unsigned i =0; i < v.size() - 1; i++){
            dist = distance(v[i], v[i + 1]);
            if(dist == leastDist){
                closePoints.push_back(v[i]);
                closePoints.push_back(v[i + 1]);
            }
            else if(dist < leastDist){
                closePoints.clear();
                closePoints.push_back(v[i]);
                closePoints.push_back(v[i + 1]);

            }
        }
        return dist;
    }
    else{
            // divide the vector into two
            middleLoc = v.size() / 2;

            for(int i = 0; i < middleLoc; i++){
                leftHalf.push_back(v[i]);
            }
            for(unsigned i = middleLoc ; i < v.size(); i++){
                rightHalf.push_back(v[i]);
            }

            // recursivly find the least distances in each side
            S1 = closestPair(leftHalf);
            S2 = closestPair(rightHalf);
            cout << "s1 is: " << S1 << endl;
            cout << "s2 is: " << S2 << endl;

            float S = min(S1, S2);
            middleLoc = myVec.size() / 2;
            // identify all points within S from L(the middle)
            for(int i = middleLoc - S; i < middleLoc + S; i++){
                pointsFromL.push_back(myVec[i]);
            }

            // sort the vector by the points' x
            sort(pointsFromL.begin(), pointsFromL.end(), pairCompare);

            // do some snipping as extra stuff gets added into the vector somehow
            pointsFromL.erase(pointsFromL.begin(),pointsFromL.begin()+ 3);
            pointsFromL.pop_back();
            pointsFromL.pop_back();

            float dM = closestCrossPair(pointsFromL, S);
            cout << "The dM" << dM << endl;
            return dM;

            // TO DO:
            // Send vector of closest points to print

            cout << "the final S: " << S << endl;
    }

    //    return S;
}


/**
 * @brief Points::distance  Find the distance between two points using Distance Formula
 * @param a The first point
 * @param b The second point
 * @return The distance between the points
 */
float Points::distance(pair<int,int> a, pair<int,int> b){
    float x = 0, y = 0;
    x = b.first - a.first;
    y = b.second - a.second;

    x *= x;
    y *= y;

    return dist = sqrt(x + y);
}


/**
 * @brief Points::closestCrossPair  Find the closest pair that have one point on one side, and the other point on the other side
 * @param mY  The vector of points that are within S from L
 * @param S The distance from L to the outer border
 * @return The least distance
 */
float Points::closestCrossPair(vector<pair<int,int>> mY, float S){
    float dM = S;

    for(unsigned i = 1; i < mY.size()- 1; i++){
        unsigned j = i + 1;
        while((mY[j].second - mY[i].second <= S) && (j < mY.size())){
            float d = distance(mY[i], mY[j]);
            dM = min(d, dM);
            j++;
        }
    }
    return dM;
}


/**
 * @brief Points::outputToFile Send the vector of closest points to a file
 * @param v The vector of closest points
 */
void Points::outputToFile(vector<pair<int, int> > v){
    // Write results to file output.txt
    ofstream output("output.txt");

    output << dist << endl;
    for(unsigned i = 0; i < v.size() - 1; i+=2){
        output << v[i].first << ' ' << v[i].second << ' '
             << v[i + 1].first << ' ' << v[i + 1].second << endl;
    }
    output.close();
}


#endif // POINTS_H

