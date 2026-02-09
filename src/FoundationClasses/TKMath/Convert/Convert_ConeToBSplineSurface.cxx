

#include <Convert_ConeToBSplineSurface.hpp>
#include <gp.hpp>
#include <gp_Cone.hpp>
#include <gp_Trsf.hpp>
#include <Standard_DomainError.hpp>

namespace
{
  constexpr int TheUDegree  = 2;
  constexpr int TheVDegree  = 1;
  constexpr int TheNbUKnots = 5;
  constexpr int TheNbVKnots = 2;
  constexpr int TheNbUPoles = 9;
  constexpr int TheNbVPoles = 2;
} // namespace

static void ComputePoles(const double                R,
                         const double                A,
                         const double                U1,
                         const double                U2,
                         const double                V1,
                         const double                V2,
                         NCollection_Array2<gp_Pnt>& Poles)
{
  double deltaU = U2 - U1;

  int i;

  int    nbUSpans = (int)std::trunc(1.2 * deltaU / M_PI) + 1;
  double AlfaU    = deltaU / (nbUSpans * 2);

  double x[TheNbVPoles];
  double z[TheNbVPoles];

  x[0] = R + V1 * std::sin(A);
  z[0] = V1 * std::cos(A);
  x[1] = R + V2 * std::sin(A);
  z[1] = V2 * std::cos(A);

  double UStart = U1;
  Poles(1, 1)   = gp_Pnt(x[0] * std::cos(UStart), x[0] * std::sin(UStart), z[0]);
  Poles(1, 2)   = gp_Pnt(x[1] * std::cos(UStart), x[1] * std::sin(UStart), z[1]);

  for (i = 1; i <= nbUSpans; i++)
  {
    Poles(2 * i, 1) = gp_Pnt(x[0] * std::cos(UStart + AlfaU) / std::cos(AlfaU),
                             x[0] * std::sin(UStart + AlfaU) / std::cos(AlfaU),
                             z[0]);
    Poles(2 * i, 2) = gp_Pnt(x[1] * std::cos(UStart + AlfaU) / std::cos(AlfaU),
                             x[1] * std::sin(UStart + AlfaU) / std::cos(AlfaU),
                             z[1]);
    Poles(2 * i + 1, 1) =
      gp_Pnt(x[0] * std::cos(UStart + 2 * AlfaU), x[0] * std::sin(UStart + 2 * AlfaU), z[0]);
    Poles(2 * i + 1, 2) =
      gp_Pnt(x[1] * std::cos(UStart + 2 * AlfaU), x[1] * std::sin(UStart + 2 * AlfaU), z[1]);
    UStart += 2 * AlfaU;
  }
}

Convert_ConeToBSplineSurface::Convert_ConeToBSplineSurface(const gp_Cone& C,
                                                           const double   U1,
                                                           const double   U2,
                                                           const double   V1,
                                                           const double   V2)
    : Convert_ElementarySurfaceToBSplineSurface(TheNbUPoles,
                                                TheNbVPoles,
                                                TheNbUKnots,
                                                TheNbVKnots,
                                                TheUDegree,
                                                TheVDegree)
{
  double deltaU = U2 - U1;
  Standard_DomainError_Raise_if((std::abs(V2 - V1) <= std::abs(Epsilon(V1))) || (deltaU > 2 * M_PI)
                                  || (deltaU < 0.),
                                "Convert_ConeToBSplineSurface");

  isuperiodic = false;
  isvperiodic = false;

  int i, j;

  int    nbUSpans = (int)std::trunc(1.2 * deltaU / M_PI) + 1;
  double AlfaU    = deltaU / (nbUSpans * 2);

  nbUPoles = 2 * nbUSpans + 1;
  nbUKnots = nbUSpans + 1;

  nbVPoles = 2;
  nbVKnots = 2;

  double R = C.RefRadius();
  double A = C.SemiAngle();

  ComputePoles(R, A, U1, U2, V1, V2, poles);

  for (i = 1; i <= nbUKnots; i++)
  {
    uknots(i) = U1 + (i - 1) * 2 * AlfaU;
    umults(i) = 2;
  }
  umults(1)++;
  umults(nbUKnots)++;
  vknots(1) = V1;
  vmults(1) = 2;
  vknots(2) = V2;
  vmults(2) = 2;

  double  W1;
  gp_Trsf Trsf;
  Trsf.SetTransformation(C.Position(), gp::XOY());

  for (i = 1; i <= nbUPoles; i++)
  {
    if (i % 2 == 0)
      W1 = std::cos(AlfaU);
    else
      W1 = 1.;

    for (j = 1; j <= nbVPoles; j++)
    {
      weights(i, j) = W1;
      poles(i, j).Transform(Trsf);
    }
  }
}

Convert_ConeToBSplineSurface::Convert_ConeToBSplineSurface(const gp_Cone& C,
                                                           const double   V1,
                                                           const double   V2)
    : Convert_ElementarySurfaceToBSplineSurface(TheNbUPoles,
                                                TheNbVPoles,
                                                TheNbUKnots,
                                                TheNbVKnots,
                                                TheUDegree,
                                                TheVDegree)
{
  Standard_DomainError_Raise_if(std::abs(V2 - V1) <= std::abs(Epsilon(V1)),
                                "Convert_ConeToBSplineSurface");

  int i, j;

  isuperiodic = true;
  isvperiodic = false;

  double R = C.RefRadius();
  double A = C.SemiAngle();

  ComputePoles(R, A, 0., 2. * M_PI, V1, V2, poles);

  nbUPoles = 6;
  nbUKnots = 4;
  nbVPoles = 2;
  nbVKnots = 2;

  for (i = 1; i <= nbUKnots; i++)
  {
    uknots(i) = (i - 1) * 2. * M_PI / 3.;
    umults(i) = 2;
  }
  vknots(1) = V1;
  vmults(1) = 2;
  vknots(2) = V2;
  vmults(2) = 2;

  double  W;
  gp_Trsf Trsf;
  Trsf.SetTransformation(C.Position(), gp::XOY());

  for (i = 1; i <= nbUPoles; i++)
  {
    if (i % 2 == 0)
      W = 0.5;
    else
      W = 1.;

    for (j = 1; j <= nbVPoles; j++)
    {
      weights(i, j) = W;
      poles(i, j).Transform(Trsf);
    }
  }
}
