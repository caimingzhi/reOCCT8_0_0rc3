#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class Adaptor3d_HSurfaceTool;
class Bnd_Box;

class IntCurveSurface_ThePolyhedronOfHInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurveSurface_ThePolyhedronOfHInter(
    const occ::handle<Adaptor3d_Surface>& Surface,
    const int                             nbdU,
    const int                             nbdV,
    const double                          U1,
    const double                          V1,
    const double                          U2,
    const double                          V2);

  Standard_EXPORT IntCurveSurface_ThePolyhedronOfHInter(
    const occ::handle<Adaptor3d_Surface>& Surface,
    const NCollection_Array1<double>&     Upars,
    const NCollection_Array1<double>&     Vpars);

  Standard_EXPORT void Destroy();

  ~IntCurveSurface_ThePolyhedronOfHInter() { Destroy(); }

  Standard_EXPORT void DeflectionOverEstimation(const double flec);

  Standard_EXPORT void UMinSingularity(const bool Sing);

  Standard_EXPORT void UMaxSingularity(const bool Sing);

  Standard_EXPORT void VMinSingularity(const bool Sing);

  Standard_EXPORT void VMaxSingularity(const bool Sing);

  Standard_EXPORT void Size(int& nbdu, int& nbdv) const;

  Standard_EXPORT int NbTriangles() const;

  Standard_EXPORT void Triangle(const int Index, int& P1, int& P2, int& P3) const;

  Standard_EXPORT int TriConnex(const int Triang,
                                const int Pivot,
                                const int Pedge,
                                int&      TriCon,
                                int&      OtherP) const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT void Point(const gp_Pnt& thePnt,
                             const int     lig,
                             const int     col,
                             const double  U,
                             const double  V);

  Standard_EXPORT const gp_Pnt& Point(const int Index, double& U, double& V) const;

  Standard_EXPORT const gp_Pnt& Point(const int Index) const;

  Standard_EXPORT void Point(const int Index, gp_Pnt& P) const;

  Standard_EXPORT const Bnd_Box& Bounding() const;

  Standard_EXPORT void FillBounding();

  Standard_EXPORT const occ::handle<NCollection_HArray1<Bnd_Box>>& ComponentsBounding() const;

  Standard_EXPORT double DeflectionOverEstimation() const;

  Standard_EXPORT bool HasUMinSingularity() const;

  Standard_EXPORT bool HasUMaxSingularity() const;

  Standard_EXPORT bool HasVMinSingularity() const;

  Standard_EXPORT bool HasVMaxSingularity() const;

  Standard_EXPORT void PlaneEquation(const int Triang,
                                     gp_XYZ&   NormalVector,
                                     double&   PolarDistance) const;

  Standard_EXPORT bool Contain(const int Triang, const gp_Pnt& ThePnt) const;

  Standard_EXPORT void Parameters(const int Index, double& U, double& V) const;

  Standard_EXPORT bool IsOnBound(const int Index1, const int Index2) const;

  double GetBorderDeflection() const { return TheBorderDeflection; }

  Standard_EXPORT void Dump() const;

protected:
  Standard_EXPORT void Init(const occ::handle<Adaptor3d_Surface>& Surface,
                            const double                          U1,
                            const double                          V1,
                            const double                          U2,
                            const double                          V2);

  Standard_EXPORT void Init(const occ::handle<Adaptor3d_Surface>& Surface,
                            const NCollection_Array1<double>&     Upars,
                            const NCollection_Array1<double>&     Vpars);

private:
  int                                       nbdeltaU;
  int                                       nbdeltaV;
  Bnd_Box                                   TheBnd;
  occ::handle<NCollection_HArray1<Bnd_Box>> TheComponentsBnd;
  double                                    TheDeflection;
  void*                                     C_MyPnts;
  void*                                     C_MyU;
  void*                                     C_MyV;
  bool                                      UMinSingular;
  bool                                      UMaxSingular;
  bool                                      VMinSingular;
  bool                                      VMaxSingular;
  double                                    TheBorderDeflection;
  void*                                     C_MyIsOnBounds;
};
