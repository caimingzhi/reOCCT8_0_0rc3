// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// cky 16.01.99 Remove couts.
// rln 28.12.98 CCI60005

#include <Bnd_Box.hpp>
#include <BndLib_Add3dCurve.hpp>
#include <BndLib_AddSurface.hpp>
#include <BRepBndLib.hpp>
#include <BRepToIGESBRep_Entity.hpp>
#include <DEIGES_Parameters.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomToIGES_GeomCurve.hpp>
#include <GeomToIGES_GeomSurface.hpp>
#include <gp_XYZ.hpp>
#include <IGESControl_Controller.hpp>
#include <IGESControl_Writer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESSelect_WorkLibrary.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Static.hpp>
#include <Message_ProgressScope.hpp>
#include <OSD_FileSystem.hpp>
#include <ShapeAnalysis_ShapeTolerance.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Standard_Transient.hpp>
#include <TopoDS_Shape.hpp>
#include <Transfer_FinderProcess.hpp>
#include <XSAlgo.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

#include <cerrno>

//=============================================================================

IGESControl_Writer::IGESControl_Writer()
    : myTP(new Transfer_FinderProcess(10000)),
      myIsComputed(false)
{
  IGESControl_Controller::Init();
  myEditor.Init(IGESSelect_WorkLibrary::DefineProtocol());
  myEditor.SetUnitName(Interface_Static::CVal("write.iges.unit"));
  myEditor.ApplyUnit();
  myWriteMode = Interface_Static::IVal("write.iges.brep.mode");
  myModel     = myEditor.Model();
}

//=============================================================================

IGESControl_Writer::IGESControl_Writer(const char* theUnit, const int theModecr)
    : myTP(new Transfer_FinderProcess(10000)),
      myWriteMode(theModecr),
      myIsComputed(false)
{
  IGESControl_Controller::Init();
  myEditor.Init(IGESSelect_WorkLibrary::DefineProtocol());
  myEditor.SetUnitName(theUnit);
  myEditor.ApplyUnit();
  myModel = myEditor.Model();
}

//=============================================================================

IGESControl_Writer::IGESControl_Writer(const occ::handle<IGESData_IGESModel>& theModel,
                                       const int                              theModecr)
    : myTP(new Transfer_FinderProcess(10000)),
      myModel(theModel),
      myEditor(theModel, IGESSelect_WorkLibrary::DefineProtocol()),
      myWriteMode(theModecr),
      myIsComputed(false)
{
}

//=============================================================================

bool IGESControl_Writer::AddShape(const TopoDS_Shape&          theShape,
                                  const Message_ProgressRange& theProgress)
{
  if (theShape.IsNull())
    return false;

  XSAlgo_ShapeProcessor::PrepareForTransfer();

  InitializeMissingParameters();

  Message_ProgressScope aPS(theProgress, nullptr, 2);

  XSAlgo_ShapeProcessor aShapeProcessor(myShapeProcParams);
  TopoDS_Shape Shape = aShapeProcessor.ProcessShape(theShape, myShapeProcFlags.first, aPS.Next());

  if (!aPS.More())
    return false;

  BRepToIGES_BREntity B0;
  B0.SetTransferProcess(myTP);
  B0.SetModel(myModel);
  BRepToIGESBRep_Entity B1;
  B1.SetTransferProcess(myTP);
  B1.SetModel(myModel);
  occ::handle<IGESData_IGESEntity> ent =
    myWriteMode ? B1.TransferShape(Shape, aPS.Next()) : B0.TransferShape(Shape, aPS.Next());
  if (!aPS.More())
    return false;

  if (ent.IsNull())
    return false;
  aShapeProcessor.MergeTransferInfo(myTP);

  // 22.10.98 gka BUC60080

  int  oldnb = myModel->NbEntities();
  bool aent  = AddEntity(ent);
  int  newnb = myModel->NbEntities();

  double oldtol = myModel->GlobalSection().Resolution(), newtol;

  int tolmod = Interface_Static::IVal("write.precision.mode");
  if (tolmod == 2)
    newtol = Interface_Static::RVal("write.precision.val");
  else
  {
    ShapeAnalysis_ShapeTolerance stu;
    double                       Tolv = stu.Tolerance(Shape, tolmod, TopAbs_VERTEX);
    double                       Tole = stu.Tolerance(Shape, tolmod, TopAbs_EDGE);

    if (tolmod == 0)
    { // Average
      double Tol1 = (Tolv + Tole) / 2;
      newtol      = (oldtol * oldnb + Tol1 * (newnb - oldnb)) / newnb;
    }
    else if (tolmod < 0)
    { // Least
      newtol = std::min(Tolv, Tole);
      if (oldnb > 0)
        newtol = std::min(oldtol, newtol);
    }
    else
    { // Greatest
      newtol = std::max(Tolv, Tole);
      if (oldnb > 0)
        newtol = std::max(oldtol, newtol);
    }
  }

  IGESData_GlobalSection gs = myModel->GlobalSection();
  gs.SetResolution(newtol / gs.UnitValue()); // rln 28.12.98 CCI60005

  // #34 22.10.98 rln BUC60081
  Bnd_Box box;
  BRepBndLib::Add(Shape, box);
  if (!(box.IsVoid() || box.IsOpenXmax() || box.IsOpenYmax() || box.IsOpenZmax() || box.IsOpenXmin()
        || box.IsOpenYmin() || box.IsOpenZmin()))
  {
    double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
    box.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
    gs.MaxMaxCoords(gp_XYZ(aXmax / gs.UnitValue(), aYmax / gs.UnitValue(), aZmax / gs.UnitValue()));
    gs.MaxMaxCoords(gp_XYZ(aXmin / gs.UnitValue(), aYmin / gs.UnitValue(), aZmin / gs.UnitValue()));
  }

  myModel->SetGlobalSection(gs);

  return aent;
}

bool IGESControl_Writer::AddGeom(const occ::handle<Standard_Transient>& geom)
{
  if (geom.IsNull() || !geom->IsKind(STANDARD_TYPE(Geom_Geometry)))
    return false;
  DeclareAndCast(Geom_Curve, Curve, geom);
  DeclareAndCast(Geom_Surface, Surf, geom);
  occ::handle<IGESData_IGESEntity> ent;

  //  We recognize: Curve and Surface from Geom
  //   what about Point; Geom2d ?

  //  GeomToIGES_GeomPoint GP;
  GeomToIGES_GeomCurve GC;
  GC.SetModel(myModel);
  GeomToIGES_GeomSurface GS;
  GS.SetModel(myModel);

  // #34 22.10.98 rln BUC60081
  IGESData_GlobalSection gs = myModel->GlobalSection();
  Bnd_Box                box;

  if (!Curve.IsNull())
  {
    ent = GC.TransferCurve(Curve, Curve->FirstParameter(), Curve->LastParameter());
    BndLib_Add3dCurve::Add(GeomAdaptor_Curve(Curve), 0, box);
  }
  else if (!Surf.IsNull())
  {
    double U1, U2, V1, V2;
    Surf->Bounds(U1, U2, V1, V2);
    ent = GS.TransferSurface(Surf, U1, U2, V1, V2);
    BndLib_AddSurface::Add(GeomAdaptor_Surface(Surf), 0, box);
  }

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  box.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
  gs.MaxMaxCoords(gp_XYZ(aXmax / gs.UnitValue(), aYmax / gs.UnitValue(), aZmax / gs.UnitValue()));
  gs.MaxMaxCoords(gp_XYZ(aXmin / gs.UnitValue(), aYmin / gs.UnitValue(), aZmin / gs.UnitValue()));
  myModel->SetGlobalSection(gs);
  return AddEntity(ent);
}

//=============================================================================

bool IGESControl_Writer::AddEntity(const occ::handle<IGESData_IGESEntity>& ent)
{
  if (ent.IsNull())
    return false;
  myModel->AddWithRefs(ent, IGESSelect_WorkLibrary::DefineProtocol());
  myIsComputed = false;
  return true;
}

//=============================================================================

void IGESControl_Writer::ComputeModel()
{
  if (!myIsComputed)
  {
    myEditor.ComputeStatus();
    myEditor.AutoCorrectModel();
    myIsComputed = true;
  }
}

//=============================================================================

bool IGESControl_Writer::Write(Standard_OStream& S, const bool fnes)
{
  if (!S)
    return false;
  ComputeModel();
  int nbEnt = myModel->NbEntities();
  if (!nbEnt)
    return false;
  IGESData_IGESWriter IW(myModel);
  //  do not forget the fnes mode ... to transmit to IW
  IW.SendModel(IGESSelect_WorkLibrary::DefineProtocol());
  if (fnes)
    IW.WriteMode() = 10;
  bool status = IW.Print(S);
  return status;
}

//=============================================================================

bool IGESControl_Writer::Write(const char* file, const bool fnes)
{
  const occ::handle<OSD_FileSystem>& aFileSystem = OSD_FileSystem::DefaultFileSystem();
  std::shared_ptr<std::ostream>      aStream =
    aFileSystem->OpenOStream(file, std::ios::out | std::ios::binary);
  if (aStream.get() == nullptr)
  {
    return false;
  }
  bool res = Write(*aStream, fnes);

  errno = 0;
  aStream->flush();
  res = aStream->good() && res && !errno;
  aStream.reset();

  return res;
}

//=============================================================================

void IGESControl_Writer::SetShapeFixParameters(
  const XSAlgo_ShapeProcessor::ParameterMap& theParameters)
{
  myShapeProcParams = theParameters;
}

//=============================================================================

void IGESControl_Writer::SetShapeFixParameters(XSAlgo_ShapeProcessor::ParameterMap&& theParameters)
{
  myShapeProcParams = std::move(theParameters);
}

//=============================================================================

void IGESControl_Writer::SetShapeFixParameters(
  const DE_ShapeFixParameters&               theParameters,
  const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters)
{
  XSAlgo_ShapeProcessor::SetShapeFixParameters(theParameters,
                                               theAdditionalParameters,
                                               myShapeProcParams);
}

//=============================================================================

void IGESControl_Writer::SetShapeProcessFlags(const ShapeProcess::OperationsFlags& theFlags)
{
  myShapeProcFlags.first  = theFlags;
  myShapeProcFlags.second = true;
}

//=============================================================================

void IGESControl_Writer::InitializeMissingParameters()
{
  if (GetShapeFixParameters().IsEmpty())
  {
    SetShapeFixParameters(DEIGES_Parameters::GetDefaultShapeFixParameters());
  }

  if (!myShapeProcFlags.second)
  {
    myShapeProcFlags.first.set(ShapeProcess::Operation::DirectFaces);
    myShapeProcFlags.second = true;
  }
}
