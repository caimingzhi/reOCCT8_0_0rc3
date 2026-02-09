#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopExp_Explorer.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Face;
class TopoDS_Edge;

class BRepGProp_Domain
{
public:
  DEFINE_STANDARD_ALLOC

  BRepGProp_Domain();

  BRepGProp_Domain(const TopoDS_Face& F);

  void Init(const TopoDS_Face& F);

  bool More();

  void Init();

  const TopoDS_Edge& Value();

  Standard_EXPORT void Next();

private:
  TopExp_Explorer myExplorer;
};

#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>

inline BRepGProp_Domain::BRepGProp_Domain() = default;

inline BRepGProp_Domain::BRepGProp_Domain(const TopoDS_Face& F)
    : myExplorer(F.Oriented(TopAbs_FORWARD), TopAbs_EDGE)
{
}

inline void BRepGProp_Domain::Init(const TopoDS_Face& F)
{
  myExplorer.Init(F.Oriented(TopAbs_FORWARD), TopAbs_EDGE);
}

inline bool BRepGProp_Domain::More()
{
  return myExplorer.More();
}

inline void BRepGProp_Domain::Init()
{
  myExplorer.ReInit();
}

inline const TopoDS_Edge& BRepGProp_Domain::Value()
{
  return TopoDS::Edge(myExplorer.Current());
}
