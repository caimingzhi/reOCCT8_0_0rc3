#include <BRepBuilderAPI_ModifyShape.hpp>
#include <BRepTools_Modification.hpp>
#include <Standard_NullObject.hpp>
#include <TopoDS_Shape.hpp>

//=================================================================================================

BRepBuilderAPI_ModifyShape::BRepBuilderAPI_ModifyShape() = default;

//=================================================================================================

BRepBuilderAPI_ModifyShape::BRepBuilderAPI_ModifyShape(const TopoDS_Shape& S)
    : myModifier(S),
      myInitialShape(S)
{
}

//=================================================================================================

BRepBuilderAPI_ModifyShape::BRepBuilderAPI_ModifyShape(const occ::handle<BRepTools_Modification>& M)
{
  myModification = M;
}

//=================================================================================================

BRepBuilderAPI_ModifyShape::BRepBuilderAPI_ModifyShape(const TopoDS_Shape&                        S,
                                                       const occ::handle<BRepTools_Modification>& M)
    : myModifier(S),
      myInitialShape(S)
{
  myModification = M;
  DoModif();
}

//=================================================================================================

void BRepBuilderAPI_ModifyShape::DoModif()
{
  if (myInitialShape.IsNull() || myModification.IsNull())
  {
    throw Standard_NullObject();
  }
  myModifier.Perform(myModification);
  if (myModifier.IsDone())
  {
    Done();
    myShape = myModifier.ModifiedShape(myInitialShape);
  }
  else
  {
    NotDone();
  }
}

//=================================================================================================

void BRepBuilderAPI_ModifyShape::DoModif(const TopoDS_Shape& S)
{
  if (!S.IsEqual(myInitialShape) || !IsDone())
  {
    myInitialShape = S;
    myModifier.Init(S);
    DoModif();
  }
}

//=================================================================================================

void BRepBuilderAPI_ModifyShape::DoModif(const occ::handle<BRepTools_Modification>& M)
{
  myModification = M;
  DoModif();
}

//=================================================================================================

void BRepBuilderAPI_ModifyShape::DoModif(const TopoDS_Shape&                        S,
                                         const occ::handle<BRepTools_Modification>& M)
{
  myInitialShape = S;
  myModifier.Init(S);
  myModification = M;
  DoModif();
}

//=================================================================================================

TopoDS_Shape BRepBuilderAPI_ModifyShape::ModifiedShape(const TopoDS_Shape& S) const
{
  return myModifier.ModifiedShape(S);
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepBuilderAPI_ModifyShape::Modified(const TopoDS_Shape& F)
{
  myGenerated.Clear();
  myGenerated.Append(myModifier.ModifiedShape(F));
  return myGenerated;
}
