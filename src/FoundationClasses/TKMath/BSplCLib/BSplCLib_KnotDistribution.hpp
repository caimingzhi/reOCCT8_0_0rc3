#pragma once

//! This enumeration describes the repartition of the
//! knots sequence. If all the knots differ by the
//! same positive constant from the preceding knot the
//! "KnotDistribution" is <Uniform> else it is
//! <NonUniform>
enum BSplCLib_KnotDistribution
{
  BSplCLib_NonUniform,
  BSplCLib_Uniform
};
