#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <SelectMgr_Selection.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <Select3D_SensitiveEntity.hpp>
#include <NCollection_Sequence.hpp>
#include <StdSelect_BRepOwner.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>

class Select3D_SensitiveEntity;
class SelectMgr_SelectableObject;
class TopoDS_Face;

class StdSelect_BRepSelectionTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Load(const occ::handle<SelectMgr_Selection>& aSelection,
                                   const TopoDS_Shape&                     aShape,
                                   const TopAbs_ShapeEnum                  aType,
                                   const double                            theDeflection,
                                   const double                            theDeviationAngle,
                                   const bool                              AutoTriangulation = true,
                                   const int                               aPriority         = -1,
                                   const int                               NbPOnEdge         = 9,
                                   const double                            MaximalParameter  = 500);

  Standard_EXPORT static void Load(const occ::handle<SelectMgr_Selection>&        aSelection,
                                   const occ::handle<SelectMgr_SelectableObject>& Origin,
                                   const TopoDS_Shape&                            aShape,
                                   const TopAbs_ShapeEnum                         aType,
                                   const double                                   theDeflection,
                                   const double                                   theDeviationAngle,
                                   const bool   AutoTriangulation = true,
                                   const int    aPriority         = -1,
                                   const int    NbPOnEdge         = 9,
                                   const double MaximalParameter  = 500);

  static int GetStandardPriority(const TopoDS_Shape& theShape, const TopAbs_ShapeEnum theType)
  {
    switch (theType)
    {
      case TopAbs_VERTEX:
        return 8;
      case TopAbs_EDGE:
        return 7;
      case TopAbs_WIRE:
        return 6;
      case TopAbs_FACE:
        return 5;
      case TopAbs_SHAPE:
      default:
        break;
    }

    switch (theShape.ShapeType())
    {
      case TopAbs_VERTEX:
        return 9;
      case TopAbs_EDGE:
        return 8;
      case TopAbs_WIRE:
        return 7;
      case TopAbs_FACE:
        return 6;
      case TopAbs_SHELL:
        return 5;
      case TopAbs_COMPOUND:
      case TopAbs_COMPSOLID:
      case TopAbs_SOLID:
      case TopAbs_SHAPE:
      default:
        return 4;
    }
  }

  Standard_EXPORT static void ComputeSensitive(const TopoDS_Shape&                       theShape,
                                               const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                               const occ::handle<SelectMgr_Selection>& theSelection,
                                               const double theDeflection,
                                               const double theDeflAngle,
                                               const int    theNbPOnEdge,
                                               const double theMaxiParam,
                                               const bool   theAutoTriang = true);

  Standard_EXPORT static bool GetSensitiveForFace(
    const TopoDS_Face&                                           theFace,
    const occ::handle<SelectMgr_EntityOwner>&                    theOwner,
    NCollection_Sequence<occ::handle<Select3D_SensitiveEntity>>& theOutList,
    const bool                                                   theAutoTriang   = true,
    const int                                                    theNbPOnEdge    = 9,
    const double                                                 theMaxiParam    = 500,
    const bool                                                   theInteriorFlag = true);

  Standard_EXPORT static bool GetSensitiveForCylinder(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theSubfacesMap,
    const occ::handle<SelectMgr_EntityOwner>&                            theOwner,
    const occ::handle<SelectMgr_Selection>&                              theSelection);

  Standard_EXPORT static void GetEdgeSensitive(const TopoDS_Shape&                       theShape,
                                               const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                               const occ::handle<SelectMgr_Selection>& theSelection,
                                               const double theDeflection,
                                               const double theDeviationAngle,
                                               const int    theNbPOnEdge,
                                               const double theMaxiParam,
                                               occ::handle<Select3D_SensitiveEntity>& theSensitive);

  Standard_EXPORT static void PreBuildBVH(const occ::handle<SelectMgr_Selection>& theSelection);
};
