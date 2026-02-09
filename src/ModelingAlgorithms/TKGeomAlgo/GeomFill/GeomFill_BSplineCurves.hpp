#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomFill_FillingStyle.hpp>
class Geom_BSplineSurface;
class Geom_BSplineCurve;

class GeomFill_BSplineCurves
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_BSplineCurves();

  Standard_EXPORT GeomFill_BSplineCurves(const occ::handle<Geom_BSplineCurve>& C1,
                                         const occ::handle<Geom_BSplineCurve>& C2,
                                         const occ::handle<Geom_BSplineCurve>& C3,
                                         const occ::handle<Geom_BSplineCurve>& C4,
                                         const GeomFill_FillingStyle           Type);

  Standard_EXPORT GeomFill_BSplineCurves(const occ::handle<Geom_BSplineCurve>& C1,
                                         const occ::handle<Geom_BSplineCurve>& C2,
                                         const occ::handle<Geom_BSplineCurve>& C3,
                                         const GeomFill_FillingStyle           Type);

  Standard_EXPORT GeomFill_BSplineCurves(const occ::handle<Geom_BSplineCurve>& C1,
                                         const occ::handle<Geom_BSplineCurve>& C2,
                                         const GeomFill_FillingStyle           Type);

  Standard_EXPORT void Init(const occ::handle<Geom_BSplineCurve>& C1,
                            const occ::handle<Geom_BSplineCurve>& C2,
                            const occ::handle<Geom_BSplineCurve>& C3,
                            const occ::handle<Geom_BSplineCurve>& C4,
                            const GeomFill_FillingStyle           Type);

  Standard_EXPORT void Init(const occ::handle<Geom_BSplineCurve>& C1,
                            const occ::handle<Geom_BSplineCurve>& C2,
                            const occ::handle<Geom_BSplineCurve>& C3,
                            const GeomFill_FillingStyle           Type);

  Standard_EXPORT void Init(const occ::handle<Geom_BSplineCurve>& C1,
                            const occ::handle<Geom_BSplineCurve>& C2,
                            const GeomFill_FillingStyle           Type);

  const occ::handle<Geom_BSplineSurface>& Surface() const;

private:
  occ::handle<Geom_BSplineSurface> mySurface;
};

inline const occ::handle<Geom_BSplineSurface>& GeomFill_BSplineCurves::Surface() const
{
  return mySurface;
}
