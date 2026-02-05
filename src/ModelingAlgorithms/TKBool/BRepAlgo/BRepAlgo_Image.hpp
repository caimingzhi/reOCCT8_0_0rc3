#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_ShapeEnum.hpp>
class TopoDS_Shape;

//! Stores link between a shape <S> and a shape <NewS>
//! obtained from <S>. <NewS> is an image of <S>.
class BRepAlgo_Image
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgo_Image();

  Standard_EXPORT void SetRoot(const TopoDS_Shape& S);

  //! Links <NewS> as image of <OldS>.
  Standard_EXPORT void Bind(const TopoDS_Shape& OldS, const TopoDS_Shape& NewS);

  //! Links <NewS> as image of <OldS>.
  Standard_EXPORT void Bind(const TopoDS_Shape& OldS, const NCollection_List<TopoDS_Shape>& NewS);

  //! Add <NewS> to the image of <OldS>.
  Standard_EXPORT void Add(const TopoDS_Shape& OldS, const TopoDS_Shape& NewS);

  //! Add <NewS> to the image of <OldS>.
  Standard_EXPORT void Add(const TopoDS_Shape& OldS, const NCollection_List<TopoDS_Shape>& NewS);

  Standard_EXPORT void Clear();

  //! Remove <S> to set of images.
  Standard_EXPORT void Remove(const TopoDS_Shape& S);

  //! Removes the root <theRoot> from the list of roots and up and down maps.
  Standard_EXPORT void RemoveRoot(const TopoDS_Shape& Root);

  //! Replaces the <OldRoot> with the <NewRoot>, so all images
  //! of the <OldRoot> become the images of the <NewRoot>.
  //! The <OldRoot> is removed.
  Standard_EXPORT void ReplaceRoot(const TopoDS_Shape& OldRoot, const TopoDS_Shape& NewRoot);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Roots() const;

  Standard_EXPORT bool IsImage(const TopoDS_Shape& S) const;

  //! Returns the generator of <S>
  Standard_EXPORT const TopoDS_Shape& ImageFrom(const TopoDS_Shape& S) const;

  //! Returns the upper generator of <S>
  Standard_EXPORT const TopoDS_Shape& Root(const TopoDS_Shape& S) const;

  Standard_EXPORT bool HasImage(const TopoDS_Shape& S) const;

  //! Returns the Image of <S>.
  //! Returns <S> in the list if HasImage(S) is false.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Image(const TopoDS_Shape& S) const;

  //! Stores in <L> the images of images of...images of <S>.
  //! <L> contains only <S> if HasImage(S) is false.
  Standard_EXPORT void LastImage(const TopoDS_Shape& S, NCollection_List<TopoDS_Shape>& L) const;

  //! Keeps only the link between roots and lastimage.
  Standard_EXPORT void Compact();

  //! Deletes in the images the shape of type <ShapeType>
  //! which are not in <S>.
  //! Warning: Compact() must be call before.
  Standard_EXPORT void Filter(const TopoDS_Shape& S, const TopAbs_ShapeEnum ShapeType);

private:
  NCollection_List<TopoDS_Shape>                                                             roots;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>                   up;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> down;
};
