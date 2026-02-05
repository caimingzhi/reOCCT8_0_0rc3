#pragma once

//! This enumeration describes the form of the
//! sequence of mutiplicities. MultDistribution is:
//!
//! Constant if all the multiplicities have the same
//! value.
//!
//! QuasiConstant if all the internal knots have the
//! same multiplicity and if the first and last knot
//! have a different multiplicity.
//!
//! NonConstant in other cases.
enum BSplCLib_MultDistribution
{
  BSplCLib_NonConstant,
  BSplCLib_Constant,
  BSplCLib_QuasiConstant
};
