#include <TNaming_IteratorOnShapesSet.hpp>
#include <TNaming_ShapesSet.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>

TNaming_ShapesSet::TNaming_ShapesSet(const TopoDS_Shape& CS, const TopAbs_ShapeEnum Type)
{
  if (CS.IsNull())
    return;
#ifdef OCCT_DEBUG_INT
  std::cout << "ShapeSet: CS TShape = " << CS.TShape() << " Type = " << Type << std::endl;
#endif
  if (Type == TopAbs_SHAPE)
  {
    if (CS.ShapeType() == TopAbs_SOLID || CS.ShapeType() == TopAbs_FACE
        || CS.ShapeType() == TopAbs_EDGE || CS.ShapeType() == TopAbs_VERTEX)
    {
      Add(CS);
    }
    else
    {
      for (TopoDS_Iterator it(CS); it.More(); it.Next())
      {
        Add(it.Value());
      }
    }
  }
  else
  {

    if (Type > CS.ShapeType())
    {
      for (TopExp_Explorer exp(CS, Type); exp.More(); exp.Next())
      {
        Add(exp.Current());
#ifdef OCCT_DEBUG_INT
        std::cout << "ShapeSet: sub-shape TShape = " << exp.Current().TShape() << std::endl;
#endif
      }
    }
    else
    {

      Add(CS);
    }
  }
}

void TNaming_ShapesSet::Add(const TNaming_ShapesSet& Shapes)
{
  TNaming_IteratorOnShapesSet it(Shapes);
  for (; it.More(); it.Next())
  {
    myMap.Add(it.Value());
  }
}

void TNaming_ShapesSet::Filter(const TNaming_ShapesSet& Shapes)
{

  TNaming_ShapesSet           ToRemove;
  TNaming_IteratorOnShapesSet it(*this);
  for (; it.More(); it.Next())
  {
    const TopoDS_Shape& S = it.Value();
    if (!Shapes.Contains(S))
    {
      ToRemove.Add(S);
    }
  }
  Remove(ToRemove);
}

void TNaming_ShapesSet::Remove(const TNaming_ShapesSet& Shapes)
{
  TNaming_IteratorOnShapesSet it(Shapes);
  for (; it.More(); it.Next())
  {
    myMap.Remove(it.Value());
  }
}
