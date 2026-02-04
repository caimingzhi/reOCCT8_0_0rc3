#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_State.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Shape;

class TopOpeBRepDS_ShapeWithState
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_ShapeWithState();

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Part(const TopAbs_State aState) const;

  Standard_EXPORT void AddPart(const TopoDS_Shape& aShape, const TopAbs_State aState);

  Standard_EXPORT void AddParts(const NCollection_List<TopoDS_Shape>& aListOfShape,
                                const TopAbs_State                    aState);

  Standard_EXPORT void SetState(const TopAbs_State aState);

  Standard_EXPORT TopAbs_State State() const;

  Standard_EXPORT void SetIsSplitted(const bool anIsSplitted);

  Standard_EXPORT bool IsSplitted() const;

private:
  NCollection_List<TopoDS_Shape> myPartIn;
  NCollection_List<TopoDS_Shape> myPartOut;
  NCollection_List<TopoDS_Shape> myPartOn;
  TopAbs_State                   myState;
  bool                           myIsSplitted;
};

