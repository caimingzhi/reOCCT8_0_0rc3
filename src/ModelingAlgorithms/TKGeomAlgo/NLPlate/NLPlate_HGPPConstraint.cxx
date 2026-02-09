#include <NLPlate_HGPPConstraint.hpp>
#include <Plate_D1.hpp>
#include <Plate_D2.hpp>
#include <Plate_D3.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NLPlate_HGPPConstraint, Standard_Transient)

void NLPlate_HGPPConstraint::SetUVFreeSliding(const bool) {}

void NLPlate_HGPPConstraint::SetIncrementalLoadAllowed(const bool) {}

void NLPlate_HGPPConstraint::SetActiveOrder(const int ActiveOrder)
{
  myActiveOrder = ActiveOrder;
}

void NLPlate_HGPPConstraint::SetUV(const gp_XY& UV)
{
  myUV = UV;
}

void NLPlate_HGPPConstraint::SetOrientation(const int) {}

void NLPlate_HGPPConstraint::SetG0Criterion(const double) {}

void NLPlate_HGPPConstraint::SetG1Criterion(const double) {}

void NLPlate_HGPPConstraint::SetG2Criterion(const double) {}

void NLPlate_HGPPConstraint::SetG3Criterion(const double) {}

bool NLPlate_HGPPConstraint::UVFreeSliding() const
{
  return false;
}

bool NLPlate_HGPPConstraint::IncrementalLoadAllowed() const
{
  return false;
}

const gp_XY& NLPlate_HGPPConstraint::UV() const
{
  return myUV;
}

static const gp_XYZ XYZnull(0., 0., 0.);

const gp_XYZ& NLPlate_HGPPConstraint::G0Target() const
{
  return XYZnull;
}

static const Plate_D1 D1null(XYZnull, XYZnull);

const Plate_D1& NLPlate_HGPPConstraint::G1Target() const
{
  return D1null;
}

static const Plate_D2 D2null(XYZnull, XYZnull, XYZnull);

const Plate_D2& NLPlate_HGPPConstraint::G2Target() const
{
  return D2null;
}

static const Plate_D3 D3null(XYZnull, XYZnull, XYZnull, XYZnull);

const Plate_D3& NLPlate_HGPPConstraint::G3Target() const
{
  return D3null;
}

int NLPlate_HGPPConstraint::Orientation()
{
  return 0;
}

double NLPlate_HGPPConstraint::G0Criterion() const
{
  return 0.;
}

double NLPlate_HGPPConstraint::G1Criterion() const
{
  return 0.;
}

double NLPlate_HGPPConstraint::G2Criterion() const
{
  return 0.;
}

double NLPlate_HGPPConstraint::G3Criterion() const
{
  return 0.;
}
