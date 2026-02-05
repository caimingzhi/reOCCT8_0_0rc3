#pragma once

#include <HLRBRep_Curve.hpp>

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Vec.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Cone.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <gp_Ax1.hpp>
class TopoDS_Face;
class gp_Pnt;
class gp_Vec;
class gp_Pln;

class HLRBRep_Surface
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an undefined surface with no face loaded.
  Standard_EXPORT HLRBRep_Surface();

  void Projector(const HLRAlgo_Projector* Proj) { myProj = Proj; }

  //! Returns the 3D Surface.
  BRepAdaptor_Surface& Surface();

  //! Returns the 3D Surface (const version).
  const BRepAdaptor_Surface& Surface() const;

  //! Sets the 3D Surface to be projected.
  Standard_EXPORT void Surface(const TopoDS_Face& F);

  //! returns true if it is a side face
  Standard_EXPORT bool IsSide(const double tolf, const double toler) const;

  Standard_EXPORT bool IsAbove(const bool back, const HLRBRep_Curve* A, const double tolC) const;

  double FirstUParameter() const;

  double LastUParameter() const;

  double FirstVParameter() const;

  double LastVParameter() const;

  GeomAbs_Shape UContinuity() const;

  GeomAbs_Shape VContinuity() const;

  //! If necessary, breaks the surface in U intervals of
  //! continuity <S>. And returns the number of
  //! intervals.
  int NbUIntervals(const GeomAbs_Shape S) const;

  //! If necessary, breaks the surface in V intervals of
  //! continuity <S>. And returns the number of
  //! intervals.
  int NbVIntervals(const GeomAbs_Shape S) const;

  GeomAbs_Shape UIntervalContinuity() const;

  GeomAbs_Shape VIntervalContinuity() const;

  bool IsUClosed() const;

  bool IsVClosed() const;

  bool IsUPeriodic() const;

  double UPeriod() const;

  bool IsVPeriodic() const;

  double VPeriod() const;

  //! Computes the point of parameters U,V on the surface.
  Standard_EXPORT gp_Pnt Value(const double U, const double V) const;

  //! Computes the point of parameters U,V on the surface.
  void D0(const double U, const double V, gp_Pnt& P) const;

  //! Computes the point and the first derivatives on
  //! the surface.
  //! Raised if the continuity of the current
  //! intervals is not C1.
  void D1(const double U, const double V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V) const;

  //! Computes the point, the first and second
  //! derivatives on the surface.
  //! Raised if the continuity of the current
  //! intervals is not C2.
  void D2(const double U,
          const double V,
          gp_Pnt&      P,
          gp_Vec&      D1U,
          gp_Vec&      D1V,
          gp_Vec&      D2U,
          gp_Vec&      D2V,
          gp_Vec&      D2UV) const;

  //! Computes the point, the first, second and third
  //! derivatives on the surface.
  //! Raised if the continuity of the current
  //! intervals is not C3.
  void D3(const double U,
          const double V,
          gp_Pnt&      P,
          gp_Vec&      D1U,
          gp_Vec&      D1V,
          gp_Vec&      D2U,
          gp_Vec&      D2V,
          gp_Vec&      D2UV,
          gp_Vec&      D3U,
          gp_Vec&      D3V,
          gp_Vec&      D3UUV,
          gp_Vec&      D3UVV) const;

  //! Computes the derivative of order Nu in the
  //! direction U and Nv in the direction V at the point P(U,
  //! V).
  //! Raised if the current U interval is not not CNu
  //! and the current V interval is not CNv.
  //! Raised if Nu + Nv < 1 or Nu < 0 or Nv < 0.
  gp_Vec DN(const double U, const double V, const int Nu, const int Nv) const;

  //! Returns the type of the surface : Plane, Cylinder,
  //! Cone, Sphere, Torus, BezierSurface,
  //! BSplineSurface, SurfaceOfRevolution,
  //! SurfaceOfExtrusion, OtherSurface
  GeomAbs_SurfaceType GetType() const;

  Standard_EXPORT gp_Pln Plane() const;

  gp_Cylinder Cylinder() const;

  gp_Cone Cone() const;

  gp_Sphere Sphere() const;

  gp_Torus Torus() const;

  int UDegree() const;

  int NbUPoles() const;

  int VDegree() const;

  int NbVPoles() const;

  int NbUKnots() const;

  int NbVKnots() const;

  gp_Ax1 Axis() const;

private:
  //! returns true if it is a side face
  Standard_EXPORT bool SideRowsOfPoles(const double                tol,
                                       const int                   nbuPoles,
                                       const int                   nbvPoles,
                                       NCollection_Array2<gp_Pnt>& Pnt) const;

  BRepAdaptor_Surface      mySurf;
  GeomAbs_SurfaceType      myType;
  const HLRAlgo_Projector* myProj;
};

#include <BRepAdaptor_Surface.hpp>
#include <HLRBRep_BSurfaceTool.hpp>

//=================================================================================================

inline BRepAdaptor_Surface& HLRBRep_Surface::Surface()
{
  return mySurf;
}

//=================================================================================================

inline const BRepAdaptor_Surface& HLRBRep_Surface::Surface() const
{
  return mySurf;
}

//=================================================================================================

inline double HLRBRep_Surface::FirstUParameter() const
{
  return HLRBRep_BSurfaceTool::FirstUParameter(mySurf);
}

//=================================================================================================

inline double HLRBRep_Surface::LastUParameter() const
{
  return HLRBRep_BSurfaceTool::LastUParameter(mySurf);
}

//=================================================================================================

inline double HLRBRep_Surface::FirstVParameter() const
{
  return HLRBRep_BSurfaceTool::FirstVParameter(mySurf);
}

//=================================================================================================

inline double HLRBRep_Surface::LastVParameter() const
{
  return HLRBRep_BSurfaceTool::LastVParameter(mySurf);
}

//=================================================================================================

inline GeomAbs_Shape HLRBRep_Surface::UContinuity() const
{
  return HLRBRep_BSurfaceTool::UContinuity(mySurf);
}

//=================================================================================================

inline GeomAbs_Shape HLRBRep_Surface::VContinuity() const
{
  return HLRBRep_BSurfaceTool::VContinuity(mySurf);
}

//=================================================================================================

inline int HLRBRep_Surface::NbUIntervals(const GeomAbs_Shape S) const
{
  return HLRBRep_BSurfaceTool::NbUIntervals(mySurf, S);
}

//=================================================================================================

inline int HLRBRep_Surface::NbVIntervals(const GeomAbs_Shape S) const
{
  return HLRBRep_BSurfaceTool::NbVIntervals(mySurf, S);
}

//=================================================================================================

inline bool HLRBRep_Surface::IsUClosed() const
{
  return HLRBRep_BSurfaceTool::IsUClosed(mySurf);
}

//=================================================================================================

inline bool HLRBRep_Surface::IsVClosed() const
{
  return HLRBRep_BSurfaceTool::IsVClosed(mySurf);
}

//=================================================================================================

inline bool HLRBRep_Surface::IsUPeriodic() const
{
  return HLRBRep_BSurfaceTool::IsUPeriodic(mySurf);
}

//=================================================================================================

inline double HLRBRep_Surface::UPeriod() const
{
  return HLRBRep_BSurfaceTool::UPeriod(mySurf);
}

//=================================================================================================

inline bool HLRBRep_Surface::IsVPeriodic() const
{
  return HLRBRep_BSurfaceTool::IsVPeriodic(mySurf);
}

//=================================================================================================

inline double HLRBRep_Surface::VPeriod() const
{
  return HLRBRep_BSurfaceTool::VPeriod(mySurf);
}

//=================================================================================================

inline void HLRBRep_Surface::D0(const double U, const double V, gp_Pnt& P) const
{
  HLRBRep_BSurfaceTool::D0(mySurf, U, V, P);
}

//=================================================================================================

inline void HLRBRep_Surface::D1(const double U,
                                const double V,
                                gp_Pnt&      P,
                                gp_Vec&      D1U,
                                gp_Vec&      D1V) const
{
  HLRBRep_BSurfaceTool::D1(mySurf, U, V, P, D1U, D1V);
}

//=================================================================================================

inline void HLRBRep_Surface::D2(const double U,
                                const double V,
                                gp_Pnt&      P,
                                gp_Vec&      D1U,
                                gp_Vec&      D1V,
                                gp_Vec&      D2U,
                                gp_Vec&      D2V,
                                gp_Vec&      D2UV) const
{
  HLRBRep_BSurfaceTool::D2(mySurf, U, V, P, D1U, D1V, D2U, D2V, D2UV);
}

//=================================================================================================

inline void HLRBRep_Surface::D3(const double U,
                                const double V,
                                gp_Pnt&      P,
                                gp_Vec&      D1U,
                                gp_Vec&      D1V,
                                gp_Vec&      D2U,
                                gp_Vec&      D2V,
                                gp_Vec&      D2UV,
                                gp_Vec&      D3U,
                                gp_Vec&      D3V,
                                gp_Vec&      D3UUV,
                                gp_Vec&      D3UVV) const
{
  HLRBRep_BSurfaceTool::D3(mySurf, U, V, P, D1U, D1V, D2U, D2V, D2UV, D3U, D3V, D3UUV, D3UVV);
}

//=================================================================================================

inline gp_Vec HLRBRep_Surface::DN(const double U, const double V, const int Nu, const int Nv) const
{
  return HLRBRep_BSurfaceTool::DN(mySurf, U, V, Nu, Nv);
}

//=================================================================================================

inline GeomAbs_SurfaceType HLRBRep_Surface::GetType() const
{
  return myType;
}

//=================================================================================================

inline gp_Cylinder HLRBRep_Surface::Cylinder() const
{
  return HLRBRep_BSurfaceTool::Cylinder(mySurf);
}

//=================================================================================================

inline gp_Cone HLRBRep_Surface::Cone() const
{
  return HLRBRep_BSurfaceTool::Cone(mySurf);
}

//=================================================================================================

inline gp_Sphere HLRBRep_Surface::Sphere() const
{
  return HLRBRep_BSurfaceTool::Sphere(mySurf);
}

//=================================================================================================

inline gp_Torus HLRBRep_Surface::Torus() const
{
  return HLRBRep_BSurfaceTool::Torus(mySurf);
}

//=================================================================================================

inline int HLRBRep_Surface::UDegree() const
{
  return HLRBRep_BSurfaceTool::UDegree(mySurf);
}

//=================================================================================================

inline int HLRBRep_Surface::NbUPoles() const
{
  return HLRBRep_BSurfaceTool::NbUPoles(mySurf);
}

//=================================================================================================

inline int HLRBRep_Surface::VDegree() const
{
  return HLRBRep_BSurfaceTool::VDegree(mySurf);
}

//=================================================================================================

inline int HLRBRep_Surface::NbVPoles() const
{
  return HLRBRep_BSurfaceTool::NbVPoles(mySurf);
}

//=================================================================================================

inline int HLRBRep_Surface::NbUKnots() const
{
  return HLRBRep_BSurfaceTool::NbUKnots(mySurf);
}

//=================================================================================================

inline int HLRBRep_Surface::NbVKnots() const
{
  return HLRBRep_BSurfaceTool::NbVKnots(mySurf);
}

//=================================================================================================

inline gp_Ax1 HLRBRep_Surface::Axis() const
{
  return HLRBRep_BSurfaceTool::AxeOfRevolution(mySurf);
}
