#pragma once


//! Lists the types of fillet shapes. These include the following:
//! -   ChFi3d_Rational (default value), which is the
//! standard NURBS representation of circles,
//! -   ChFi3d_QuasiAngular, which is a NURBS
//! representation of circles where the parameters
//! match those of the circle,
//! -   ChFi3d_Polynomial, which corresponds to a
//! polynomial approximation of circles. This type
//! facilitates the implementation of the construction algorithm.
enum ChFi3d_FilletShape
{
  ChFi3d_Rational,
  ChFi3d_QuasiAngular,
  ChFi3d_Polynomial
};

