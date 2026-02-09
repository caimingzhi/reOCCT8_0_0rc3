#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomFill_FillingStyle.hpp>
class Geom_BezierSurface;
class Geom_BezierCurve;

class GeomFill_BezierCurves
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_BezierCurves();

  Standard_EXPORT GeomFill_BezierCurves(const occ::handle<Geom_BezierCurve>& C1,
                                        const occ::handle<Geom_BezierCurve>& C2,
                                        const occ::handle<Geom_BezierCurve>& C3,
                                        const occ::handle<Geom_BezierCurve>& C4,
                                        const GeomFill_FillingStyle          Type);

  Standard_EXPORT GeomFill_BezierCurves(const occ::handle<Geom_BezierCurve>& C1,
                                        const occ::handle<Geom_BezierCurve>& C2,
                                        const occ::handle<Geom_BezierCurve>& C3,
                                        const GeomFill_FillingStyle          Type);

  Standard_EXPORT GeomFill_BezierCurves(const occ::handle<Geom_BezierCurve>& C1,
                                        const occ::handle<Geom_BezierCurve>& C2,
                                        const GeomFill_FillingStyle          Type);

  Standard_EXPORT void Init(const occ::handle<Geom_BezierCurve>& C1,
                            const occ::handle<Geom_BezierCurve>& C2,
                            const occ::handle<Geom_BezierCurve>& C3,
                            const occ::handle<Geom_BezierCurve>& C4,
                            const GeomFill_FillingStyle          Type);

  Standard_EXPORT void Init(const occ::handle<Geom_BezierCurve>& C1,
                            const occ::handle<Geom_BezierCurve>& C2,
                            const occ::handle<Geom_BezierCurve>& C3,
                            const GeomFill_FillingStyle          Type);

  Standard_EXPORT void Init(const occ::handle<Geom_BezierCurve>& C1,
                            const occ::handle<Geom_BezierCurve>& C2,
                            const GeomFill_FillingStyle          Type);

  const occ::handle<Geom_BezierSurface>& Surface() const;

private:
  occ::handle<Geom_BezierSurface> mySurface;
};

inline const occ::handle<Geom_BezierSurface>& GeomFill_BezierCurves::Surface() const
{
  return mySurface;
}
