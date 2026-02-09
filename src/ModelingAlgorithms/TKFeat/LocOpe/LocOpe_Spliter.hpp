#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class LocOpe_WiresOnShape;

class LocOpe_Spliter
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_Spliter();

  LocOpe_Spliter(const TopoDS_Shape& S);

  void Init(const TopoDS_Shape& S);

  Standard_EXPORT void Perform(const occ::handle<LocOpe_WiresOnShape>& PW);

  bool IsDone() const;

  const TopoDS_Shape& ResultingShape() const;

  const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& DirectLeft() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Left() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& DescendantShapes(const TopoDS_Shape& S);

private:
  TopoDS_Shape myShape;
  bool         myDone;
  TopoDS_Shape myRes;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
  NCollection_List<TopoDS_Shape> myDLeft;
  NCollection_List<TopoDS_Shape> myLeft;
};

#include <StdFail_NotDone.hpp>

inline LocOpe_Spliter::LocOpe_Spliter()
    : myDone(false)
{
}

inline LocOpe_Spliter::LocOpe_Spliter(const TopoDS_Shape& S)
    : myShape(S),
      myDone(false)
{
}

inline void LocOpe_Spliter::Init(const TopoDS_Shape& S)
{
  myShape = S;
  myDone  = false;
}

inline bool LocOpe_Spliter::IsDone() const
{
  return myDone;
}

inline const TopoDS_Shape& LocOpe_Spliter::Shape() const
{
  return myShape;
}

inline const TopoDS_Shape& LocOpe_Spliter::ResultingShape() const
{
  if (!myDone)
  {
    throw StdFail_NotDone();
  }
  return myRes;
}
