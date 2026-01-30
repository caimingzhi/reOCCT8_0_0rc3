// Created on: 1994-03-22
// Created by: GUYOT and UNTEREINER
// Copyright (c) 1994-1999 Matra Datavision
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

#include <IGESToBRep.hpp>

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <Geom2d_Curve.hpp>
#include <GeomLib.hpp>
#include <IGESBasic_SingleParent.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESGeom_BoundedSurface.hpp>
#include <IGESGeom_BSplineCurve.hpp>
#include <IGESGeom_BSplineSurface.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_CompositeCurve.hpp>
#include <IGESGeom_ConicArc.hpp>
#include <IGESGeom_CopiousData.hpp>
#include <IGESGeom_Line.hpp>
#include <IGESGeom_OffsetCurve.hpp>
#include <IGESGeom_OffsetSurface.hpp>
#include <IGESGeom_Plane.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESGeom_RuledSurface.hpp>
#include <IGESGeom_SplineCurve.hpp>
#include <IGESGeom_SplineSurface.hpp>
#include <IGESGeom_SurfaceOfRevolution.hpp>
#include <IGESGeom_TabulatedCylinder.hpp>
#include <IGESGeom_TrimmedSurface.hpp>
#include <IGESSolid_ConicalSurface.hpp>
#include <IGESSolid_CylindricalSurface.hpp>
#include <IGESSolid_EdgeList.hpp>
#include <IGESSolid_ManifoldSolid.hpp>
#include <IGESSolid_PlaneSurface.hpp>
#include <IGESSolid_Shell.hpp>
#include <IGESSolid_SphericalSurface.hpp>
#include <IGESSolid_ToroidalSurface.hpp>
#include <IGESSolid_VertexList.hpp>
#include <IGESToBRep_AlgoContainer.hpp>
#include <MoniTool_Macros.hpp>
#include <Precision.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <XSAlgo.hpp>

static occ::handle<IGESToBRep_AlgoContainer> theContainer;

//=================================================================================================

void IGESToBRep::Init()
{
  static bool init = false;
  if (init)
    return;
  init = true;
  XSAlgo::Init();
  theContainer = new IGESToBRep_AlgoContainer;
}

//=================================================================================================

void IGESToBRep::SetAlgoContainer(const occ::handle<IGESToBRep_AlgoContainer>& aContainer)
{
  theContainer = aContainer;
}

//=================================================================================================

occ::handle<IGESToBRep_AlgoContainer> IGESToBRep::AlgoContainer()
{
  return theContainer;
}

//=======================================================================
// function : IsCurveAndSurface
// purpose  : Return True if the IgesEntity can be transferred
//           by TransferCurveAndSurface
//=======================================================================
bool IGESToBRep::IsCurveAndSurface(const occ::handle<IGESData_IGESEntity>& start)
{
  // S4054
  if (start.IsNull())
    return false;
  if (IsTopoCurve(start))
    return true;
  if (IsTopoSurface(start))
    return true;
  if (IsBRepEntity(start))
    return true;
  return false;
}

//=======================================================================
// function : IsBasicCurve
// purpose  : Return True if the IgesEntity can be transferred
//           by TransferBasicCurve
//=======================================================================
bool IGESToBRep::IsBasicCurve(const occ::handle<IGESData_IGESEntity>& start)
{
  // S4054
  if (start.IsNull())
    return false;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_BSplineCurve)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_Line)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_CircularArc)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_ConicArc)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_CopiousData)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_SplineCurve)))
    return true;
  return false;
}

//=======================================================================
// function : IsBasicSurface
// purpose  : Return True if the IgesEntity can be transferred
//           by TransferBasicSurface
//=======================================================================
bool IGESToBRep::IsBasicSurface(const occ::handle<IGESData_IGESEntity>& start)
{
  // S4054
  if (start.IsNull())
    return false;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_BSplineSurface)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_SplineSurface)))
    return true;
  // S4181 pdn 15.04.99 added to basic surfaces
  if (start->IsKind(STANDARD_TYPE(IGESSolid_PlaneSurface)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_CylindricalSurface)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_ConicalSurface)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_SphericalSurface)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_ToroidalSurface)))
    return true;

  return false;
}

//=======================================================================
// function : IsTopoCurve
// purpose  : Return True if the IgesEntity can be transferred
//           by TransferTopoCurve
//=======================================================================
bool IGESToBRep::IsTopoCurve(const occ::handle<IGESData_IGESEntity>& start)
{
  // S4054
  if (start.IsNull())
    return false;
  if (IsBasicCurve(start))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_CompositeCurve)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_CurveOnSurface)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_Boundary)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_Point)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_OffsetCurve)))
    return true;
  return false;
}

//=======================================================================
// function : IsTopoSurface
// purpose  : Return True if the IgesEntity can be transferred
//           by TransferTopoSurface
//=======================================================================
bool IGESToBRep::IsTopoSurface(const occ::handle<IGESData_IGESEntity>& start)
{
  // S4054
  if (start.IsNull())
    return false;
  if (IsBasicSurface(start))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_TrimmedSurface)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_SurfaceOfRevolution)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_TabulatedCylinder)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_RuledSurface)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_Plane)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_BoundedSurface)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESGeom_OffsetSurface)))
    return true;
  // S4181 pdn 15.04.99 removing to basic surface
  // if (start->IsKind(STANDARD_TYPE(IGESSolid_PlaneSurface)))       return true;
  //  SingleParent, special case (Perforated Face: contains only PLANEs)
  if (start->IsKind(STANDARD_TYPE(IGESBasic_SingleParent)))
  {
    DeclareAndCast(IGESBasic_SingleParent, sp, start);
    if (!sp->SingleParent()->IsKind(STANDARD_TYPE(IGESGeom_Plane)))
      return false;
    int nb = sp->NbChildren();
    for (int i = 1; i <= nb; i++)
    {
      if (!sp->Child(i)->IsKind(STANDARD_TYPE(IGESGeom_Plane)))
        return false;
    }
    return true;
  }
  return false;
}

//=======================================================================
// function : IsBRepEntity
// purpose  : Return True if the IgesEntity can be transferred
//           by TransferBRepEntity
//=======================================================================
bool IGESToBRep::IsBRepEntity(const occ::handle<IGESData_IGESEntity>& start)
{
  // S4054
  if (start.IsNull())
    return false;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_Face)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_Shell)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_ManifoldSolid)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_VertexList)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_EdgeList)))
    return true;
  if (start->IsKind(STANDARD_TYPE(IGESSolid_Loop)))
    return true;
  return false;
}

//=======================================================================
// function : IGESCurveToSequenceOfIGESCurve
// purpose  : Creates a sequence of IGES curves from IGES curve:
//           - if curve is CompositeCurve its components are recursively added,
//           - if curve is ordinary IGES curve it is simply added
//           - otherwise (Null or not curve) it is ignored
// remark   : if sequence is Null it is created, otherwise it is appended
// returns  : number of curves in sequence
// example  : (A B (C (D ( E F) G) H)) -> (A B C D E F G H)
//=======================================================================

int IGESToBRep::IGESCurveToSequenceOfIGESCurve(
  const occ::handle<IGESData_IGESEntity>&                              curve,
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& sequence)
{
  if (sequence.IsNull())
    sequence = new NCollection_HSequence<occ::handle<Standard_Transient>>;
  if (!curve.IsNull())
  {
    if (curve->IsKind(STANDARD_TYPE(IGESGeom_CompositeCurve)))
    {
      occ::handle<IGESGeom_CompositeCurve> comp = occ::down_cast<IGESGeom_CompositeCurve>(curve);
      for (int i = 1; i <= comp->NbCurves(); i++)
      {
        occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> tmpsequence;
        IGESCurveToSequenceOfIGESCurve(comp->Curve(i), tmpsequence);
        sequence->Append(tmpsequence);
      }
    }
    else if (IGESToBRep::IsTopoCurve(curve) && !curve->IsKind(STANDARD_TYPE(IGESGeom_Point)))
      sequence->Append(curve);
  }
  return sequence->Length();
}

//=======================================================================
// function : TransferPCurve
// purpose  : Copies pcurve on face <face> from <fromedge> to <toedge>
//           If <toedge> already has pcurve on that <face>, <toedge> becomes
//           a seam-edge; if both pcurves are not SameRange, the SameRange is
//           called. Returns False if pcurves are not made SameRange
//           Making <toedge> SameParameter should be done outside the method (???)
//=======================================================================

bool IGESToBRep::TransferPCurve(const TopoDS_Edge& fromedge,
                                const TopoDS_Edge& toedge,
                                const TopoDS_Face& face)
{
  bool                      result = true;
  double                    olda, oldb, a, b;
  occ::handle<Geom2d_Curve> oldpcurve = BRep_Tool::CurveOnSurface(toedge, face, olda, oldb),
                            pcurve    = BRep_Tool::CurveOnSurface(fromedge, face, a, b);
  BRep_Builder B;
  if (!oldpcurve.IsNull())
  {
    if (olda != a || oldb != b)
    {
      try
      {
        OCC_CATCH_SIGNALS
        occ::handle<Geom2d_Curve> newpcurve;
        GeomLib::SameRange(Precision::PConfusion(), oldpcurve, olda, oldb, a, b, newpcurve);
        if (!newpcurve.IsNull())
        {
          olda      = a;
          oldb      = b;
          oldpcurve = newpcurve;
        }
        else
        {
#ifdef OCCT_DEBUG
          std::cout << "Warning: IGESToBRep::TransferPCurve: pcurves are not SameRange"
                    << std::endl;
#endif
          result = false;
        }
      }
      catch (Standard_Failure const& anException)
      {
#ifdef OCCT_DEBUG
        std::cout << "\n**IGESToBRep::TransferPCurve: Exception in SameRange : ";
        anException.Print(std::cout);
#endif
        (void)anException;
        result = false;
      }
    }
    if (toedge.Orientation() == TopAbs_FORWARD)
      B.UpdateEdge(toedge,
                   occ::down_cast<Geom2d_Curve>(pcurve->Copy()),
                   occ::down_cast<Geom2d_Curve>(oldpcurve->Copy()),
                   face,
                   0);
    else
      B.UpdateEdge(toedge,
                   occ::down_cast<Geom2d_Curve>(oldpcurve->Copy()),
                   occ::down_cast<Geom2d_Curve>(pcurve->Copy()),
                   face,
                   0);
  }
  else
  {
    olda = a;
    oldb = b;
    B.UpdateEdge(toedge, occ::down_cast<Geom2d_Curve>(pcurve->Copy()), face, 0);
  }
  B.Range(toedge, face, a, b);
  double first, last;
  if (!BRep_Tool::Curve(toedge, first, last).IsNull() && (first != a || last != b))
    B.SameRange(toedge, false);
  else
    B.SameRange(toedge, true);
  return result;
}
