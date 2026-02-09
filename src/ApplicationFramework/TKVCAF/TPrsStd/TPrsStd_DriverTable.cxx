#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd_Axis.hpp>
#include <TDataXtd_Constraint.hpp>
#include <TDataXtd_Geometry.hpp>
#include <TDataXtd_Plane.hpp>
#include <TDataXtd_Point.hpp>
#include <TNaming_NamedShape.hpp>
#include <TPrsStd_AxisDriver.hpp>
#include <TPrsStd_ConstraintDriver.hpp>
#include <TPrsStd_Driver.hpp>
#include <TPrsStd_DriverTable.hpp>
#include <TPrsStd_GeometryDriver.hpp>
#include <TPrsStd_NamedShapeDriver.hpp>
#include <TPrsStd_PlaneDriver.hpp>
#include <TPrsStd_PointDriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TPrsStd_DriverTable, Standard_Transient)

static occ::handle<TPrsStd_DriverTable> drivertable;

occ::handle<TPrsStd_DriverTable> TPrsStd_DriverTable::Get()
{
  if (drivertable.IsNull())
  {
    drivertable = new TPrsStd_DriverTable;

    new occ::handle<TPrsStd_DriverTable>(drivertable);
#ifdef OCCT_DEBUG
    std::cout << "The new TPrsStd_DriverTable was created" << std::endl;
#endif
  }
  return drivertable;
}

TPrsStd_DriverTable::TPrsStd_DriverTable()
{
  InitStandardDrivers();
}

void TPrsStd_DriverTable::InitStandardDrivers()
{
  if (myDrivers.Extent() > 0)
    return;

  occ::handle<TPrsStd_AxisDriver>       axisdrv   = new TPrsStd_AxisDriver;
  occ::handle<TPrsStd_ConstraintDriver> cnstrdrv  = new TPrsStd_ConstraintDriver;
  occ::handle<TPrsStd_GeometryDriver>   geomdrv   = new TPrsStd_GeometryDriver;
  occ::handle<TPrsStd_NamedShapeDriver> nshapedrv = new TPrsStd_NamedShapeDriver;
  occ::handle<TPrsStd_PlaneDriver>      planedrv  = new TPrsStd_PlaneDriver;
  occ::handle<TPrsStd_PointDriver>      pointdrv  = new TPrsStd_PointDriver;

  myDrivers.Bind(TDataXtd_Axis::GetID(), axisdrv);
  myDrivers.Bind(TDataXtd_Constraint::GetID(), cnstrdrv);
  myDrivers.Bind(TDataXtd_Geometry::GetID(), geomdrv);
  myDrivers.Bind(TNaming_NamedShape::GetID(), nshapedrv);
  myDrivers.Bind(TDataXtd_Plane::GetID(), planedrv);
  myDrivers.Bind(TDataXtd_Point::GetID(), pointdrv);
}

bool TPrsStd_DriverTable::AddDriver(const Standard_GUID&               guid,
                                    const occ::handle<TPrsStd_Driver>& driver)
{
  return myDrivers.Bind(guid, driver);
}

bool TPrsStd_DriverTable::FindDriver(const Standard_GUID&         guid,
                                     occ::handle<TPrsStd_Driver>& driver) const
{
  if (myDrivers.IsBound(guid))
  {
    driver = myDrivers.Find(guid);
    return true;
  }
  return false;
}

bool TPrsStd_DriverTable::RemoveDriver(const Standard_GUID& guid)
{
  return myDrivers.UnBind(guid);
}

void TPrsStd_DriverTable::Clear()
{
  myDrivers.Clear();
}
