////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main.cpp
/// @brief   The main function.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <cmath>
#include <climits>
#include <iostream>
#include <harmonic.hpp>
#include <timer.hpp>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Main function
///
int main( int argc, char** argv ) {

  const char *input  = "input.obj";
  const char *output = "output.obj";
  Method method  = Method::KIRCHHOFF;

  int nv, nf, nb, *F = nullptr, *idx_b;
  double timer, *V = nullptr, *C = nullptr, *L, *U;

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

  // Verify boundary
  idx_b = new int[nv];
  cout << "Verifying boundary ....................." << flush;
  tic(&timer);
  verifyBoundary(nv, nf, F, &nb, idx_b); cout << " Done.  ";
  toc(&timer);

  // Reorder vertices
  cout << "Reordering vertices ...................." << flush;
  tic(&timer);
  reorderVertex(nv, nb, nf, V, C, F, idx_b); cout << " Done.  ";
  toc(&timer);

  // Construct Laplacian
  L = new double[nv * nv];
  cout << "Constructing Laplacian ................." << flush;
  tic(&timer);
  constructLaplacian(method, nv, nf, V, F, L); cout << " Done.  ";
  toc(&timer);

  // Map boundary
  U = new double[2 * nv];
  cout << "Mapping Boundary ......................." << flush;
  tic(&timer);
  mapBoundary(nv, nb, V, U); cout << " Done.  ";
  toc(&timer);

  // Solve harmonic
  cout << "Solving Harmonic ......................." << flush;
  tic(&timer);
  solveHarmonic(nv, nb, L, U); cout << " Done.  ";
  toc(&timer);

  cout << endl;

  // Write object
  writeObject(output, nv, nf, U, C, F);

  // Free memory
  delete[] V;
  delete[] C;
  delete[] F;
  delete[] L;
  delete[] U;
  delete[] idx_b;

  return 0;
}
