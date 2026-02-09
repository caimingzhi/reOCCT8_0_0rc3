#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntPatch_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <IntPatch_Line.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <NCollection_List.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <NCollection_Vector.hpp>

class Adaptor3d_TopolTool;

class IntPatch_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_Intersection();

  Standard_EXPORT IntPatch_Intersection(const occ::handle<Adaptor3d_Surface>&   S1,
                                        const occ::handle<Adaptor3d_TopolTool>& D1,
                                        const occ::handle<Adaptor3d_Surface>&   S2,
                                        const occ::handle<Adaptor3d_TopolTool>& D2,
                                        const double                            TolArc,
                                        const double                            TolTang);

  Standard_EXPORT IntPatch_Intersection(const occ::handle<Adaptor3d_Surface>&   S1,
                                        const occ::handle<Adaptor3d_TopolTool>& D1,
                                        const double                            TolArc,
                                        const double                            TolTang);

  Standard_EXPORT void SetTolerances(const double TolArc,
                                     const double TolTang,
                                     const double UVMaxStep,
                                     const double Fleche);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   S1,
                               const occ::handle<Adaptor3d_TopolTool>& D1,
                               const occ::handle<Adaptor3d_Surface>&   S2,
                               const occ::handle<Adaptor3d_TopolTool>& D2,
                               const double                            TolArc,
                               const double                            TolTang,
                               const bool                              isGeomInt            = true,
                               const bool                              theIsReqToKeepRLine  = false,
                               const bool                              theIsReqToPostWLProc = true);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   S1,
                               const occ::handle<Adaptor3d_TopolTool>& D1,
                               const occ::handle<Adaptor3d_Surface>&   S2,
                               const occ::handle<Adaptor3d_TopolTool>& D2,
                               const double                            TolArc,
                               const double                            TolTang,
                               NCollection_List<IntSurf_PntOn2S>&      LOfPnts,
                               const bool                              isGeomInt            = true,
                               const bool                              theIsReqToKeepRLine  = false,
                               const bool                              theIsReqToPostWLProc = true);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   S1,
                               const occ::handle<Adaptor3d_TopolTool>& D1,
                               const occ::handle<Adaptor3d_Surface>&   S2,
                               const occ::handle<Adaptor3d_TopolTool>& D2,
                               const double                            U1,
                               const double                            V1,
                               const double                            U2,
                               const double                            V2,
                               const double                            TolArc,
                               const double                            TolTang);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   S1,
                               const occ::handle<Adaptor3d_TopolTool>& D1,
                               const double                            TolArc,
                               const double                            TolTang);

  bool IsDone() const;

  bool IsEmpty() const;

  bool TangentFaces() const;

  bool OppositeFaces() const;

  int NbPnts() const;

  const IntPatch_Point& Point(const int Index) const;

  int NbLines() const;

  const occ::handle<IntPatch_Line>& Line(const int Index) const;

  Standard_EXPORT const NCollection_Sequence<occ::handle<IntPatch_Line>>& SequenceOfLine() const;

  Standard_EXPORT void Dump(const int                               Mode,
                            const occ::handle<Adaptor3d_Surface>&   S1,
                            const occ::handle<Adaptor3d_TopolTool>& D1,
                            const occ::handle<Adaptor3d_Surface>&   S2,
                            const occ::handle<Adaptor3d_TopolTool>& D2) const;

  Standard_EXPORT static bool CheckSingularPoints(const occ::handle<Adaptor3d_Surface>&   theS1,
                                                  const occ::handle<Adaptor3d_TopolTool>& theD1,
                                                  const occ::handle<Adaptor3d_Surface>&   theS2,
                                                  double&                                 theDist);

  Standard_EXPORT static double DefineUVMaxStep(const occ::handle<Adaptor3d_Surface>&   theS1,
                                                const occ::handle<Adaptor3d_TopolTool>& theD1,
                                                const occ::handle<Adaptor3d_Surface>&   theS2,
                                                const occ::handle<Adaptor3d_TopolTool>& theD2);

  Standard_EXPORT static void PrepareSurfaces(
    const occ::handle<Adaptor3d_Surface>&               theS1,
    const occ::handle<Adaptor3d_TopolTool>&             theD1,
    const occ::handle<Adaptor3d_Surface>&               theS2,
    const occ::handle<Adaptor3d_TopolTool>&             theD2,
    const double                                        Tol,
    NCollection_Vector<occ::handle<Adaptor3d_Surface>>& theSeqHS1,
    NCollection_Vector<occ::handle<Adaptor3d_Surface>>& theSeqHS2);

private:
  Standard_EXPORT void ParamParamPerfom(const occ::handle<Adaptor3d_Surface>&   S1,
                                        const occ::handle<Adaptor3d_TopolTool>& D1,
                                        const occ::handle<Adaptor3d_Surface>&   S2,
                                        const occ::handle<Adaptor3d_TopolTool>& D2,
                                        const double                            TolArc,
                                        const double                            TolTang,
                                        NCollection_List<IntSurf_PntOn2S>&      LOfPnts,
                                        const GeomAbs_SurfaceType               typs1,
                                        const GeomAbs_SurfaceType               typs2);

  Standard_EXPORT void GeomGeomPerfom(const occ::handle<Adaptor3d_Surface>&   S1,
                                      const occ::handle<Adaptor3d_TopolTool>& D1,
                                      const occ::handle<Adaptor3d_Surface>&   S2,
                                      const occ::handle<Adaptor3d_TopolTool>& D2,
                                      const double                            TolArc,
                                      const double                            TolTang,
                                      NCollection_List<IntSurf_PntOn2S>&      LOfPnts,
                                      const GeomAbs_SurfaceType               typs1,
                                      const GeomAbs_SurfaceType               typs2,
                                      const bool                              theIsReqToKeepRLine);

  Standard_EXPORT void GeomParamPerfom(const occ::handle<Adaptor3d_Surface>&   S1,
                                       const occ::handle<Adaptor3d_TopolTool>& D1,
                                       const occ::handle<Adaptor3d_Surface>&   S2,
                                       const occ::handle<Adaptor3d_TopolTool>& D2,
                                       const bool                              isNotAnalitical,
                                       const GeomAbs_SurfaceType               typs1,
                                       const GeomAbs_SurfaceType               typs2);

  bool                                             done;
  bool                                             empt;
  bool                                             tgte;
  bool                                             oppo;
  NCollection_Sequence<IntPatch_Point>             spnt;
  NCollection_Sequence<occ::handle<IntPatch_Line>> slin;
  double                                           myTolArc;
  double                                           myTolTang;
  double                                           myUVMaxStep;
  double                                           myFleche;
  bool                                             myIsStartPnt;
  double                                           myU1Start;
  double                                           myV1Start;
  double                                           myU2Start;
  double                                           myV2Start;
};

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <IntPatch_Line.hpp>

inline bool IntPatch_Intersection::IsDone() const
{
  return done;
}

inline bool IntPatch_Intersection::IsEmpty() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return empt;
}

inline bool IntPatch_Intersection::TangentFaces() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return tgte;
}

inline bool IntPatch_Intersection::OppositeFaces() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (!tgte)
  {
    throw Standard_DomainError();
  }
  return oppo;
}

inline int IntPatch_Intersection::NbPnts() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return spnt.Length();
}

inline const IntPatch_Point& IntPatch_Intersection::Point(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return spnt(Index);
}

inline int IntPatch_Intersection::NbLines() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return slin.Length();
}

inline const occ::handle<IntPatch_Line>& IntPatch_Intersection::Line(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return slin(Index);
}
