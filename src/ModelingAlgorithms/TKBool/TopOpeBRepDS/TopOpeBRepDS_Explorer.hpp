#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Integer.hpp>
class TopOpeBRepDS_HDataStructure;
class TopoDS_Shape;
class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Vertex;

class TopOpeBRepDS_Explorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_Explorer();

  Standard_EXPORT TopOpeBRepDS_Explorer(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                        const TopAbs_ShapeEnum T        = TopAbs_SHAPE,
                                        const bool             findkeep = true);

  Standard_EXPORT void Init(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                            const TopAbs_ShapeEnum                          T        = TopAbs_SHAPE,
                            const bool                                      findkeep = true);

  Standard_EXPORT TopAbs_ShapeEnum Type() const;

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const TopoDS_Shape& Current() const;

  Standard_EXPORT int Index() const;

  Standard_EXPORT const TopoDS_Face& Face() const;

  Standard_EXPORT const TopoDS_Edge& Edge() const;

  Standard_EXPORT const TopoDS_Vertex& Vertex() const;

private:
  Standard_EXPORT void Find();

  occ::handle<TopOpeBRepDS_HDataStructure> myHDS;
  TopAbs_ShapeEnum                         myT;
  int                                      myI;
  int                                      myN;
  bool                                     myB;
  bool                                     myFK;
};

