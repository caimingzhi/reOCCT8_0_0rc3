#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf.hpp>
#include <HLRBRep_BiPoint.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Boolean.hpp>
class Draw_Display;
class Draw_Color;

//! This class stores all the information concerning
//! hidden lines on a view.
//!
//! * View number
//! * Matrix of projection
//! * Type of projection, focal
//! * Arrays of 3d points
//!
//! A drawable shape contains a list of such objects
//! to store the hidden lines for each view. The
//! IsSame method is used to check if hidden lines
//! must be recompiled.
class DBRep_HideData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT DBRep_HideData();

  //! ViewId is the view number
  //! TProj the projection
  //! Focal <= 0 means parallel projection
  //! Alg : the hidden lines
  Standard_EXPORT void Set(const int           ViewId,
                           const gp_Trsf&      TProj,
                           const double        Focal,
                           const TopoDS_Shape& S,
                           const double        ang);

  int ViewId() const { return myView; }

  double Angle() const { return myAngle; }

  //! Returns True if the projection is the same
  Standard_EXPORT bool IsSame(const gp_Trsf& TProj, const double Focla) const;

  Standard_EXPORT void DrawOn(Draw_Display&     D,
                              const bool        withRg1,
                              const bool        withRgN,
                              const bool        withHid,
                              const Draw_Color& VisCol,
                              const Draw_Color& HidCol);

  //! Returns the subshape touched by the last pick.
  Standard_EXPORT const TopoDS_Shape& LastPick() const;

private:
  int                               myView;
  gp_Trsf                           myTrsf;
  double                            myFocal;
  NCollection_List<HLRBRep_BiPoint> myBiPntVis;
  NCollection_List<HLRBRep_BiPoint> myBiPntHid;
  TopoDS_Shape                      myPickShap;
  double                            myAngle;
};
