#include <BRep_Builder.hpp>
#include <Message_ProgressScope.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeFix.hpp>
#include <ShapeFix_Edge.hpp>
#include <ShapeFix_Shape.hpp>
#include <ShapeFix_Shell.hpp>
#include <ShapeFix_Solid.hpp>
#include <ShapeFix_Wire.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeFix_Shape, ShapeFix_Root)

ShapeFix_Shape::ShapeFix_Shape()
{
  myStatus                = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myFixSolidMode          = -1;
  myFixShellMode          = -1;
  myFixFaceMode           = -1;
  myFixWireMode           = -1;
  myFixSameParameterMode  = -1;
  myFixVertexPositionMode = 0;
  myFixVertexTolMode      = -1;
  myFixSolid              = new ShapeFix_Solid;
}

ShapeFix_Shape::ShapeFix_Shape(const TopoDS_Shape& shape)
{
  myStatus                = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myFixSolidMode          = -1;
  myFixShellMode          = -1;
  myFixFaceMode           = -1;
  myFixWireMode           = -1;
  myFixSameParameterMode  = -1;
  myFixSolid              = new ShapeFix_Solid;
  myFixVertexPositionMode = 0;
  myFixVertexTolMode      = -1;
  Init(shape);
}

void ShapeFix_Shape::Init(const TopoDS_Shape& shape)
{
  myShape = shape;
  if (Context().IsNull())
  {
    SetContext(new ShapeBuild_ReShape);
    Context()->ModeConsiderLocation() = true;
  }
  myResult = myShape;
}

bool ShapeFix_Shape::Perform(const Message_ProgressRange& theProgress)
{
  int                        savFixSmallAreaWireMode = 0;
  int                        savFixVertexTolMode     = myFixVertexTolMode;
  occ::handle<ShapeFix_Face> fft                     = FixFaceTool();
  if (!fft.IsNull())
  {
    savFixSmallAreaWireMode = fft->FixSmallAreaWireMode();
    if (savFixSmallAreaWireMode == -1 && myShape.ShapeType() == TopAbs_FACE)
    {
      fft->FixSmallAreaWireMode() = true;
    }
  }

  myStatus                = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  bool             status = false;
  TopAbs_ShapeEnum st;

  TopLoc_Location nullLoc, L;
  L                          = myShape.Location();
  TopoDS_Shape aShapeNullLoc = myShape;
  const bool   aIsRecorded   = Context()->IsNewShape(myShape);
  aShapeNullLoc.Location(nullLoc);
  if (aIsRecorded || myMapFixingShape.Contains(aShapeNullLoc))
  {
    myShape.Location(L, false);
    myResult = Context()->Apply(myShape);
    status   = true;
    return status;
  }
  myMapFixingShape.Add(aShapeNullLoc);

  myShape.Location(L, false);
  TopoDS_Shape S = Context()->Apply(myShape);
  if (NeedFix(myFixVertexPositionMode))
    ShapeFix::FixVertexPosition(S, Precision(), Context());

  st = S.ShapeType();

  Message_ProgressScope aPS(theProgress, "Fixing stage", 2);

  switch (st)
  {
    case TopAbs_COMPOUND:
    case TopAbs_COMPSOLID:
    {
      TopoDS_Shape shape                   = myShape;
      int          savFixSameParameterMode = myFixSameParameterMode;
      myFixSameParameterMode               = false;
      myFixVertexTolMode                   = false;
      int aShapesNb                        = S.NbChildren();

      Message_ProgressScope aPSSubShape(aPS.Next(), "Fixing sub-shape", aShapesNb);
      for (TopoDS_Iterator anIter(S); anIter.More() && aPSSubShape.More(); anIter.Next())
      {
        myShape = anIter.Value();
        if (Perform(aPSSubShape.Next()))
          status = true;
      }
      if (!aPSSubShape.More())
        return false;

      myFixSameParameterMode = savFixSameParameterMode;
      myFixVertexTolMode     = savFixVertexTolMode;
      myShape                = shape;
      break;
    }
    case TopAbs_SOLID:
    {
      if (!NeedFix(myFixSolidMode))
        break;
      myFixSolid->Init(TopoDS::Solid(S));
      myFixSolid->SetContext(Context());

      if (myFixSolid->Perform(aPS.Next()))
        status = true;

      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE4);
      break;
    }
    case TopAbs_SHELL:
    {
      if (!NeedFix(myFixShellMode))
        break;
      occ::handle<ShapeFix_Shell> sfsh = FixShellTool();
      sfsh->Init(TopoDS::Shell(S));
      sfsh->SetContext(Context());

      if (sfsh->Perform(aPS.Next()))
        status = true;

      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE4);
      break;
    }
    case TopAbs_FACE:
    {
      if (!NeedFix(myFixFaceMode))
        break;
      occ::handle<ShapeFix_Face> sff           = FixFaceTool();
      bool                       savTopoMode   = sff->FixWireTool()->ModifyTopologyMode();
      sff->FixWireTool()->ModifyTopologyMode() = true;
      sff->Init(TopoDS::Face(S));
      sff->SetContext(Context());

      if (sff->Perform())
      {
        status = true;
      }
      sff->FixWireTool()->ModifyTopologyMode() = savTopoMode;
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
      break;
    }
    case TopAbs_WIRE:
    {
      if (!NeedFix(myFixWireMode))
        break;
      occ::handle<ShapeFix_Wire> sfw           = FixWireTool();
      bool                       savTopoMode   = sfw->ModifyTopologyMode();
      bool                       savClosedMode = sfw->ClosedWireMode();
      sfw->ModifyTopologyMode()                = true;
      if (!S.Closed())
        sfw->ClosedWireMode() = false;
      sfw->SetFace(TopoDS_Face());
      sfw->Load(TopoDS::Wire(S));
      sfw->SetContext(Context());
      if (sfw->Perform())
      {
        status = true;
        Context()->Replace(S, sfw->Wire());
      }
      sfw->ModifyTopologyMode() = savTopoMode;
      sfw->ClosedWireMode()     = savClosedMode;
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
      break;
    }
    case TopAbs_EDGE:
    {
      occ::handle<ShapeFix_Edge> sfe = FixEdgeTool();
      sfe->SetContext(Context());
      if (sfe->FixVertexTolerance(TopoDS::Edge(S)))
        myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
      break;
    }
    case TopAbs_VERTEX:
    case TopAbs_SHAPE:
    default:
      break;
  }
  if (!aPS.More())
    return false;

  myResult = Context()->Apply(S);

  if (NeedFix(myFixSameParameterMode))
  {
    SameParameter(myResult, false, aPS.Next());
    if (!aPS.More())
      return false;
  }
  if (NeedFix(myFixVertexTolMode))
  {
    int             nbF = 0;
    TopExp_Explorer anExpF(myResult, TopAbs_FACE);
    for (; anExpF.More() && nbF <= 1; anExpF.Next())
      nbF++;
    if (nbF > 1)
    {

      occ::handle<ShapeFix_Edge> sfe = FixEdgeTool();
      for (anExpF.ReInit(); anExpF.More(); anExpF.Next())
      {
        TopoDS_Face     aF = TopoDS::Face(anExpF.Current());
        TopExp_Explorer anExpE(aF, TopAbs_EDGE);
        for (; anExpE.More(); anExpE.Next())
          sfe->FixVertexTolerance(TopoDS::Edge(anExpE.Current()), aF);
      }
    }
  }

  myResult = Context()->Apply(myResult);

  if (!fft.IsNull())
    fft->FixSmallAreaWireMode() = savFixSmallAreaWireMode;

  return status;
}

void ShapeFix_Shape::SameParameter(const TopoDS_Shape&          sh,
                                   const bool                   enforce,
                                   const Message_ProgressRange& theProgress)
{
  ShapeFix::SameParameter(sh, enforce, 0.0, theProgress);
}

TopoDS_Shape ShapeFix_Shape::Shape() const
{
  return myResult;
}

void ShapeFix_Shape::SetMsgRegistrator(const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg)
{
  ShapeFix_Root::SetMsgRegistrator(msgreg);
  myFixSolid->SetMsgRegistrator(msgreg);
}

void ShapeFix_Shape::SetPrecision(const double preci)
{
  ShapeFix_Root::SetPrecision(preci);
  myFixSolid->SetPrecision(preci);
}

void ShapeFix_Shape::SetMinTolerance(const double mintol)
{
  ShapeFix_Root::SetMinTolerance(mintol);
  myFixSolid->SetMinTolerance(mintol);
}

void ShapeFix_Shape::SetMaxTolerance(const double maxtol)
{
  ShapeFix_Root::SetMaxTolerance(maxtol);
  myFixSolid->SetMaxTolerance(maxtol);
}

bool ShapeFix_Shape::Status(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatus, status);
}
