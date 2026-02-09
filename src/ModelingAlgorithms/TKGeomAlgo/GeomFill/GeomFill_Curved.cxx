#include <GeomFill_Curved.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_NotImplemented.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Array1.hpp>

GeomFill_Curved::GeomFill_Curved() = default;

GeomFill_Curved::GeomFill_Curved(const NCollection_Array1<gp_Pnt>& P1,
                                 const NCollection_Array1<gp_Pnt>& P2,
                                 const NCollection_Array1<gp_Pnt>& P3,
                                 const NCollection_Array1<gp_Pnt>& P4)
{
  Init(P1, P2, P3, P4);
}

GeomFill_Curved::GeomFill_Curved(const NCollection_Array1<gp_Pnt>& P1,
                                 const NCollection_Array1<gp_Pnt>& P2,
                                 const NCollection_Array1<gp_Pnt>& P3,
                                 const NCollection_Array1<gp_Pnt>& P4,
                                 const NCollection_Array1<double>& W1,
                                 const NCollection_Array1<double>& W2,
                                 const NCollection_Array1<double>& W3,
                                 const NCollection_Array1<double>& W4)
{
  Init(P1, P2, P3, P4, W1, W2, W3, W4);
}

GeomFill_Curved::GeomFill_Curved(const NCollection_Array1<gp_Pnt>& P1,
                                 const NCollection_Array1<gp_Pnt>& P2)
{
  Init(P1, P2);
}

GeomFill_Curved::GeomFill_Curved(const NCollection_Array1<gp_Pnt>& P1,
                                 const NCollection_Array1<gp_Pnt>& P2,
                                 const NCollection_Array1<double>& W1,
                                 const NCollection_Array1<double>& W2)
{
  Init(P1, P2, W1, W2);
}

void GeomFill_Curved::Init(const NCollection_Array1<gp_Pnt>& P1,
                           const NCollection_Array1<gp_Pnt>& P2,
                           const NCollection_Array1<gp_Pnt>& P3,
                           const NCollection_Array1<gp_Pnt>& P4)
{
  Standard_DomainError_Raise_if(P1.Length() != P3.Length() || P2.Length() != P4.Length(), " ");

  int NPolU = P1.Length();
  int NPolV = P2.Length();

  IsRational = false;

  double NU = NPolU - 1;
  double NV = NPolV - 1;
  myPoles   = new NCollection_HArray2<gp_Pnt>(1, NPolU, 1, NPolV);

  int i, j, k;
  for (i = 1; i <= NPolU; i++)
  {
    myPoles->SetValue(i, 1, P1(i));
    myPoles->SetValue(i, NPolV, P3(i));
  }
  double PU, PU1, PV, PV1;

  for (j = 2; j <= NPolV - 1; j++)
  {
    PV  = (j - 1) / NV;
    PV1 = 1 - PV;
    PV /= 2.;
    PV1 /= 2.;
    myPoles->SetValue(1, j, P4(j));
    myPoles->SetValue(NPolU, j, P2(j));

    for (i = 2; i <= NPolU - 1; i++)
    {
      PU  = (i - 1) / NU;
      PU1 = 1 - PU;
      PU /= 2.;
      PU1 /= 2.;
      gp_Pnt P;
      for (k = 1; k <= 3; k++)
      {
        P.SetCoord(k,
                   PV1 * P1(i).Coord(k) + PV * P3(i).Coord(k) + PU * P2(j).Coord(k)
                     + PU1 * P4(j).Coord(k));
      }
      myPoles->SetValue(i, j, P);
    }
  }
}

void GeomFill_Curved::Init(const NCollection_Array1<gp_Pnt>& P1,
                           const NCollection_Array1<gp_Pnt>& P2,
                           const NCollection_Array1<gp_Pnt>& P3,
                           const NCollection_Array1<gp_Pnt>& P4,
                           const NCollection_Array1<double>& W1,
                           const NCollection_Array1<double>& W2,
                           const NCollection_Array1<double>& W3,
                           const NCollection_Array1<double>& W4)
{
  Standard_DomainError_Raise_if(W1.Length() != W3.Length() || W2.Length() != W4.Length(), " ");
  Standard_DomainError_Raise_if(W1.Length() != P1.Length() || W2.Length() != P2.Length()
                                  || W3.Length() != P3.Length() || W4.Length() != P4.Length(),
                                " ");

  Init(P1, P2, P3, P4);
  IsRational = true;

  int NPolU = W1.Length();
  int NPolV = W2.Length();

  double NU = NPolU - 1;
  double NV = NPolV - 1;
  myWeights = new NCollection_HArray2<double>(1, NPolU, 1, NPolV);

  int i, j;
  for (i = 1; i <= NPolU; i++)
  {
    myWeights->SetValue(i, 1, W1(i));
    myWeights->SetValue(i, NPolV, W3(i));
  }
  double PU, PU1, PV, PV1;

  for (j = 2; j <= NPolV - 1; j++)
  {
    PV  = (j - 1) / NV;
    PV1 = 1 - PV;
    PV /= 2.;
    PV1 /= 2.;
    myWeights->SetValue(1, j, W4(j));
    myWeights->SetValue(NPolU, j, W2(j));

    for (i = 2; i <= NPolU - 1; i++)
    {
      PU  = (i - 1) / NU;
      PU1 = 1 - PU;
      PU /= 2.;
      PU1 /= 2.;
      double W = PV1 * W1(i) + PV * W3(i) + PU * W2(j) + PU1 * W4(j);
      myWeights->SetValue(i, j, W);
    }
  }
}

void GeomFill_Curved::Init(const NCollection_Array1<gp_Pnt>& P1,
                           const NCollection_Array1<gp_Pnt>& P2)
{
  int NPolU = P1.Length();
  int NPolV = P2.Length();

  IsRational = false;

  myPoles = new NCollection_HArray2<gp_Pnt>(1, NPolU, 1, NPolV);

  int i, j;

  for (j = 1; j <= NPolV; j++)
  {
    gp_Vec Tra(P2(1), P2(j));
    for (i = 1; i <= NPolU; i++)
    {
      myPoles->SetValue(i, j, P1(i).Translated(Tra));
    }
  }
}

void GeomFill_Curved::Init(const NCollection_Array1<gp_Pnt>& P1,
                           const NCollection_Array1<gp_Pnt>& P2,
                           const NCollection_Array1<double>& W1,
                           const NCollection_Array1<double>& W2)
{
  Init(P1, P2);
  IsRational = true;

  int NPolU = W1.Length();
  int NPolV = W2.Length();

  myWeights = new NCollection_HArray2<double>(1, NPolU, 1, NPolV);
  for (int j = 1; j <= NPolV; j++)
  {
    double Factor = W2(j) / W1(1);
    for (int i = 1; i <= NPolU; i++)
    {
      myWeights->SetValue(i, j, W1(i) * Factor);
    }
  }
}
