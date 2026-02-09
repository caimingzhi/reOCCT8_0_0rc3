#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Sweep_NumShape.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>

class Sweep_NumShapeIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Sweep_NumShapeIterator();

  Standard_EXPORT void Init(const Sweep_NumShape& aShape);

  bool More() const;

  Standard_EXPORT void Next();

  const Sweep_NumShape& Value() const;

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

inline const Sweep_NumShape& Sweep_NumShapeIterator::Value() const
{
  return myCurrentNumShape;
}

inline TopAbs_Orientation Sweep_NumShapeIterator::Orientation() const
{
  return myCurrentOrientation;
}
