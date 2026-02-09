#pragma once

#include <NCollection_Vector.hpp>
#include <TopAbs.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>

class TopExp_Explorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopExp_Explorer() noexcept;

  Standard_EXPORT TopExp_Explorer(const TopoDS_Shape&    S,
                                  const TopAbs_ShapeEnum ToFind,
                                  const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE);

  Standard_EXPORT void Init(const TopoDS_Shape&    S,
                            const TopAbs_ShapeEnum ToFind,
                            const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE);

  bool More() const noexcept { return hasMore; }

  Standard_EXPORT void Next();

  const TopoDS_Shape& Value() const noexcept { return Current(); }

  Standard_EXPORT const TopoDS_Shape& Current() const noexcept;

  void ReInit() { Init(myShape, toFind, toAvoid); }

  const TopoDS_Shape& ExploredShape() const noexcept { return myShape; }

  Standard_EXPORT int Depth() const noexcept;

  Standard_EXPORT void Clear();

  Standard_EXPORT ~TopExp_Explorer();

private:
  NCollection_Vector<TopoDS_Iterator> myStack;
  TopoDS_Shape                        myShape;
  TopAbs_ShapeEnum                    toFind;
  TopAbs_ShapeEnum                    toAvoid;
  bool                                hasMore;
};
