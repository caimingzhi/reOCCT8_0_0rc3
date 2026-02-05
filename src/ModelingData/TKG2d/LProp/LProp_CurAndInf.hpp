#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Sequence.hpp>

enum LProp_CIType
{
  LProp_Inflection,
  LProp_MinCur,
  LProp_MaxCur
};

#include <Standard_Boolean.hpp>

//! Stores the parameters of a curve 2d or 3d corresponding
//! to the curvature's extremas and the Inflection's Points.
class LProp_CurAndInf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LProp_CurAndInf();

  Standard_EXPORT void AddInflection(const double Param);

  Standard_EXPORT void AddExtCur(const double Param, const bool IsMin);

  Standard_EXPORT void Clear();

  Standard_EXPORT bool IsEmpty() const;

  //! Returns the number of points.
  //! The Points are stored to increasing parameter.
  Standard_EXPORT int NbPoints() const;

  //! Returns the parameter of the Nth point.
  //! raises if N not in the range [1,NbPoints()]
  Standard_EXPORT double Parameter(const int N) const;

  //! Returns
  //! - MinCur if the Nth parameter corresponds to
  //! a minimum of the radius of curvature.
  //! - MaxCur if the Nth parameter corresponds to
  //! a maximum of the radius of curvature.
  //! - Inflection if the parameter corresponds to
  //! a point of inflection.
  //! raises if N not in the range [1,NbPoints()]
  Standard_EXPORT LProp_CIType Type(const int N) const;

private:
  NCollection_Sequence<double>       theParams;
  NCollection_Sequence<LProp_CIType> theTypes;
};
