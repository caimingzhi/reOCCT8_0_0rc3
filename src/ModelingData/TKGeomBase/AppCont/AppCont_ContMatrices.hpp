#pragma once

#include <math_Vector.hpp>

// Stockage des matrices de resolution d approxiamtion continue.
// La classe est limitee a 26 pour MMatrix et InvMMatrix, (pas de contraintes)
// pour IBPMatrix (contraintes de passage aux extremites)
// et IBTMatrix (contraintes de tangence aux extremites).

void InvMMatrix(const int classe, math_Matrix& M);

void MMatrix(const int classe, math_Matrix& M);

void IBPMatrix(const int classe, math_Matrix& M);

void IBTMatrix(const int classe, math_Matrix& M);

void VBernstein(const int classe, const int nbpoints, math_Matrix& M);

