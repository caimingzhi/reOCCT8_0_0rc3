#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_GUID.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>
#include <TNaming_Evolution.hpp>
#include <TNaming_NameType.hpp>
class TDF_Label;
class TopLoc_Location;
class gp_Trsf;
class TNaming_NamedShape;
class TopoDS_Shape;
class TopoDS_Face;
class TopoDS_Wire;
class TopoDS_Solid;
class TopoDS_Shell;

class TNaming
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Substitute(
    const TDF_Label&                                                          labelsource,
    const TDF_Label&                                                          labelcible,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& mapOldNew);

  Standard_EXPORT static void Update(
    const TDF_Label&                                                          label,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& mapOldNew);

  Standard_EXPORT static void Displace(const TDF_Label&       label,
                                       const TopLoc_Location& aLocation,
                                       const bool             WithOld = true);

  Standard_EXPORT static void ChangeShapes(
    const TDF_Label&                                                          label,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& M);

  Standard_EXPORT static void Transform(const TDF_Label& label, const gp_Trsf& aTransformation);

  Standard_EXPORT static void Replicate(const occ::handle<TNaming_NamedShape>& NS,
                                        const gp_Trsf&                         T,
                                        const TDF_Label&                       L);

  Standard_EXPORT static void Replicate(const TopoDS_Shape& SH,
                                        const gp_Trsf&      T,
                                        const TDF_Label&    L);

  Standard_EXPORT static TopoDS_Shape MakeShape(
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& MS);

  Standard_EXPORT static TopoDS_Shape FindUniqueContext(const TopoDS_Shape& S,
                                                        const TopoDS_Shape& Context);

  Standard_EXPORT static TopoDS_Shape FindUniqueContextSet(
    const TopoDS_Shape&                             S,
    const TopoDS_Shape&                             Context,
    occ::handle<NCollection_HArray1<TopoDS_Shape>>& Arr);

  Standard_EXPORT static bool SubstituteSShape(const TDF_Label&    accesslabel,
                                               const TopoDS_Shape& From,
                                               TopoDS_Shape&       To);

  Standard_EXPORT static bool OuterWire(const TopoDS_Face& theFace, TopoDS_Wire& theWire);

  Standard_EXPORT static bool OuterShell(const TopoDS_Solid& theSolid, TopoDS_Shell& theShell);

  Standard_EXPORT static void IDList(NCollection_List<Standard_GUID>& anIDList);

  Standard_EXPORT static Standard_OStream& Print(const TNaming_Evolution EVOL, Standard_OStream& S);

  Standard_EXPORT static Standard_OStream& Print(const TNaming_NameType NAME, Standard_OStream& S);

  Standard_EXPORT static Standard_OStream& Print(const TDF_Label& ACCESS, Standard_OStream& S);
};
