// Created by: CKY / Contract Toubro-Larsen
// Copyright (c) 1993-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <IGESDraw_Drawing.hpp>
#include <IGESDraw_PerspectiveView.hpp>
#include <IGESDraw_View.hpp>
#include <IGESGraph_DrawingSize.hpp>
#include <IGESGraph_DrawingUnits.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_Drawing, IGESData_IGESEntity)

IGESDraw_Drawing::IGESDraw_Drawing() = default;

void IGESDraw_Drawing::Init(
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViews,
  const occ::handle<NCollection_HArray1<gp_XY>>&                                allViewOrigins,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&     allAnnotations)
{
  if (!allViews.IsNull())
  {
    int  Len  = allViews->Length();
    bool Flag = (allViewOrigins->Length() == Len);
    if (!Flag || allViews->Lower() != 1 || allViewOrigins->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDraw_Drawing : Init");
  }
  if (!allAnnotations.IsNull())
    if (allAnnotations->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDraw_Drawing : Init");

  theViews       = allViews;
  theViewOrigins = allViewOrigins;
  theAnnotations = allAnnotations;
  InitTypeAndForm(404, 0);
}

int IGESDraw_Drawing::NbViews() const
{
  return (theViews.IsNull() ? 0 : theViews->Length());
}

occ::handle<IGESData_ViewKindEntity> IGESDraw_Drawing::ViewItem(const int ViewIndex) const
{
  return theViews->Value(ViewIndex);
}

gp_Pnt2d IGESDraw_Drawing::ViewOrigin(const int TViewIndex) const
{
  return (gp_Pnt2d(theViewOrigins->Value(TViewIndex)));
}

int IGESDraw_Drawing::NbAnnotations() const
{
  return (theAnnotations.IsNull() ? 0 : theAnnotations->Length());
}

occ::handle<IGESData_IGESEntity> IGESDraw_Drawing::Annotation(const int AnnotationIndex) const
{
  return (theAnnotations->Value(AnnotationIndex));
}

gp_XY IGESDraw_Drawing::ViewToDrawing(const int NumView, const gp_XYZ& ViewCoords) const
{
  gp_XY  thisOrigin     = theViewOrigins->Value(NumView);
  double XOrigin        = thisOrigin.X();
  double YOrigin        = thisOrigin.Y();
  double theScaleFactor = 0.;

  occ::handle<IGESData_ViewKindEntity> tempView = theViews->Value(NumView);
  if (tempView->IsKind(STANDARD_TYPE(IGESDraw_View)))
  {
    DeclareAndCast(IGESDraw_View, thisView, tempView);
    theScaleFactor = thisView->ScaleFactor();
  }
  else if (tempView->IsKind(STANDARD_TYPE(IGESDraw_PerspectiveView)))
  {
    DeclareAndCast(IGESDraw_PerspectiveView, thisView, tempView);
    theScaleFactor = thisView->ScaleFactor();
  }

  double XV = ViewCoords.X();
  double YV = ViewCoords.Y();

  double XD = XOrigin + (theScaleFactor * XV);
  double YD = YOrigin + (theScaleFactor * YV);

  return (gp_XY(XD, YD));
}

bool IGESDraw_Drawing::DrawingUnit(double& val) const
{
  val                                = 0.;
  occ::handle<Standard_Type> typunit = STANDARD_TYPE(IGESGraph_DrawingUnits);
  if (NbTypedProperties(typunit) != 1)
    return false;
  DeclareAndCast(IGESGraph_DrawingUnits, units, TypedProperty(typunit));
  if (units.IsNull())
    return false;
  val = units->UnitValue();
  return true;
}

bool IGESDraw_Drawing::DrawingSize(double& X, double& Y) const
{
  X = Y                              = 0.;
  occ::handle<Standard_Type> typsize = STANDARD_TYPE(IGESGraph_DrawingSize);
  if (NbTypedProperties(typsize) != 1)
    return false;
  DeclareAndCast(IGESGraph_DrawingSize, size, TypedProperty(typsize));
  if (size.IsNull())
    return false;
  X = size->XSize();
  Y = size->YSize();
  return true;
}
