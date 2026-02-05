#include <Standard_NullObject.hpp>
#include <TopoDS_Builder.hpp>
#include <TopoDS_FrozenShape.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_TShape.hpp>
#include <TopoDS_TWire.hpp>
#include <TopoDS_UnCompatibleShapes.hpp>
class TopoDS_Shape;

//=======================================================================
// function : MakeShape
// purpose  : Make a Shape from a TShape
//=======================================================================
void TopoDS_Builder::MakeShape(TopoDS_Shape& S, const occ::handle<TopoDS_TShape>& T) const
{
  S.TShape(T);
  S.Location(TopLoc_Location());
  S.Orientation(TopAbs_FORWARD);
}

//=======================================================================
// function : Add
// purpose  : insert aComponent in aShape
//=======================================================================

void TopoDS_Builder::Add(TopoDS_Shape& aShape, const TopoDS_Shape& aComponent) const
{
  // From now the Component cannot be edited
  aComponent.TShape()->Free(false);

  // Note that freezing aComponent before testing if aShape is free
  // prevents from self-insertion
  // but aShape will be frozen when the Exception is raised
  if (aShape.Free())
  {
    static const unsigned int aTb[9] = {
      // COMPOUND to:
      (1 << ((unsigned int)TopAbs_COMPOUND)),
      // COMPSOLID to:
      (1 << ((unsigned int)TopAbs_COMPOUND)),
      // SOLID to:
      (1 << ((unsigned int)TopAbs_COMPOUND)) | (1 << ((unsigned int)TopAbs_COMPSOLID)),
      // SHELL to:
      (1 << ((unsigned int)TopAbs_COMPOUND)) | (1 << ((unsigned int)TopAbs_SOLID)),
      // FACE to:
      (1 << ((unsigned int)TopAbs_COMPOUND)) | (1 << ((unsigned int)TopAbs_SHELL)),
      // WIRE to:
      (1 << ((unsigned int)TopAbs_COMPOUND)) | (1 << ((unsigned int)TopAbs_FACE)),
      // EDGE to:
      (1 << ((unsigned int)TopAbs_COMPOUND)) | (1 << ((unsigned int)TopAbs_SOLID))
        | (1 << ((unsigned int)TopAbs_WIRE)),
      // VERTEX to:
      (1 << ((unsigned int)TopAbs_COMPOUND)) | (1 << ((unsigned int)TopAbs_SOLID))
        | (1 << ((unsigned int)TopAbs_FACE)) | (1 << ((unsigned int)TopAbs_EDGE)),
      // SHAPE to:
      0};
    //
    const unsigned int iC = (unsigned int)aComponent.ShapeType();
    const unsigned int iS = (unsigned int)aShape.ShapeType();
    //
    if ((aTb[iC] & (1 << iS)) != 0)
    {
      NCollection_List<TopoDS_Shape>& L = aShape.TShape()->myShapes;
      L.Append(aComponent);
      TopoDS_Shape& S = L.Last();
      //
      // compute the relative Orientation
      if (aShape.Orientation() == TopAbs_REVERSED)
        S.Reverse();
      //
      // and the Relative Location
      const TopLoc_Location& aLoc = aShape.Location();
      if (!aLoc.IsIdentity())
        S.Move(aLoc.Inverted(), false);
      //
      // Set the TShape as modified.
      aShape.TShape()->Modified(true);
    }
    else
    {
      throw TopoDS_UnCompatibleShapes("TopoDS_Builder::Add");
    }
  }
  else
  {
    throw TopoDS_FrozenShape("TopoDS_Builder::Add");
  }
}

//=======================================================================
// function : Remove
// purpose  : Remove a Shape from an other one
//=======================================================================

void TopoDS_Builder::Remove(TopoDS_Shape& aShape, const TopoDS_Shape& aComponent) const
{
  // check  if aShape  is  not Frozen
  TopoDS_FrozenShape_Raise_if(!aShape.Free(), "TopoDS_Builder::Remove");

  // compute the relative Orientation and Location of aComponent
  TopoDS_Shape S = aComponent;
  if (aShape.Orientation() == TopAbs_REVERSED)
    S.Reverse();
  S.Location(S.Location().Predivided(aShape.Location()), false);

  NCollection_List<TopoDS_Shape>&          L = aShape.TShape()->myShapes;
  NCollection_List<TopoDS_Shape>::Iterator It(L);
  while (It.More())
  {
    if (It.Value() == S)
    {
      L.Remove(It);
      aShape.TShape()->Modified(true);
      break;
    }
    It.Next();
  }
}
