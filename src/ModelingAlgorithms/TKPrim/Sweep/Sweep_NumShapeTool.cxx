#include <Standard_ConstructionError.hpp>
#include <Standard_OutOfRange.hpp>
#include <Sweep_NumShapeTool.hpp>

//=================================================================================================

Sweep_NumShapeTool::Sweep_NumShapeTool(const Sweep_NumShape& aShape)
    : myNumShape(aShape)
{
}

//=================================================================================================

int Sweep_NumShapeTool::NbShapes() const
{
  if (myNumShape.Type() == TopAbs_EDGE)
  {
    if (myNumShape.Closed())
    {
      return myNumShape.Index();
    }
    else
    {
      return myNumShape.Index() + 1;
    }
  }
  else
  {
    return 1;
  }
}

//=================================================================================================

int Sweep_NumShapeTool::Index(const Sweep_NumShape& aShape) const
{
  if (aShape.Type() == TopAbs_EDGE)
  {
    return 1;
  }
  else
  {
    if (aShape.Closed())
    {
      return 2;
    }
    else
    {
      return (aShape.Index() + 1);
    }
  }
}

//=================================================================================================

Sweep_NumShape Sweep_NumShapeTool::Shape(const int anIndex) const
{
  if (anIndex == 1)
  {
    return myNumShape;
  }
  else
  {
    return Sweep_NumShape((anIndex - 1), TopAbs_VERTEX, myNumShape.Closed(), false, false);
  }
}

//=================================================================================================

TopAbs_ShapeEnum Sweep_NumShapeTool::Type(const Sweep_NumShape& aShape) const
{
  return aShape.Type();
}

//=================================================================================================

TopAbs_Orientation Sweep_NumShapeTool::Orientation(const Sweep_NumShape& aShape) const
{
  return aShape.Orientation();
}

//=================================================================================================

bool Sweep_NumShapeTool::HasFirstVertex() const
{
  if (myNumShape.Type() == TopAbs_EDGE)
    return !myNumShape.BegInfinite();
  return true;
}

//=================================================================================================

bool Sweep_NumShapeTool::HasLastVertex() const
{
  if (myNumShape.Type() == TopAbs_EDGE)
    return !myNumShape.EndInfinite();
  return true;
}

//=================================================================================================

Sweep_NumShape Sweep_NumShapeTool::FirstVertex() const
{
  if (myNumShape.Type() == TopAbs_EDGE)
  {
    if (HasFirstVertex())
    {
      return Sweep_NumShape(1, TopAbs_VERTEX, myNumShape.Closed(), false, false);
    }
    else
      throw Standard_ConstructionError("infinite Shape");
  }
  return myNumShape;
}

//=================================================================================================

Sweep_NumShape Sweep_NumShapeTool::LastVertex() const
{
  if (myNumShape.Type() == TopAbs_EDGE)
  {
    if (HasLastVertex())
    {
      return Sweep_NumShape(NbShapes() - 1, TopAbs_VERTEX, myNumShape.Closed(), false, false);
    }
    else
      throw Standard_ConstructionError("infinite Shape");
  }
  return myNumShape;
}
