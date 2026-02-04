#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TNaming_Evolution.hpp>
#include <TNaming_NamedShape.hpp>
class TNaming_UsedShapes;
class TopoDS_Shape;
class TDF_Label;
class TNaming_NamedShape;

class TNaming_Localizer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TNaming_Localizer();

  Standard_EXPORT void Init(const occ::handle<TNaming_UsedShapes>& US, const int CurTrans);

  Standard_EXPORT const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& SubShapes(
    const TopoDS_Shape&    S,
    const TopAbs_ShapeEnum Type);

  Standard_EXPORT const NCollection_IndexedDataMap<TopoDS_Shape,
                                                   NCollection_List<TopoDS_Shape>,
                                                   TopTools_ShapeMapHasher>&
                        Ancestors(const TopoDS_Shape& S, const TopAbs_ShapeEnum Type);

  Standard_EXPORT void FindFeaturesInAncestors(
    const TopoDS_Shape&                                     S,
    const TopoDS_Shape&                                     In,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& AncInFeatures);

  Standard_EXPORT void GoBack(const TopoDS_Shape&                                S,
                              const TDF_Label&                                   Lab,
                              const TNaming_Evolution                            Evol,
                              NCollection_List<TopoDS_Shape>&                    OldS,
                              NCollection_List<occ::handle<TNaming_NamedShape>>& OldLab);

  Standard_EXPORT void Backward(
    const occ::handle<TNaming_NamedShape>&                  NS,
    const TopoDS_Shape&                                     S,
    NCollection_Map<occ::handle<TNaming_NamedShape>>&       Primitives,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& ValidShapes);

  Standard_EXPORT void FindNeighbourg(
    const TopoDS_Shape&                                     Cont,
    const TopoDS_Shape&                                     S,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& Neighbourg);

  Standard_EXPORT static bool IsNew(const TopoDS_Shape&                    S,
                                    const occ::handle<TNaming_NamedShape>& NS);

  Standard_EXPORT static void FindGenerator(const occ::handle<TNaming_NamedShape>& NS,
                                            const TopoDS_Shape&                    S,
                                            NCollection_List<TopoDS_Shape>& theListOfGenerators);

  //! Finds context of the shape <S>.
  Standard_EXPORT static void FindShapeContext(const occ::handle<TNaming_NamedShape>& NS,
                                               const TopoDS_Shape&                    theS,
                                               TopoDS_Shape&                          theSC);

private:
  int                                                                      myCurTrans;
  occ::handle<TNaming_UsedShapes>                                          myUS;
  NCollection_List<TopoDS_Shape>                                           myShapeWithSubShapes;
  NCollection_List<NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>> mySubShapes;
  NCollection_List<TopoDS_Shape>                                           myShapeWithAncestors;
  NCollection_List<NCollection_IndexedDataMap<TopoDS_Shape,
                                              NCollection_List<TopoDS_Shape>,
                                              TopTools_ShapeMapHasher>>
    myAncestors;
};

