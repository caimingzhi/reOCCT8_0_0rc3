#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

//! class for instantiation of AppBlend
class GeomFill_Line : public Standard_Transient
{

public:
  Standard_EXPORT GeomFill_Line();

  Standard_EXPORT GeomFill_Line(const int NbPoints);

  int NbPoints() const;

  int Point(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_Line, Standard_Transient)

private:
  int myNbPoints;
};

inline int GeomFill_Line::NbPoints() const
{
  return myNbPoints;
}

//=================================================================================================

inline int GeomFill_Line::Point(const int Index) const
{
  return Index;
}
