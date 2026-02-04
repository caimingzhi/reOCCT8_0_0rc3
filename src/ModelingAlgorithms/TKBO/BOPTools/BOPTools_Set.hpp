#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <NCollection_List.hpp>

class BOPTools_Set
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPTools_Set();
  Standard_EXPORT virtual ~BOPTools_Set();

  Standard_EXPORT BOPTools_Set(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  //! Copy constructor.
  Standard_EXPORT BOPTools_Set(const BOPTools_Set& theOther);

  Standard_EXPORT BOPTools_Set& Assign(const BOPTools_Set& Other);

  BOPTools_Set& operator=(const BOPTools_Set& Other) { return Assign(Other); }

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT void Add(const TopoDS_Shape& theS, const TopAbs_ShapeEnum theType);

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT bool IsEqual(const BOPTools_Set& aOther) const;

  bool operator==(const BOPTools_Set& theOther) const { return IsEqual(theOther); }

  size_t GetSum() const { return mySum; }

protected:
  Standard_EXPORT void Clear();

  occ::handle<NCollection_BaseAllocator> myAllocator;
  NCollection_List<TopoDS_Shape>         myShapes;
  TopoDS_Shape                           myShape;
  int                                    myNbShapes;
  size_t                                 mySum;
  int                                    myUpper;
};

namespace std
{
template <>
struct hash<BOPTools_Set>
{
  size_t operator()(const BOPTools_Set& theSet) const noexcept { return theSet.GetSum(); }
};
} // namespace std

