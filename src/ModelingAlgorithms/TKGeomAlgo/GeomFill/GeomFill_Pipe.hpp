#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomFill_Trihedron.hpp>
#include <GeomAbs_Shape.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <GeomFill_PipeError.hpp>

class Geom_Surface;
class GeomFill_LocationLaw;
class GeomFill_SectionLaw;
class Geom_Curve;
class Geom2d_Curve;
class gp_Dir;

class GeomFill_Pipe
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_Pipe();

  Standard_EXPORT GeomFill_Pipe(const occ::handle<Geom_Curve>& Path, const double Radius);

  Standard_EXPORT GeomFill_Pipe(const occ::handle<Geom_Curve>& Path,
                                const occ::handle<Geom_Curve>& FirstSect,
                                const GeomFill_Trihedron       Option = GeomFill_IsCorrectedFrenet);

  Standard_EXPORT GeomFill_Pipe(const occ::handle<Geom2d_Curve>& Path,
                                const occ::handle<Geom_Surface>& Support,
                                const occ::handle<Geom_Curve>&   FirstSect);

  Standard_EXPORT GeomFill_Pipe(const occ::handle<Geom_Curve>& Path,
                                const occ::handle<Geom_Curve>& FirstSect,
                                const gp_Dir&                  Dir);

  Standard_EXPORT GeomFill_Pipe(const occ::handle<Geom_Curve>& Path,
                                const occ::handle<Geom_Curve>& FirstSect,
                                const occ::handle<Geom_Curve>& LastSect);

  Standard_EXPORT GeomFill_Pipe(const occ::handle<Geom_Curve>&                       Path,
                                const NCollection_Sequence<occ::handle<Geom_Curve>>& NSections);

  Standard_EXPORT GeomFill_Pipe(const occ::handle<Geom_Curve>& Path,
                                const occ::handle<Geom_Curve>& Curve1,
                                const occ::handle<Geom_Curve>& Curve2,
                                const double                   Radius);

  Standard_EXPORT GeomFill_Pipe(const occ::handle<Adaptor3d_Curve>& Path,
                                const occ::handle<Adaptor3d_Curve>& Curve1,
                                const occ::handle<Adaptor3d_Curve>& Curve2,
                                const double                        Radius);

  Standard_EXPORT GeomFill_Pipe(const occ::handle<Geom_Curve>&      Path,
                                const occ::handle<Adaptor3d_Curve>& Guide,
                                const occ::handle<Geom_Curve>&      FirstSect,
                                const bool                          ByACR,
                                const bool                          rotat);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Path, const double Radius);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Path,
                            const occ::handle<Geom_Curve>& FirstSect,
                            const GeomFill_Trihedron       Option = GeomFill_IsCorrectedFrenet);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& Path,
                            const occ::handle<Geom_Surface>& Support,
                            const occ::handle<Geom_Curve>&   FirstSect);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Path,
                            const occ::handle<Geom_Curve>& FirstSect,
                            const gp_Dir&                  Dir);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Path,
                            const occ::handle<Geom_Curve>& FirstSect,
                            const occ::handle<Geom_Curve>& LastSect);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>&                       Path,
                            const NCollection_Sequence<occ::handle<Geom_Curve>>& NSections);

  Standard_EXPORT void Init(const occ::handle<Adaptor3d_Curve>& Path,
                            const occ::handle<Adaptor3d_Curve>& Curve1,
                            const occ::handle<Adaptor3d_Curve>& Curve2,
                            const double                        Radius);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>&      Path,
                            const occ::handle<Adaptor3d_Curve>& Guide,
                            const occ::handle<Geom_Curve>&      FirstSect,
                            const bool                          ByACR,
                            const bool                          rotat);

  Standard_EXPORT void Perform(const bool WithParameters = false, const bool myPolynomial = false);

  Standard_EXPORT void Perform(const double        Tol,
                               const bool          Polynomial,
                               const GeomAbs_Shape Conti        = GeomAbs_C1,
                               const int           MaxDegree    = 11,
                               const int           NbMaxSegment = 30);

  const occ::handle<Geom_Surface>& Surface() const;

  bool ExchangeUV() const;

  void GenerateParticularCase(const bool B);

  bool GenerateParticularCase() const;

  double ErrorOnSurf() const;

  bool IsDone() const;

  GeomFill_PipeError GetStatus() const { return myStatus; }

private:
  Standard_EXPORT void Init();

  Standard_EXPORT void ApproxSurf(const bool WithParameters);

  Standard_EXPORT bool KPartT4();

  GeomFill_PipeError                myStatus;
  double                            myRadius;
  double                            myError;
  occ::handle<Adaptor3d_Curve>      myAdpPath;
  occ::handle<Adaptor3d_Curve>      myAdpFirstSect;
  occ::handle<Adaptor3d_Curve>      myAdpLastSect;
  occ::handle<Geom_Surface>         mySurface;
  occ::handle<GeomFill_LocationLaw> myLoc;
  occ::handle<GeomFill_SectionLaw>  mySec;
  int                               myType;
  bool                              myExchUV;
  bool                              myKPart;
  bool                              myPolynomial;
};

inline const occ::handle<Geom_Surface>& GeomFill_Pipe::Surface() const
{
  return mySurface;
}

inline bool GeomFill_Pipe::ExchangeUV() const
{
  return myExchUV;
}

inline void GeomFill_Pipe::GenerateParticularCase(const bool B)
{
  myKPart = B;
}

inline bool GeomFill_Pipe::GenerateParticularCase() const
{
  return myKPart;
}

inline double GeomFill_Pipe::ErrorOnSurf() const
{
  return myError;
}

inline bool GeomFill_Pipe::IsDone() const
{
  return myStatus == GeomFill_PipeOk;
}
