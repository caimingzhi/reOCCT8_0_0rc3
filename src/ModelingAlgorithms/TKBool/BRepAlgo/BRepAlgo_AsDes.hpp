#pragma once

#include <Standard.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
class TopoDS_Shape;

//! SD to store descendants and ascendants of Shapes.
class BRepAlgo_AsDes : public Standard_Transient
{

public:
  //! Creates an empty AsDes.
  Standard_EXPORT BRepAlgo_AsDes();

  Standard_EXPORT void Clear();

  //! Stores <SS> as a futur subshape of <S>.
  Standard_EXPORT void Add(const TopoDS_Shape& S, const TopoDS_Shape& SS);

  //! Stores <SS> as futurs SubShapes of <S>.
  Standard_EXPORT void Add(const TopoDS_Shape& S, const NCollection_List<TopoDS_Shape>& SS);

  Standard_EXPORT bool HasAscendant(const TopoDS_Shape& S) const;

  Standard_EXPORT bool HasDescendant(const TopoDS_Shape& S) const;

  //! Returns the Shape containing <S>.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Ascendant(const TopoDS_Shape& S) const;

  //! Returns futur subhapes of <S>.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Descendant(const TopoDS_Shape& S) const;

  //! Returns futur subhapes of <S>.
  Standard_EXPORT NCollection_List<TopoDS_Shape>& ChangeDescendant(const TopoDS_Shape& S);

  //! Replace theOldS by theNewS.
  //! theOldS disappear from this.
  Standard_EXPORT void Replace(const TopoDS_Shape& theOldS, const TopoDS_Shape& theNewS);

  //! Remove theS from me.
  Standard_EXPORT void Remove(const TopoDS_Shape& theS);

  //! Returns True if (S1> and <S2> has common
  //! Descendants. Stores in <LC> the Commons Descendants.
  Standard_EXPORT bool HasCommonDescendant(const TopoDS_Shape&             S1,
                                           const TopoDS_Shape&             S2,
                                           NCollection_List<TopoDS_Shape>& LC) const;

  DEFINE_STANDARD_RTTIEXT(BRepAlgo_AsDes, Standard_Transient)

private:
  //! Replace theOldS by theNewS.
  //! theOldS disappear from this.
  Standard_EXPORT void BackReplace(const TopoDS_Shape&                   theOldS,
                                   const TopoDS_Shape&                   theNewS,
                                   const NCollection_List<TopoDS_Shape>& theL,
                                   const bool                            theInUp);

private:
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> up;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> down;
};
