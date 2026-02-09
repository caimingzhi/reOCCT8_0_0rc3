#include <Geom2d_Circle.hpp>
#include <Geom2d_Conic.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Conic.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Parabola.hpp>
#include <GeomToStep_MakeCircle.hpp>
#include <GeomToStep_MakeConic.hpp>
#include <GeomToStep_MakeEllipse.hpp>
#include <GeomToStep_MakeHyperbola.hpp>
#include <GeomToStep_MakeParabola.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Circle.hpp>
#include <StepGeom_Conic.hpp>
#include <StepGeom_Ellipse.hpp>
#include <StepGeom_Hyperbola.hpp>
#include <StepGeom_Parabola.hpp>

GeomToStep_MakeConic::GeomToStep_MakeConic(const occ::handle<Geom_Conic>& C,
                                           const StepData_Factors&        theLocalFactors)
{
  done = true;
  if (C->IsKind(STANDARD_TYPE(Geom_Circle)))
  {
    occ::handle<Geom_Circle> Cer = occ::down_cast<Geom_Circle>(C);
    GeomToStep_MakeCircle    MkCircle(Cer, theLocalFactors);
    theConic = MkCircle.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom_Ellipse)))
  {
    occ::handle<Geom_Ellipse> Ell = occ::down_cast<Geom_Ellipse>(C);
    GeomToStep_MakeEllipse    MkEllipse(Ell, theLocalFactors);
    theConic = MkEllipse.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom_Hyperbola)))
  {
    occ::handle<Geom_Hyperbola> Hyp = occ::down_cast<Geom_Hyperbola>(C);
    GeomToStep_MakeHyperbola    MkHyperbola(Hyp, theLocalFactors);
    theConic = MkHyperbola.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom_Parabola)))
  {
    occ::handle<Geom_Parabola> Par = occ::down_cast<Geom_Parabola>(C);
    GeomToStep_MakeParabola    MkParabola(Par, theLocalFactors);
    theConic = MkParabola.Value();
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "3D Curve Type   : " << C->DynamicType() << std::endl;
#endif
    done = false;
  }
}

GeomToStep_MakeConic::GeomToStep_MakeConic(const occ::handle<Geom2d_Conic>& C,
                                           const StepData_Factors&          theLocalFactors)
{
  done = true;
  if (C->IsKind(STANDARD_TYPE(Geom2d_Circle)))
  {
    occ::handle<Geom2d_Circle> Cer = occ::down_cast<Geom2d_Circle>(C);
    GeomToStep_MakeCircle      MkCircle(Cer, theLocalFactors);
    theConic = MkCircle.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom2d_Ellipse)))
  {
    occ::handle<Geom2d_Ellipse> Ell = occ::down_cast<Geom2d_Ellipse>(C);
    GeomToStep_MakeEllipse      MkEllipse(Ell, theLocalFactors);
    theConic = MkEllipse.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom2d_Hyperbola)))
  {
    occ::handle<Geom2d_Hyperbola> Hyp = occ::down_cast<Geom2d_Hyperbola>(C);
    GeomToStep_MakeHyperbola      MkHyperbola(Hyp, theLocalFactors);
    theConic = MkHyperbola.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom2d_Parabola)))
  {
    occ::handle<Geom2d_Parabola> Par = occ::down_cast<Geom2d_Parabola>(C);
    GeomToStep_MakeParabola      MkParabola(Par, theLocalFactors);
    theConic = MkParabola.Value();
  }
  else
  {

#ifdef OCCT_DEBUG
    std::cout << "2D conic not yet implemented" << std::endl;
#endif
    done = false;
  }
}

const occ::handle<StepGeom_Conic>& GeomToStep_MakeConic::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeConic::Value() - no result");
  return theConic;
}
