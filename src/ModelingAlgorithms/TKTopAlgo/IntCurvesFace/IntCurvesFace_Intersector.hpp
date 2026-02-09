#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Bnd_BoundSortBox.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <IntCurveSurface_ThePolyhedronOfHInter.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Face.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>
#include <TopAbs_State.hpp>

#include <memory>

class BRepTopAdaptor_TopolTool;
class gp_Lin;
class gp_Pnt;
class IntCurveSurface_HInter;
class gp_Pnt2d;
class Bnd_Box;

class IntCurvesFace_Intersector : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(IntCurvesFace_Intersector, Standard_Transient)

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurvesFace_Intersector(const TopoDS_Face& F,
                                            const double       aTol,
                                            const bool         aRestr    = true,
                                            const bool         UseBToler = true);

  Standard_EXPORT void Perform(const gp_Lin& L, const double PInf, const double PSup);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>& HCu,
                               const double                        PInf,
                               const double                        PSup);

  Standard_EXPORT GeomAbs_SurfaceType SurfaceType() const;

  bool IsDone() const;

  int NbPnt() const;

  double UParameter(const int I) const;

  double VParameter(const int I) const;

  double WParameter(const int I) const;

  const gp_Pnt& Pnt(const int I) const;

  IntCurveSurface_TransitionOnCurve Transition(const int I) const;

  TopAbs_State State(const int I) const;

  bool IsParallel() const;

  const TopoDS_Face& Face() const;

  Standard_EXPORT TopAbs_State ClassifyUVPoint(const gp_Pnt2d& Puv) const;

  Standard_EXPORT Bnd_Box Bounding() const;

  Standard_EXPORT void SetUseBoundToler(bool UseBToler);

  Standard_EXPORT bool GetUseBoundToler() const;

  Standard_EXPORT ~IntCurvesFace_Intersector() override;

private:
  Standard_EXPORT void InternalCall(const IntCurveSurface_HInter& HICS,
                                    const double                  pinf,
                                    const double                  psup);

  occ::handle<BRepTopAdaptor_TopolTool>                   myTopolTool;
  occ::handle<BRepAdaptor_Surface>                        Hsurface;
  double                                                  Tol;
  NCollection_Sequence<IntCurveSurface_IntersectionPoint> SeqPnt;
  NCollection_Sequence<int>                               mySeqState;
  bool                                                    done;
  bool                                                    myReady;
  int                                                     nbpnt;
  TopoDS_Face                                             face;
  std::unique_ptr<IntCurveSurface_ThePolyhedronOfHInter>  myPolyhedron;
  std::unique_ptr<Bnd_BoundSortBox>                       myBndBounding;
  bool                                                    myUseBoundTol;
  bool                                                    myIsParallel;
};

#include <IntCurveSurface_IntersectionPoint.hpp>
#include <TopAbs_State.hpp>

inline bool IntCurvesFace_Intersector::IsDone() const
{
  return (done);
}

inline int IntCurvesFace_Intersector::NbPnt() const
{
  return (nbpnt);
}

inline const gp_Pnt& IntCurvesFace_Intersector::Pnt(const int i) const
{
  return (SeqPnt.Value(i).Pnt());
}

inline double IntCurvesFace_Intersector::UParameter(const int i) const
{
  return (SeqPnt.Value(i).U());
}

inline double IntCurvesFace_Intersector::VParameter(const int i) const
{
  return (SeqPnt.Value(i).V());
}

inline double IntCurvesFace_Intersector::WParameter(const int i) const
{
  return (SeqPnt.Value(i).W());
}

inline IntCurveSurface_TransitionOnCurve IntCurvesFace_Intersector::Transition(const int i) const
{
  return (SeqPnt.Value(i).Transition());
}

inline TopAbs_State IntCurvesFace_Intersector::State(const int i) const
{
  return (mySeqState.Value(i) == 0) ? TopAbs_IN : TopAbs_ON;
}

inline bool IntCurvesFace_Intersector::IsParallel() const
{
  return myIsParallel;
}

inline const TopoDS_Face& IntCurvesFace_Intersector::Face() const
{
  return (face);
}
