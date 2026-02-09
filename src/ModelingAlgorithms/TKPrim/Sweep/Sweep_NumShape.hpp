#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_Orientation.hpp>

class Sweep_NumShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Sweep_NumShape();

  Standard_EXPORT Sweep_NumShape(const int              Index,
                                 const TopAbs_ShapeEnum Type,
                                 const bool             Closed = false,
                                 const bool             BegInf = false,
                                 const bool             EndInf = false);

  Standard_EXPORT void Init(const int              Index,
                            const TopAbs_ShapeEnum Type,
                            const bool             Closed = false,
                            const bool             BegInf = false,
                            const bool             EndInf = false);

  int Index() const;

  TopAbs_ShapeEnum Type() const;

  bool Closed() const;

  bool BegInfinite() const;

  bool EndInfinite() const;

  Standard_EXPORT TopAbs_Orientation Orientation() const;

private:
  TopAbs_ShapeEnum myType;
  int              myIndex;
  bool             myClosed;
  bool             myBegInf;
  bool             myEndInf;
};

inline int Sweep_NumShape::Index() const
{
  return myIndex;
}

inline TopAbs_ShapeEnum Sweep_NumShape::Type() const
{
  return myType;
}

inline bool Sweep_NumShape::Closed() const
{
  return myClosed;
}

inline bool Sweep_NumShape::BegInfinite() const
{
  return myBegInf;
}

inline bool Sweep_NumShape::EndInfinite() const
{
  return myEndInf;
}
