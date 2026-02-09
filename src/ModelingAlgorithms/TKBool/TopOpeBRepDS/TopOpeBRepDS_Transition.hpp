#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopAbs_State.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>

class TopOpeBRepDS_Transition
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_Transition();

  Standard_EXPORT TopOpeBRepDS_Transition(const TopAbs_State     StateBefore,
                                          const TopAbs_State     StateAfter,
                                          const TopAbs_ShapeEnum ShapeBefore = TopAbs_FACE,
                                          const TopAbs_ShapeEnum ShapeAfter  = TopAbs_FACE);

  Standard_EXPORT TopOpeBRepDS_Transition(const TopAbs_Orientation O);

  Standard_EXPORT void Set(const TopAbs_State     StateBefore,
                           const TopAbs_State     StateAfter,
                           const TopAbs_ShapeEnum ShapeBefore = TopAbs_FACE,
                           const TopAbs_ShapeEnum ShapeAfter  = TopAbs_FACE);

  Standard_EXPORT void StateBefore(const TopAbs_State S);

  Standard_EXPORT void StateAfter(const TopAbs_State S);

  Standard_EXPORT void ShapeBefore(const TopAbs_ShapeEnum SE);

  Standard_EXPORT void ShapeAfter(const TopAbs_ShapeEnum SE);

  Standard_EXPORT void Before(const TopAbs_State     S,
                              const TopAbs_ShapeEnum ShapeBefore = TopAbs_FACE);

  Standard_EXPORT void After(const TopAbs_State S, const TopAbs_ShapeEnum ShapeAfter = TopAbs_FACE);

  Standard_EXPORT void Index(const int I);

  Standard_EXPORT void IndexBefore(const int I);

  Standard_EXPORT void IndexAfter(const int I);

  Standard_EXPORT TopAbs_State Before() const;

  Standard_EXPORT TopAbs_ShapeEnum ONBefore() const;

  Standard_EXPORT TopAbs_State After() const;

  Standard_EXPORT TopAbs_ShapeEnum ONAfter() const;

  Standard_EXPORT TopAbs_ShapeEnum ShapeBefore() const;

  Standard_EXPORT TopAbs_ShapeEnum ShapeAfter() const;

  Standard_EXPORT int Index() const;

  Standard_EXPORT int IndexBefore() const;

  Standard_EXPORT int IndexAfter() const;

  Standard_EXPORT void Set(const TopAbs_Orientation O);

  Standard_EXPORT TopAbs_Orientation Orientation(const TopAbs_State     S,
                                                 const TopAbs_ShapeEnum T = TopAbs_FACE) const;

  Standard_EXPORT TopOpeBRepDS_Transition Complement() const;

  Standard_EXPORT bool IsUnknown() const;

private:
  Standard_EXPORT TopAbs_Orientation OrientationON(const TopAbs_State     S,
                                                   const TopAbs_ShapeEnum T) const;

  TopAbs_State     myStateBefore;
  TopAbs_State     myStateAfter;
  TopAbs_ShapeEnum myShapeBefore;
  TopAbs_ShapeEnum myShapeAfter;
  int              myIndexBefore;
  int              myIndexAfter;
};
