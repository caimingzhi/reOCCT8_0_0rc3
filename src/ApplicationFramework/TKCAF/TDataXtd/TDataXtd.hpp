#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_GUID.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>
#include <TDataXtd_GeometryEnum.hpp>
#include <TDataXtd_ConstraintEnum.hpp>

//! This package defines extension of standard attributes for
//! modelling (mainly for work with geometry).
class TDataXtd
{
public:
  DEFINE_STANDARD_ALLOC

  //! Appends to <anIDList> the list of the attributes
  //! IDs of this package. CAUTION: <anIDList> is NOT
  //! cleared before use.
  //! Print of TDataExt enumeration
  //! =============================
  Standard_EXPORT static void IDList(NCollection_List<Standard_GUID>& anIDList);

  //! Prints the name of the geometry dimension <GEO> as a String on
  //! the Stream <S> and returns <S>.
  Standard_EXPORT static Standard_OStream& Print(const TDataXtd_GeometryEnum GEO,
                                                 Standard_OStream&           S);

  //! Prints the name of the constraint <CTR> as a String on
  //! the Stream <S> and returns <S>.
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
