

#include <Adaptor3d_Curve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Vrml_Coordinate3.hpp>
#include <Vrml_IndexedLineSet.hpp>
#include <Vrml_Material.hpp>
#include <Vrml_Separator.hpp>
#include <VrmlConverter_Curve.hpp>
#include <VrmlConverter_Drawer.hpp>
#include <VrmlConverter_LineAspect.hpp>

static void FindLimits(const Adaptor3d_Curve& aCurve,
                       const double           aLimit,
                       double&                First,
                       double&                Last)
{
  First         = aCurve.FirstParameter();
  Last          = aCurve.LastParameter();
  bool firstInf = Precision::IsNegativeInfinite(First);
  bool lastInf  = Precision::IsPositiveInfinite(Last);

  if (firstInf || lastInf)
  {
    gp_Pnt P1, P2;
    double delta = 1;
    if (firstInf && lastInf)
    {
      do
      {
        delta *= 2;
        First = -delta;
        Last  = delta;
        aCurve.D0(First, P1);
        aCurve.D0(Last, P2);
      } while (P1.Distance(P2) < aLimit);
    }
    else if (firstInf)
    {
      aCurve.D0(Last, P2);
      do
      {
        delta *= 2;
        First = Last - delta;
        aCurve.D0(First, P1);
      } while (P1.Distance(P2) < aLimit);
    }
    else if (lastInf)
    {
      aCurve.D0(First, P1);
      do
      {
        delta *= 2;
        Last = First + delta;
        aCurve.D0(Last, P2);
      } while (P1.Distance(P2) < aLimit);
    }
  }
}

static void DrawCurve(const Adaptor3d_Curve&                   aCurve,
                      const int                                NbP,
                      const double                             U1,
                      const double                             U2,
                      const occ::handle<VrmlConverter_Drawer>& aDrawer,
                      Standard_OStream&                        anOStream)
{
  int                                      nbintervals = 1, i;
  occ::handle<NCollection_HArray1<gp_Vec>> HAV1;
  occ::handle<NCollection_HArray1<int>>    HAI1;

  if (aCurve.GetType() == GeomAbs_BSplineCurve)
  {
    nbintervals = aCurve.NbKnots() - 1;

    nbintervals = std::max(1, nbintervals / 3);
  }

  switch (aCurve.GetType())
  {
    case GeomAbs_Line:
    {
      gp_Vec V;
      HAV1 = new NCollection_HArray1<gp_Vec>(1, 2);

      gp_Pnt p = aCurve.Value(U1);
      V.SetX(p.X());
      V.SetY(p.Y());
      V.SetZ(p.Z());
      HAV1->SetValue(1, V);

      p = aCurve.Value(U2);
      V.SetX(p.X());
      V.SetY(p.Y());
      V.SetZ(p.Z());
      HAV1->SetValue(2, V);

      HAI1 = new NCollection_HArray1<int>(1, 3);

      HAI1->SetValue(1, 0);
      HAI1->SetValue(2, 1);
      HAI1->SetValue(3, -1);
    }
    break;
    default:
    {

      double U;
      int    N = std::max(2, NbP * nbintervals);

      gp_Vec V;
      HAV1 = new NCollection_HArray1<gp_Vec>(1, N);

      HAI1      = new NCollection_HArray1<int>(1, N + 1);
      double DU = (U2 - U1) / (N - 1);
      gp_Pnt p;

      for (i = 1; i <= N; i++)
      {
        U = U1 + (i - 1) * DU;
        p = aCurve.Value(U);

        V.SetX(p.X());
        V.SetY(p.Y());
        V.SetZ(p.Z());
        HAV1->SetValue(i, V);
      }

      for (i = HAI1->Lower(); i < HAI1->Upper(); i++)
      {
        HAI1->SetValue(i, i - 1);
      }
      HAI1->SetValue(HAI1->Upper(), -1);
    }
  }

  occ::handle<VrmlConverter_LineAspect> LA = new VrmlConverter_LineAspect;
  LA                                       = aDrawer->LineAspect();

  Vrml_Separator SE1;
  SE1.Print(anOStream);

  if (LA->HasMaterial())
  {

    occ::handle<Vrml_Material> M;
    M = LA->Material();

    M->Print(anOStream);
  }

  occ::handle<Vrml_Coordinate3> C3 = new Vrml_Coordinate3(HAV1);
  C3->Print(anOStream);

  Vrml_IndexedLineSet ILS;
  ILS.SetCoordIndex(HAI1);
  ILS.Print(anOStream);

  SE1.Print(anOStream);
}

void VrmlConverter_Curve::Add(const Adaptor3d_Curve&                   aCurve,
                              const occ::handle<VrmlConverter_Drawer>& aDrawer,
                              Standard_OStream&                        anOStream)
{

  int    NbPoints = aDrawer->Discretisation();
  double V1, V2;
  double aLimit = aDrawer->MaximalParameterValue();
  FindLimits(aCurve, aLimit, V1, V2);

  DrawCurve(aCurve, NbPoints, V1, V2, aDrawer, anOStream);
}

void VrmlConverter_Curve::Add(const Adaptor3d_Curve&                   aCurve,
                              const double                             U1,
                              const double                             U2,
                              const occ::handle<VrmlConverter_Drawer>& aDrawer,
                              Standard_OStream&                        anOStream)
{

  int    NbPoints = aDrawer->Discretisation();
  double V1       = U1;
  double V2       = U2;

  if (Precision::IsNegativeInfinite(V1))
    V1 = -aDrawer->MaximalParameterValue();
  if (Precision::IsPositiveInfinite(V2))
    V2 = aDrawer->MaximalParameterValue();

  DrawCurve(aCurve, NbPoints, V1, V2, aDrawer, anOStream);
}

void VrmlConverter_Curve::Add(const Adaptor3d_Curve& aCurve,
                              const double           U1,
                              const double           U2,
                              Standard_OStream&      anOStream,
                              const int              aNbPoints)
{
  occ::handle<VrmlConverter_Drawer>     aDrawer = new VrmlConverter_Drawer;
  occ::handle<VrmlConverter_LineAspect> la      = new VrmlConverter_LineAspect;
  aDrawer->SetLineAspect(la);

  double V1 = U1;
  double V2 = U2;

  if (Precision::IsNegativeInfinite(V1))
    V1 = -aDrawer->MaximalParameterValue();
  if (Precision::IsPositiveInfinite(V2))
    V2 = aDrawer->MaximalParameterValue();

  DrawCurve(aCurve, aNbPoints, V1, V2, aDrawer, anOStream);
}
