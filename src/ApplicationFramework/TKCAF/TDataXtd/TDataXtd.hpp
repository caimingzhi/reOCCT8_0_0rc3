#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_GUID.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>
#include <TDataXtd_GeometryEnum.hpp>
#include <TDataXtd_ConstraintEnum.hpp>

class TDataXtd
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void IDList(NCollection_List<Standard_GUID>& anIDList);

  Standard_EXPORT static Standard_OStream& Print(const TDataXtd_GeometryEnum GEO,
                                                 Standard_OStream&           S);

  Standard_EXPORT static Standard_OStream& Print(const TDataXtd_ConstraintEnum CTR,
                                                 Standard_OStream&             S);

private:
  friend class TDataXtd_Position;
  friend class TDataXtd_Constraint;
  friend class TDataXtd_Placement;
  friend class TDataXtd_Geometry;
  friend class TDataXtd_Point;
  friend class TDataXtd_Axis;
  friend class TDataXtd_Plane;
  friend class TDataXtd_Pattern;
  friend class TDataXtd_PatternStd;
  friend class TDataXtd_Shape;
  friend class TDataXtd_Triangulation;
};
