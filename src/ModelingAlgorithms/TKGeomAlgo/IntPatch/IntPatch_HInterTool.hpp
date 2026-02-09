#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>

class gp_Pnt2d;
class Adaptor3d_HVertex;
class gp_Pnt;

class IntPatch_HInterTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_HInterTool();

  static bool SingularOnUMin(const occ::handle<Adaptor3d_Surface>& S);

  static bool SingularOnUMax(const occ::handle<Adaptor3d_Surface>& S);

  static bool SingularOnVMin(const occ::handle<Adaptor3d_Surface>& S);

  static bool SingularOnVMax(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT static int NbSamplesU(const occ::handle<Adaptor3d_Surface>& S,
                                        const double                          u1,
                                        const double                          u2);

  Standard_EXPORT static int NbSamplesV(const occ::handle<Adaptor3d_Surface>& S,
                                        const double                          v1,
                                        const double                          v2);

  Standard_EXPORT int NbSamplePoints(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT void SamplePoint(const occ::handle<Adaptor3d_Surface>& S,
                                   const int                             Index,
                                   double&                               U,
                                   double&                               V) const;

  Standard_EXPORT static bool HasBeenSeen(const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT static int NbSamplesOnArc(const occ::handle<Adaptor2d_Curve2d>& A);

  Standard_EXPORT static void Bounds(const occ::handle<Adaptor2d_Curve2d>& C,
                                     double&                               Ufirst,
                                     double&                               Ulast);

  Standard_EXPORT static bool Project(const occ::handle<Adaptor2d_Curve2d>& C,
                                      const gp_Pnt2d&                       P,
                                      double&                               Paramproj,
                                      gp_Pnt2d&                             Ptproj);

  Standard_EXPORT static double Tolerance(const occ::handle<Adaptor3d_HVertex>& V,
                                          const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT static double Parameter(const occ::handle<Adaptor3d_HVertex>& V,
                                          const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT static int NbPoints(const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT static void Value(const occ::handle<Adaptor2d_Curve2d>& C,
                                    const int                             Index,
                                    gp_Pnt&                               Pt,
                                    double&                               Tol,
                                    double&                               U);

  Standard_EXPORT static bool IsVertex(const occ::handle<Adaptor2d_Curve2d>& C, const int Index);

  Standard_EXPORT static void Vertex(const occ::handle<Adaptor2d_Curve2d>& C,
                                     const int                             Index,
                                     occ::handle<Adaptor3d_HVertex>&       V);

  Standard_EXPORT static int NbSegments(const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT static bool HasFirstPoint(const occ::handle<Adaptor2d_Curve2d>& C,
                                            const int                             Index,
                                            int&                                  IndFirst);

  Standard_EXPORT static bool HasLastPoint(const occ::handle<Adaptor2d_Curve2d>& C,
                                           const int                             Index,
                                           int&                                  IndLast);

  Standard_EXPORT static bool IsAllSolution(const occ::handle<Adaptor2d_Curve2d>& C);

private:
  double uinf;
  double vinf;
  double usup;
  double vsup;
};

inline bool IntPatch_HInterTool::SingularOnUMin(const occ::handle<Adaptor3d_Surface>&)
{
  return false;
}

inline bool IntPatch_HInterTool::SingularOnUMax(const occ::handle<Adaptor3d_Surface>&)
{
  return false;
}

inline bool IntPatch_HInterTool::SingularOnVMin(const occ::handle<Adaptor3d_Surface>&)
{
  return false;
}

inline bool IntPatch_HInterTool::SingularOnVMax(const occ::handle<Adaptor3d_Surface>&)
{
  return false;
}
