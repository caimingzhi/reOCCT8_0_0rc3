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

class DBRep_HideData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT DBRep_HideData();

  Standard_EXPORT void Set(const int           ViewId,
                           const gp_Trsf&      TProj,
                           const double        Focal,
                           const TopoDS_Shape& S,
                           const double        ang);

  int ViewId() const { return myView; }

  double Angle() const { return myAngle; }

  Standard_EXPORT bool IsSame(const gp_Trsf& TProj, const double Focla) const;

  Standard_EXPORT void DrawOn(Draw_Display&     D,
                              const bool        withRg1,
                              const bool        withRgN,
                              const bool        withHid,
                              const Draw_Color& VisCol,
                              const Draw_Color& HidCol);

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
