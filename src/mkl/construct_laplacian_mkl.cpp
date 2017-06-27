////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    construct_laplacian_mkl.cpp
/// @brief   The implementation of Laplacian construction using MKL.
///
/// @author  Yen Chen Chen
/// @author  Yuhsiang Mike Tsai
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <harmonic.hpp>
#include <mkl.h>

void constructLaplacian(
    const Method method,
    const int nv,
    const int nf,
    const double *V,
    const int *F,
    double *L
) {

  static_cast<void>(V);

  // L := 0
  cblas_dscal(nv*nv, 0.0, L, 1);

  switch ( method ) {

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Kirchhoff Laplacian matrix
    case Method::KIRCHHOFF: {

      // Set L from faces
      for ( int i = 0; i < nf; ++i ) {
        int fx = F[i]-1;
        int fy = F[i+nf]-1;
        int fz = F[i+nf*2]-1;

        L[fx+fy*nv] = -1;
        L[fy+fz*nv] = -1;
        L[fz+fx*nv] = -1;
        L[fy+fx*nv] = -1;
        L[fz+fy*nv] = -1;
        L[fx+fz*nv] = -1;
      }

      // L[i, i] := - sum( L[i-col] )
      for ( int i = 0; i < nv; ++i ) {
        L[i+i*nv] = cblas_dasum(nv, L+i*nv, 1);
      }

      // // L[i, i] := - sum( L[i-col] )
      // double dnone = -1.0;
      // for ( int i = 0; i < nv; ++i ) {
      //   L[i+i*nv] = cblas_ddot(nv, L+i*nv, 1, &dnone, 0);
      // }

      break;
    }

    default: {
      std::cerr << "Method " << int(method) << " is not available!";
      abort();
    }
  }
}
