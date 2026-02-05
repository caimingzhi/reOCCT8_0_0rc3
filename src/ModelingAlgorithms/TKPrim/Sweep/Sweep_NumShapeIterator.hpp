#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Sweep_NumShape.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>

//! This class provides iteration services required by
//! the Swept Primitives for a Directing NumShape
//! Line.
class Sweep_NumShapeIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Sweep_NumShapeIterator();

  //! Reset the NumShapeIterator on sub-shapes of <aShape>.
  Standard_EXPORT void Init(const Sweep_NumShape& aShape);

  //! Returns True if there is a current sub-shape.
  bool More() const;

  //! Moves to the next sub-shape.
  Standard_EXPORT void Next();

  //! Returns the current sub-shape.
  const Sweep_NumShape& Value() const;

  //! Returns the orientation of the current sub-shape.
  TopAbs_Orientation Orientation() const;

private:
  Sweep_NumShape     myNumShape;
  Sweep_NumShape     myCurrentNumShape;
  int                myCurrentRange;
  bool               myMore;
  TopAbs_Orientation myCurrentOrientation;
};

inline bool Sweep_NumShapeIterator::More() const
{
  return myMore;
}

//=================================================================================================

inline const Sweep_NumShape& Sweep_NumShapeIterator::Value() const
{
  return myCurrentNumShape;
}

//=================================================================================================

inline TopAbs_Orientation Sweep_NumShapeIterator::Orientation() const
{
  return myCurrentOrientation;
}
