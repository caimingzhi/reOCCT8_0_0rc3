

#include <Geom2d_Hyperbola.hpp>
#include <Geom_Hyperbola.hpp>
#include <GeomToStep_MakeAxis2Placement2d.hpp>
#include <GeomToStep_MakeAxis2Placement3d.hpp>
#include <GeomToStep_MakeHyperbola.hpp>
#include <gp_Hypr.hpp>
#include <gp_Hypr2d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis2Placement2d.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_Hyperbola.hpp>
#include <TCollection_HAsciiString.hpp>

GeomToStep_MakeHyperbola::GeomToStep_MakeHyperbola(const occ::handle<Geom2d_Hyperbola>& C,
                                                   const StepData_Factors& theLocalFactors)
{
  gp_Hypr2d gpHyp;
  gpHyp = C->Hypr2d();

  occ::handle<StepGeom_Hyperbola>        HStep = new StepGeom_Hyperbola;
  StepGeom_Axis2Placement                Ax2;
  occ::handle<StepGeom_Axis2Placement2d> Ax2Step;
  double                                 majorR, minorR;

  GeomToStep_MakeAxis2Placement2d MkAxis2(gpHyp.Axis(), theLocalFactors);
  Ax2Step = MkAxis2.Value();
  majorR  = gpHyp.MajorRadius();
  minorR  = gpHyp.MinorRadius();
  Ax2.SetValue(Ax2Step);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  HStep->Init(name, Ax2, majorR, minorR);
  theHyperbola = HStep;
  done         = true;
}

GeomToStep_MakeHyperbola::GeomToStep_MakeHyperbola(const occ::handle<Geom_Hyperbola>& C,
                                                   const StepData_Factors& theLocalFactors)
{
  gp_Hypr gpHyp;
  gpHyp = C->Hypr();

  occ::handle<StepGeom_Hyperbola>        HStep = new StepGeom_Hyperbola;
  StepGeom_Axis2Placement                Ax2;
  occ::handle<StepGeom_Axis2Placement3d> Ax2Step;
  double                                 majorR, minorR;

  GeomToStep_MakeAxis2Placement3d MkAxis2(gpHyp.Position(), theLocalFactors);
  Ax2Step = MkAxis2.Value();
  majorR  = gpHyp.MajorRadius();
  minorR  = gpHyp.MinorRadius();
  Ax2.SetValue(Ax2Step);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  double                                fact = theLocalFactors.LengthFactor();
  HStep->Init(name, Ax2, majorR / fact, minorR / fact);
  theHyperbola = HStep;
  done         = true;
}

const occ::handle<StepGeom_Hyperbola>& GeomToStep_MakeHyperbola::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeHyperbola::Value() - no result");
  return theHyperbola;
}
