////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    map_boundary_mkl.cpp
/// @brief   The implementation of boundary mapping using MKL.
///
/// @author  Yuhsiang Mike Tsai
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define _USE_MATH_DEFINES
#include <cmath>
#include <harmonic.hpp>
#include <mkl.h>

double diffnorm(const double *x, const double *y, int n, int inc){
  double ans=0;
  double temp=0;
  for (int i=0; i<n; i++){
    temp=x[i*inc]-y[i*inc];
    ans+=temp*temp;
  }
  return sqrt(ans);
}

void mapBoundary(
    const int nv,
    const int nb,
    const double *V,
    double *U
) {

  double *Ux = U;
  double *Uy = U+nv;

  double prefix_sum = 0, nrm = 0;
  for ( int i = 0; i < nb; i++ ) {
    if ( i < nb-1 ){
      nrm = diffnorm(V+i, V+i+1, 3, nv);
    } else {
      nrm = diffnorm(V+nb-1, V, 3, nv);
    }
    prefix_sum += nrm;
    Ux[i] = prefix_sum;
  }

  double head = Ux[0], total = Ux[nb-1] - Ux[0];

  // Uy := 2pi * (Ux-head) / total
  vdLinearFrac(nb, Ux, Ux, 2*M_PI, -2*M_PI*head, 0.0, total, Uy);

  // Ux := cos(Uy)
  vdCos(nv, Uy, Ux);

  // Uy := sin(Uy)
  vdSin(nv, Uy, Uy);
}
