#pragma once

#include <Extrema_ExtPS.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_Sequence.hpp>

class Geom_Surface;
class Geom_Curve;

class ShapeAnalysis_Surface : public Standard_Transient
{

public:
  Standard_EXPORT ShapeAnalysis_Surface(const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void Init(const occ::handle<ShapeAnalysis_Surface>& other);

  Standard_EXPORT void SetDomain(const double U1,
                                 const double U2,
                                 const double V1,
                                 const double V2);

  const occ::handle<Geom_Surface>& Surface() const;

  Standard_EXPORT const occ::handle<GeomAdaptor_Surface>& Adaptor3d();

  const occ::handle<GeomAdaptor_Surface>& TrueAdaptor3d() const;

  double Gap() const;

  gp_Pnt Value(const double u, const double v);

  gp_Pnt Value(const gp_Pnt2d& p2d);

  Standard_EXPORT bool HasSingularities(const double preci);

  Standard_EXPORT int NbSingularities(const double preci);

  Standard_EXPORT bool Singularity(const int num,
                                   double&   preci,
                                   gp_Pnt&   P3d,
                                   gp_Pnt2d& firstP2d,
                                   gp_Pnt2d& lastP2d,
                                   double&   firstpar,
                                   double&   lastpar,
                                   bool&     uisodeg);

  Standard_EXPORT bool IsDegenerated(const gp_Pnt& P3d, const double preci);

  Standard_EXPORT bool DegeneratedValues(const gp_Pnt& P3d,
                                         const double  preci,
                                         gp_Pnt2d&     firstP2d,
                                         gp_Pnt2d&     lastP2d,
                                         double&       firstpar,
                                         double&       lastpar,
                                         const bool    forward = true);

  Standard_EXPORT bool ProjectDegenerated(const gp_Pnt&   P3d,
                                          const double    preci,
                                          const gp_Pnt2d& neighbour,
                                          gp_Pnt2d&       result);

  Standard_EXPORT bool ProjectDegenerated(const int                           nbrPnt,
                                          const NCollection_Sequence<gp_Pnt>& points,
                                          NCollection_Sequence<gp_Pnt2d>&     pnt2d,
                                          const double                        preci,
                                          const bool                          direct);

  Standard_EXPORT bool IsDegenerated(const gp_Pnt2d& p2d1,
                                     const gp_Pnt2d& p2d2,
                                     const double    tol,
                                     const double    ratio);

  void Bounds(double& ufirst, double& ulast, double& vfirst, double& vlast) const;

  Standard_EXPORT void ComputeBoundIsos();

  Standard_EXPORT occ::handle<Geom_Curve> UIso(const double U);

  Standard_EXPORT occ::handle<Geom_Curve> VIso(const double V);

  Standard_EXPORT bool IsUClosed(const double preci = -1);

  Standard_EXPORT bool IsVClosed(const double preci = -1);

  Standard_EXPORT gp_Pnt2d ValueOfUV(const gp_Pnt& P3D, const double preci);

  Standard_EXPORT gp_Pnt2d NextValueOfUV(const gp_Pnt2d& p2dPrev,
                                         const gp_Pnt&   P3D,
                                         const double    preci,
                                         const double    maxpreci = -1.0);

  Standard_EXPORT double UVFromIso(const gp_Pnt& P3D, const double preci, double& U, double& V);

  double UCloseVal() const;

  double VCloseVal() const;

  Standard_EXPORT const Bnd_Box& GetBoxUF();

  Standard_EXPORT const Bnd_Box& GetBoxUL();

  Standard_EXPORT const Bnd_Box& GetBoxVF();

  Standard_EXPORT const Bnd_Box& GetBoxVL();

  DEFINE_STANDARD_RTTIEXT(ShapeAnalysis_Surface, Standard_Transient)

protected:
  occ::handle<Geom_Surface>        mySurf;
  occ::handle<GeomAdaptor_Surface> myAdSur;
  Extrema_ExtPS                    myExtPS;
  bool                             myExtOK;
  int                              myNbDeg;
  double                           myPreci[4];
  gp_Pnt                           myP3d[4];
  gp_Pnt2d                         myFirstP2d[4];
  gp_Pnt2d                         myLastP2d[4];
  double                           myFirstPar[4];
  double                           myLastPar[4];
  bool                             myUIsoDeg[4];
  bool                             myIsos;
  double                           myUF;
  double                           myUL;
  double                           myVF;
  double                           myVL;
  occ::handle<Geom_Curve>          myIsoUF;
  occ::handle<Geom_Curve>          myIsoUL;
  occ::handle<Geom_Curve>          myIsoVF;
  occ::handle<Geom_Curve>          myIsoVL;
  bool                             myIsoBoxes;
  Bnd_Box                          myBndUF;
  Bnd_Box                          myBndUL;
  Bnd_Box                          myBndVF;
  Bnd_Box                          myBndVL;
  double                           myGap;
  double                           myUDelt;
  double                           myVDelt;
  double                           myUCloseVal;
  double                           myVCloseVal;

private:
  Standard_EXPORT void ComputeSingularities();

  Standard_EXPORT void ComputeBoxes();

  Standard_EXPORT int SurfaceNewton(const gp_Pnt2d& p2dPrev,
                                    const gp_Pnt&   P3D,
                                    const double    preci,
                                    gp_Pnt2d&       sol);

  Standard_EXPORT void SortSingularities();
};

#include <Geom_Surface.hpp>
#include <GeomAdaptor_Surface.hpp>

inline const occ::handle<Geom_Surface>& ShapeAnalysis_Surface::Surface() const
{
  return mySurf;
}

inline const occ::handle<GeomAdaptor_Surface>& ShapeAnalysis_Surface::TrueAdaptor3d() const
{
  return myAdSur;
}

inline double ShapeAnalysis_Surface::Gap() const
{
  return myGap;
}

inline gp_Pnt ShapeAnalysis_Surface::Value(const double u, const double v)
{
  return myAdSur->Value(u, v);
}

inline gp_Pnt ShapeAnalysis_Surface::Value(const gp_Pnt2d& p2d)
{
  return myAdSur->Value(p2d.X(), p2d.Y());
}

inline void ShapeAnalysis_Surface::Bounds(double& ufirst,
                                          double& ulast,
                                          double& vfirst,
                                          double& vlast) const
{
  ufirst = myUF;
  ulast  = myUL;
  vfirst = myVF;
  vlast  = myVL;
}

inline double ShapeAnalysis_Surface::UCloseVal() const
{
  return myUCloseVal;
}

inline double ShapeAnalysis_Surface::VCloseVal() const
{
  return myVCloseVal;
}
