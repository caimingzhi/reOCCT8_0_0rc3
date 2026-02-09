#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToIGES_GeomEntity.hpp>
class IGESData_IGESEntity;
class Geom_Curve;
class Geom_BoundedCurve;
class Geom_BSplineCurve;
class Geom_BezierCurve;
class Geom_TrimmedCurve;
class Geom_Conic;
class Geom_Circle;
class Geom_Ellipse;
class Geom_Hyperbola;
class Geom_Line;
class Geom_Parabola;
class Geom_OffsetCurve;

class GeomToIGES_GeomCurve : public GeomToIGES_GeomEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToIGES_GeomCurve();

  Standard_EXPORT GeomToIGES_GeomCurve(const GeomToIGES_GeomEntity& GE);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_Curve>& start,
    const double                   Udeb,
    const double                   Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_BoundedCurve>& start,
    const double                          Udeb,
    const double                          Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_BSplineCurve>& start,
    const double                          Udeb,
    const double                          Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_BezierCurve>& start,
    const double                         Udeb,
    const double                         Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_TrimmedCurve>& start,
    const double                          Udeb,
    const double                          Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_Conic>& start,
    const double                   Udeb,
    const double                   Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_Circle>& start,
    const double                    Udeb,
    const double                    Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_Ellipse>& start,
    const double                     Udeb,
    const double                     Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_Hyperbola>& start,
    const double                       Udeb,
    const double                       Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_Line>& start,
    const double                  Udeb,
    const double                  Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_Parabola>& start,
    const double                      Udeb,
    const double                      Ufin);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCurve(
    const occ::handle<Geom_OffsetCurve>& start,
    const double                         Udeb,
    const double                         Ufin);
};
