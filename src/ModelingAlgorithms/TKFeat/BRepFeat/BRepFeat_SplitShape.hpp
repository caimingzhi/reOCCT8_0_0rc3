#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <LocOpe_Spliter.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Sequence.hpp>

class LocOpe_WiresOnShape;
class TopoDS_Shape;
class TopoDS_Wire;
class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Compound;

class BRepFeat_SplitShape : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  BRepFeat_SplitShape();

  BRepFeat_SplitShape(const TopoDS_Shape& S);

  bool Add(const NCollection_Sequence<TopoDS_Shape>& theEdges);

  void Init(const TopoDS_Shape& S);

  void SetCheckInterior(const bool ToCheckInterior);

  void Add(const TopoDS_Wire& W, const TopoDS_Face& F);

  void Add(const TopoDS_Edge& E, const TopoDS_Face& F);

  void Add(const TopoDS_Compound& Comp, const TopoDS_Face& F);

  void Add(const TopoDS_Edge& E, const TopoDS_Edge& EOn);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& DirectLeft() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Left() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Right() const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& S) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& F) override;

private:
  LocOpe_Spliter                   mySShape;
  occ::handle<LocOpe_WiresOnShape> myWOnShape;

  mutable NCollection_List<TopoDS_Shape> myRight;
};

#include <LocOpe_WiresOnShape.hpp>

inline BRepFeat_SplitShape::BRepFeat_SplitShape() = default;

inline BRepFeat_SplitShape::BRepFeat_SplitShape(const TopoDS_Shape& S)
    : mySShape(S)
{
  myWOnShape = new LocOpe_WiresOnShape(S);
}

inline bool BRepFeat_SplitShape::Add(const NCollection_Sequence<TopoDS_Shape>& theEdges)
{
  return myWOnShape->Add(theEdges);
}

inline void BRepFeat_SplitShape::Init(const TopoDS_Shape& S)
{
  mySShape.Init(S);
  if (myWOnShape.IsNull())
  {
    myWOnShape = new LocOpe_WiresOnShape(S);
  }
  else
  {
    myWOnShape->Init(S);
  }
}

inline void BRepFeat_SplitShape::SetCheckInterior(const bool ToCheckInterior)
{
  myWOnShape->SetCheckInterior(ToCheckInterior);
}

inline void BRepFeat_SplitShape::Add(const TopoDS_Wire& W, const TopoDS_Face& F)
{
  myWOnShape->Bind(W, F);
}

inline void BRepFeat_SplitShape::Add(const TopoDS_Edge& E, const TopoDS_Face& F)
{
  myWOnShape->Bind(E, F);
}

inline void BRepFeat_SplitShape::Add(const TopoDS_Compound& Comp, const TopoDS_Face& F)
{
  myWOnShape->Bind(Comp, F);
}

inline void BRepFeat_SplitShape::Add(const TopoDS_Edge& E, const TopoDS_Edge& EOn)
{
  myWOnShape->Bind(E, EOn);
}
