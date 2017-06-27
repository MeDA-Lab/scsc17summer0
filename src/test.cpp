////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main.cpp
/// @brief   The main function.
///
/// @author  Yen Chen Chen
///

#include <cmath>
#include <climits>
#include <iostream>
#include <harmonic.hpp>
using namespace std;

int main( int argc, char** argv ) {

  const char *input  = "input.obj";
  const char *output = "output.obj";
  Method method  = Method::KIRCHHOFF;

  int nv, nf, *F = nullptr;
  double *V = nullptr, *C = nullptr, *L;

  // Read arguments
  readArgs(argc, argv, input, output, method);

  // Read object
  readObject(input, &nv, &nf, &V, &C, &F);
  if ( nv > sqrt(INT_MAX) ) {
  cerr << "The size of the Laplacian matrix (" << nv << " x " << nv << " = " << long(nv) * long(nv)
       << ") exceed the maximum value of integer (" << INT_MAX << ")" << endl;
  abort();
  }

  cout << endl;

  // Construct Laplacian
  L = new double[nv * nv];
  constructLaplacian(method, nv, nf, V, F, L);

  // Print out result
  for (int i = 0; i < nv; ++i)
  {
    for (int j = 0; j < nv; ++j)
    {
      cout << L[i+j*nv] << '\t';
    }
    cout << endl;
  }

  return 0;
}