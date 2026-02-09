

#include <BRepLib.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESToBRep.hpp>
#include <IGESToBRep_Actor.hpp>
#include <IGESToBRep_CurveAndSurface.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Static.hpp>
#include <Message_ProgressScope.hpp>
#include <ShapeExtend_Explorer.hpp>
#include <ShapeFix_ShapeTolerance.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep_ShapeBinder.hpp>
#include <XSAlgo.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESToBRep_Actor, Transfer_ActorOfTransientProcess)

namespace
{

  static bool EncodeRegul(const TopoDS_Shape& theShape)
  {
    const double aToleranceAngle = Interface_Static::RVal("read.encoderegularity.angle");
    if (theShape.IsNull())
    {
      return true;
    }
    if (aToleranceAngle <= 0.)
    {
      return true;
    }

    try
    {
      OCC_CATCH_SIGNALS
      BRepLib::EncodeRegularity(theShape, aToleranceAngle);
    }
    catch (const Standard_Failure&)
    {
      return false;
    }
    return true;
  }

  static void TrimTolerances(const TopoDS_Shape& theShape, const double theTolerance)
  {
    if (Interface_Static::IVal("read.maxprecision.mode") == 1)
    {
      ShapeFix_ShapeTolerance aSFST;
      aSFST.LimitTolerance(theShape,
                           0,
                           std::max(theTolerance, Interface_Static::RVal("read.maxprecision.val")));
    }
  }
} // namespace

IGESToBRep_Actor::IGESToBRep_Actor()
    : thecontinuity(0),
      theeps(0.0001)
{
}

void IGESToBRep_Actor::SetModel(const occ::handle<Interface_InterfaceModel>& model)
{
  themodel = model;
  theeps   = occ::down_cast<IGESData_IGESModel>(themodel)->GlobalSection().Resolution();
}

void IGESToBRep_Actor::SetContinuity(const int continuity)
{
  thecontinuity = continuity;
}

int IGESToBRep_Actor::GetContinuity() const
{
  return thecontinuity;
}

bool IGESToBRep_Actor::Recognize(const occ::handle<Standard_Transient>& start)
{
  DeclareAndCast(IGESData_IGESModel, mymodel, themodel);
  DeclareAndCast(IGESData_IGESEntity, ent, start);
  if (ent.IsNull())
    return false;

  int typnum = ent->TypeNumber();
  int fornum = ent->FormNumber();
  return IGESToBRep::IsCurveAndSurface(ent)
         || ((typnum == 402 && (fornum == 1 || fornum == 7 || fornum == 14 || fornum == 15))
             || (typnum == 408) || (typnum == 308));
}

occ::handle<Transfer_Binder> IGESToBRep_Actor::Transfer(
  const occ::handle<Standard_Transient>&        start,
  const occ::handle<Transfer_TransientProcess>& TP,
  const Message_ProgressRange&                  theProgress)
{
  DeclareAndCast(IGESData_IGESModel, mymodel, themodel);
  DeclareAndCast(IGESData_IGESEntity, ent, start);
  if (mymodel.IsNull() || ent.IsNull())
    return NullResult();
  int anum = mymodel->Number(start);

  if (Interface_Static::IVal("read.iges.faulty.entities") == 0 && mymodel->IsErrorEntity(anum))
    return NullResult();
  TopoDS_Shape shape;

  int    typnum = ent->TypeNumber();
  int    fornum = ent->FormNumber();
  double eps;
  if (IGESToBRep::IsCurveAndSurface(ent)
      || (typnum == 402 && (fornum == 1 || fornum == 7 || fornum == 14 || fornum == 15))
      || (typnum == 408) || (typnum == 308))
  {

    Message_ProgressScope aPS(theProgress, "Transfer stage", 2);

    XSAlgo_ShapeProcessor::PrepareForTransfer();
    IGESToBRep_CurveAndSurface CAS;
    CAS.SetModel(mymodel);
    CAS.SetContinuity(thecontinuity);
    CAS.SetTransferProcess(TP);
    int Ival = Interface_Static::IVal("read.precision.mode");
    if (Ival == 0)
      eps = mymodel->GlobalSection().Resolution();
    else
      eps = Interface_Static::RVal("read.precision.val");

    Ival = Interface_Static::IVal("read.iges.bspline.approxd1.mode");
    CAS.SetModeApprox((Ival > 0));
    Ival = Interface_Static::IVal("read.surfacecurve.mode");
    CAS.SetSurfaceCurve(Ival);

    if (eps > 1.E-08)
    {
      CAS.SetEpsGeom(eps);
      theeps = eps * CAS.GetUnitFactor();
    }
    int nbTPitems = TP->NbMapped();
    {
      try
      {
        OCC_CATCH_SIGNALS
        shape = CAS.TransferGeometry(ent, aPS.Next());
      }
      catch (Standard_Failure const&)
      {
        shape.Nullify();
      }
    }

    XSAlgo_ShapeProcessor::ParameterMap aParameters = GetShapeFixParameters();
    XSAlgo_ShapeProcessor::SetParameter("FixShape.Tolerance3d", theeps, true, aParameters);
    XSAlgo_ShapeProcessor::SetParameter("FixShape.MaxTolerance3d",
                                        CAS.GetMaxTol(),
                                        true,
                                        aParameters);

    XSAlgo_ShapeProcessor aShapeProcessor(aParameters);
    shape = aShapeProcessor.ProcessShape(shape, GetProcessingFlags().first, aPS.Next());
    aShapeProcessor.MergeTransferInfo(TP, nbTPitems);
  }

  ShapeExtend_Explorer SBE;
  if (SBE.ShapeType(shape, true) != TopAbs_SHAPE)
  {
    if (!shape.IsNull())
    {
      EncodeRegul(shape);

      TrimTolerances(shape, UsedTolerance());
    }
  }
  occ::handle<TransferBRep_ShapeBinder> binder;
  if (!shape.IsNull())
    binder = new TransferBRep_ShapeBinder(shape);
  return binder;
}

double IGESToBRep_Actor::UsedTolerance() const
{
  return theeps;
}
