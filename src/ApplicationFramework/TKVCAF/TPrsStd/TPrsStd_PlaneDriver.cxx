

#include <AIS_InteractiveContext.hpp>
#include <AIS_InteractiveObject.hpp>
#include <AIS_Plane.hpp>
#include <Geom_Plane.hpp>
#include <gp_Pln.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd_Geometry.hpp>
#include <TDataXtd_Plane.hpp>
#include <TDF_Label.hpp>
#include <TNaming_Tool.hpp>
#include <TPrsStd_PlaneDriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TPrsStd_PlaneDriver, TPrsStd_Driver)

TPrsStd_PlaneDriver::TPrsStd_PlaneDriver() = default;

bool TPrsStd_PlaneDriver::Update(const TDF_Label&                    aLabel,
                                 occ::handle<AIS_InteractiveObject>& anAISObject)
{
  occ::handle<TDataXtd_Plane> apPlane;

  if (!aLabel.FindAttribute(TDataXtd_Plane::GetID(), apPlane))
  {
    return false;
  }

  gp_Pln pln;
  if (!TDataXtd_Geometry::Plane(aLabel, pln))
  {
    return false;
  }
  occ::handle<Geom_Plane> apt = new Geom_Plane(pln);

  occ::handle<AIS_Plane> aisplane;
  if (anAISObject.IsNull())
    aisplane = new AIS_Plane(apt, pln.Location());
  else
  {
    aisplane = occ::down_cast<AIS_Plane>(anAISObject);
    if (aisplane.IsNull())
      aisplane = new AIS_Plane(apt, pln.Location());
    else
    {
      aisplane->SetComponent(apt);
      aisplane->SetCenter(pln.Location());
      aisplane->ResetTransformation();
      aisplane->SetToUpdate();
      aisplane->UpdateSelection();
    }
  }
  anAISObject = aisplane;
  return true;
}
