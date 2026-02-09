#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <TNaming_NamedShape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
class TNaming_NamedShape;
class TNaming_OldShapeIterator;
class TopoDS_Shape;
class TDF_Label;
class TNaming_UsedShapes;

class TNaming_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopoDS_Shape CurrentShape(const occ::handle<TNaming_NamedShape>& NS);

  Standard_EXPORT static TopoDS_Shape CurrentShape(const occ::handle<TNaming_NamedShape>& NS,
                                                   const NCollection_Map<TDF_Label>&      Updated);

  Standard_EXPORT static occ::handle<TNaming_NamedShape> CurrentNamedShape(
    const occ::handle<TNaming_NamedShape>& NS,
    const NCollection_Map<TDF_Label>&      Updated);

  Standard_EXPORT static occ::handle<TNaming_NamedShape> CurrentNamedShape(
    const occ::handle<TNaming_NamedShape>& NS);

  Standard_EXPORT static occ::handle<TNaming_NamedShape> NamedShape(const TopoDS_Shape& aShape,
                                                                    const TDF_Label&    anAcces);

  Standard_EXPORT static TopoDS_Shape GetShape(const occ::handle<TNaming_NamedShape>& NS);

  Standard_EXPORT static TopoDS_Shape OriginalShape(const occ::handle<TNaming_NamedShape>& NS);

  Standard_EXPORT static TopoDS_Shape GeneratedShape(
    const TopoDS_Shape&                    S,
    const occ::handle<TNaming_NamedShape>& Generation);

  Standard_EXPORT static void Collect(const occ::handle<TNaming_NamedShape>&            NS,
                                      NCollection_Map<occ::handle<TNaming_NamedShape>>& Labels,
                                      const bool OnlyModif = true);

  Standard_EXPORT static bool HasLabel(const TDF_Label& access, const TopoDS_Shape& aShape);

  Standard_EXPORT static TDF_Label Label(const TDF_Label&    access,
                                         const TopoDS_Shape& aShape,
                                         int&                TransDef);

  Standard_EXPORT static TopoDS_Shape InitialShape(const TopoDS_Shape&          aShape,
                                                   const TDF_Label&             anAcces,
                                                   NCollection_List<TDF_Label>& Labels);

  Standard_EXPORT static int ValidUntil(const TDF_Label& access, const TopoDS_Shape& S);

  Standard_EXPORT static void FindShape(const NCollection_Map<TDF_Label>&      Valid,
                                        const NCollection_Map<TDF_Label>&      Forbiden,
                                        const occ::handle<TNaming_NamedShape>& Arg,
                                        TopoDS_Shape&                          S);

  friend class TNaming_Localizer;
  friend class TNaming_NamedShape;
  friend class TNaming_OldShapeIterator;

private:
  Standard_EXPORT static bool HasLabel(const occ::handle<TNaming_UsedShapes>& Shapes,
                                       const TopoDS_Shape&                    aShape);

  Standard_EXPORT static int ValidUntil(const TopoDS_Shape&                    S,
                                        const occ::handle<TNaming_UsedShapes>& US);

  Standard_EXPORT static TDF_Label Label(const occ::handle<TNaming_UsedShapes>& Shapes,
                                         const TopoDS_Shape&                    aShape,
                                         int&                                   TransDef);

  Standard_EXPORT static void FirstOlds(
    const occ::handle<TNaming_UsedShapes>&                         Shapes,
    const TopoDS_Shape&                                            S,
    TNaming_OldShapeIterator&                                      it,
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS,
    NCollection_List<TDF_Label>&                                   Labels);
};
