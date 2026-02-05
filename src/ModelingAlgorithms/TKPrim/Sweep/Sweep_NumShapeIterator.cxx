#include <Standard_NoSuchObject.hpp>
#include <Sweep_NumShapeIterator.hpp>

//=================================================================================================

Sweep_NumShapeIterator::Sweep_NumShapeIterator()
    : myNumShape(0, TopAbs_SHAPE),
      myCurrentNumShape(0, TopAbs_SHAPE),
      myCurrentRange(0),
      myMore(false)
{
}

//=================================================================================================

void Sweep_NumShapeIterator::Init(const Sweep_NumShape& aShape)
{
  myNumShape = aShape;
  if (myNumShape.Type() == TopAbs_EDGE)
  {
    int nbvert = myNumShape.Index();
    myMore     = (nbvert >= 1);
    if (myMore)
    {
      myCurrentRange    = 1;
      myCurrentNumShape = Sweep_NumShape(1, TopAbs_VERTEX, myNumShape.Closed(), false, false);
      if (nbvert == 1)
      {
        if (myNumShape.BegInfinite())
        {
          myCurrentOrientation = TopAbs_REVERSED;
        }
        else
        {
          myCurrentOrientation = TopAbs_FORWARD;
        }
      }
      else
      {
        myCurrentOrientation = TopAbs_FORWARD;
      }
    }
  }
}

//=================================================================================================

void Sweep_NumShapeIterator::Next()
{
  myCurrentRange++;
  myMore = myCurrentRange <= myNumShape.Index();
  if (myMore)
  {
    if (myNumShape.Type() == TopAbs_EDGE)
    {
      myCurrentNumShape =
        Sweep_NumShape(myCurrentRange, TopAbs_VERTEX, myNumShape.Closed(), false, false);
      myCurrentOrientation = TopAbs_REVERSED;
    }
  }
}
