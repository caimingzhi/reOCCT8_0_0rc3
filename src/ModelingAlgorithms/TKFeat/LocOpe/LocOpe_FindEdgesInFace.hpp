#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopoDS_Face.hpp>
#include <NCollection_List.hpp>
class TopoDS_Edge;

class LocOpe_FindEdgesInFace
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_FindEdgesInFace();

  LocOpe_FindEdgesInFace(const TopoDS_Shape& S, const TopoDS_Face& F);

  Standard_EXPORT void Set(const TopoDS_Shape& S, const TopoDS_Face& F);

  void Init();

  bool More() const;

  const TopoDS_Edge& Edge() const;

  void Next();

private:
  TopoDS_Shape                             myShape;
  TopoDS_Face                              myFace;
  NCollection_List<TopoDS_Shape>           myList;
  NCollection_List<TopoDS_Shape>::Iterator myIt;
};

#include <TopoDS.hpp>

inline LocOpe_FindEdgesInFace::LocOpe_FindEdgesInFace() = default;

inline LocOpe_FindEdgesInFace::LocOpe_FindEdgesInFace(const TopoDS_Shape& S, const TopoDS_Face& F)
{
  Set(S, F);
}

inline void LocOpe_FindEdgesInFace::Init()
{
  myIt.Initialize(myList);
}

inline bool LocOpe_FindEdgesInFace::More() const
{
  return myIt.More();
}

inline const TopoDS_Edge& LocOpe_FindEdgesInFace::Edge() const
{
  return TopoDS::Edge(myIt.Value());
}

inline void LocOpe_FindEdgesInFace::Next()
{
  myIt.Next();
}
