#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>

#include <NCollection_List.hpp>
class TopoDS_Edge;

class LocOpe_FindEdges
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_FindEdges();

  LocOpe_FindEdges(const TopoDS_Shape& FFrom, const TopoDS_Shape& FTo);

  Standard_EXPORT void Set(const TopoDS_Shape& FFrom, const TopoDS_Shape& FTo);

  void InitIterator();

  bool More() const;

  const TopoDS_Edge& EdgeFrom() const;

  const TopoDS_Edge& EdgeTo() const;

  void Next();

private:
  TopoDS_Shape                             myFFrom;
  TopoDS_Shape                             myFTo;
  NCollection_List<TopoDS_Shape>           myLFrom;
  NCollection_List<TopoDS_Shape>           myLTo;
  NCollection_List<TopoDS_Shape>::Iterator myItFrom;
  NCollection_List<TopoDS_Shape>::Iterator myItTo;
};

#include <TopoDS.hpp>

//=================================================================================================

inline LocOpe_FindEdges::LocOpe_FindEdges() = default;

//=================================================================================================

inline LocOpe_FindEdges::LocOpe_FindEdges(const TopoDS_Shape& FFrom, const TopoDS_Shape& FTo)
{
  Set(FFrom, FTo);
}

//=================================================================================================

inline void LocOpe_FindEdges::InitIterator()
{
  myItFrom.Initialize(myLFrom);
  myItTo.Initialize(myLTo);
}

//=================================================================================================

inline bool LocOpe_FindEdges::More() const
{
  return myItFrom.More();
}

//=================================================================================================

inline const TopoDS_Edge& LocOpe_FindEdges::EdgeFrom() const
{
  return TopoDS::Edge(myItFrom.Value());
}

//=================================================================================================

inline const TopoDS_Edge& LocOpe_FindEdges::EdgeTo() const
{
  return TopoDS::Edge(myItTo.Value());
}

//=================================================================================================

inline void LocOpe_FindEdges::Next()
{
  myItFrom.Next();
  myItTo.Next();
}
