#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_ExtPS.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <Extrema_ExtAlgo.hpp>
#include <Extrema_ExtFlag.hpp>
class gp_Pnt;
class Geom_Surface;

class GeomAPI_ProjectPointOnSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomAPI_ProjectPointOnSurf();

  Standard_EXPORT GeomAPI_ProjectPointOnSurf(const gp_Pnt&                    P,
                                             const occ::handle<Geom_Surface>& Surface,
                                             const Extrema_ExtAlgo Algo = Extrema_ExtAlgo_Grad);

  Standard_EXPORT GeomAPI_ProjectPointOnSurf(const gp_Pnt&                    P,
                                             const occ::handle<Geom_Surface>& Surface,
                                             const double                     Tolerance,
                                             const Extrema_ExtAlgo Algo = Extrema_ExtAlgo_Grad);

  Standard_EXPORT GeomAPI_ProjectPointOnSurf(const gp_Pnt&                    P,
                                             const occ::handle<Geom_Surface>& Surface,
                                             const double                     Umin,
                                             const double                     Usup,
                                             const double                     Vmin,
                                             const double                     Vsup,
                                             const double                     Tolerance,
                                             const Extrema_ExtAlgo Algo = Extrema_ExtAlgo_Grad);

  Standard_EXPORT GeomAPI_ProjectPointOnSurf(const gp_Pnt&                    P,
                                             const occ::handle<Geom_Surface>& Surface,
                                             const double                     Umin,
                                             const double                     Usup,
                                             const double                     Vmin,
                                             const double                     Vsup,
                                             const Extrema_ExtAlgo Algo = Extrema_ExtAlgo_Grad);

  Standard_EXPORT void Init(const gp_Pnt&                    P,
                            const occ::handle<Geom_Surface>& Surface,
                            const double                     Tolerance,
                            const Extrema_ExtAlgo            Algo = Extrema_ExtAlgo_Grad);

  Standard_EXPORT void Init(const gp_Pnt&                    P,
                            const occ::handle<Geom_Surface>& Surface,
                            const Extrema_ExtAlgo            Algo = Extrema_ExtAlgo_Grad);

  Standard_EXPORT void Init(const gp_Pnt&                    P,
                            const occ::handle<Geom_Surface>& Surface,
                            const double                     Umin,
                            const double                     Usup,
                            const double                     Vmin,
                            const double                     Vsup,
                            const double                     Tolerance,
                            const Extrema_ExtAlgo            Algo = Extrema_ExtAlgo_Grad);

  Standard_EXPORT void Init(const gp_Pnt&                    P,
                            const occ::handle<Geom_Surface>& Surface,
                            const double                     Umin,
                            const double                     Usup,
                            const double                     Vmin,
                            const double                     Vsup,
                            const Extrema_ExtAlgo            Algo = Extrema_ExtAlgo_Grad);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& Surface,
                            const double                     Umin,
                            const double                     Usup,
                            const double                     Vmin,
                            const double                     Vsup,
                            const double                     Tolerance,
                            const Extrema_ExtAlgo            Algo = Extrema_ExtAlgo_Grad);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& Surface,
                            const double                     Umin,
                            const double                     Usup,
                            const double                     Vmin,
                            const double                     Vsup,
                            const Extrema_ExtAlgo            Algo = Extrema_ExtAlgo_Grad);

  void SetExtremaAlgo(const Extrema_ExtAlgo theAlgo) { myExtPS.SetAlgo(theAlgo); }

  void SetExtremaFlag(const Extrema_ExtFlag theExtFlag) { myExtPS.SetFlag(theExtFlag); }

  Standard_EXPORT void Perform(const gp_Pnt& P);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbPoints() const;
  Standard_EXPORT     operator int() const;

  Standard_EXPORT gp_Pnt Point(const int Index) const;

  Standard_EXPORT void Parameters(const int Index, double& U, double& V) const;

  Standard_EXPORT double Distance(const int Index) const;

  Standard_EXPORT gp_Pnt NearestPoint() const;
  Standard_EXPORT        operator gp_Pnt() const;

  Standard_EXPORT void LowerDistanceParameters(double& U, double& V) const;

  Standard_EXPORT double LowerDistance() const;
  Standard_EXPORT        operator double() const;

  const Extrema_ExtPS& Extrema() const;

private:
  Standard_EXPORT void Init();

  bool                myIsDone;
  int                 myIndex;
  Extrema_ExtPS       myExtPS;
  GeomAdaptor_Surface myGeomAdaptor;
};

inline const Extrema_ExtPS& GeomAPI_ProjectPointOnSurf::Extrema() const
{
  return myExtPS;
}
