#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GProp_GProps.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
class gp_Pnt;

class GProp_PGProps : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GProp_PGProps();

  Standard_EXPORT void AddPoint(const gp_Pnt& P);

  Standard_EXPORT void AddPoint(const gp_Pnt& P, const double Density);

  Standard_EXPORT GProp_PGProps(const NCollection_Array1<gp_Pnt>& Pnts);

  Standard_EXPORT GProp_PGProps(const NCollection_Array2<gp_Pnt>& Pnts);

  Standard_EXPORT GProp_PGProps(const NCollection_Array1<gp_Pnt>& Pnts,
                                const NCollection_Array1<double>& Density);

  Standard_EXPORT GProp_PGProps(const NCollection_Array2<gp_Pnt>& Pnts,
                                const NCollection_Array2<double>& Density);

  Standard_EXPORT static gp_Pnt Barycentre(const NCollection_Array1<gp_Pnt>& Pnts);

  Standard_EXPORT static gp_Pnt Barycentre(const NCollection_Array2<gp_Pnt>& Pnts);

  Standard_EXPORT static void Barycentre(const NCollection_Array1<gp_Pnt>& Pnts,
                                         const NCollection_Array1<double>& Density,
                                         double&                           Mass,
                                         gp_Pnt&                           G);

  Standard_EXPORT static void Barycentre(const NCollection_Array2<gp_Pnt>& Pnts,
                                         const NCollection_Array2<double>& Density,
                                         double&                           Mass,
                                         gp_Pnt&                           G);
};
