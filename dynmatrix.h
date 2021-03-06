#ifndef __DYNMATRIX
#define __DYNMATRIX
#include <string>

struct DistanceNode {
  double distance;
  DistanceNode* nextInColumn;
  DistanceNode* nextInRow;
  // you can add a constructor
    DistanceNode(double d):
            distance(d),nextInColumn(NULL),nextInRow(NULL){}
};

struct ClusterNode {
  std::string name;
  // you can add more data members
  ClusterNode* prev;
  ClusterNode* next;
  DistanceNode* row;
  DistanceNode* column;
  // you can add a constructor
    ClusterNode(std::string d):
            name(d),prev(NULL),next(NULL),row(NULL),column(NULL){}
};

void addCluster(ClusterNode *&head,ClusterNode *&tail,const std::string& name);
// adds a cluster (at the tail) and the corresponding row and column to data structure
// distance of all added DistanceNodes should be initialized to 0.0
// at the end, tail should point to the newly added ClusterNode

void removeCluster(ClusterNode *&head,ClusterNode *&tail,ClusterNode *toBeRemoved);
// removes a cluster pointed to by toBeRemoved and the corresponding row and column
// if toBeRemoved is the first or last cluster then head or tail needs to be updated

void findMinimum(ClusterNode *head,ClusterNode *&C,ClusterNode *&D);
// finds the minimum distance (between two different clusters) in the data structure 
// and returns the two clusters via C and D

#endif
