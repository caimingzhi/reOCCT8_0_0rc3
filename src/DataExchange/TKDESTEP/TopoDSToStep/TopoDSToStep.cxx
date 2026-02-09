#include <TopoDSToStep.hpp>

#include <BRep_Tool.hpp>
#include <BRepTools_Modifier.hpp>
#include <Standard_Transient.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDSToStep_Tool.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <TransferBRep.hpp>
#include <TransferBRep_ShapeMapper.hpp>

occ::handle<TCollection_HAsciiString> TopoDSToStep::DecodeBuilderError(
  const TopoDSToStep_BuilderError E)
{
  occ::handle<TCollection_HAsciiString> mess;
  switch (E)
  {
    case TopoDSToStep_BuilderDone:
    {
      mess = new TCollection_HAsciiString("Builder Done");
      break;
    }
    case TopoDSToStep_NoFaceMapped:
    {
      mess = new TCollection_HAsciiString("None of the Shell Faces has been mapped");
      break;
    }
    case TopoDSToStep_BuilderOther:
    {
      mess = new TCollection_HAsciiString("Other Error in Builder");
      break;
    }
  }
  return mess;
}

occ::handle<TCollection_HAsciiString> TopoDSToStep::DecodeFaceError(
  const TopoDSToStep_MakeFaceError E)
{
  occ::handle<TCollection_HAsciiString> mess;
  switch (E)
  {
    case TopoDSToStep_FaceDone:
    {
      mess = new TCollection_HAsciiString("Face Done");
      break;
    }
    case TopoDSToStep_FaceOther:
    {
      mess = new TCollection_HAsciiString("Other Error in Make STEP face");
      break;
    }
    case TopoDSToStep_InfiniteFace:
    {
      mess = new TCollection_HAsciiString("The Face has no Outer Wire");
      break;
    }
    case TopoDSToStep_NonManifoldFace:
    {
      mess = new TCollection_HAsciiString("The Face is Internal or External");
      break;
    }
    case TopoDSToStep_NoWireMapped:
    {
      mess = new TCollection_HAsciiString("None of the Face Wires has been mapped");
      break;
    }
  }
  return mess;
}

occ::handle<TCollection_HAsciiString> TopoDSToStep::DecodeWireError(
  const TopoDSToStep_MakeWireError E)
{
  occ::handle<TCollection_HAsciiString> mess;
  switch (E)
  {
    case TopoDSToStep_WireDone:
    {
      mess = new TCollection_HAsciiString("Wire Done");
      break;
    }
    case TopoDSToStep_WireOther:
    {
      mess = new TCollection_HAsciiString("Other Error in Make STEP wire");
      break;
    }
    case TopoDSToStep_NonManifoldWire:
    {
      mess = new TCollection_HAsciiString("The Wire is Internal or External");
      break;
    }
  }
  return mess;
}

occ::handle<TCollection_HAsciiString> TopoDSToStep::DecodeEdgeError(
  const TopoDSToStep_MakeEdgeError E)
{
  occ::handle<TCollection_HAsciiString> mess;
  switch (E)
  {
    case TopoDSToStep_EdgeDone:
    {
      mess = new TCollection_HAsciiString("Edge Done");
      break;
    }
    case TopoDSToStep_EdgeOther:
    {
      mess = new TCollection_HAsciiString("Other Error in Make STEP Edge");
      break;
    }
    case TopoDSToStep_NonManifoldEdge:
    {
      mess = new TCollection_HAsciiString("The Edge is Internal or External");
      break;
    }
  }
  return mess;
}

occ::handle<TCollection_HAsciiString> TopoDSToStep::DecodeVertexError(
  const TopoDSToStep_MakeVertexError E)
{
  occ::handle<TCollection_HAsciiString> mess;
  switch (E)
  {
    case TopoDSToStep_VertexDone:
    {
      mess = new TCollection_HAsciiString("Vertex Done");
      break;
    }
    case TopoDSToStep_VertexOther:
    {
      mess = new TCollection_HAsciiString("Other Error in Make STEP Vertex");
      break;
    }
  }
  return mess;
}

void TopoDSToStep::AddResult(const occ::handle<Transfer_FinderProcess>& FP,
                             const TopoDS_Shape&                        Shape,
                             const occ::handle<Standard_Transient>&     ent)
{
  occ::handle<Transfer_SimpleBinderOfTransient> result = new Transfer_SimpleBinderOfTransient;
  result->SetResult(ent);

  occ::handle<TransferBRep_ShapeMapper> mapper = TransferBRep::ShapeMapper(FP, Shape);
  occ::handle<Transfer_Binder>          binder = FP->Find(mapper);

  if (binder.IsNull())
    FP->Bind(mapper, result);
  else
    binder->AddResult(result);
}

void TopoDSToStep::AddResult(const occ::handle<Transfer_FinderProcess>& FP,
                             const TopoDSToStep_Tool&                   Tool)
{
  const NCollection_DataMap<TopoDS_Shape, occ::handle<Standard_Transient>, TopTools_ShapeMapHasher>&
    Map = Tool.Map();
  NCollection_DataMap<TopoDS_Shape, occ::handle<Standard_Transient>, TopTools_ShapeMapHasher>::
    Iterator it(Map);
  for (; it.More(); it.Next())
    TopoDSToStep::AddResult(FP, it.Key(), it.Value());
}
