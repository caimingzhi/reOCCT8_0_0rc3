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

#include <IGESData_IGESDumper.hpp>
#include <IGESGeom_BoundedSurface.hpp>
#include <IGESGeom_BSplineCurve.hpp>
#include <IGESGeom_BSplineSurface.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_CompositeCurve.hpp>
#include <IGESGeom_ConicArc.hpp>
#include <IGESGeom_CopiousData.hpp>
#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Flash.hpp>
#include <IGESGeom_Line.hpp>
#include <IGESGeom_OffsetCurve.hpp>
#include <IGESGeom_OffsetSurface.hpp>
#include <IGESGeom_Plane.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESGeom_RuledSurface.hpp>
#include <IGESGeom_SpecificModule.hpp>
#include <IGESGeom_SplineCurve.hpp>
#include <IGESGeom_SplineSurface.hpp>
#include <IGESGeom_SurfaceOfRevolution.hpp>
#include <IGESGeom_TabulatedCylinder.hpp>
#include <IGESGeom_ToolBoundary.hpp>
#include <IGESGeom_ToolBoundedSurface.hpp>
#include <IGESGeom_ToolBSplineCurve.hpp>
#include <IGESGeom_ToolBSplineSurface.hpp>
#include <IGESGeom_ToolCircularArc.hpp>
#include <IGESGeom_ToolCompositeCurve.hpp>
#include <IGESGeom_ToolConicArc.hpp>
#include <IGESGeom_ToolCopiousData.hpp>
#include <IGESGeom_ToolCurveOnSurface.hpp>
#include <IGESGeom_ToolDirection.hpp>
#include <IGESGeom_ToolFlash.hpp>
#include <IGESGeom_ToolLine.hpp>
#include <IGESGeom_ToolOffsetCurve.hpp>
#include <IGESGeom_ToolOffsetSurface.hpp>
#include <IGESGeom_ToolPlane.hpp>
#include <IGESGeom_ToolPoint.hpp>
#include <IGESGeom_ToolRuledSurface.hpp>
#include <IGESGeom_ToolSplineCurve.hpp>
#include <IGESGeom_ToolSplineSurface.hpp>
#include <IGESGeom_ToolSurfaceOfRevolution.hpp>
#include <IGESGeom_ToolTabulatedCylinder.hpp>
#include <IGESGeom_ToolTransformationMatrix.hpp>
#include <IGESGeom_ToolTrimmedSurface.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <IGESGeom_TrimmedSurface.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_SpecificModule, IGESData_SpecificModule)

//  Each Module is attached to a Protocol : it must interpret Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol
IGESGeom_SpecificModule::IGESGeom_SpecificModule() = default;

void IGESGeom_SpecificModule::OwnDump(const int                               CN,
                                      const occ::handle<IGESData_IGESEntity>& ent,
                                      const IGESData_IGESDumper&              dumper,
                                      Standard_OStream&                       S,
                                      const int                               own) const
{
  switch (CN)
  {
    case 1: {
      DeclareAndCast(IGESGeom_BSplineCurve, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolBSplineCurve tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 2: {
      DeclareAndCast(IGESGeom_BSplineSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolBSplineSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 3: {
      DeclareAndCast(IGESGeom_Boundary, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolBoundary tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 4: {
      DeclareAndCast(IGESGeom_BoundedSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolBoundedSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 5: {
      DeclareAndCast(IGESGeom_CircularArc, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolCircularArc tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 6: {
      DeclareAndCast(IGESGeom_CompositeCurve, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolCompositeCurve tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 7: {
      DeclareAndCast(IGESGeom_ConicArc, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolConicArc tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 8: {
      DeclareAndCast(IGESGeom_CopiousData, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolCopiousData tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 9: {
      DeclareAndCast(IGESGeom_CurveOnSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolCurveOnSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 10: {
      DeclareAndCast(IGESGeom_Direction, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolDirection tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 11: {
      DeclareAndCast(IGESGeom_Flash, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolFlash tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 12: {
      DeclareAndCast(IGESGeom_Line, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolLine tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 13: {
      DeclareAndCast(IGESGeom_OffsetCurve, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolOffsetCurve tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 14: {
      DeclareAndCast(IGESGeom_OffsetSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolOffsetSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 15: {
      DeclareAndCast(IGESGeom_Plane, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolPlane tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 16: {
      DeclareAndCast(IGESGeom_Point, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolPoint tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 17: {
      DeclareAndCast(IGESGeom_RuledSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolRuledSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 18: {
      DeclareAndCast(IGESGeom_SplineCurve, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolSplineCurve tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 19: {
      DeclareAndCast(IGESGeom_SplineSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolSplineSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 20: {
      DeclareAndCast(IGESGeom_SurfaceOfRevolution, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolSurfaceOfRevolution tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 21: {
      DeclareAndCast(IGESGeom_TabulatedCylinder, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolTabulatedCylinder tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 22: {
      DeclareAndCast(IGESGeom_TransformationMatrix, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolTransformationMatrix tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 23: {
      DeclareAndCast(IGESGeom_TrimmedSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESGeom_ToolTrimmedSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    default:
      break;
  }
}

bool IGESGeom_SpecificModule::OwnCorrect(const int                               CN,
                                         const occ::handle<IGESData_IGESEntity>& ent) const
{
  //   Applies only on some types
  switch (CN)
  {
    case 3: {
      DeclareAndCast(IGESGeom_Boundary, anent, ent);
      if (anent.IsNull())
        break;
      IGESGeom_ToolBoundary tool;
      return tool.OwnCorrect(anent);
    }
    case 7: {
      DeclareAndCast(IGESGeom_ConicArc, anent, ent);
      if (anent.IsNull())
        break;
      IGESGeom_ToolConicArc tool;
      return tool.OwnCorrect(anent);
    }
    case 9: {
      DeclareAndCast(IGESGeom_Boundary, anent, ent);
      if (anent.IsNull())
        break;
      IGESGeom_ToolBoundary tool;
      return tool.OwnCorrect(anent);
    }
    case 11: {
      DeclareAndCast(IGESGeom_Flash, anent, ent);
      if (anent.IsNull())
        break;
      IGESGeom_ToolFlash tool;
      return tool.OwnCorrect(anent);
    }
    case 13: {
      DeclareAndCast(IGESGeom_OffsetCurve, anent, ent);
      if (anent.IsNull())
        break;
      IGESGeom_ToolOffsetCurve tool;
      return tool.OwnCorrect(anent);
    }
    case 22: {
      DeclareAndCast(IGESGeom_TransformationMatrix, anent, ent);
      if (anent.IsNull())
        break;
      IGESGeom_ToolTransformationMatrix tool;
      return tool.OwnCorrect(anent);
    }
    default:
      break;
  }
  return false;
}
