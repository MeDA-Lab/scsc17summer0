////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    verify_boundary_sparse.cpp
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

int64_t construct_key (int i, int j, int nv){
  if (i<j) {
    return i*(int64_t)nv+j;
  }
  else {
    return j*(int64_t)nv+i;
  }
}

int compare(const void *a, const void *b) {
  // pair<int,int> pair_a = (pair<int,int>) *a;
  // pair<int,int> pair_b = (pair<int,int>) *b;
  return ( *(int64_t*)a - *(int64_t*)b );
}
void verifyBoundarySparse(
    const int nv,
    const int nf,
    const int *F,
    int *ptr_nb,
    int *idx_b
) {
  int64_t *key=new int64_t [3*nf];
  int p[3];
  for (int i=0; i<nf; i++){
    // cout<<i<<endl;
    p[0]=F[i]-1;
    p[1]=F[nf+i]-1;
    p[2]=F[2*nf+i]-1;
    key[3*i]=construct_key(p[0],p[1],nv);
    key[3*i+1]=construct_key(p[1],p[2],nv);
    key[3*i+2]=construct_key(p[2],p[0],nv);

  }

  qsort(key, 3*nf, sizeof(int64_t), compare);
  int nb=0, bd_vertex=nv+1, bd_ind=nv+1;
  int *Bi= new int [2*nv], *Bj = new int [2*nv];
  int i=0;
  while (i<3*nf) {
    int temp_step=0;
    int64_t pinned=key[i];
    while (i<3*nf && key[i]==pinned){
      i++;
      temp_step++;
    }
    if (temp_step==1){
      nb++;
      Bi[nb-1]=pinned/nv+1;
      Bj[nb-1]=pinned%nv+1;
      if (Bi[nb-1]<bd_vertex){
        bd_vertex = Bi[nb-1];
        bd_ind=nb-1;
      }
      nb++;
      Bi[nb-1]=pinned%nv+1;
      Bj[nb-1]=pinned/nv+1;
      if (Bi[nb-1]<bd_vertex){
        bd_vertex = Bi[nb-1];
        bd_ind=nb-1;
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
  return;
}
