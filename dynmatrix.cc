#include "dynmatrix.h"
#include <iostream>
#include <fstream>

void addCluster(ClusterNode *&head,ClusterNode *&tail,const std::string& name)
//adds a cluster (at the tail) and the corresponding row and column to data structure
//distance of all added DistanceNodes should be initialized to 0.0
// at the end, tail should point to the newly added ClusterNode
{
    ClusterNode* newCluster = new ClusterNode(name);
    DistanceNode* newDNode = new DistanceNode(0);

    if (tail) {
        ClusterNode* curr = tail;

        DistanceNode * recordRow = newDNode;
        DistanceNode * recordCol = newDNode;

        while(curr){

            DistanceNode* newRow = new DistanceNode(0);
            newRow->nextInRow = recordRow;

            DistanceNode* newCol = new DistanceNode(0);
            newCol->nextInColumn = recordCol;

            DistanceNode* lastRow = curr->row;
            DistanceNode* lastCol = curr->column;
            while(lastRow->nextInRow){
                lastRow=lastRow->nextInRow;
            }
            while(lastCol->nextInColumn){
                lastCol=lastCol->nextInColumn;
            }

            lastRow->nextInRow = newCol;
            lastCol->nextInColumn = newRow;

            curr=curr->prev;
            recordRow=newRow;
            recordCol=newCol;
        }
        tail->next = newCluster;
        newCluster->prev = tail;
        newCluster->column = recordCol;  //after we set up all the DistanceNode(Row and Column) we need to assign them to newCluster
        newCluster->row = recordRow;
        tail = newCluster;
    } else {
        newCluster->row = newDNode;
        newCluster->column = newDNode;
        head = newCluster;
        tail = head;
    }
}


void removeCluster(ClusterNode *&head,ClusterNode *&tail,ClusterNode *toBeRemoved)
// removes a cluster pointed to by toBeRemoved and the corresponding row and column
// if toBeRemoved is the first or last cluster then head or tail needs to be updated
{  if(toBeRemoved==tail) {
        if (toBeRemoved->prev) {
            DistanceNode *lastRow = toBeRemoved->prev->row;
            DistanceNode *lastCol = toBeRemoved->prev->column;
            toBeRemoved->prev->next = NULL;
            tail = toBeRemoved->prev;

            delete toBeRemoved;

            while (lastCol) {
                DistanceNode *temp = lastCol->nextInRow;
                lastCol->nextInRow = NULL;
                delete temp;
                lastCol = lastCol->nextInColumn;
            }

            while (lastRow) {
                DistanceNode *temp = lastRow->nextInColumn;
                lastRow->nextInColumn = NULL;
                delete temp;
                lastRow = lastRow->nextInRow;
            }

        } else {
            delete tail->row;  //here rowDistanceNode == columnDistanceNode;
            delete tail;
            tail = NULL;
            head = NULL;
        }
    }else if(toBeRemoved==head){
         if(head->next) {
             delete head->row;
             head = head->next;
             delete head->prev;
             head->prev = NULL;

             ClusterNode *nextC = head;
             while (nextC) {
                 DistanceNode *temp1 = nextC->column;
                 DistanceNode *temp2 = nextC->row;
                 nextC->column = nextC->column->nextInColumn;
                 nextC->row = nextC->row->nextInRow;
                 delete temp1;
                 delete temp2;
                 nextC = nextC->next;  //not sure if this line is right
             }
         }else{
             delete head->row;
             delete head;
             head = NULL;
         }
   }else{

        DistanceNode * prevColNode = toBeRemoved->prev->column;
        DistanceNode * prevRowNode = toBeRemoved->prev->row;

        toBeRemoved->prev->next = toBeRemoved->next;

        toBeRemoved->next->prev = toBeRemoved->prev;

        delete toBeRemoved;

        while(prevColNode){
            DistanceNode * temp = prevColNode->nextInRow;      // pay attention here: delete column, we iterate through row
                                                               // it is very easy to make mistake here, please draw a pic
            prevColNode->nextInRow = prevColNode->nextInRow->nextInRow;
            delete temp;
            prevColNode=prevColNode->nextInColumn;
        }
        while(prevRowNode){
             DistanceNode * temp = prevRowNode->nextInColumn;
             prevRowNode->nextInColumn = prevRowNode->nextInColumn->nextInColumn;
             delete temp;
             prevRowNode=prevRowNode->nextInRow;
        }   

   }

}

void findMinimum(ClusterNode *head,ClusterNode *&C,ClusterNode *&D)
// finds the minimum distance (between two different clusters) in the data structure 
// and returns the two clusters via C and D
{
     if(C->next != D || D->next != C){

         ClusterNode * nearestNode1 = C;
         ClusterNode * nearestRecordNode1 = C;
         ClusterNode * nearestRecordNode2 = C->next;
         double nearestSoFar = 1000000000000000000000.0;
  
         while(nearestNode1!=D){
           
           ClusterNode * nearestNode2 = nearestNode1->next;
           while(nearestNode2!=D->next){
              int count = 0;
              ClusterNode * firstCount = head;
              while(firstCount!=nearestNode2){
                  count++;
                  firstCount = firstCount->next;
                  }
              DistanceNode * countDNode = nearestNode1->row;
              for(int i=0; i<count; i++){
                  countDNode=countDNode->nextInRow;
              } 
               if(countDNode->distance>0 && countDNode->distance < nearestSoFar){
                 nearestSoFar = countDNode->distance;
                 nearestRecordNode2=nearestNode2;
                 nearestRecordNode1=nearestNode1;
                }
               nearestNode2=nearestNode2->next;
           }
          nearestNode1=nearestNode1->next;
           }
            C=nearestRecordNode1;
            D=nearestRecordNode2;
         }
}
            



