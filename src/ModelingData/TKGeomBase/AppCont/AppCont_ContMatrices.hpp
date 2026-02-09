#pragma once

#include <math_Vector.hpp>

void InvMMatrix(const int classe, math_Matrix& M);

void MMatrix(const int classe, math_Matrix& M);

void IBPMatrix(const int classe, math_Matrix& M);

void IBTMatrix(const int classe, math_Matrix& M);

void VBernstein(const int classe, const int nbpoints, math_Matrix& M);
