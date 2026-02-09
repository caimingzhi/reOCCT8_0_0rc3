#pragma once

#include <Standard.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
class TopoDS_Shape;

class BRepAlgo_AsDes : public Standard_Transient
{

public:
  Standard_EXPORT BRepAlgo_AsDes();

  Standard_EXPORT void Clear();

  Standard_EXPORT void Add(const TopoDS_Shape& S, const TopoDS_Shape& SS);

  Standard_EXPORT void Add(const TopoDS_Shape& S, const NCollection_List<TopoDS_Shape>& SS);

  Standard_EXPORT bool HasAscendant(const TopoDS_Shape& S) const;

  Standard_EXPORT bool HasDescendant(const TopoDS_Shape& S) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Ascendant(const TopoDS_Shape& S) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Descendant(const TopoDS_Shape& S) const;

  Standard_EXPORT NCollection_List<TopoDS_Shape>& ChangeDescendant(const TopoDS_Shape& S);

  Standard_EXPORT void Replace(const TopoDS_Shape& theOldS, const TopoDS_Shape& theNewS);

  Standard_EXPORT void Remove(const TopoDS_Shape& theS);

  Standard_EXPORT bool HasCommonDescendant(const TopoDS_Shape&             S1,
                                           const TopoDS_Shape&             S2,
                                           NCollection_List<TopoDS_Shape>& LC) const;

  DEFINE_STANDARD_RTTIEXT(BRepAlgo_AsDes, Standard_Transient)

private:
  Standard_EXPORT void BackReplace(const TopoDS_Shape&                   theOldS,
                                   const TopoDS_Shape&                   theNewS,
                                   const NCollection_List<TopoDS_Shape>& theL,
                                   const bool                            theInUp);

private:
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> up;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> down;
};
