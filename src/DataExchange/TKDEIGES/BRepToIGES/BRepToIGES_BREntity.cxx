#include <BRep_Builder.hpp>
#include <BRepToIGES_BREntity.hpp>
#include <BRepToIGES_BRShell.hpp>
#include <BRepToIGES_BRSolid.hpp>
#include <BRepToIGES_BRWire.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Static.hpp>
#include <Standard_Transient.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_CompSolid.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <Transfer_TransientMapper.hpp>
#include <TransferBRep_ShapeMapper.hpp>

char Name[100];

BRepToIGES_BREntity::BRepToIGES_BREntity()
    : TheUnitFactor(1.0),
      myConvSurface(Interface_Static::IVal("write.convertsurface.mode") != 0),
      myPCurveMode(Interface_Static::IVal("write.surfacecurve.mode") != 0),
      TheMap(new Transfer_FinderProcess())
{
}

void BRepToIGES_BREntity::Init()
{
  TheMap        = new Transfer_FinderProcess();
  TheUnitFactor = 1.;
  myConvSurface = Interface_Static::IVal("write.convertsurface.mode") != 0;
  myPCurveMode  = Interface_Static::IVal("write.surfacecurve.mode") != 0;
}

void BRepToIGES_BREntity::SetModel(const occ::handle<IGESData_IGESModel>& model)
{
  TheModel          = model;
  double unitfactor = TheModel->GlobalSection().UnitValue();
  if (unitfactor != 1.)
    TheUnitFactor = unitfactor;
}

occ::handle<IGESData_IGESModel> BRepToIGES_BREntity::GetModel() const
{
  return TheModel;
}

double BRepToIGES_BREntity::GetUnit() const
{
  return TheUnitFactor;
}

void BRepToIGES_BREntity::SetTransferProcess(const occ::handle<Transfer_FinderProcess>& TP)
{
  TheMap = TP;
}

occ::handle<Transfer_FinderProcess> BRepToIGES_BREntity::GetTransferProcess() const
{
  return TheMap;
}

occ::handle<IGESData_IGESEntity> BRepToIGES_BREntity::TransferShape(
  const TopoDS_Shape&          start,
  const Message_ProgressRange& theProgress)
{
  occ::handle<IGESData_IGESEntity> res;

  if (start.IsNull())
    return res;

  if (start.ShapeType() == TopAbs_VERTEX)
  {
    TopoDS_Vertex     V = TopoDS::Vertex(start);
    BRepToIGES_BRWire BW(*this);
    BW.SetModel(GetModel());
    res = BW.TransferVertex(V);
  }
  else if (start.ShapeType() == TopAbs_EDGE)
  {
    TopoDS_Edge       E = TopoDS::Edge(start);
    BRepToIGES_BRWire BW(*this);
    BW.SetModel(GetModel());
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> anEmptyMap;
    res = BW.TransferEdge(E, anEmptyMap, false);
  }
  else if (start.ShapeType() == TopAbs_WIRE)
  {
    TopoDS_Wire       W = TopoDS::Wire(start);
    BRepToIGES_BRWire BW(*this);
    BW.SetModel(GetModel());
    res = BW.TransferWire(W);
  }
  else
  {

    if (start.ShapeType() == TopAbs_FACE)
    {
      TopoDS_Face        F = TopoDS::Face(start);
      BRepToIGES_BRShell BS(*this);
      BS.SetModel(GetModel());
      res = BS.TransferFace(F, theProgress);
    }
    else if (start.ShapeType() == TopAbs_SHELL)
    {
      TopoDS_Shell       S = TopoDS::Shell(start);
      BRepToIGES_BRShell BS(*this);
      BS.SetModel(GetModel());
      res = BS.TransferShell(S, theProgress);
    }
    else if (start.ShapeType() == TopAbs_SOLID)
    {
      TopoDS_Solid       M = TopoDS::Solid(start);
      BRepToIGES_BRSolid BS(*this);
      BS.SetModel(GetModel());
      res = BS.TransferSolid(M, theProgress);
    }
    else if (start.ShapeType() == TopAbs_COMPSOLID)
    {
      TopoDS_CompSolid   C = TopoDS::CompSolid(start);
      BRepToIGES_BRSolid BS(*this);
      BS.SetModel(GetModel());
      res = BS.TransferCompSolid(C, theProgress);
    }
    else if (start.ShapeType() == TopAbs_COMPOUND)
    {
      TopoDS_Compound    C = TopoDS::Compound(start);
      BRepToIGES_BRSolid BS(*this);
      BS.SetModel(GetModel());
      res = BS.TransferCompound(C, theProgress);
    }
    else
    {
    }
  }

  return res;
}

void BRepToIGES_BREntity::AddFail(const TopoDS_Shape& start, const char* amess)
{
  occ::handle<TransferBRep_ShapeMapper> Mapper = new TransferBRep_ShapeMapper(start);
  TheMap->AddFail(Mapper, amess);
}

void BRepToIGES_BREntity::AddWarning(const TopoDS_Shape& start, const char* amess)
{
  occ::handle<TransferBRep_ShapeMapper> Mapper = new TransferBRep_ShapeMapper(start);
  TheMap->AddWarning(Mapper, amess);
}

void BRepToIGES_BREntity::AddFail(const occ::handle<Standard_Transient>& start, const char* amess)
{
  occ::handle<Transfer_TransientMapper> Mapper = new Transfer_TransientMapper(start);
  TheMap->AddFail(Mapper, amess);
}

void BRepToIGES_BREntity::AddWarning(const occ::handle<Standard_Transient>& start,
                                     const char*                            amess)
{
  occ::handle<Transfer_TransientMapper> Mapper = new Transfer_TransientMapper(start);
  TheMap->AddWarning(Mapper, amess);
}

bool BRepToIGES_BREntity::HasShapeResult(const TopoDS_Shape& start) const
{
  occ::handle<TransferBRep_ShapeMapper> Mapper = new TransferBRep_ShapeMapper(start);
  DeclareAndCast(Transfer_SimpleBinderOfTransient, binder, TheMap->Find(Mapper));
  if (binder.IsNull())
    return false;
  return binder->HasResult();
}

occ::handle<Standard_Transient> BRepToIGES_BREntity::GetShapeResult(const TopoDS_Shape& start) const
{
  occ::handle<Standard_Transient> res;

  occ::handle<TransferBRep_ShapeMapper> Mapper = new TransferBRep_ShapeMapper(start);
  DeclareAndCast(Transfer_SimpleBinderOfTransient, binder, TheMap->Find(Mapper));
  if (binder.IsNull())
    return res;
  if (binder->HasResult())
    res = binder->Result();
  return res;
}

void BRepToIGES_BREntity::SetShapeResult(const TopoDS_Shape&                    start,
                                         const occ::handle<Standard_Transient>& result)
{
  occ::handle<TransferBRep_ShapeMapper>         Mapper = new TransferBRep_ShapeMapper(start);
  occ::handle<Transfer_SimpleBinderOfTransient> binder = new Transfer_SimpleBinderOfTransient;
  binder->SetResult(result);
  TheMap->Bind(Mapper, binder);
}

bool BRepToIGES_BREntity::HasShapeResult(const occ::handle<Standard_Transient>& start) const
{
  occ::handle<Transfer_TransientMapper> Mapper = new Transfer_TransientMapper(start);
  DeclareAndCast(Transfer_SimpleBinderOfTransient, binder, TheMap->Find(Mapper));
  if (binder.IsNull())
    return false;
  return binder->HasResult();
}

occ::handle<Standard_Transient> BRepToIGES_BREntity::GetShapeResult(
  const occ::handle<Standard_Transient>& start) const
{
  occ::handle<Standard_Transient> res;

  occ::handle<Transfer_TransientMapper> Mapper = new Transfer_TransientMapper(start);
  DeclareAndCast(Transfer_SimpleBinderOfTransient, binder, TheMap->Find(Mapper));
  if (binder.IsNull())
    return res;
  if (binder->HasResult())
    res = binder->Result();
  return res;
}

void BRepToIGES_BREntity::SetShapeResult(const occ::handle<Standard_Transient>& start,
                                         const occ::handle<Standard_Transient>& result)
{
  occ::handle<Transfer_TransientMapper>         Mapper = new Transfer_TransientMapper(start);
  occ::handle<Transfer_SimpleBinderOfTransient> binder = new Transfer_SimpleBinderOfTransient;
  TheMap->Bind(Mapper, binder);
  binder->SetResult(result);
}

bool BRepToIGES_BREntity::GetConvertSurfaceMode() const
{
  return myConvSurface;
}

bool BRepToIGES_BREntity::GetPCurveMode() const
{
  return myPCurveMode;
}

BRepToIGES_BREntity::~BRepToIGES_BREntity() = default;
