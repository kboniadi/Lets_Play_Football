#ifndef MSTGRAPH_H
#define MSTGRAPH_H

#include<vector>
#include<iostream>
#include<string>
#include<climits>
#include<iomanip>
#include"dbmanager.h"

using namespace std;

struct mstEdge{
    int start;
    int end;
    int weight;
    mstEdge(int start, int end, int weight):start(start),end(end),weight(weight){}
};

struct mstVertex{
    int key;
    int index;
    mstVertex* parent; //parent node
};

class mstGraph{
private:
    vector<mstVertex> vertices;    //Vector to store the vertices
    int numVertex; // number of vertices
    int** adjMatrix;    // adjacency matrix

    vector<mstVertex*> mstVec; // vector working as a priority queue

    /**
     * Function to create the adjacency matrix and initialize all the element to -1
     **/
    void initializeMatrix();

    /**
     * Function to delete the matrix
     **/
    void deleteMatrix();

    /**
     * Function to find the minimum value for MST and remove from the "queue"
     * @return the pointer to the vertex with the minimum key
     **/
    mstVertex* extractMin();

    /**
     * Function to do the MST
     **/
    void primMST(int start);



    /**
     * Function to check if the vertex is in the mstVec
     * @param search : vertex to be checked
     **/
    bool isExist(mstVertex search);

public:
    /**
     * Default constructor
     **/
    mstGraph();

    /**
     * Function to do the MST
     * @param start : starting location
     **/

    /**
     * Function to add an edge into the adjacency matrix
     * @param start : starting state
     * @param end : ending state
     * @param weight : distance between 2 states
     **/
    void addEdge(int start, int end,int weight);

    /**
     * Function to get the total mileage of the MST
     **/
    long getMSTdistance();

    void getMST(vector<mstEdge>&);

    /**
     * Class destructor
     **/
    ~mstGraph();
};

#endif // MSTGRAPH_H
