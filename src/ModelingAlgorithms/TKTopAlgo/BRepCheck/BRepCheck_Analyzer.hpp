#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <BRepCheck_Result.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopAbs_ShapeEnum.hpp>
class BRepCheck_Result;

class BRepCheck_Analyzer
{
public:
  DEFINE_STANDARD_ALLOC

  BRepCheck_Analyzer(const TopoDS_Shape& S,
                     const bool          GeomControls  = true,
                     const bool          theIsParallel = false,
                     const bool          theIsExact    = false)
      : myIsParallel(theIsParallel),
        myIsExact(theIsExact)
  {
    Init(S, GeomControls);
  }

  Standard_EXPORT void Init(const TopoDS_Shape& S, const bool GeomControls = true);

  void SetExactMethod(const bool theIsExact) { myIsExact = theIsExact; }

  bool IsExactMethod() { return myIsExact; }

  void SetParallel(const bool theIsParallel) { myIsParallel = theIsParallel; }

  bool IsParallel() { return myIsParallel; }

  Standard_EXPORT bool IsValid(const TopoDS_Shape& S) const;

  bool IsValid() const { return IsValid(myShape); }

  const occ::handle<BRepCheck_Result>& Result(const TopoDS_Shape& theSubS) const
  {
    return myMap.FindFromKey(theSubS);
  }

private:
  Standard_EXPORT void Put(const TopoDS_Shape& S, const bool Gctrl);

  Standard_EXPORT void Perform();

  Standard_EXPORT bool ValidSub(const TopoDS_Shape& S, const TopAbs_ShapeEnum SubType) const;

private:
  TopoDS_Shape                                                            myShape;
  NCollection_IndexedDataMap<TopoDS_Shape, occ::handle<BRepCheck_Result>> myMap;
  bool                                                                    myIsParallel;
  bool                                                                    myIsExact;
};
