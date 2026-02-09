#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntPatch_Line.hpp>
#include <NCollection_Sequence.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <NCollection_List.hpp>

class Adaptor3d_TopolTool;
class IntPatch_Polyhedron;
class IntPatch_PrmPrmIntersection_T3Bits;
class IntSurf_LineOn2S;

class IntPatch_PrmPrmIntersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_PrmPrmIntersection();

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Caro1,
                               const IntPatch_Polyhedron&              Polyhedron1,
                               const occ::handle<Adaptor3d_TopolTool>& Domain1,
                               const occ::handle<Adaptor3d_Surface>&   Caro2,
                               const IntPatch_Polyhedron&              Polyhedron2,
                               const occ::handle<Adaptor3d_TopolTool>& Domain2,
                               const double                            TolTangency,
                               const double                            Epsilon,
                               const double                            Deflection,
                               const double                            Increment);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Caro1,
                               const IntPatch_Polyhedron&              Polyhedron1,
                               const occ::handle<Adaptor3d_TopolTool>& Domain1,
                               const double                            TolTangency,
                               const double                            Epsilon,
                               const double                            Deflection,
                               const double                            Increment);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Caro1,
                               const occ::handle<Adaptor3d_TopolTool>& Domain1,
                               const occ::handle<Adaptor3d_Surface>&   Caro2,
                               const occ::handle<Adaptor3d_TopolTool>& Domain2,
                               const double                            TolTangency,
                               const double                            Epsilon,
                               const double                            Deflection,
                               const double                            Increment,
                               const bool                              ClearFlag = true);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Caro1,
                               const occ::handle<Adaptor3d_TopolTool>& Domain1,
                               const occ::handle<Adaptor3d_Surface>&   Caro2,
                               const occ::handle<Adaptor3d_TopolTool>& Domain2,
                               const double                            TolTangency,
                               const double                            Epsilon,
                               const double                            Deflection,
                               const double                            Increment,
                               NCollection_List<IntSurf_PntOn2S>&      ListOfPnts);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Caro1,
                               const occ::handle<Adaptor3d_TopolTool>& Domain1,
                               const occ::handle<Adaptor3d_Surface>&   Caro2,
                               const occ::handle<Adaptor3d_TopolTool>& Domain2,
                               const double                            U1,
                               const double                            V1,
                               const double                            U2,
                               const double                            V2,
                               const double                            TolTangency,
                               const double                            Epsilon,
                               const double                            Deflection,
                               const double                            Increment);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Caro1,
                               const occ::handle<Adaptor3d_TopolTool>& Domain1,
                               const double                            TolTangency,
                               const double                            Epsilon,
                               const double                            Deflection,
                               const double                            Increment);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Caro1,
                               const occ::handle<Adaptor3d_TopolTool>& Domain1,
                               const occ::handle<Adaptor3d_Surface>&   Caro2,
                               const IntPatch_Polyhedron&              Polyhedron2,
                               const occ::handle<Adaptor3d_TopolTool>& Domain2,
                               const double                            TolTangency,
                               const double                            Epsilon,
                               const double                            Deflection,
                               const double                            Increment);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Caro1,
                               const IntPatch_Polyhedron&              Polyhedron1,
                               const occ::handle<Adaptor3d_TopolTool>& Domain1,
                               const occ::handle<Adaptor3d_Surface>&   Caro2,
                               const occ::handle<Adaptor3d_TopolTool>& Domain2,
                               const double                            TolTangency,
                               const double                            Epsilon,
                               const double                            Deflection,
                               const double                            Increment);

  bool IsDone() const;

  bool IsEmpty() const;

  int NbLines() const;

  const occ::handle<IntPatch_Line>& Line(const int Index) const;

  Standard_EXPORT occ::handle<IntPatch_Line> NewLine(const occ::handle<Adaptor3d_Surface>& Caro1,
                                                     const occ::handle<Adaptor3d_Surface>& Caro2,
                                                     const int IndexLine,
                                                     const int LowPoint,
                                                     const int HighPoint,
                                                     const int NbPoints) const;

  int GrilleInteger(const int ix, const int iy, const int iz) const;

  void IntegerGrille(const int t, int& ix, int& iy, int& iz) const;

  int DansGrille(const int t) const;

  int NbPointsGrille() const;

  Standard_EXPORT void RemplitLin(const int                           x1,
                                  const int                           y1,
                                  const int                           z1,
                                  const int                           x2,
                                  const int                           y2,
                                  const int                           z2,
                                  IntPatch_PrmPrmIntersection_T3Bits& Map) const;

  Standard_EXPORT void RemplitTri(const int                           x1,
                                  const int                           y1,
                                  const int                           z1,
                                  const int                           x2,
                                  const int                           y2,
                                  const int                           z2,
                                  const int                           x3,
                                  const int                           y3,
                                  const int                           z3,
                                  IntPatch_PrmPrmIntersection_T3Bits& Map) const;

  Standard_EXPORT void Remplit(const int                           a,
                               const int                           b,
                               const int                           c,
                               IntPatch_PrmPrmIntersection_T3Bits& Map) const;

  int CodeReject(const double x1,
                 const double y1,
                 const double z1,
                 const double x2,
                 const double y2,
                 const double z2,
                 const double x3,
                 const double y3,
                 const double z3) const;

  Standard_EXPORT void PointDepart(occ::handle<IntSurf_LineOn2S>&        LineOn2S,
                                   const occ::handle<Adaptor3d_Surface>& S1,
                                   const int                             SU1,
                                   const int                             SV1,
                                   const occ::handle<Adaptor3d_Surface>& S2,
                                   const int                             SU2,
                                   const int                             SV2) const;

private:
  bool                                             done;
  bool                                             empt;
  NCollection_Sequence<occ::handle<IntPatch_Line>> SLin;
};

#include <StdFail_NotDone.hpp>
#include <IntPatch_Line.hpp>

#define _DECAL 7
#define _DECAL2 14
#define _BASE 128
#define _BASEM1 127

inline int IntPatch_PrmPrmIntersection::NbLines() const
{
  if (!done)
    throw StdFail_NotDone(" IntPatch_PrmPrmIntersection ");
  return (SLin.Length());
}

inline const occ::handle<IntPatch_Line>& IntPatch_PrmPrmIntersection::Line(const int n) const
{
  if (!done)
    throw StdFail_NotDone(" IntPatch_PrmPrmIntersection ");
  return (SLin.Value(n));
}

inline bool IntPatch_PrmPrmIntersection::IsEmpty() const
{
  if (!done)
    throw StdFail_NotDone(" IntPatch_PrmPrmIntersection ");
  return (empt);
}

inline bool IntPatch_PrmPrmIntersection::IsDone() const
{
  return (done);
}

inline int IntPatch_PrmPrmIntersection::GrilleInteger(const int ix,
                                                      const int iy,
                                                      const int iz) const
{
  int tz = iz << _DECAL2;
  int ty = iy << _DECAL;
  int t  = ix;
  t |= ty;
  t |= tz;
  return (t);
}

inline void IntPatch_PrmPrmIntersection::IntegerGrille(const int tt,
                                                       int&      ix,
                                                       int&      iy,
                                                       int&      iz) const
{
  int t = tt;
  ix    = t & _BASEM1;
  t >>= _DECAL;
  iy = t & _BASEM1;
  t >>= _DECAL;
  iz = t;
}

inline int IntPatch_PrmPrmIntersection::DansGrille(const int t) const
{
  if (t >= 0)
  {
    if (t < _BASE)
    {
      return (1);
    }
  }
  return (0);
}

inline int IntPatch_PrmPrmIntersection::NbPointsGrille() const
{
  return (_BASE);
}

inline int IntPatch_PrmPrmIntersection::CodeReject(const double x0,
                                                   const double y0,
                                                   const double z0,
                                                   const double x1,
                                                   const double y1,
                                                   const double z1,
                                                   const double x,
                                                   const double y,
                                                   const double z) const
{
  int code = 0;
  if (x < x0)
    code = 1;
  if (y < y0)
    code |= 2;
  if (z < z0)
    code |= 4;
  if (x > x1)
    code |= 8;
  if (y > y1)
    code |= 16;
  if (z > z1)
    code |= 32;
  return (code);
}
