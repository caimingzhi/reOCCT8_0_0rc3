#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
class TopOpeBRepBuild_ShapeSet;
class TopOpeBRepBuild_BlockIterator;
class TopoDS_Shape;

class TopOpeBRepBuild_BlockBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_BlockBuilder();

  Standard_EXPORT TopOpeBRepBuild_BlockBuilder(TopOpeBRepBuild_ShapeSet& SS);

  Standard_EXPORT void MakeBlock(TopOpeBRepBuild_ShapeSet& SS);

  Standard_EXPORT void InitBlock();

  Standard_EXPORT bool MoreBlock() const;

  Standard_EXPORT void NextBlock();

  Standard_EXPORT TopOpeBRepBuild_BlockIterator BlockIterator() const;

  //! Returns the current element of <BI>.
  Standard_EXPORT const TopoDS_Shape& Element(const TopOpeBRepBuild_BlockIterator& BI) const;

  Standard_EXPORT const TopoDS_Shape& Element(const int I) const;

  Standard_EXPORT int Element(const TopoDS_Shape& S) const;

  Standard_EXPORT bool ElementIsValid(const TopOpeBRepBuild_BlockIterator& BI) const;

  Standard_EXPORT bool ElementIsValid(const int I) const;

  Standard_EXPORT int AddElement(const TopoDS_Shape& S);

  Standard_EXPORT void SetValid(const TopOpeBRepBuild_BlockIterator& BI, const bool isvalid);

  Standard_EXPORT void SetValid(const int I, const bool isvalid);

  Standard_EXPORT bool CurrentBlockIsRegular();

private:
  NCollection_DataMap<int, int>        myOrientedShapeMapIsValid;
  NCollection_IndexedMap<TopoDS_Shape> myOrientedShapeMap;
  NCollection_Sequence<int>            myBlocks;
  int                                  myBlockIndex;
  bool                                 myIsDone;
  NCollection_Sequence<int>            myBlocksIsRegular;
};

