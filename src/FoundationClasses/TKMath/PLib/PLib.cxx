#include <PLib.hpp>

#include <GeomAbs_Shape.hpp>
#include <math.hpp>
#include <math_Gauss.hpp>
#include <math_Matrix.hpp>
#include <BSplCLib.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_ConstructionError.hpp>

#include <array>

void PLib::SetPoles(const NCollection_Array1<gp_Pnt2d>& Poles, NCollection_Array1<double>& FP)
{
  int j      = FP.Lower();
  int PLower = Poles.Lower();
  int PUpper = Poles.Upper();

  for (int i = PLower; i <= PUpper; i++)
  {
    const gp_Pnt2d& P = Poles(i);
    FP(j)             = P.Coord(1);
    j++;
    FP(j) = P.Coord(2);
    j++;
  }
}

void PLib::SetPoles(const NCollection_Array1<gp_Pnt2d>& Poles,
                    const NCollection_Array1<double>&   Weights,
                    NCollection_Array1<double>&         FP)
{
  int j      = FP.Lower();
  int PLower = Poles.Lower();
  int PUpper = Poles.Upper();

  for (int i = PLower; i <= PUpper; i++)
  {
    double          w = Weights(i);
    const gp_Pnt2d& P = Poles(i);
    FP(j)             = P.Coord(1) * w;
    j++;
    FP(j) = P.Coord(2) * w;
    j++;
    FP(j) = w;
    j++;
  }
}

void PLib::GetPoles(const NCollection_Array1<double>& FP, NCollection_Array1<gp_Pnt2d>& Poles)
{
  int j      = FP.Lower();
  int PLower = Poles.Lower();
  int PUpper = Poles.Upper();

  for (int i = PLower; i <= PUpper; i++)
  {
    gp_Pnt2d& P = Poles(i);
    P.SetCoord(1, FP(j));
    j++;
    P.SetCoord(2, FP(j));
    j++;
  }
}

void PLib::GetPoles(const NCollection_Array1<double>& FP,
                    NCollection_Array1<gp_Pnt2d>&     Poles,
                    NCollection_Array1<double>&       Weights)
{
  int j      = FP.Lower();
  int PLower = Poles.Lower();
  int PUpper = Poles.Upper();

  for (int i = PLower; i <= PUpper; i++)
  {
    double w    = FP(j + 2);
    Weights(i)  = w;
    gp_Pnt2d& P = Poles(i);
    P.SetCoord(1, FP(j) / w);
    j++;
    P.SetCoord(2, FP(j) / w);
    j++;
    j++;
  }
}

void PLib::SetPoles(const NCollection_Array1<gp_Pnt>& Poles, NCollection_Array1<double>& FP)
{
  int j      = FP.Lower();
  int PLower = Poles.Lower();
  int PUpper = Poles.Upper();

  for (int i = PLower; i <= PUpper; i++)
  {
    const gp_Pnt& P = Poles(i);
    FP(j)           = P.Coord(1);
    j++;
    FP(j) = P.Coord(2);
    j++;
    FP(j) = P.Coord(3);
    j++;
  }
}

void PLib::SetPoles(const NCollection_Array1<gp_Pnt>& Poles,
                    const NCollection_Array1<double>& Weights,
                    NCollection_Array1<double>&       FP)
{
  int j      = FP.Lower();
  int PLower = Poles.Lower();
  int PUpper = Poles.Upper();

  for (int i = PLower; i <= PUpper; i++)
  {
    double        w = Weights(i);
    const gp_Pnt& P = Poles(i);
    FP(j)           = P.Coord(1) * w;
    j++;
    FP(j) = P.Coord(2) * w;
    j++;
    FP(j) = P.Coord(3) * w;
    j++;
    FP(j) = w;
    j++;
  }
}

void PLib::GetPoles(const NCollection_Array1<double>& FP, NCollection_Array1<gp_Pnt>& Poles)
{
  int j      = FP.Lower();
  int PLower = Poles.Lower();
  int PUpper = Poles.Upper();

  for (int i = PLower; i <= PUpper; i++)
  {
    gp_Pnt& P = Poles(i);
    P.SetCoord(1, FP(j));
    j++;
    P.SetCoord(2, FP(j));
    j++;
    P.SetCoord(3, FP(j));
    j++;
  }
}

void PLib::GetPoles(const NCollection_Array1<double>& FP,
                    NCollection_Array1<gp_Pnt>&       Poles,
                    NCollection_Array1<double>&       Weights)
{
  int j      = FP.Lower();
  int PLower = Poles.Lower();
  int PUpper = Poles.Upper();

  for (int i = PLower; i <= PUpper; i++)
  {
    double w   = FP(j + 3);
    Weights(i) = w;
    gp_Pnt& P  = Poles(i);
    P.SetCoord(1, FP(j) / w);
    j++;
    P.SetCoord(2, FP(j) / w);
    j++;
    P.SetCoord(3, FP(j) / w);
    j++;
    j++;
  }
}

namespace
{

  template <int MaxDegree>
  class BinomAllocator
  {
  public:
    constexpr BinomAllocator()
        : myBinom{}
    {

      myBinom[0][0] = 1;

      for (int i = 1; i <= MaxDegree; ++i)
      {

        myBinom[i][0] = 1;
        myBinom[i][i] = 1;

        for (int j = 1; j < i; ++j)
        {
          myBinom[i][j] = myBinom[i - 1][j - 1] + myBinom[i - 1][j];
        }
      }
    }

    constexpr int Value(const int N, const int P) const { return myBinom[N][P]; }

  private:
    int myBinom[MaxDegree + 1][MaxDegree + 1];
  };

  template <int MaxDegree = BSplCLib::MaxDegree()>
  inline const BinomAllocator<MaxDegree>& GetBinomAllocator()
  {
    static constexpr BinomAllocator<MaxDegree> THE_ALLOCATOR{};
    return THE_ALLOCATOR;
  }

} // namespace

double PLib::Bin(const int N, const int P)
{
  const auto& aBinom = GetBinomAllocator();

  Standard_OutOfRange_Raise_if(N < 0 || N > BSplCLib::MaxDegree(),
                               "PLib::Bin: degree N is out of supported range [0, 25]");
  Standard_OutOfRange_Raise_if(P < 0 || P > N,
                               "PLib::Bin: parameter P is out of valid range [0, N]");

  return double(aBinom.Value(N, P));
}

void PLib::RationalDerivative(const int  Degree,
                              const int  DerivativeRequest,
                              const int  Dimension,
                              double&    Ders,
                              double&    RDers,
                              const bool All)
{

  double                         Inverse;
  double*                        PolesArray    = &Ders;
  double*                        RationalArray = &RDers;
  double                         Factor;
  int                            ii, Index, OtherIndex, Index1, Index2, jj;
  NCollection_LocalArray<double> binomial_array;
  NCollection_LocalArray<double> derivative_storage;
  if (Dimension == 3)
  {
    int DeRequest1 = DerivativeRequest + 1;
    int MinDegRequ = DerivativeRequest;
    if (MinDegRequ > Degree)
      MinDegRequ = Degree;
    binomial_array.Allocate(DeRequest1);

    for (ii = 0; ii < DeRequest1; ii++)
    {
      binomial_array[ii] = 1.0e0;
    }
    if (!All)
    {
      int DimDeRequ1 = (DeRequest1 << 1) + DeRequest1;
      derivative_storage.Allocate(DimDeRequ1);
      RationalArray = derivative_storage;
    }

    Inverse    = 1.0e0 / PolesArray[3];
    Index      = 0;
    Index2     = -6;
    OtherIndex = 0;

    for (ii = 0; ii <= MinDegRequ; ii++)
    {
      Index2 += 3;
      Index1               = Index2;
      RationalArray[Index] = PolesArray[OtherIndex];
      Index++;
      OtherIndex++;
      RationalArray[Index] = PolesArray[OtherIndex];
      Index++;
      OtherIndex++;
      RationalArray[Index] = PolesArray[OtherIndex];
      Index -= 2;
      OtherIndex += 2;

      for (jj = ii - 1; jj >= 0; jj--)
      {
        Factor = binomial_array[jj] * PolesArray[((ii - jj) << 2) + 3];
        RationalArray[Index] -= Factor * RationalArray[Index1];
        Index++;
        Index1++;
        RationalArray[Index] -= Factor * RationalArray[Index1];
        Index++;
        Index1++;
        RationalArray[Index] -= Factor * RationalArray[Index1];
        Index -= 2;
        Index1 -= 5;
      }

      for (jj = ii; jj >= 1; jj--)
      {
        binomial_array[jj] += binomial_array[jj - 1];
      }
      RationalArray[Index] *= Inverse;
      Index++;
      RationalArray[Index] *= Inverse;
      Index++;
      RationalArray[Index] *= Inverse;
      Index++;
    }

    for (ii = MinDegRequ + 1; ii <= DerivativeRequest; ii++)
    {
      Index2 += 3;
      Index1               = Index2;
      RationalArray[Index] = 0.0e0;
      Index++;
      RationalArray[Index] = 0.0e0;
      Index++;
      RationalArray[Index] = 0.0e0;
      Index -= 2;

      for (jj = ii - 1; jj >= ii - MinDegRequ; jj--)
      {
        Factor = binomial_array[jj] * PolesArray[((ii - jj) << 2) + 3];
        RationalArray[Index] -= Factor * RationalArray[Index1];
        Index++;
        Index1++;
        RationalArray[Index] -= Factor * RationalArray[Index1];
        Index++;
        Index1++;
        RationalArray[Index] -= Factor * RationalArray[Index1];
        Index -= 2;
        Index1 -= 5;
      }

      for (jj = ii; jj >= 1; jj--)
      {
        binomial_array[jj] += binomial_array[jj - 1];
      }
      RationalArray[Index] *= Inverse;
      Index++;
      RationalArray[Index] *= Inverse;
      Index++;
      RationalArray[Index] *= Inverse;
      Index++;
    }

    if (!All)
    {
      RationalArray    = &RDers;
      int DimDeRequ    = (DerivativeRequest << 1) + DerivativeRequest;
      RationalArray[0] = derivative_storage[DimDeRequ];
      DimDeRequ++;
      RationalArray[1] = derivative_storage[DimDeRequ];
      DimDeRequ++;
      RationalArray[2] = derivative_storage[DimDeRequ];
    }
  }
  else
  {
    int kk;
    int Dimension1 = Dimension + 1;
    int Dimension2 = Dimension << 1;
    int DeRequest1 = DerivativeRequest + 1;
    int MinDegRequ = DerivativeRequest;
    if (MinDegRequ > Degree)
      MinDegRequ = Degree;
    binomial_array.Allocate(DeRequest1);

    for (ii = 0; ii < DeRequest1; ii++)
    {
      binomial_array[ii] = 1.0e0;
    }
    if (!All)
    {
      int DimDeRequ1 = Dimension * DeRequest1;
      derivative_storage.Allocate(DimDeRequ1);
      RationalArray = derivative_storage;
    }

    Inverse    = 1.0e0 / PolesArray[Dimension];
    Index      = 0;
    Index2     = -Dimension2;
    OtherIndex = 0;

    for (ii = 0; ii <= MinDegRequ; ii++)
    {
      Index2 += Dimension;
      Index1 = Index2;

      for (kk = 0; kk < Dimension; kk++)
      {
        RationalArray[Index] = PolesArray[OtherIndex];
        Index++;
        OtherIndex++;
      }
      Index -= Dimension;
      ++OtherIndex;

      for (jj = ii - 1; jj >= 0; jj--)
      {
        Factor = binomial_array[jj] * PolesArray[(ii - jj) * Dimension1 + Dimension];

        for (kk = 0; kk < Dimension; kk++)
        {
          RationalArray[Index] -= Factor * RationalArray[Index1];
          Index++;
          Index1++;
        }
        Index -= Dimension;
        Index1 -= Dimension2;
      }

      for (jj = ii; jj >= 1; jj--)
      {
        binomial_array[jj] += binomial_array[jj - 1];
      }

      for (kk = 0; kk < Dimension; kk++)
      {
        RationalArray[Index] *= Inverse;
        Index++;
      }
    }

    for (ii = MinDegRequ + 1; ii <= DerivativeRequest; ii++)
    {
      Index2 += Dimension;
      Index1 = Index2;

      for (kk = 0; kk < Dimension; kk++)
      {
        RationalArray[Index] = 0.0e0;
        Index++;
      }
      Index -= Dimension;

      for (jj = ii - 1; jj >= ii - MinDegRequ; jj--)
      {
        Factor = binomial_array[jj] * PolesArray[(ii - jj) * Dimension1 + Dimension];

        for (kk = 0; kk < Dimension; kk++)
        {
          RationalArray[Index] -= Factor * RationalArray[Index1];
          Index++;
          Index1++;
        }
        Index -= Dimension;
        Index1 -= Dimension2;
      }

      for (jj = ii; jj >= 1; jj--)
      {
        binomial_array[jj] += binomial_array[jj - 1];
      }

      for (kk = 0; kk < Dimension; kk++)
      {
        RationalArray[Index] *= Inverse;
        Index++;
      }
    }

    if (!All)
    {
      RationalArray = &RDers;
      int DimDeRequ = Dimension * DerivativeRequest;

      for (kk = 0; kk < Dimension; kk++)
      {
        RationalArray[kk] = derivative_storage[DimDeRequ];
        DimDeRequ++;
      }
    }
  }
}

void PLib::RationalDerivatives(const int DerivativeRequest,
                               const int Dimension,
                               double&   PolesDerivates,

                               double& WeightsDerivates,

                               double& RationalDerivates)
{

  double  Inverse;
  double* PolesArray    = &PolesDerivates;
  double* WeightsArray  = &WeightsDerivates;
  double* RationalArray = &RationalDerivates;
  double  Factor;

  int ii, Index, Index1, Index2, jj;
  int DeRequest1 = DerivativeRequest + 1;

  NCollection_LocalArray<double> binomial_array(DeRequest1);
  NCollection_LocalArray<double> derivative_storage;

  for (ii = 0; ii < DeRequest1; ii++)
  {
    binomial_array[ii] = 1.0e0;
  }
  Inverse = 1.0e0 / WeightsArray[0];
  if (Dimension == 3)
  {
    Index  = 0;
    Index2 = -6;

    for (ii = 0; ii < DeRequest1; ii++)
    {
      Index2 += 3;
      Index1               = Index2;
      RationalArray[Index] = PolesArray[Index];
      Index++;
      RationalArray[Index] = PolesArray[Index];
      Index++;
      RationalArray[Index] = PolesArray[Index];
      Index -= 2;

      for (jj = ii - 1; jj >= 0; jj--)
      {
        Factor = binomial_array[jj] * WeightsArray[ii - jj];
        RationalArray[Index] -= Factor * RationalArray[Index1];
        Index++;
        Index1++;
        RationalArray[Index] -= Factor * RationalArray[Index1];
        Index++;
        Index1++;
        RationalArray[Index] -= Factor * RationalArray[Index1];
        Index -= 2;
        Index1 -= 5;
      }

      for (jj = ii; jj >= 1; jj--)
      {
        binomial_array[jj] += binomial_array[jj - 1];
      }
      RationalArray[Index] *= Inverse;
      Index++;
      RationalArray[Index] *= Inverse;
      Index++;
      RationalArray[Index] *= Inverse;
      Index++;
    }
  }
  else
  {
    int kk;
    int Dimension2 = Dimension << 1;
    Index          = 0;
    Index2         = -Dimension2;

    for (ii = 0; ii < DeRequest1; ii++)
    {
      Index2 += Dimension;
      Index1 = Index2;

      for (kk = 0; kk < Dimension; kk++)
      {
        RationalArray[Index] = PolesArray[Index];
        Index++;
      }
      Index -= Dimension;

      for (jj = ii - 1; jj >= 0; jj--)
      {
        Factor = binomial_array[jj] * WeightsArray[ii - jj];

        for (kk = 0; kk < Dimension; kk++)
        {
          RationalArray[Index] -= Factor * RationalArray[Index1];
          Index++;
          Index1++;
        }
        Index -= Dimension;
        Index1 -= Dimension2;
      }

      for (jj = ii; jj >= 1; jj--)
      {
        binomial_array[jj] += binomial_array[jj - 1];
      }

      for (kk = 0; kk < Dimension; kk++)
      {
        RationalArray[Index] *= Inverse;
        Index++;
      }
    }
  }
}

namespace
{

  constexpr int THE_MAX_OPT_DIM = 15;

  template <int dim>
  inline void eval_poly0(double* theResult, const double* theCoeffs, int theDegree, double thePar)
  {
    std::array<double, dim> aLocal;
    for (int i = 0; i < dim; ++i)
    {
      aLocal[i] = theCoeffs[i];
    }

    const double* aCoeffs = theCoeffs;
    for (int aDeg = 0; aDeg < theDegree; ++aDeg)
    {
      aCoeffs -= dim;
      for (int i = 0; i < dim; ++i)
      {
        aLocal[i] = aLocal[i] * thePar + aCoeffs[i];
      }
    }

    for (int i = 0; i < dim; ++i)
    {
      theResult[i] = aLocal[i];
    }
  }

  template <int dim>
  inline void eval_poly1(double* theResult, const double* theCoeffs, int theDegree, double thePar)
  {
    std::array<double, dim> aLocal0;
    std::array<double, dim> aLocal1;

    for (int i = 0; i < dim; ++i)
    {
      aLocal0[i] = theCoeffs[i];
      aLocal1[i] = 0.0;
    }

    const double* aCoeffs = theCoeffs;
    for (int aDeg = 0; aDeg < theDegree; ++aDeg)
    {
      aCoeffs -= dim;
      for (int i = 0; i < dim; ++i)
      {
        const double aVal = aLocal0[i];
        aLocal1[i]        = aLocal1[i] * thePar + aVal;
        aLocal0[i]        = aVal * thePar + aCoeffs[i];
      }
    }

    for (int i = 0; i < dim; ++i)
    {
      theResult[i]       = aLocal0[i];
      theResult[dim + i] = aLocal1[i];
    }
  }

  template <int dim>
  inline void eval_poly2(double* theResult, const double* theCoeffs, int theDegree, double thePar)
  {
    std::array<double, dim> aLocal0;
    std::array<double, dim> aLocal1;
    std::array<double, dim> aLocal2;

    for (int i = 0; i < dim; ++i)
    {
      aLocal0[i] = theCoeffs[i];
      aLocal1[i] = 0.0;
      aLocal2[i] = 0.0;
    }

    const double* aCoeffs = theCoeffs;
    for (int aDeg = 0; aDeg < theDegree; ++aDeg)
    {
      aCoeffs -= dim;
      for (int i = 0; i < dim; ++i)
      {
        const double aD1  = aLocal1[i];
        const double aVal = aLocal0[i];
        aLocal2[i]        = aLocal2[i] * thePar + aD1 * 2.0;
        aLocal1[i]        = aD1 * thePar + aVal;
        aLocal0[i]        = aVal * thePar + aCoeffs[i];
      }
    }

    for (int i = 0; i < dim; ++i)
    {
      theResult[i]           = aLocal0[i];
      theResult[dim + i]     = aLocal1[i];
      theResult[2 * dim + i] = aLocal2[i];
    }
  }

  inline void eval_poly0_runtime(double*       theResult,
                                 const double* theCoeffs,
                                 int           theDegree,
                                 double        thePar,
                                 int           theDimension)
  {
    for (int i = 0; i < theDimension; ++i)
    {
      theResult[i] = theCoeffs[i];
    }

    const double* aCoeffs = theCoeffs;
    for (int aDeg = 0; aDeg < theDegree; ++aDeg)
    {
      aCoeffs -= theDimension;
      for (int i = 0; i < theDimension; ++i)
      {
        theResult[i] = theResult[i] * thePar + aCoeffs[i];
      }
    }
  }

  inline void eval_poly1_runtime(double*       theResult,
                                 const double* theCoeffs,
                                 int           theDegree,
                                 double        thePar,
                                 int           theDimension)
  {
    double* aRes0 = theResult;
    double* aRes1 = theResult + theDimension;

    for (int i = 0; i < theDimension; ++i)
    {
      aRes0[i] = theCoeffs[i];
      aRes1[i] = 0.0;
    }

    const double* aCoeffs = theCoeffs;
    for (int aDeg = 0; aDeg < theDegree; ++aDeg)
    {
      aCoeffs -= theDimension;
      for (int i = 0; i < theDimension; ++i)
      {
        const double aVal = aRes0[i];
        aRes1[i]          = aRes1[i] * thePar + aVal;
        aRes0[i]          = aVal * thePar + aCoeffs[i];
      }
    }
  }

  inline void eval_poly2_runtime(double*       theResult,
                                 const double* theCoeffs,
                                 int           theDegree,
                                 double        thePar,
                                 int           theDimension)
  {
    double* aRes0 = theResult;
    double* aRes1 = theResult + theDimension;
    double* aRes2 = theResult + 2 * theDimension;

    for (int i = 0; i < theDimension; ++i)
    {
      aRes0[i] = theCoeffs[i];
      aRes1[i] = 0.0;
      aRes2[i] = 0.0;
    }

    const double* aCoeffs = theCoeffs;
    for (int aDeg = 0; aDeg < theDegree; ++aDeg)
    {
      aCoeffs -= theDimension;
      for (int i = 0; i < theDimension; ++i)
      {
        const double aD1  = aRes1[i];
        const double aVal = aRes0[i];
        aRes2[i]          = aRes2[i] * thePar + aD1 * 2.0;
        aRes1[i]          = aD1 * thePar + aVal;
        aRes0[i]          = aVal * thePar + aCoeffs[i];
      }
    }
  }

  using EvalPolyFunc = void (*)(double*, const double*, int, double);

  template <template <int> class EvalFunc, typename FuncPtr, int... Is>
  constexpr std::array<FuncPtr, sizeof...(Is)> makeDispatchTable(std::integer_sequence<int, Is...>)
  {
    return {{&EvalFunc<Is + 1>::call...}};
  }

  template <int Dim>
  struct EvalPoly0Wrapper
  {
    static void call(double* r, const double* c, int d, double p) { eval_poly0<Dim>(r, c, d, p); }
  };

  template <int Dim>
  struct EvalPoly1Wrapper
  {
    static void call(double* r, const double* c, int d, double p) { eval_poly1<Dim>(r, c, d, p); }
  };

  template <int Dim>
  struct EvalPoly2Wrapper
  {
    static void call(double* r, const double* c, int d, double p) { eval_poly2<Dim>(r, c, d, p); }
  };

  constexpr std::array<EvalPolyFunc, THE_MAX_OPT_DIM> THE_EVAL_POLY0_TABLE =
    makeDispatchTable<EvalPoly0Wrapper, EvalPolyFunc>(
      std::make_integer_sequence<int, THE_MAX_OPT_DIM>{});

  constexpr std::array<EvalPolyFunc, THE_MAX_OPT_DIM> THE_EVAL_POLY1_TABLE =
    makeDispatchTable<EvalPoly1Wrapper, EvalPolyFunc>(
      std::make_integer_sequence<int, THE_MAX_OPT_DIM>{});

  constexpr std::array<EvalPolyFunc, THE_MAX_OPT_DIM> THE_EVAL_POLY2_TABLE =
    makeDispatchTable<EvalPoly2Wrapper, EvalPolyFunc>(
      std::make_integer_sequence<int, THE_MAX_OPT_DIM>{});

} // namespace

void PLib::EvalPolynomial(const double  Par,
                          const int     DerivativeRequest,
                          const int     Degree,
                          const int     Dimension,
                          const double& PolynomialCoeff,
                          double&       Results)

{
  const double* aCoeffs = &PolynomialCoeff + Degree * Dimension;
  double*       aRes    = &Results;

  switch (DerivativeRequest)
  {
    case 1:
    {
      if (Dimension >= 1 && Dimension <= THE_MAX_OPT_DIM)
      {
        THE_EVAL_POLY1_TABLE[Dimension - 1](aRes, aCoeffs, Degree, Par);
      }
      else
      {
        eval_poly1_runtime(aRes, aCoeffs, Degree, Par, Dimension);
      }
      break;
    }
    case 2:
    {
      if (Dimension >= 1 && Dimension <= THE_MAX_OPT_DIM)
      {
        THE_EVAL_POLY2_TABLE[Dimension - 1](aRes, aCoeffs, Degree, Par);
      }
      else
      {
        eval_poly2_runtime(aRes, aCoeffs, Degree, Par, Dimension);
      }
      break;
    }
    default:
    {

      const int aResSize = (1 + DerivativeRequest) * Dimension;
      for (int i = 0; i < aResSize; ++i)
      {
        aRes[i] = 0.0;
      }

      for (int aDeg = 0; aDeg <= Degree; ++aDeg)
      {
        double* aPtr = aRes + aResSize - Dimension;

        for (int aDeriv = DerivativeRequest; aDeriv > 0; --aDeriv)
        {
          double* anOriginal = aPtr - Dimension;
          for (int ind = 0; ind < Dimension; ++ind)
          {
            aPtr[ind] = aPtr[ind] * Par + anOriginal[ind] * aDeriv;
          }
          aPtr = anOriginal;
        }

        for (int ind = 0; ind < Dimension; ++ind)
        {
          aPtr[ind] = aPtr[ind] * Par + aCoeffs[ind];
        }
        aCoeffs -= Dimension;
      }
    }
  }
}

void PLib::NoDerivativeEvalPolynomial(const double  Par,
                                      const int     Degree,
                                      const int     Dimension,
                                      const int     DegreeDimension,
                                      const double& PolynomialCoeff,
                                      double&       Results)
{
  const double* aCoeffs = &PolynomialCoeff + DegreeDimension;
  double*       aRes    = &Results;

  if (Dimension >= 1 && Dimension <= THE_MAX_OPT_DIM)
  {
    THE_EVAL_POLY0_TABLE[Dimension - 1](aRes, aCoeffs, Degree, Par);
  }
  else
  {
    eval_poly0_runtime(aRes, aCoeffs, Degree, Par, Dimension);
  }
}

void PLib::EvalPoly2Var(const double UParameter,
                        const double VParameter,
                        const int    UDerivativeRequest,
                        const int    VDerivativeRequest,
                        const int    UDegree,
                        const int    VDegree,
                        const int    Dimension,
                        double&      PolynomialCoeff,
                        double&      Results)

{
  int                        Udim = (VDegree + 1) * Dimension, index = Udim * UDerivativeRequest;
  NCollection_Array1<double> Curve(1, Udim * (UDerivativeRequest + 1));
  NCollection_Array1<double> Point(1, Dimension * (VDerivativeRequest + 1));
  double*                    Result = (double*)&Curve.ChangeValue(1);
  double*                    Digit  = (double*)&Point.ChangeValue(1);
  double*                    ResultArray;
  ResultArray = &Results;

  PLib::EvalPolynomial(UParameter, UDerivativeRequest, UDegree, Udim, PolynomialCoeff, Result[0]);

  PLib::EvalPolynomial(VParameter, VDerivativeRequest, VDegree, Dimension, Result[index], Digit[0]);

  index = Dimension * VDerivativeRequest;

  for (int i = 0; i < Dimension; i++)
  {
    ResultArray[i] = Digit[index + i];
  }
}

int PLib::EvalLagrange(const double Parameter,
                       const int    DerivativeRequest,
                       const int    Degree,
                       const int    Dimension,
                       double&      Values,
                       double&      Parameters,
                       double&      Results)
{

  int     ii, jj, kk, Index, Index1, ReturnCode = 0;
  int     local_request = DerivativeRequest;
  double* ParameterArray;
  double  difference;
  double* PointsArray;
  double* ResultArray;

  PointsArray    = &Values;
  ParameterArray = &Parameters;
  ResultArray    = &Results;
  if (local_request >= Degree)
  {
    local_request = Degree;
  }
  NCollection_LocalArray<double> divided_differences_array((Degree + 1) * Dimension);

  for (ii = 0; ii < (Degree + 1) * Dimension; ii++)
  {
    divided_differences_array[ii] = PointsArray[ii];
  }

  for (ii = Degree; ii >= 0; ii--)
  {

    for (jj = Degree; jj > Degree - ii; jj--)
    {
      Index  = jj * Dimension;
      Index1 = Index - Dimension;

      for (kk = 0; kk < Dimension; kk++)
      {
        divided_differences_array[Index + kk] -= divided_differences_array[Index1 + kk];
      }
      difference = ParameterArray[jj] - ParameterArray[jj - Degree - 1 + ii];
      if (std::abs(difference) < RealSmall())
      {
        ReturnCode = 1;
        goto FINISH;
      }
      difference = 1.0e0 / difference;

      for (kk = 0; kk < Dimension; kk++)
      {
        divided_differences_array[Index + kk] *= difference;
      }
    }
  }

  Index = Degree * Dimension;

  for (kk = 0; kk < Dimension; kk++)
  {
    ResultArray[kk] = divided_differences_array[Index + kk];
  }

  for (ii = Dimension; ii < (local_request + 1) * Dimension; ii++)
  {
    ResultArray[ii] = 0.0e0;
  }

  for (ii = Degree; ii >= 1; ii--)
  {
    difference = Parameter - ParameterArray[ii - 1];

    for (jj = local_request; jj > 0; jj--)
    {
      Index  = jj * Dimension;
      Index1 = Index - Dimension;

      for (kk = 0; kk < Dimension; kk++)
      {
        ResultArray[Index + kk] *= difference;
        ResultArray[Index + kk] += ResultArray[Index1 + kk] * (double)jj;
      }
    }
    Index = (ii - 1) * Dimension;

    for (kk = 0; kk < Dimension; kk++)
    {
      ResultArray[kk] *= difference;
      ResultArray[kk] += divided_differences_array[Index + kk];
    }
  }
FINISH:
  return (ReturnCode);
}

int PLib::EvalCubicHermite(const double Parameter,
                           const int    DerivativeRequest,
                           const int    Dimension,
                           double&      Values,
                           double&      Derivatives,
                           double&      theParameters,
                           double&      Results)
{

  int ii, jj, kk, pp, Index, Index1, Degree, ReturnCode;
  int local_request = DerivativeRequest;

  ReturnCode = 0;
  Degree     = 3;
  double  ParametersArray[4];
  double  difference;
  double  inverse;
  double* FirstLast;
  double* PointsArray;
  double* DerivativesArray;
  double* ResultArray;

  DerivativesArray = &Derivatives;
  PointsArray      = &Values;
  FirstLast        = &theParameters;
  ResultArray      = &Results;
  if (local_request >= Degree)
  {
    local_request = Degree;
  }
  NCollection_LocalArray<double> divided_differences_array((Degree + 1) * Dimension);

  for (ii = 0, jj = 0; ii < 2; ii++, jj += 2)
  {
    ParametersArray[jj] = ParametersArray[jj + 1] = FirstLast[ii];
  }

  inverse = FirstLast[1] - FirstLast[0];
  inverse = 1.0e0 / inverse;

  for (ii = 0, jj = Dimension, kk = 2 * Dimension, pp = 3 * Dimension; ii < Dimension;
       ii++, jj++, kk++, pp++)
  {
    divided_differences_array[ii] = PointsArray[ii];
    divided_differences_array[kk] = inverse * (PointsArray[jj] - PointsArray[ii]);
    divided_differences_array[jj] = DerivativesArray[ii];
    divided_differences_array[pp] = DerivativesArray[jj];
  }

  for (ii = 1; ii <= Degree; ii++)
  {

    for (jj = Degree; jj >= ii + 1; jj--)
    {
      Index  = jj * Dimension;
      Index1 = Index - Dimension;

      for (kk = 0; kk < Dimension; kk++)
      {
        divided_differences_array[Index + kk] -= divided_differences_array[Index1 + kk];
      }

      for (kk = 0; kk < Dimension; kk++)
      {
        divided_differences_array[Index + kk] *= inverse;
      }
    }
  }

  Index = Degree * Dimension;

  for (kk = 0; kk < Dimension; kk++)
  {
    ResultArray[kk] = divided_differences_array[Index + kk];
  }

  for (ii = Dimension; ii < (local_request + 1) * Dimension; ii++)
  {
    ResultArray[ii] = 0.0e0;
  }

  for (ii = Degree; ii >= 1; ii--)
  {
    difference = Parameter - ParametersArray[ii - 1];

    for (jj = local_request; jj > 0; jj--)
    {
      Index  = jj * Dimension;
      Index1 = Index - Dimension;

      for (kk = 0; kk < Dimension; kk++)
      {
        ResultArray[Index + kk] *= difference;
        ResultArray[Index + kk] += ResultArray[Index1 + kk] * (double)jj;
      }
    }
    Index = (ii - 1) * Dimension;

    for (kk = 0; kk < Dimension; kk++)
    {
      ResultArray[kk] *= difference;
      ResultArray[kk] += divided_differences_array[Index + kk];
    }
  }

  return (ReturnCode);
}

bool PLib::HermiteCoefficients(const double FirstParameter,
                               const double LastParameter,
                               const int    FirstOrder,
                               const int    LastOrder,
                               math_Matrix& MatrixCoefs)
{
  int         NbCoeff = FirstOrder + LastOrder + 2, Ordre[2];
  int         ii, jj, pp, cote, iof = 0;
  double      Prod, TBorne = FirstParameter;
  math_Vector Coeff(1, NbCoeff), B(1, NbCoeff, 0.0);
  math_Matrix MAT(1, NbCoeff, 1, NbCoeff, 0.0);

  if ((FirstOrder < 0) || (LastOrder < 0))
    return false;
  double D1 = fabs(FirstParameter), D2 = fabs(LastParameter);
  if (D1 > 100 || D2 > 100)
    return false;
  D2 += D1;
  if (D2 < 0.01)
    return false;
  if (fabs(LastParameter - FirstParameter) / D2 < 0.01)
    return false;

  Ordre[0] = FirstOrder + 1;
  Ordre[1] = LastOrder + 1;

  for (cote = 0; cote <= 1; cote++)
  {
    Coeff.Init(1);

    for (pp = 1; pp <= Ordre[cote]; pp++)
    {
      ii   = pp + iof;
      Prod = 1;

      for (jj = pp; jj <= NbCoeff; jj++)
      {

        MAT(ii, jj) = Coeff(jj) * Prod;
        Coeff(jj) *= jj - pp;
        Prod *= TBorne;
      }
    }
    TBorne = LastParameter;
    iof    = Ordre[0];
  }

  math_Gauss ResolCoeff(MAT, 1.0e-10);
  if (!ResolCoeff.IsDone())
    return false;

  for (ii = 1; ii <= NbCoeff; ii++)
  {
    B(ii) = 1;
    ResolCoeff.Solve(B, Coeff);
    MatrixCoefs.SetRow(ii, Coeff);
    B(ii) = 0;
  }
  return true;
}

void PLib::CoefficientsPoles(const NCollection_Array1<gp_Pnt>& Coefs,
                             const NCollection_Array1<double>* WCoefs,
                             NCollection_Array1<gp_Pnt>&       Poles,
                             NCollection_Array1<double>*       Weights)
{
  NCollection_Array1<double> tempC(1, 3 * Coefs.Length());
  PLib::SetPoles(Coefs, tempC);
  NCollection_Array1<double> tempP(1, 3 * Poles.Length());
  PLib::SetPoles(Coefs, tempP);
  PLib::CoefficientsPoles(3, tempC, WCoefs, tempP, Weights);
  PLib::GetPoles(tempP, Poles);
}

void PLib::CoefficientsPoles(const NCollection_Array1<gp_Pnt2d>& Coefs,
                             const NCollection_Array1<double>*   WCoefs,
                             NCollection_Array1<gp_Pnt2d>&       Poles,
                             NCollection_Array1<double>*         Weights)
{
  NCollection_Array1<double> tempC(1, 2 * Coefs.Length());
  PLib::SetPoles(Coefs, tempC);
  NCollection_Array1<double> tempP(1, 2 * Poles.Length());
  PLib::SetPoles(Coefs, tempP);
  PLib::CoefficientsPoles(2, tempC, WCoefs, tempP, Weights);
  PLib::GetPoles(tempP, Poles);
}

void PLib::CoefficientsPoles(const NCollection_Array1<double>& Coefs,
                             const NCollection_Array1<double>* WCoefs,
                             NCollection_Array1<double>&       Poles,
                             NCollection_Array1<double>*       Weights)
{
  PLib::CoefficientsPoles(1, Coefs, WCoefs, Poles, Weights);
}

void PLib::CoefficientsPoles(const int                         dim,
                             const NCollection_Array1<double>& Coefs,
                             const NCollection_Array1<double>* WCoefs,
                             NCollection_Array1<double>&       Poles,
                             NCollection_Array1<double>*       Weights)
{
  bool rat    = WCoefs != nullptr;
  int  loc    = Coefs.Lower();
  int  lop    = Poles.Lower();
  int  lowc   = 0;
  int  lowp   = 0;
  int  upc    = Coefs.Upper();
  int  upp    = Poles.Upper();
  int  upwc   = 0;
  int  upwp   = 0;
  int  reflen = Coefs.Length() / dim;
  int  i, j, k;

  if (rat)
  {
    lowc = WCoefs->Lower();
    lowp = Weights->Lower();
    upwc = WCoefs->Upper();
    upwp = Weights->Upper();
  }

  for (i = 0; i < dim; i++)
  {
    Poles(lop + i) = Coefs(loc + i);
    Poles(upp - i) = Coefs(upc - i);
  }
  if (rat)
  {
    (*Weights)(lowp) = (*WCoefs)(lowc);
    (*Weights)(upwp) = (*WCoefs)(upwc);
  }

  double Cnp;
  for (i = 2; i < reflen; i++)
  {
    Cnp = PLib::Bin(reflen - 1, i - 1);
    if (rat)
      (*Weights)(lowp + i - 1) = (*WCoefs)(lowc + i - 1) / Cnp;

    for (j = 0; j < dim; j++)
    {
      Poles(lop + dim * (i - 1) + j) = Coefs(loc + dim * (i - 1) + j) / Cnp;
    }
  }

  for (i = 1; i <= reflen - 1; i++)
  {

    for (j = reflen - 1; j >= i; j--)
    {
      if (rat)
        (*Weights)(lowp + j) += (*Weights)(lowp + j - 1);

      for (k = 0; k < dim; k++)
      {
        Poles(lop + dim * j + k) += Poles(lop + dim * (j - 1) + k);
      }
    }
  }
  if (rat)
  {

    for (i = 1; i <= reflen; i++)
    {

      for (j = 0; j < dim; j++)
      {
        Poles(lop + dim * (i - 1) + j) /= (*Weights)(lowp + i - 1);
      }
    }
  }
}

void PLib::Trimming(const double                U1,
                    const double                U2,
                    NCollection_Array1<gp_Pnt>& Coefs,
                    NCollection_Array1<double>* WCoefs)
{
  NCollection_Array1<double> temp(1, 3 * Coefs.Length());
  PLib::SetPoles(Coefs, temp);
  PLib::Trimming(U1, U2, 3, temp, WCoefs);
  PLib::GetPoles(temp, Coefs);
}

void PLib::Trimming(const double                  U1,
                    const double                  U2,
                    NCollection_Array1<gp_Pnt2d>& Coefs,
                    NCollection_Array1<double>*   WCoefs)
{
  NCollection_Array1<double> temp(1, 2 * Coefs.Length());
  PLib::SetPoles(Coefs, temp);
  PLib::Trimming(U1, U2, 2, temp, WCoefs);
  PLib::GetPoles(temp, Coefs);
}

void PLib::Trimming(const double                U1,
                    const double                U2,
                    NCollection_Array1<double>& Coefs,
                    NCollection_Array1<double>* WCoefs)
{
  PLib::Trimming(U1, U2, 1, Coefs, WCoefs);
}

void PLib::Trimming(const double                U1,
                    const double                U2,
                    const int                   dim,
                    NCollection_Array1<double>& Coefs,
                    NCollection_Array1<double>* WCoefs)
{

  double lsp = U2 - U1;
  int    indc, indw = 0;
  int    upc = Coefs.Upper() - dim + 1, upw = 0;
  int    len = Coefs.Length() / dim;
  bool   rat = WCoefs != nullptr;

  if (rat)
  {
    if (len != WCoefs->Length())
      throw Standard_Failure("PLib::Trimming : nbcoefs/dim != nbweights !!!");
    upw = WCoefs->Upper();
  }
  len--;

  for (int i = 1; i <= len; i++)
  {
    int j;
    indc = upc - dim * (i - 1);
    if (rat)
      indw = upw - i + 1;

    for (j = 0; j < dim; j++)
    {
      Coefs(indc - dim + j) += U1 * Coefs(indc + j);
    }
    if (rat)
      (*WCoefs)(indw - 1) += U1 * (*WCoefs)(indw);

    while (indc < upc)
    {
      indc += dim;

      for (int k = 0; k < dim; k++)
      {
        Coefs(indc - dim + k) = U1 * Coefs(indc + k) + lsp * Coefs(indc - dim + k);
      }
      if (rat)
      {
        indw++;
        (*WCoefs)(indw - 1) = U1 * (*WCoefs)(indw) + lsp * (*WCoefs)(indw - 1);
      }
    }

    for (j = 0; j < dim; j++)
    {
      Coefs(upc + j) *= lsp;
    }
    if (rat)
      (*WCoefs)(upw) *= lsp;
  }
}

void PLib::CoefficientsPoles(const NCollection_Array2<gp_Pnt>& Coefs,
                             const NCollection_Array2<double>* WCoefs,
                             NCollection_Array2<gp_Pnt>&       Poles,
                             NCollection_Array2<double>*       Weights)
{
  bool rat       = (WCoefs != nullptr);
  int  LowerRow  = Poles.LowerRow();
  int  UpperRow  = Poles.UpperRow();
  int  LowerCol  = Poles.LowerCol();
  int  UpperCol  = Poles.UpperCol();
  int  ColLength = Poles.ColLength();
  int  RowLength = Poles.RowLength();

  int    Row, Col;
  double W, Cnp;

  int    I1, I2;
  int    NPoleu, NPolev;
  gp_XYZ Temp;

  for (NPoleu = LowerRow; NPoleu <= UpperRow; NPoleu++)
  {
    Poles(NPoleu, LowerCol) = Coefs(NPoleu, LowerCol);
    if (rat)
    {
      (*Weights)(NPoleu, LowerCol) = (*WCoefs)(NPoleu, LowerCol);
    }

    for (Col = LowerCol + 1; Col <= UpperCol - 1; Col++)
    {
      Cnp  = PLib::Bin(RowLength - 1, Col - LowerCol);
      Temp = Coefs(NPoleu, Col).XYZ();
      Temp.Divide(Cnp);
      Poles(NPoleu, Col).SetXYZ(Temp);
      if (rat)
      {
        (*Weights)(NPoleu, Col) = (*WCoefs)(NPoleu, Col) / Cnp;
      }
    }
    Poles(NPoleu, UpperCol) = Coefs(NPoleu, UpperCol);
    if (rat)
    {
      (*Weights)(NPoleu, UpperCol) = (*WCoefs)(NPoleu, UpperCol);
    }

    for (I1 = 1; I1 <= RowLength - 1; I1++)
    {

      for (I2 = UpperCol; I2 >= LowerCol + I1; I2--)
      {
        Temp.SetLinearForm(Poles(NPoleu, I2).XYZ(), Poles(NPoleu, I2 - 1).XYZ());
        Poles(NPoleu, I2).SetXYZ(Temp);
        if (rat)
          (*Weights)(NPoleu, I2) += (*Weights)(NPoleu, I2 - 1);
      }
    }
  }

  for (NPolev = LowerCol; NPolev <= UpperCol; NPolev++)
  {

    for (Row = LowerRow + 1; Row <= UpperRow - 1; Row++)
    {
      Cnp  = PLib::Bin(ColLength - 1, Row - LowerRow);
      Temp = Poles(Row, NPolev).XYZ();
      Temp.Divide(Cnp);
      Poles(Row, NPolev).SetXYZ(Temp);
      if (rat)
        (*Weights)(Row, NPolev) /= Cnp;
    }

    for (I1 = 1; I1 <= ColLength - 1; I1++)
    {

      for (I2 = UpperRow; I2 >= LowerRow + I1; I2--)
      {
        Temp.SetLinearForm(Poles(I2, NPolev).XYZ(), Poles(I2 - 1, NPolev).XYZ());
        Poles(I2, NPolev).SetXYZ(Temp);
        if (rat)
          (*Weights)(I2, NPolev) += (*Weights)(I2 - 1, NPolev);
      }
    }
  }
  if (rat)
  {

    for (Row = LowerRow; Row <= UpperRow; Row++)
    {

      for (Col = LowerCol; Col <= UpperCol; Col++)
      {
        W    = (*Weights)(Row, Col);
        Temp = Poles(Row, Col).XYZ();
        Temp.Divide(W);
        Poles(Row, Col).SetXYZ(Temp);
      }
    }
  }
}

void PLib::UTrimming(const double                U1,
                     const double                U2,
                     NCollection_Array2<gp_Pnt>& Coeffs,
                     NCollection_Array2<double>* WCoeffs)
{
  bool                       rat = WCoeffs != nullptr;
  int                        lr  = Coeffs.LowerRow();
  int                        ur  = Coeffs.UpperRow();
  int                        lc  = Coeffs.LowerCol();
  int                        uc  = Coeffs.UpperCol();
  NCollection_Array1<gp_Pnt> Temp(lr, ur);
  NCollection_Array1<double> Temw(lr, ur);

  for (int icol = lc; icol <= uc; icol++)
  {
    int irow;
    for (irow = lr; irow <= ur; irow++)
    {
      Temp(irow) = Coeffs(irow, icol);
      if (rat)
        Temw(irow) = (*WCoeffs)(irow, icol);
    }
    if (rat)
      PLib::Trimming(U1, U2, Temp, &Temw);
    else
      PLib::Trimming(U1, U2, Temp, PLib::NoWeights());

    for (irow = lr; irow <= ur; irow++)
    {
      Coeffs(irow, icol) = Temp(irow);
      if (rat)
        (*WCoeffs)(irow, icol) = Temw(irow);
    }
  }
}

void PLib::VTrimming(const double                V1,
                     const double                V2,
                     NCollection_Array2<gp_Pnt>& Coeffs,
                     NCollection_Array2<double>* WCoeffs)
{
  bool                       rat = WCoeffs != nullptr;
  int                        lr  = Coeffs.LowerRow();
  int                        ur  = Coeffs.UpperRow();
  int                        lc  = Coeffs.LowerCol();
  int                        uc  = Coeffs.UpperCol();
  NCollection_Array1<gp_Pnt> Temp(lc, uc);
  NCollection_Array1<double> Temw(lc, uc);

  for (int irow = lr; irow <= ur; irow++)
  {
    int icol;
    for (icol = lc; icol <= uc; icol++)
    {
      Temp(icol) = Coeffs(irow, icol);
      if (rat)
        Temw(icol) = (*WCoeffs)(irow, icol);
    }
    if (rat)
      PLib::Trimming(V1, V2, Temp, &Temw);
    else
      PLib::Trimming(V1, V2, Temp, PLib::NoWeights());

    for (icol = lc; icol <= uc; icol++)
    {
      Coeffs(irow, icol) = Temp(icol);
      if (rat)
        (*WCoeffs)(irow, icol) = Temw(icol);
    }
  }
}

bool PLib::HermiteInterpolate(const int                         Dimension,
                              const double                      FirstParameter,
                              const double                      LastParameter,
                              const int                         FirstOrder,
                              const int                         LastOrder,
                              const NCollection_Array2<double>& FirstConstr,
                              const NCollection_Array2<double>& LastConstr,
                              NCollection_Array1<double>&       Coefficients)
{
  double Pattern[3][6];

  Pattern[0][0] = 1;
  Pattern[0][1] = 1;
  Pattern[0][2] = 1;
  Pattern[0][3] = 1;
  Pattern[0][4] = 1;
  Pattern[0][5] = 1;
  Pattern[1][0] = 0;
  Pattern[1][1] = 1;
  Pattern[1][2] = 2;
  Pattern[1][3] = 3;
  Pattern[1][4] = 4;
  Pattern[1][5] = 5;
  Pattern[2][0] = 0;
  Pattern[2][1] = 0;
  Pattern[2][2] = 2;
  Pattern[2][3] = 6;
  Pattern[2][4] = 12;
  Pattern[2][5] = 20;

  math_Matrix A(0, FirstOrder + LastOrder + 1, 0, FirstOrder + LastOrder + 1);

  int irow;
  for (irow = 0; irow <= FirstOrder; irow++)
  {
    double FirstVal = 1.;

    for (int icol = 0; icol <= FirstOrder + LastOrder + 1; icol++)
    {
      A(irow, icol) = Pattern[irow][icol] * FirstVal;
      if (irow <= icol)
        FirstVal *= FirstParameter;
    }
  }

  for (irow = 0; irow <= LastOrder; irow++)
  {
    double LastVal = 1.;

    for (int icol = 0; icol <= FirstOrder + LastOrder + 1; icol++)
    {
      A(irow + FirstOrder + 1, icol) = Pattern[irow][icol] * LastVal;
      if (irow <= icol)
        LastVal *= LastParameter;
    }
  }

  math_Gauss Equations(A);

  for (int idim = 1; idim <= Dimension; idim++)
  {

    math_Vector B(0, FirstOrder + LastOrder + 1);
    int         icol;
    for (icol = 0; icol <= FirstOrder; icol++)
      B(icol) = FirstConstr(idim, icol);

    for (icol = 0; icol <= LastOrder; icol++)
      B(FirstOrder + 1 + icol) = LastConstr(idim, icol);

    Equations.Solve(B);

    if (!Equations.IsDone())
      return false;

    for (icol = 0; icol <= FirstOrder + LastOrder + 1; icol++)
      Coefficients(Dimension * icol + idim - 1) = B(icol);
  }
  return true;
}

void PLib::JacobiParameters(const GeomAbs_Shape ConstraintOrder,
                            const int           MaxDegree,
                            const int           Code,
                            int&                NbGaussPoints,
                            int&                WorkDegree)
{

  const int NDEG8 = 8, NDEG10 = 10, NDEG15 = 15, NDEG20 = 20, NDEG25 = 25, NDEG30 = 30, NDEG40 = 40,
            NDEG50 = 50, NDEG61 = 61;

  int NivConstr = 0;
  switch (ConstraintOrder)
  {
    case GeomAbs_C0:
      NivConstr = 0;
      break;
    case GeomAbs_C1:
      NivConstr = 1;
      break;
    case GeomAbs_C2:
      NivConstr = 2;
      break;
    default:
      throw Standard_ConstructionError("Invalid ConstraintOrder");
  }
  if (MaxDegree < 2 * NivConstr + 1)
    throw Standard_ConstructionError("Invalid MaxDegree");

  if (Code >= 1)
    WorkDegree = MaxDegree + 9;
  else
    WorkDegree = MaxDegree + 6;

  int IPMIN = 0;
  if (WorkDegree < NDEG8)
    IPMIN = NDEG8;
  else if (WorkDegree < NDEG10)
    IPMIN = NDEG10;
  else if (WorkDegree < NDEG15)
    IPMIN = NDEG15;
  else if (WorkDegree < NDEG20)
    IPMIN = NDEG20;
  else if (WorkDegree < NDEG25)
    IPMIN = NDEG25;
  else if (WorkDegree < NDEG30)
    IPMIN = NDEG30;
  else if (WorkDegree < NDEG40)
    IPMIN = NDEG40;
  else if (WorkDegree < NDEG50)
    IPMIN = NDEG50;
  else if (WorkDegree < NDEG61)
    IPMIN = NDEG61;
  else
    throw Standard_ConstructionError("Invalid MaxDegree");

  int IWANT = 0;
  switch (Code)
  {
    case -5:
      IWANT = NDEG8;
      break;
    case -4:
      IWANT = NDEG10;
      break;
    case -3:
      IWANT = NDEG15;
      break;
    case -2:
      IWANT = NDEG20;
      break;
    case -1:
      IWANT = NDEG25;
      break;
    case 1:
      IWANT = NDEG30;
      break;
    case 2:
      IWANT = NDEG40;
      break;
    case 3:
      IWANT = NDEG50;
      break;
    case 4:
      IWANT = NDEG61;
      break;
    default:
      throw Standard_ConstructionError("Invalid Code");
  }

  NbGaussPoints = std::max(IPMIN, IWANT);
}

int PLib::NivConstr(const GeomAbs_Shape ConstraintOrder)
{
  int NivConstr = 0;
  switch (ConstraintOrder)
  {
    case GeomAbs_C0:
      NivConstr = 0;
      break;
    case GeomAbs_C1:
      NivConstr = 1;
      break;
    case GeomAbs_C2:
      NivConstr = 2;
      break;
    default:
      throw Standard_ConstructionError("Invalid ConstraintOrder");
  }
  return NivConstr;
}

GeomAbs_Shape PLib::ConstraintOrder(const int NivConstr)
{
  GeomAbs_Shape ConstraintOrder = GeomAbs_C0;
  switch (NivConstr)
  {
    case 0:
      ConstraintOrder = GeomAbs_C0;
      break;
    case 1:
      ConstraintOrder = GeomAbs_C1;
      break;
    case 2:
      ConstraintOrder = GeomAbs_C2;
      break;
    default:
      throw Standard_ConstructionError("Invalid NivConstr");
  }
  return ConstraintOrder;
}

void PLib::EvalLength(const int    Degree,
                      const int    Dimension,
                      double&      PolynomialCoeff,
                      const double U1,
                      const double U2,
                      double&      Length)
{
  int    i, j, idim, degdim;
  double C1, C2, Sum, Tran, X1, X2, Der1, Der2, D1, D2, DD;

  double* PolynomialArray = &PolynomialCoeff;

  int NbGaussPoints = 4 * std::min((Degree / 4) + 1, 10);

  math_Vector GaussPoints(1, NbGaussPoints);
  math::GaussPoints(NbGaussPoints, GaussPoints);

  math_Vector GaussWeights(1, NbGaussPoints);
  math::GaussWeights(NbGaussPoints, GaussWeights);

  C1 = (U2 + U1) / 2.;
  C2 = (U2 - U1) / 2.;

  Sum = 0;

  for (j = 1; j <= NbGaussPoints / 2; j++)
  {

    Tran = C2 * GaussPoints(j);
    X1   = C1 + Tran;
    X2   = C1 - Tran;

    degdim = Degree * Dimension;
    Der1 = Der2 = 0.;
    for (idim = 0; idim < Dimension; idim++)
    {
      D1 = D2 = Degree * PolynomialArray[idim + degdim];
      for (i = Degree - 1; i >= 1; i--)
      {
        DD = i * PolynomialArray[idim + i * Dimension];
        D1 = D1 * X1 + DD;
        D2 = D2 * X2 + DD;
      }
      Der1 += D1 * D1;
      Der2 += D2 * D2;
    }

    Sum += GaussWeights(j) * C2 * (std::sqrt(Der1) + std::sqrt(Der2));
  }
  Length = Sum;
}

void PLib::EvalLength(const int    Degree,
                      const int    Dimension,
                      double&      PolynomialCoeff,
                      const double U1,
                      const double U2,
                      const double Tol,
                      double&      Length,
                      double&      Error)
{
  int    i;
  int    NbSubInt = 1, MaxNbIter = 13, NbIter = 1;
  double dU, OldLen, LenI;

  PLib::EvalLength(Degree, Dimension, PolynomialCoeff, U1, U2, Length);

  do
  {
    OldLen = Length;
    Length = 0.;
    NbSubInt *= 2;
    dU = (U2 - U1) / NbSubInt;
    for (i = 1; i <= NbSubInt; i++)
    {
      PLib::EvalLength(Degree, Dimension, PolynomialCoeff, U1 + (i - 1) * dU, U1 + i * dU, LenI);
      Length += LenI;
    }
    NbIter++;
    Error = std::abs(OldLen - Length);
  } while (Error > Tol && NbIter <= MaxNbIter);
}
