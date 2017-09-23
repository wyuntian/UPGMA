#include <iostream>
#include <fstream>
#include <algorithm>
#include "dynmatrix.h"
#include "dynmatrix.cc"
#include <string>
#include <cstring>
#include <stdio.h>
#include <string.h>


using namespace std;

// construct a string representation 

void usage() {
  cerr << "Usage: upgma species.txt" << endl;
}

void printCluster(ClusterNode *head, ClusterNode *tail){
    cout<<"---------------------------\n";
    ClusterNode* cn = head;
    while(cn){
        cout<<cn->name<<"       ";
        cn = cn->next;
    }
    cout<<endl;

    cn = head;
    while(cn){
        DistanceNode* t = cn->row;
        while(t){
            cout<<t->distance<<"          ";
            t = t->nextInRow;
        }
        cout<<endl;
        cn=cn->next;
    }
    cout<<"---------------------------\n";
}

 //helper function, return the number of species
  int countNum(ClusterNode * c){
      std::string cName = c->name;
      int numCount = int(std::count(cName.begin(),cName.end(),','));
     // int length = strlen(cName);
     //  cName[length]='\0';
     
     // int numComma = 0;
     // for(int i=0; i<=cName.size(); i++){
     //    if(strcmp(cName[i],&",")==0){
     //       numComma++;
     //    }
      //}
      return numCount+1;
   }

int main( int argc, char *argv[] ) {
  if( argc != 2 ) {
    usage();
    return 0;
  }

  // let's start with empty DynMatrix:
  ClusterNode* head = NULL; 
  ClusterNode* tail = NULL;

  int n = 0; // number of species
  ifstream fin( argv[1] );
  if( fin.is_open() ) {
      // read species:
      string species;
      while ((fin.peek() != '\n') && (fin >> species)) {
          n++;
          cout << species << endl;
          // YOUR CODE HERE: replace print statemnt by a code that insert a new species into DynMatrix
          addCluster(head, tail, species);

      }
      printCluster(head, tail);
      // read distances:
      ClusterNode *startCluster = head;
      //DistanceNode * theRowDNode = startCluster->row;
      for (int i = 0; i < n && fin; i++)
          for (int j = 0; j < n && fin; j++) {
              double d;
              fin >> d;
              //cout << d << endl;
              // YOUR CODE HERE: replace print statemnt by a code that updates distance field of the corresponding DistanceNode
              int accI = i;
              int accJ = j;
              DistanceNode *theRowDNode = startCluster->row;
              while (accI > 0) {
                  theRowDNode = theRowDNode->nextInRow;
                  accI--;
              }
              while (accJ > 0) {
                  theRowDNode = theRowDNode->nextInColumn;
                  accJ--;
              }
              theRowDNode->distance = d;
              //printCluster(head,tail);
              //fin.close();
          }
      printCluster(head,tail);
      fin.close();
      //printCluster(head,tail);
  }

    //printCluster(head,tail);

  // YOUR CODE HERE: implement UPGMA method

   while(head!=tail){
  
        ClusterNode * C = head;   //Every time set C to head and D to the tail of the new List;
        ClusterNode * D = tail;
     
        findMinimum(head, C, D);  //reset C, D to nearest species by calling findMinimum;
        string newClusterName="("+C->name+","+D->name+")";
        addCluster(head,tail,newClusterName);  //add new generated species group to the tail of matrix;
        ClusterNode * newCluster = tail;
          
        //calculate and put distance data into all distanceNodes(of new species) of the matrix
        DistanceNode * newRowDNode = newCluster->row;    //get the first distanceNode of row
        DistanceNode * newColDNode = newCluster->column; 
        DistanceNode * cColDNode = C->column;            //get the data from C for distance formular
        DistanceNode * dColDNode = D->column;            //get the data from D for distance formular
          
            while(newColDNode->nextInColumn){
                double dcx = cColDNode->distance;           //cColNode[i] and cRowNode[i] are equvalent,
                double ddx = dColDNode->distance;           //so we only need one of them
             
                //calculate the distance data for E and assign the distance to both corresponding RowNode 
                //and ColumnNode
                double dex = ((countNum(C))*dcx + (countNum(D))*ddx)/((countNum(C))+(countNum(D)));
                newRowDNode->distance=dex;
                newColDNode->distance=dex;

                cColDNode=cColDNode->nextInColumn;  //move both cColumnNode and dColumnNode to the next
                dColDNode=dColDNode->nextInColumn; 
     
                newRowDNode=newRowDNode->nextInRow; //move both RowNode and ColumnNode of newCluster to next
                newColDNode=newColDNode->nextInColumn;
             }
        removeCluster(head,newCluster,C);  //After finishing adding the new Cluster, delete old C,D
        removeCluster(head,newCluster,D);
        printCluster(head,tail);
     }




    //printCluster(head,tail);

  // print the name of the last remaining cluster
  if (head)
    cout << head->name << endl;

  // BONUS (optional): print the tree in a nice way

  return 0;
}

