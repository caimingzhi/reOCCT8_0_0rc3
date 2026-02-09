

#include <TopExp_Explorer.hpp>

namespace
{

  inline bool isSameType(const TopAbs_ShapeEnum theType, const TopAbs_ShapeEnum toFind) noexcept
  {
    return toFind == theType;
  }

  inline bool shouldAvoid(const TopAbs_ShapeEnum theType, const TopAbs_ShapeEnum toAvoid) noexcept
  {
    return toAvoid != TopAbs_SHAPE && toAvoid == theType;
  }

  inline bool isMoreComplex(const TopAbs_ShapeEnum theType, const TopAbs_ShapeEnum toFind) noexcept
  {
    return toFind > theType;
  }
} // namespace

TopExp_Explorer::TopExp_Explorer() noexcept
    : myStack(20),
      toFind(TopAbs_SHAPE),
      toAvoid(TopAbs_SHAPE),
      hasMore(false)
{
}

TopExp_Explorer::TopExp_Explorer(const TopoDS_Shape&    S,
                                 const TopAbs_ShapeEnum ToFind,
                                 const TopAbs_ShapeEnum ToAvoid)
    : myStack(20),
      toFind(ToFind),
      toAvoid(ToAvoid),
      hasMore(false)
{
  Init(S, ToFind, ToAvoid);
}

TopExp_Explorer::~TopExp_Explorer()
{
  Clear();
}

void TopExp_Explorer::Init(const TopoDS_Shape&    S,
                           const TopAbs_ShapeEnum ToFind,
                           const TopAbs_ShapeEnum ToAvoid)
{
  Clear();

  myShape = S;
  toFind  = ToFind;
  toAvoid = ToAvoid;

  if (S.IsNull())
  {
    hasMore = false;
    return;
  }

  if (toFind == TopAbs_SHAPE)
    hasMore = false;
  else
  {
    TopAbs_ShapeEnum ty = S.ShapeType();

    if (ty > toFind)
    {
      hasMore = false;
    }
    else if (!isSameType(ty, toFind))
    {
      hasMore = true;
      Next();
    }
    else
    {
      hasMore = true;
    }
  }
}

void TopExp_Explorer::Next()
{
  if (myStack.IsEmpty())
  {
    TopAbs_ShapeEnum ty = myShape.ShapeType();

    if (isSameType(ty, toFind))
    {
      hasMore = false;
      return;
    }
    else if (shouldAvoid(ty, toAvoid))
    {
      hasMore = false;
      return;
    }
    else
    {
      myStack.Append(TopoDS_Iterator(myShape));
    }
  }
  else
    myStack.ChangeLast().Next();

  for (;;)
  {
    TopoDS_Iterator& aTopIter = myStack.ChangeLast();

    if (aTopIter.More())
    {
      const TopoDS_Shape&    aShapTop = aTopIter.Value();
      const TopAbs_ShapeEnum ty       = aShapTop.ShapeType();

      if (isSameType(ty, toFind))
      {
        hasMore = true;
        return;
      }
      else if (isMoreComplex(ty, toFind) && !shouldAvoid(ty, toAvoid))
      {
        myStack.Append(TopoDS_Iterator(aShapTop));
      }
      else
      {
        aTopIter.Next();
      }
    }
    else
    {
      myStack.EraseLast();
      if (myStack.IsEmpty())
        break;
      myStack.ChangeLast().Next();
    }
  }
  hasMore = false;
}

const TopoDS_Shape& TopExp_Explorer::Current() const noexcept
{
  return myStack.IsEmpty() ? myShape : myStack.Last().Value();
}

int TopExp_Explorer::Depth() const noexcept
{
  return myStack.Length();
}

void TopExp_Explorer::Clear()
{
  hasMore = false;
  myStack.Clear();
}
