#include <BRep_Tool.hpp>
#include <GeomToStep_MakeCartesianPoint.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepShape_VertexPoint.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TopoDSToStep_MakeStepVertex.hpp>
#include <TopoDSToStep_Tool.hpp>
#include <Transfer_FinderProcess.hpp>
#include <TransferBRep.hpp>
#include <TransferBRep_ShapeMapper.hpp>

TopoDSToStep_MakeStepVertex::TopoDSToStep_MakeStepVertex()
    : myError(TopoDSToStep_VertexOther)
{
  done = false;
}

TopoDSToStep_MakeStepVertex::TopoDSToStep_MakeStepVertex(
  const TopoDS_Vertex&                       V,
  TopoDSToStep_Tool&                         T,
  const occ::handle<Transfer_FinderProcess>& FP,
  const StepData_Factors&                    theLocalFactors)
{
  done = false;
  Init(V, T, FP, theLocalFactors);
}

void TopoDSToStep_MakeStepVertex::Init(const TopoDS_Vertex&                       aVertex,
                                       TopoDSToStep_Tool&                         aTool,
                                       const occ::handle<Transfer_FinderProcess>& FP,
                                       const StepData_Factors&                    theLocalFactors)
{

  aTool.SetCurrentVertex(aVertex);

  bool isNMMode =
    occ::down_cast<StepData_StepModel>(FP->Model())->InternalParameters.WriteNonmanifold != 0;
  if (isNMMode)
  {
    occ::handle<StepShape_VertexPoint>    aVP;
    occ::handle<TransferBRep_ShapeMapper> aSTEPMapper = TransferBRep::ShapeMapper(FP, aVertex);
    if (FP->FindTypedTransient(aSTEPMapper, STANDARD_TYPE(StepShape_VertexPoint), aVP))
    {

      myError  = TopoDSToStep_VertexOther;
      myResult = aVP;
      done     = true;
      return;
    }
  }

  if (aTool.IsBound(aVertex))
  {
    myError  = TopoDSToStep_VertexOther;
    done     = true;
    myResult = aTool.Find(aVertex);
    return;
  }

  gp_Pnt P;

  P = BRep_Tool::Pnt(aVertex);
  GeomToStep_MakeCartesianPoint         MkPoint(P, theLocalFactors.LengthFactor());
  occ::handle<StepGeom_CartesianPoint>  Gpms  = MkPoint.Value();
  occ::handle<StepShape_VertexPoint>    Vpms  = new StepShape_VertexPoint();
  occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString("");

  Vpms->Init(aName, Gpms);

  aTool.Bind(aVertex, Vpms);
  myError  = TopoDSToStep_VertexDone;
  done     = true;
  myResult = Vpms;
}

const occ::handle<StepShape_TopologicalRepresentationItem>& TopoDSToStep_MakeStepVertex::Value()
  const
{
  StdFail_NotDone_Raise_if(!done, "TopoDSToStep_MakeStepVertex::Value() - no result");
  return myResult;
}

TopoDSToStep_MakeVertexError TopoDSToStep_MakeStepVertex::Error() const
{
  return myError;
}
