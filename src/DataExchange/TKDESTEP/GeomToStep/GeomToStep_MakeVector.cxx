#include <Geom2d_Vector.hpp>
#include <Geom_Vector.hpp>
#include <GeomToStep_MakeDirection.hpp>
#include <GeomToStep_MakeVector.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Vector.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d' un vector de prostep a partir d' un Vec de gp
//=============================================================================
GeomToStep_MakeVector::GeomToStep_MakeVector(const gp_Vec&           V,
                                             const StepData_Factors& theLocalFactors)
{
  gp_Dir D       = gp_Dir(V);
  double lFactor = theLocalFactors.LengthFactor();
#include "GeomToStep_MakeVector_gen.hpp"
}

//=============================================================================
// Creation d' un vector de prostep a partir d' un Vec2d de gp
//=============================================================================

GeomToStep_MakeVector::GeomToStep_MakeVector(const gp_Vec2d&         V,
                                             const StepData_Factors& theLocalFactors)
{
  (void)theLocalFactors;
  gp_Dir2d D       = gp_Dir2d(V);
  double   lFactor = 1.;
#include "GeomToStep_MakeVector_gen.hpp"
}

//=============================================================================
// Creation d' un vector de prostep a partir d' un Vector de Geom
//=============================================================================

GeomToStep_MakeVector::GeomToStep_MakeVector(const occ::handle<Geom_Vector>& GVector,
                                             const StepData_Factors&         theLocalFactors)
{
  gp_Vec V;
  V              = GVector->Vec();
  gp_Dir D       = gp_Dir(V);
  double lFactor = theLocalFactors.LengthFactor();
#include "GeomToStep_MakeVector_gen.hpp"
}

//=============================================================================
// Creation d' un vector de prostep a partir d' un Vector de Geom2d
//=============================================================================

GeomToStep_MakeVector::GeomToStep_MakeVector(const occ::handle<Geom2d_Vector>& GVector,
                                             const StepData_Factors&           theLocalFactors)
{
  (void)theLocalFactors;
  gp_Vec2d V;
  V                = GVector->Vec2d();
  gp_Dir2d D       = gp_Dir2d(V);
  double   lFactor = 1.;
#include "GeomToStep_MakeVector_gen.hpp"
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_Vector>& GeomToStep_MakeVector::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeVector::Value() - no result");
  return theVector;
}
