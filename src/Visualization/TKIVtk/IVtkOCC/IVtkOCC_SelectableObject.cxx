#include <IVtkOCC_SelectableObject.hpp>

#include <AIS_Shape.hpp>
#include <BRepBndLib.hpp>
#include <Message.hpp>
#include <StdPrs_ToolTriangulatedShape.hpp>
#include <Select3D_SensitiveBox.hpp>
#include <SelectMgr_Selection.hpp>
#include <Standard_ErrorHandler.hpp>
#include <StdSelect_BRepOwner.hpp>
#include <StdSelect_BRepSelectionTool.hpp>
#include <TopoDS_Iterator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IVtkOCC_SelectableObject, SelectMgr_SelectableObject)

IVtkOCC_SelectableObject::IVtkOCC_SelectableObject(const IVtkOCC_Shape::Handle& theShape)
    : SelectMgr_SelectableObject(PrsMgr_TOP_AllView),
      myShape(theShape)
{
  if (!myShape.IsNull())
  {
    myShape->SetSelectableObject(this);
  }
}

IVtkOCC_SelectableObject::IVtkOCC_SelectableObject()
    : SelectMgr_SelectableObject(PrsMgr_TOP_AllView)
{
}

IVtkOCC_SelectableObject::~IVtkOCC_SelectableObject() = default;

void IVtkOCC_SelectableObject::SetShape(const IVtkOCC_Shape::Handle& theShape)
{
  myShape = theShape;
  if (!myShape.IsNull())
  {
    myShape->SetSelectableObject(this);
  }

  myBndBox.SetVoid();
  myselections.Clear();
}

void IVtkOCC_SelectableObject::ComputeSelection(
  const occ::handle<SelectMgr_Selection>& theSelection,
  const int                               theMode)
{
  if (myShape.IsNull())
  {
    return;
  }

  const TopoDS_Shape& anOcctShape = myShape->GetShape();
  if (anOcctShape.ShapeType() == TopAbs_COMPOUND && anOcctShape.NbChildren() == 0)
  {

    return;
  }

  const TopAbs_ShapeEnum           aTypeOfSel = AIS_Shape::SelectionType(theMode);
  const occ::handle<Prs3d_Drawer>& aDrawer    = myShape->Attributes();
  const double aDeflection = StdPrs_ToolTriangulatedShape::GetDeflection(anOcctShape, aDrawer);
  try
  {
    OCC_CATCH_SIGNALS
    StdSelect_BRepSelectionTool::Load(theSelection,
                                      this,
                                      anOcctShape,
                                      aTypeOfSel,
                                      aDeflection,
                                      aDrawer->DeviationAngle(),
                                      aDrawer->IsAutoTriangulation());
  }
  catch (const Standard_Failure& anException)
  {
    Message::SendFail(TCollection_AsciiString("Error: IVtkOCC_SelectableObject::ComputeSelection(")
                      + theMode + ") has failed (" + anException.what() + ")");
    if (theMode == 0)
    {
      Bnd_Box                            aBndBox       = BoundingBox();
      occ::handle<StdSelect_BRepOwner>   aOwner        = new StdSelect_BRepOwner(anOcctShape, this);
      occ::handle<Select3D_SensitiveBox> aSensitiveBox = new Select3D_SensitiveBox(aOwner, aBndBox);
      theSelection->Add(aSensitiveBox);
    }
  }
}

const Bnd_Box& IVtkOCC_SelectableObject::BoundingBox()
{
  if (myShape.IsNull())
  {
    myBndBox.SetVoid();
    return myBndBox;
  }

  const TopoDS_Shape& anOcctShape = myShape->GetShape();
  if (anOcctShape.ShapeType() == TopAbs_COMPOUND && anOcctShape.NbChildren() == 0)
  {

    myBndBox.SetVoid();
    return myBndBox;
  }

  if (myBndBox.IsVoid())
  {
    BRepBndLib::Add(anOcctShape, myBndBox, true);
  }

  return myBndBox;
}

void IVtkOCC_SelectableObject::BoundingBox(Bnd_Box& theBndBox)
{
  BoundingBox();
  theBndBox = myBndBox;
}
