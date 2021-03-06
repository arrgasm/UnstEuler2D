#include "maps.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;

//TASK:          COMPUTES THE POINT TO ELEMENT MAP (HASH TABLE)
// alorithm: loop over all elements and in each element loop over all nodes
// and then add that element number to the hash_table "p_to_e" for that node.
int create_p_to_e(int ntri, int **tri, vector<int> *p_to_e)
{
  // local vars
  int t, i;
  for (t = 0; t < ntri; t++) // loop over all elements 
    for (i = 0; i < 3; i++) // loop over nodes in each element 
       {
         p_to_e[tri[t][i]].push_back(t); //tri[t][i] is global point number
       }
  // --------------------------------------------------------------------- 

  // completed successfully !
  return 0;
}
// TASK: COMPUTES THE ELEMENT CONTAINING THAT EDGE (EXCEPT THE ORIGINAL ELEMENT ITSELF)
// on success return the element number
// on failure returns -1
int elm_contain_edge(int pt1, int pt2, int itself, vector<int> *p_to_e)
{

  unsigned int i, j; //local vars
  for(i = 0; i < p_to_e[pt1].size(); i++) //loop over elements surrounding pt1
    for(j = 0; j < p_to_e[pt2].size(); j++) //loop over elements surrounding pt2
	if (p_to_e[pt1][i] == p_to_e[pt2][j] && p_to_e[pt1][i] != itself)
	  return p_to_e[pt1][i]; //return the neighbor and immediately stop searching

  return -1; //return -1 which hmeans doesn't have neighbor
}

//TASK: makes element surrounding element map or simply neighbors
void make_nbrs(int nn, int ntri, int **tri, int nbrs[][3], vector<int> *p_to_e)
{
  // local vars 
  int t = 0, edge = 0;

  // cleaning previous p2e connectivity 
  for (t = 0; t < nn; t++) // loop over all nodes 
    p_to_e[t].clear(); //clear

  //create the point to element map
  create_p_to_e(ntri, tri, p_to_e);

  for( t = 0; t < ntri ; t++) //loop over all elements
    {
      for( edge = 0; edge < 2; edge++) //loop over ondes in each element
	nbrs[t][edge] = elm_contain_edge(tri[t][edge], tri[t][edge+1], t, p_to_e);
      // find neighbor for last point
      nbrs[t][2] = elm_contain_edge(tri[t][2], tri[t][0], t, p_to_e); 
    }
}

// creates p2p (point to point map)
// IMPORTANT : THIS VERSION OF THE MAP CONTAINS THE POINT ITSELF
// alorithm: loop over triangles 
//              for each vertex add the global node number of ALL three vertices 
//           end
//           sort
//           remove repeated occurance of node numbers 
//           end
// sample : p2p[i=0..(nn-1)][0..number of connected nodes+the node itself]
int create_p2p(int ntri, int **tri, int nn, vector<int> *p2p)
{
  // local vars
  int t, i, k;

  for (t = 0; t < ntri; t++) // loop over all elements 
    for (i = 0; i < 3; i++) // loop over nodes in each element
      for(k = 0 ; k < 3; k++) 
	p2p[tri[t][i]].push_back(tri[t][k]);

  //clean-up 
  for ( i = 0; i < nn; i++)
    {
      sort(p2p[i].begin(), p2p[i].end());
      //remove duplicates
      p2p[i].erase(unique(p2p[i].begin(), p2p[i].end()), p2p[i].end());
    }

  // completed successfully !
  return 0;
}
