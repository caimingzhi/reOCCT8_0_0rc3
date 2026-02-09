#pragma once

#include <Adaptor3d_Surface.hpp>
#include <BlendFunc_SectionShape.hpp>
#include <Convert_ParameterisationType.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>

class gp_Pnt2d;
class gp_Vec;

class BlendFunc
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void GetShape(const BlendFunc_SectionShape  SectShape,
                                       const double                  MaxAng,
                                       int&                          NbPoles,
                                       int&                          NbKnots,
                                       int&                          Degree,
                                       Convert_ParameterisationType& TypeConv);

  Standard_EXPORT static void Knots(const BlendFunc_SectionShape SectShape,
                                    NCollection_Array1<double>&  TKnots);

  Standard_EXPORT static void Mults(const BlendFunc_SectionShape SectShape,
                                    NCollection_Array1<int>&     TMults);

  Standard_EXPORT static void GetMinimalWeights(const BlendFunc_SectionShape       SectShape,
                                                const Convert_ParameterisationType TConv,
                                                const double                       AngleMin,
                                                const double                       AngleMax,
                                                NCollection_Array1<double>&        Weigths);

  Standard_EXPORT static GeomAbs_Shape NextShape(const GeomAbs_Shape S);

  Standard_EXPORT static bool ComputeNormal(const occ::handle<Adaptor3d_Surface>& Surf,
                                            const gp_Pnt2d&                       p2d,
                                            gp_Vec&                               Normal);

  Standard_EXPORT static bool ComputeDNormal(const occ::handle<Adaptor3d_Surface>& Surf,
                                             const gp_Pnt2d&                       p2d,
                                             gp_Vec&                               Normal,
                                             gp_Vec&                               DNu,
                                             gp_Vec&                               DNv);
};
