#include <Adaptor3d_Surface.hpp>
#include <GeomGridEval_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <IntCurveSurface_PolyhedronUtils.hpp>
#include <IntPatch_HInterTool.hpp>
#include <IntPatch_Polyhedron.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>

#include <cstdio>
#define MSG_DEBUG 0

#define LONGUEUR_MINI_EDGE_TRIANGLE 1e-14
#define DEFLECTION_COEFF 1.1
#define NBMAXUV 30

namespace PolyUtils = IntCurveSurface_PolyhedronUtils;

static int NbPOnU(const occ::handle<Adaptor3d_Surface>& S)
{
  const double u0   = S->FirstUParameter();
  const double u1   = S->LastUParameter();
  const int    nbpu = IntPatch_HInterTool::NbSamplesU(S, u0, u1);
  return (nbpu > NBMAXUV ? NBMAXUV : nbpu);
}

static int NbPOnV(const occ::handle<Adaptor3d_Surface>& S)
{
  const double v0   = S->FirstVParameter();
  const double v1   = S->LastVParameter();
  const int    nbpv = IntPatch_HInterTool::NbSamplesV(S, v0, v1);
  return (nbpv > NBMAXUV ? NBMAXUV : nbpv);
}

void IntPatch_Polyhedron::Destroy()
{
  gp_Pnt* CMyPnts = (gp_Pnt*)C_MyPnts;
  if (C_MyPnts)
    delete[] CMyPnts;
  double* CMyU = (double*)C_MyU;
  if (C_MyU)
    delete[] CMyU;
  double* CMyV = (double*)C_MyV;
  if (C_MyV)
    delete[] CMyV;
  C_MyPnts = C_MyU = C_MyV = nullptr;
}

IntPatch_Polyhedron::IntPatch_Polyhedron(const occ::handle<Adaptor3d_Surface>& Surface)
    : TheDeflection(Epsilon(100.)),
      nbdeltaU(NbPOnU(Surface)),
      nbdeltaV(NbPOnV(Surface)),
      C_MyPnts(nullptr),
      C_MyU(nullptr),
      C_MyV(nullptr),
      UMinSingular(IntPatch_HInterTool::SingularOnVMin(Surface)),
      UMaxSingular(IntPatch_HInterTool::SingularOnVMin(Surface)),
      VMinSingular(IntPatch_HInterTool::SingularOnVMin(Surface)),
      VMaxSingular(IntPatch_HInterTool::SingularOnVMin(Surface))
{
  const int t       = (nbdeltaU + 1) * (nbdeltaV + 1) + 1;
  gp_Pnt*   CMyPnts = new gp_Pnt[t];
  double*   CMyU    = new double[t];
  double*   CMyV    = new double[t];
  C_MyPnts          = CMyPnts;
  C_MyU             = CMyU;
  C_MyV             = CMyV;

  const double u0 = Surface->FirstUParameter();
  const double u1 = Surface->LastUParameter();
  const double v0 = Surface->FirstVParameter();
  const double v1 = Surface->LastVParameter();

  NCollection_Array1<double> aUParams(0, nbdeltaU);
  NCollection_Array1<double> aVParams(0, nbdeltaV);
  const double               U1mU0sNbdeltaU = (u1 - u0) / (double)nbdeltaU;
  const double               V1mV0sNbdeltaV = (v1 - v0) / (double)nbdeltaV;

  for (int i = 0; i <= nbdeltaU; ++i)
  {
    aUParams.SetValue(i, u0 + i * U1mU0sNbdeltaU);
  }
  for (int j = 0; j <= nbdeltaV; ++j)
  {
    aVParams.SetValue(j, v0 + j * V1mV0sNbdeltaV);
  }

  GeomGridEval_Surface anEval;
  anEval.Initialize(*Surface);
  NCollection_Array2<gp_Pnt> aGridPnts = anEval.EvaluateGrid(aUParams, aVParams);

  int Index = 1;
  for (int i1 = 0; i1 <= nbdeltaU; ++i1)
  {
    for (int i2 = 0; i2 <= nbdeltaV; ++i2)
    {
      CMyPnts[Index] = aGridPnts.Value(i1 + 1, i2 + 1);
      CMyU[Index]    = aUParams.Value(i1);
      CMyV[Index]    = aVParams.Value(i2);
      TheBnd.Add(CMyPnts[Index]);
      Index++;
    }
  }

  double tol = PolyUtils::ComputeMaxDeflection(anEval, *this, NbTriangles());
  tol *= DEFLECTION_COEFF;

  DeflectionOverEstimation(tol);
  FillBounding();
}

IntPatch_Polyhedron::IntPatch_Polyhedron(const occ::handle<Adaptor3d_Surface>& Surface,
                                         const int                             nbu,
                                         const int                             nbv)
    : TheDeflection(Epsilon(100.)),
      nbdeltaU(nbu),
      nbdeltaV(nbv),
      C_MyPnts(nullptr),
      C_MyU(nullptr),
      C_MyV(nullptr),
      UMinSingular(IntPatch_HInterTool::SingularOnVMin(Surface)),
      UMaxSingular(IntPatch_HInterTool::SingularOnVMin(Surface)),
      VMinSingular(IntPatch_HInterTool::SingularOnVMin(Surface)),
      VMaxSingular(IntPatch_HInterTool::SingularOnVMin(Surface))
{
  const int t       = (nbdeltaU + 1) * (nbdeltaV + 1) + 1;
  gp_Pnt*   CMyPnts = new gp_Pnt[t];
  double*   CMyU    = new double[t];
  double*   CMyV    = new double[t];
  C_MyPnts          = CMyPnts;
  C_MyU             = CMyU;
  C_MyV             = CMyV;

  const double u0 = Surface->FirstUParameter();
  const double u1 = Surface->LastUParameter();
  const double v0 = Surface->FirstVParameter();
  const double v1 = Surface->LastVParameter();

  NCollection_Array1<double> aUParams(0, nbdeltaU);
  NCollection_Array1<double> aVParams(0, nbdeltaV);
  const double               U1mU0sNbdeltaU = (u1 - u0) / (double)nbdeltaU;
  const double               V1mV0sNbdeltaV = (v1 - v0) / (double)nbdeltaV;

  for (int i = 0; i <= nbdeltaU; ++i)
  {
    aUParams.SetValue(i, u0 + i * U1mU0sNbdeltaU);
  }
  for (int j = 0; j <= nbdeltaV; ++j)
  {
    aVParams.SetValue(j, v0 + j * V1mV0sNbdeltaV);
  }

  GeomGridEval_Surface anEval;
  anEval.Initialize(*Surface);
  NCollection_Array2<gp_Pnt> aGridPnts = anEval.EvaluateGrid(aUParams, aVParams);

  int Index = 1;
  for (int i1 = 0; i1 <= nbdeltaU; ++i1)
  {
    for (int i2 = 0; i2 <= nbdeltaV; ++i2)
    {
      CMyPnts[Index] = aGridPnts.Value(i1 + 1, i2 + 1);
      CMyU[Index]    = aUParams.Value(i1);
      CMyV[Index]    = aVParams.Value(i2);
      TheBnd.Add(CMyPnts[Index]);
      Index++;
    }
  }

  double tol = PolyUtils::ComputeMaxDeflection(anEval, *this, NbTriangles());
  tol *= DEFLECTION_COEFF;

  DeflectionOverEstimation(tol);
  FillBounding();
}

void IntPatch_Polyhedron::Parameters(const int Index, double& U, double& V) const
{
  U = ((double*)C_MyU)[Index];
  V = ((double*)C_MyV)[Index];
}

void IntPatch_Polyhedron::DeflectionOverEstimation(const double flec)
{
  if (flec < 0.0001)
  {
    TheDeflection = 0.0001;
    TheBnd.Enlarge(0.0001);
  }
  else
  {
    TheDeflection = flec;
    TheBnd.Enlarge(flec);
  }
}

double IntPatch_Polyhedron::DeflectionOverEstimation() const
{
  return TheDeflection;
}

const Bnd_Box& IntPatch_Polyhedron::Bounding() const
{
  return TheBnd;
}

void IntPatch_Polyhedron::FillBounding()
{
  TheComponentsBnd = new NCollection_HArray1<Bnd_Box>(1, NbTriangles());
  Bnd_Box Boite;
  int     p1, p2, p3;
  int     nbtriangles = NbTriangles();
  for (int iTri = 1; iTri <= nbtriangles; iTri++)
  {
    Triangle(iTri, p1, p2, p3);
    Boite.SetVoid();
    const gp_Pnt& P1 = Point(p1);
    const gp_Pnt& P2 = Point(p2);
    const gp_Pnt& P3 = Point(p3);
    if (P1.SquareDistance(P2) > LONGUEUR_MINI_EDGE_TRIANGLE)
    {
      if (P1.SquareDistance(P3) > LONGUEUR_MINI_EDGE_TRIANGLE)
      {
        if (P2.SquareDistance(P3) > LONGUEUR_MINI_EDGE_TRIANGLE)
        {
          Boite.Add(P1);
          Boite.Add(P2);
          Boite.Add(P3);
        }
      }
    }
    Boite.Enlarge(TheDeflection);
    TheComponentsBnd->SetValue(iTri, Boite);
  }
}

const occ::handle<NCollection_HArray1<Bnd_Box>>& IntPatch_Polyhedron::ComponentsBounding() const
{
  return TheComponentsBnd;
}

int IntPatch_Polyhedron::NbTriangles() const
{
  return nbdeltaU * nbdeltaV * 2;
}

int IntPatch_Polyhedron::NbPoints() const
{
  return (nbdeltaU + 1) * (nbdeltaV + 1);
}

int IntPatch_Polyhedron::TriConnex(const int Triang,
                                   const int Pivot,
                                   const int Pedge,
                                   int&      TriCon,
                                   int&      OtherP) const
{

  int Pivotm1    = Pivot - 1;
  int nbdeltaVp1 = nbdeltaV + 1;
  int nbdeltaVm2 = nbdeltaV + nbdeltaV;

  int ligP = Pivotm1 / nbdeltaVp1;
  int colP = Pivotm1 - ligP * nbdeltaVp1;

  int ligE = 0, colE = 0, typE = 0;
  if (Pedge != 0)
  {
    ligE = (Pedge - 1) / nbdeltaVp1;
    colE = (Pedge - 1) - (ligE * nbdeltaVp1);

    if (ligP == ligE)
      typE = 1;

    else if (colP == colE)
      typE = 2;

    else
      typE = 3;
  }
  else
  {
    typE = 0;
  }

  int linT = 0, colT = 0;
  int linO = 0, colO = 0;
  int t, tt;
  if (Triang != 0)
  {
    t    = (Triang - 1) / (nbdeltaVm2);
    tt   = (Triang - 1) - t * nbdeltaVm2;
    linT = 1 + t;
    colT = 1 + tt;
    if (typE == 0)
    {
      if (ligP == linT)
      {
        ligE = ligP - 1;
        colE = colP - 1;
        typE = 3;
      }
      else
      {
        if (colT == ligP + ligP)
        {
          ligE = ligP;
          colE = colP - 1;
          typE = 1;
        }
        else
        {
          ligE = ligP + 1;
          colE = colP + 1;
          typE = 3;
        }
      }
    }
    switch (typE)
    {
      case 1:
        if (linT == ligP)
        {
          linT++;
          linO = ligP + 1;
          colO = (colP > colE) ? colP : colE;
        }
        else
        {
          linT--;
          linO = ligP - 1;
          colO = (colP < colE) ? colP : colE;
        }
        break;
      case 2:
        if (colT == (colP + colP))
        {
          colT++;
          linO = (ligP > ligE) ? ligP : ligE;
          colO = colP + 1;
        }
        else
        {
          colT--;
          linO = (ligP < ligE) ? ligP : ligE;
          colO = colP - 1;
        }
        break;
      case 3:
        if ((colT & 1) == 0)
        {
          colT--;
          linO = (ligP > ligE) ? ligP : ligE;
          colO = (colP < colE) ? colP : colE;
        }
        else
        {
          colT++;
          linO = (ligP < ligE) ? ligP : ligE;
          colO = (colP > colE) ? colP : colE;
        }
        break;
    }
  }
  else
  {

    if (Pedge == 0)
    {

      linT = (1 > ligP) ? 1 : ligP;
      colT = (1 > (colP + colP)) ? 1 : (colP + colP);
      if (ligP == 0)
        linO = ligP + 1;
      else
        linO = ligP - 1;
      colO = colP;
    }
    else
    {

      switch (typE)
      {
        case 1:
          linT = ligP + 1;
          colT = (colP > colE) ? colP : colE;
          colT += colT;
          linO = ligP + 1;
          colO = (colP > colE) ? colP : colE;
          break;
        case 2:
          linT = (ligP > ligE) ? ligP : ligE;
          colT = colP + colP;
          linO = (ligP < ligE) ? ligP : ligE;
          colO = colP - 1;
          break;
        case 3:
          linT = (ligP > ligE) ? ligP : ligE;
          colT = colP + colE;
          linO = (ligP > ligE) ? ligP : ligE;
          colO = (colP < colE) ? colP : colE;
          break;
      }
    }
  }

  TriCon = (linT - 1) * nbdeltaVm2 + colT;

  if (linT < 1)
  {
    linO = 0;
    colO = colP + colP - colE;
    if (colO < 0)
    {
      colO = 0;
      linO = 1;
    }
    else if (colO > nbdeltaV)
    {
      colO = nbdeltaV;
      linO = 1;
    }
    TriCon = 0;
  }
  else if (linT > nbdeltaU)
  {
    linO = nbdeltaU;
    colO = colP + colP - colE;
    if (colO < 0)
    {
      colO = 0;
      linO = nbdeltaU - 1;
    }
    else if (colO > nbdeltaV)
    {
      colO = nbdeltaV;
      linO = nbdeltaU - 1;
    }
    TriCon = 0;
  }

  if (colT < 1)
  {
    colO = 0;
    linO = ligP + ligP - ligE;
    if (linO < 0)
    {
      linO = 0;
      colO = 1;
    }
    else if (linO > nbdeltaU)
    {
      linO = nbdeltaU;
      colO = 1;
    }
    TriCon = 0;
  }
  else if (colT > nbdeltaV)
  {
    colO = nbdeltaV;
    linO = ligP + ligP - ligE;
    if (linO < 0)
    {
      linO = 0;
      colO = nbdeltaV - 1;
    }
    else if (linO > nbdeltaU)
    {
      linO = nbdeltaU;
      colO = nbdeltaV - 1;
    }
    TriCon = 0;
  }

  OtherP = linO * nbdeltaVp1 + colO + 1;

  if (Point(Pivot).SquareDistance(Point(Pedge)) <= LONGUEUR_MINI_EDGE_TRIANGLE)
  {
    OtherP = 0;
    TriCon = Triang;
#if MSG_DEBUG
    std::cout << " Probleme ds IntCurveSurface_Polyhedron : Pivot et PEdge Confondus " << std::endl;
#endif
    return (TriCon);
  }
  if (Point(OtherP).SquareDistance(Point(Pedge)) <= LONGUEUR_MINI_EDGE_TRIANGLE)
  {
#if MSG_DEBUG
    std::cout << " Probleme ds IntCurveSurface_Polyhedron : OtherP et PEdge Confondus "
              << std::endl;
#endif
    return (0);
  }
  return TriCon;
}

void IntPatch_Polyhedron::PlaneEquation(const int Triang,
                                        gp_XYZ&   NormalVector,
                                        double&   PolarDistance) const
{
  int i1, i2, i3;
  Triangle(Triang, i1, i2, i3);

  gp_XYZ Pointi1(Point(i1).XYZ());
  gp_XYZ Pointi2(Point(i2).XYZ());
  gp_XYZ Pointi3(Point(i3).XYZ());

  gp_XYZ v1 = Pointi2 - Pointi1;
  gp_XYZ v2 = Pointi3 - Pointi2;
  gp_XYZ v3 = Pointi1 - Pointi3;

  if (v1.SquareModulus() <= LONGUEUR_MINI_EDGE_TRIANGLE)
  {
    NormalVector.SetCoord(1.0, 0.0, 0.0);
    return;
  }
  if (v2.SquareModulus() <= LONGUEUR_MINI_EDGE_TRIANGLE)
  {
    NormalVector.SetCoord(1.0, 0.0, 0.0);
    return;
  }
  if (v3.SquareModulus() <= LONGUEUR_MINI_EDGE_TRIANGLE)
  {
    NormalVector.SetCoord(1.0, 0.0, 0.0);
    return;
  }

  NormalVector    = (v1 ^ v2) + (v2 ^ v3) + (v3 ^ v1);
  double aNormLen = NormalVector.Modulus();
  if (aNormLen < gp::Resolution())
  {
    PolarDistance = 0.;
  }
  else
  {
    NormalVector.Divide(aNormLen);
    PolarDistance = NormalVector * Point(i1).XYZ();
  }
}

bool IntPatch_Polyhedron::Contain(const int Triang, const gp_Pnt& ThePnt) const
{
  int i1, i2, i3;
  Triangle(Triang, i1, i2, i3);
  gp_XYZ Pointi1(Point(i1).XYZ());
  gp_XYZ Pointi2(Point(i2).XYZ());
  gp_XYZ Pointi3(Point(i3).XYZ());

  gp_XYZ v1 = (Pointi2 - Pointi1) ^ (ThePnt.XYZ() - Pointi1);
  gp_XYZ v2 = (Pointi3 - Pointi2) ^ (ThePnt.XYZ() - Pointi2);
  gp_XYZ v3 = (Pointi1 - Pointi3) ^ (ThePnt.XYZ() - Pointi3);
  return v1 * v2 >= 0. && v2 * v3 >= 0. && v3 * v1 >= 0.;
}

void IntPatch_Polyhedron::Dump() const {}

void IntPatch_Polyhedron::Size(int& nbdu, int& nbdv) const
{
  nbdu = nbdeltaU;
  nbdv = nbdeltaV;
}

void IntPatch_Polyhedron::Triangle(const int Index, int& P1, int& P2, int& P3) const
{
  int line   = 1 + ((Index - 1) / (nbdeltaV * 2));
  int colon  = 1 + ((Index - 1) % (nbdeltaV * 2));
  int colpnt = (colon + 1) / 2;

  P1 = (line - 1) * (nbdeltaV + 1) + colpnt;

  P2 = line * (nbdeltaV + 1) + colpnt + ((colon - 1) % 2);

  P3 = (line - 1 + (colon % 2)) * (nbdeltaV + 1) + colpnt + 1;
}

const gp_Pnt& IntPatch_Polyhedron::Point(const int Index, double& U, double& V) const
{
  gp_Pnt* CMyPnts = (gp_Pnt*)C_MyPnts;
  double* CMyU    = (double*)C_MyU;
  double* CMyV    = (double*)C_MyV;
  U               = CMyU[Index];
  V               = CMyV[Index];
  return CMyPnts[Index];
}

const gp_Pnt& IntPatch_Polyhedron::Point(const int Index) const
{
  gp_Pnt* CMyPnts = (gp_Pnt*)C_MyPnts;
  return CMyPnts[Index];
}

void IntPatch_Polyhedron::Point(const gp_Pnt&, const int, const int, const double, const double) {}

void IntPatch_Polyhedron::Point(const int Index, gp_Pnt& P) const
{
  gp_Pnt* CMyPnts = (gp_Pnt*)C_MyPnts;
  P               = CMyPnts[Index];
}
