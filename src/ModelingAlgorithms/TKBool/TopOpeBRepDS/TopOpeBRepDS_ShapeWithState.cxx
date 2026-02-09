#include <TopOpeBRepDS_ShapeWithState.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

TopOpeBRepDS_ShapeWithState::TopOpeBRepDS_ShapeWithState()
    : myState(TopAbs_UNKNOWN),
      myIsSplitted(false)
{
}

const NCollection_List<TopoDS_Shape>& TopOpeBRepDS_ShapeWithState::Part(
  const TopAbs_State aState) const
{
  static NCollection_List<TopoDS_Shape> myEmptyListOfShape;
  switch (aState)
  {
    case TopAbs_IN:
      return myPartIn;
    case TopAbs_OUT:
      return myPartOut;
    case TopAbs_ON:
      return myPartOn;
    default:
      return myEmptyListOfShape;
  }
}

void TopOpeBRepDS_ShapeWithState::AddPart(const TopoDS_Shape& aShape, const TopAbs_State aState)
{
  switch (aState)
  {
    case TopAbs_IN:
      myPartIn.Append(aShape);
      break;
    case TopAbs_OUT:
      myPartOut.Append(aShape);
      break;
    case TopAbs_ON:
      myPartOn.Append(aShape);
      break;
    default:
      break;
  }
}

void TopOpeBRepDS_ShapeWithState::AddParts(const NCollection_List<TopoDS_Shape>& aListOfShape,
                                           const TopAbs_State                    aState)
{
  NCollection_List<TopoDS_Shape>::Iterator anIt(aListOfShape);

  switch (aState)
  {
    case TopAbs_IN:
      for (; anIt.More(); anIt.Next())
      {
        myPartIn.Append(anIt.Value());
      }
      break;
    case TopAbs_OUT:
      for (; anIt.More(); anIt.Next())
      {
        myPartOut.Append(anIt.Value());
      }
      break;
    case TopAbs_ON:
      for (; anIt.More(); anIt.Next())
      {
        myPartOn.Append(anIt.Value());
      }
      break;

    default:
      break;
  }
}

void TopOpeBRepDS_ShapeWithState::SetState(const TopAbs_State aState)
{
  myState = aState;
}

TopAbs_State TopOpeBRepDS_ShapeWithState::State() const
{
  return myState;
}

void TopOpeBRepDS_ShapeWithState::SetIsSplitted(const bool aFlag)
{
  myIsSplitted = aFlag;
}

bool TopOpeBRepDS_ShapeWithState::IsSplitted() const
{
  return myIsSplitted;
}
