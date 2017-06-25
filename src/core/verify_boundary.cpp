////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    verify_boundary.cpp
/// @brief   The implementation of boundary verification.
///
/// @author  Yuhsiang Mike Tsai
///

#include <harmonic.hpp>
#include <vector>
#include <iostream>
using namespace std;

pair<int, int> find_index(int *A, int n, int value){
  pair<int, int> ind;
  int i=0;
  for (i=0; i<n; i++){
    if (A[i]==value){
      ind.first=i;
      break;
    }
  }
  for (i=i+1; i<n; i++){
    if (A[i]==value) {
      ind.second=i;
      break;
    }
  }
  return ind;
}

void verifyBoundary(
    const int nv,
    const int nf,
    const int *F,
    int *ptr_nb,
    int *idx_b
) {
  int *Gvv = new int [nv*nv];
  for (int i=0; i<nv*nv; i++){
    Gvv[i] = 0;
  }

  int p[3];
  for (int i=0; i<nf; i++){
    // cout<<i<<endl;
    p[0]=F[i];
    p[1]=F[nf+i];
    p[2]=F[2*nf+i];
    // cout <<p[0]<<" "<<p[1]<<" "<<p[2]<<"\n";
    Gvv[(p[1]-1)*nv+(p[0]-1)]++; // p0->p1
    Gvv[(p[2]-1)*nv+(p[1]-1)]++; // p1->p2
    Gvv[(p[0]-1)*nv+(p[2]-1)]++; // p2->p0
  }
  int nb=0, bd_vertex=nv+1, bd_ind=nv+1;
  int *Bi= new int [2*nv], *Bj = new int [2*nv];

  for (int j=0; j<nv; j++){
    for (int i=0; i<nv; i++){
      // (i,j)
      if (Gvv[j*nv+i]+Gvv[i*nv+j]==1){
        nb++;
        Bi[nb-1]=i+1;
        Bj[nb-1]=j+1;
        if (i+1<bd_vertex){
          bd_vertex = i+1;
          bd_ind = nb-1;
        }
      }
    }
  }
  vector<int> VB;
  pair<int, int> ind;
  for (int i=0; i<nb; i++){
    VB.push_back(bd_vertex);
    ind = find_index (Bi, nb, Bj[bd_ind]);
    if (Bj[ind.first]==bd_vertex) {
      bd_ind = ind.second;
    }
    else{
      bd_ind = ind.first;
    }
    bd_vertex = Bi[bd_ind];
    if (bd_vertex == VB[0]){
      break;
    }
  }
  *ptr_nb = VB.size();
  for (int i=0; i<*ptr_nb; i++){
    idx_b[i]=VB[i];
  }

  delete [] Bi;
  delete [] Bj;
  delete [] Gvv;
  return;
}
