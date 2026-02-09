#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_ArrayOfTriangleStrips.hpp>
#include <Graphic3d_Group.hpp>
#include <Precision.hpp>
#include <Prs3d_IsoAspect.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <StdPrs_ShadedSurface.hpp>
#include <NCollection_Array1.hpp>

void StdPrs_ShadedSurface::Add(const occ::handle<Prs3d_Presentation>& thePrs,
                               const Adaptor3d_Surface&               theSurface,
                               const occ::handle<Prs3d_Drawer>&       theDrawer)
{
  int N1 = theDrawer->UIsoAspect()->Number();
  int N2 = theDrawer->VIsoAspect()->Number();
  N1     = N1 < 3 ? 3 : N1;
  N2     = N2 < 3 ? 3 : N2;

  occ::handle<Graphic3d_Group> aGroup = thePrs->CurrentGroup();
  aGroup->SetGroupPrimitivesAspect(theDrawer->ShadingAspect()->Aspect());
  aGroup->SetClosed(theSurface.IsUClosed() && theSurface.IsVClosed());

  int                        aNBUintv = theSurface.NbUIntervals(GeomAbs_C1);
  int                        aNBVintv = theSurface.NbVIntervals(GeomAbs_C1);
  NCollection_Array1<double> anInterU(1, aNBUintv + 1);
  NCollection_Array1<double> anInterV(1, aNBVintv + 1);

  theSurface.UIntervals(anInterU, GeomAbs_C1);
  theSurface.VIntervals(anInterV, GeomAbs_C1);

  double U1, U2, V1, V2, DU, DV;

  gp_Pnt P1, P2;
  gp_Vec D1U, D1V, D1, D2;

  for (int NU = 1; NU <= aNBUintv; ++NU)
  {
    for (int NV = 1; NV <= aNBVintv; ++NV)
    {
      U1 = anInterU(NU);
      U2 = anInterU(NU + 1);
      V1 = anInterV(NV);
      V2 = anInterV(NV + 1);

      U1 = (Precision::IsNegativeInfinite(U1)) ? -theDrawer->MaximalParameterValue() : U1;
      U2 = (Precision::IsPositiveInfinite(U2)) ? theDrawer->MaximalParameterValue() : U2;

      V1 = (Precision::IsNegativeInfinite(V1)) ? -theDrawer->MaximalParameterValue() : V1;
      V2 = (Precision::IsPositiveInfinite(V2)) ? theDrawer->MaximalParameterValue() : V2;

      DU = (U2 - U1) / N1;
      DV = (V2 - V1) / N2;

      occ::handle<Graphic3d_ArrayOfTriangleStrips> aPArray =
        new Graphic3d_ArrayOfTriangleStrips(2 * (N1 + 1) * (N2 + 1),
                                            N1 + 1,
                                            true,
                                            false,
                                            false,
                                            false);
      for (int i = 1; i <= N1 + 1; ++i)
      {
        aPArray->AddBound(N2 + 1);
        for (int j = 1; j <= N2 + 1; ++j)
        {
          theSurface.D1(U1 + DU * (i - 1), V1 + DV * (j - 1), P2, D1U, D1V);
          D1 = D1U ^ D1V;
          D1.Normalize();
          theSurface.D1(U1 + DU * i, V1 + DV * (j - 1), P2, D1U, D1V);
          D2 = D1U ^ D1V;
          D2.Normalize();
          aPArray->AddVertex(P1, D1);
          aPArray->AddVertex(P2, D2);
        }
      }
      aGroup->AddPrimitiveArray(aPArray);
    }
  }
}
