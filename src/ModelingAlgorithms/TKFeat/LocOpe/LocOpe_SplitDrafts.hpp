#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>

class TopoDS_Face;
class TopoDS_Wire;
class gp_Dir;
class gp_Pln;

class LocOpe_SplitDrafts
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_SplitDrafts() = default;

  LocOpe_SplitDrafts(const TopoDS_Shape& S)
      : myShape(S)
  {
  }

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT void Perform(const TopoDS_Face& F,
                               const TopoDS_Wire& W,
                               const gp_Dir&      Extractg,
                               const gp_Pln&      NPlg,
                               const double       Angleg,
                               const gp_Dir&      Extractd,
                               const gp_Pln&      NPld,
                               const double       Angled,
                               const bool         ModifyLeft  = true,
                               const bool         ModifyRight = true);

  Standard_EXPORT void Perform(const TopoDS_Face& F,
                               const TopoDS_Wire& W,
                               const gp_Dir&      Extract,
                               const gp_Pln&      NPl,
                               const double       Angle);

  bool IsDone() const { return !myResult.IsNull(); }

  const TopoDS_Shape& OriginalShape() const { return myShape; }

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ShapesFromShape(
    const TopoDS_Shape& S) const;

private:
  TopoDS_Shape myShape;
  TopoDS_Shape myResult;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
};
