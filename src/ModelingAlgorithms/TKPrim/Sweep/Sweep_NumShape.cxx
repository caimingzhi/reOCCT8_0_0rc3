#include <Sweep_NumShape.hpp>

Sweep_NumShape::Sweep_NumShape()
    : myType(TopAbs_SHAPE),
      myIndex(0),
      myClosed(false),
      myBegInf(false),
      myEndInf(false)

{
}

Sweep_NumShape::Sweep_NumShape(const int              Index,
                               const TopAbs_ShapeEnum Type,
                               const bool             Closed,
                               const bool             BegInf,
                               const bool             EndInf)
    : myType(Type),
      myIndex(Index),
      myClosed(Closed),
      myBegInf(BegInf),
      myEndInf(EndInf)
{
}

void Sweep_NumShape::Init(const int              Index,
                          const TopAbs_ShapeEnum Type,
                          const bool             Closed,
                          const bool             BegInf,
                          const bool             EndInf)
{
  myIndex  = Index;
  myType   = Type;
  myClosed = Closed;
  myBegInf = BegInf;
  myEndInf = EndInf;
}

TopAbs_Orientation Sweep_NumShape::Orientation() const
{
  if (myType == TopAbs_EDGE)
  {
    return TopAbs_FORWARD;
  }
  else
  {
    if (myIndex == 2)
    {
      return TopAbs_FORWARD;
    }
    else
    {
      return TopAbs_REVERSED;
    }
  }
}
