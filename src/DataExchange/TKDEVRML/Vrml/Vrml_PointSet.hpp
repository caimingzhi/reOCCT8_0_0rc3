#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>

//! defines a PointSet node of VRML specifying geometry shapes.
class Vrml_PointSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_PointSet(const int aStartIndex = 0, const int aNumPoints = -1);

  Standard_EXPORT void SetStartIndex(const int aStartIndex);

  Standard_EXPORT int StartIndex() const;

  Standard_EXPORT void SetNumPoints(const int aNumPoints);

  Standard_EXPORT int NumPoints() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  int myStartIndex;
  int myNumPoints;
};
