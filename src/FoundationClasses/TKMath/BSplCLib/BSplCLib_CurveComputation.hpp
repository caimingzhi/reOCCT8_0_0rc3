#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_OutOfRange.hpp>
#include <PLib.hpp>
#include <math_Matrix.hpp>

#include <algorithm>
#include <utility>

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
struct BSplCLib_CurveTraits
{

  static void PointToCoords(double* carr, const Point& pnt, double op)
  {
    if constexpr (Dimension == 2)
    {
      carr[0] = pnt.X() + op;
      carr[1] = pnt.Y() + op;
    }
    else if constexpr (Dimension == 3)
    {
      carr[0] = pnt.X() + op;
      carr[1] = pnt.Y() + op;
      carr[2] = pnt.Z() + op;
    }
  }

  static void PointToCoordsScaled(double* carr, const Point& pnt, double scale)
  {
    if constexpr (Dimension == 2)
    {
      carr[0] = pnt.X() * scale;
      carr[1] = pnt.Y() * scale;
    }
    else if constexpr (Dimension == 3)
    {
      carr[0] = pnt.X() * scale;
      carr[1] = pnt.Y() * scale;
      carr[2] = pnt.Z() * scale;
    }
  }

  static void CoordsToPointMultiplied(Point& pnt, const double* carr, double factor)
  {
    if constexpr (Dimension == 2)
    {
      pnt.SetX(carr[0] * factor);
      pnt.SetY(carr[1] * factor);
    }
    else if constexpr (Dimension == 3)
    {
      pnt.SetX(carr[0] * factor);
      pnt.SetY(carr[1] * factor);
      pnt.SetZ(carr[2] * factor);
    }
  }

  static void CoordsToPointScaled(Point& pnt, const double* carr, double scale)
  {
    if constexpr (Dimension == 2)
    {
      pnt.SetX(carr[0] / scale);
      pnt.SetY(carr[1] / scale);
    }
    else if constexpr (Dimension == 3)
    {
      pnt.SetX(carr[0] / scale);
      pnt.SetY(carr[1] / scale);
      pnt.SetZ(carr[2] / scale);
    }
  }

  static void CoordsToPointDirect(Point& pnt, const double* carr)
  {
    if constexpr (Dimension == 2)
    {
      pnt.SetX(carr[0]);
      pnt.SetY(carr[1]);
    }
    else if constexpr (Dimension == 3)
    {
      pnt.SetX(carr[0]);
      pnt.SetY(carr[1]);
      pnt.SetZ(carr[2]);
    }
  }

  static void CoordsToVectorDirect(Vector& vec, const double* carr)
  {
    if constexpr (Dimension == 2)
    {
      vec.SetX(carr[0]);
      vec.SetY(carr[1]);
    }
    else if constexpr (Dimension == 3)
    {
      vec.SetX(carr[0]);
      vec.SetY(carr[1]);
      vec.SetZ(carr[2]);
    }
  }

  static void NullifyPoint(Point& pnt)
  {
    if constexpr (Dimension == 2)
    {
      pnt.SetCoord(0., 0.);
    }
    else if constexpr (Dimension == 3)
    {
      pnt.SetCoord(0., 0., 0.);
    }
  }

  static void NullifyVector(Vector& vec)
  {
    if constexpr (Dimension == 2)
    {
      vec.SetCoord(0., 0.);
    }
    else if constexpr (Dimension == 3)
    {
      vec.SetCoord(0., 0., 0.);
    }
  }

  static void NullifyCoords(double* carr)
  {
    if constexpr (Dimension == 2)
    {
      carr[0] = carr[1] = 0.;
    }
    else if constexpr (Dimension == 3)
    {
      carr[0] = carr[1] = carr[2] = 0.;
    }
  }

  static void CopyCoords(double* carr, const double* carr2)
  {
    if constexpr (Dimension == 2)
    {
      carr[0] = carr2[0];
      carr[1] = carr2[1];
    }
    else if constexpr (Dimension == 3)
    {
      carr[0] = carr2[0];
      carr[1] = carr2[1];
      carr[2] = carr2[2];
    }
  }

  static void ModifyCoordsScale(double* carr, double scale)
  {
    if constexpr (Dimension == 2)
    {
      carr[0] *= scale;
      carr[1] *= scale;
    }
    else if constexpr (Dimension == 3)
    {
      carr[0] *= scale;
      carr[1] *= scale;
      carr[2] *= scale;
    }
  }

  static void ModifyCoordsDivide(double* carr, double divisor)
  {
    if constexpr (Dimension == 2)
    {
      carr[0] /= divisor;
      carr[1] /= divisor;
    }
    else if constexpr (Dimension == 3)
    {
      carr[0] /= divisor;
      carr[1] /= divisor;
      carr[2] /= divisor;
    }
  }
};

template <int Size>
struct BSplCLib_KnotArrays
{
  static_assert(Size == 1 || Size == 2, "BSplCLib_KnotArrays: Size must be 1 or 2");

  template <int N = Size, typename = typename std::enable_if<N == 1>::type>
  BSplCLib_KnotArrays(double theKnotValue, int theMultiplicity)
      : myKnotBuffer{theKnotValue},
        myMultBuffer{theMultiplicity},
        Knot(myKnotBuffer[0], 1, Size),
        Mult(myMultBuffer[0], 1, Size)
  {
  }

  template <int N = Size, typename = typename std::enable_if<N == 2>::type>
  BSplCLib_KnotArrays(int theDegree)
      : myKnotBuffer{0.0, 1.0},
        myMultBuffer{theDegree + 1, theDegree + 1},
        Knot(myKnotBuffer[0], 1, Size),
        Mult(myMultBuffer[0], 1, Size)
  {
  }

private:
  double myKnotBuffer[Size];
  int    myMultBuffer[Size];

public:
  NCollection_Array1<double> Knot;
  NCollection_Array1<int>    Mult;
};

static constexpr int THE_MAX_DEGREE = BSplCLib::MaxDegree();

inline void validateBSplineDegree([[maybe_unused]] int theDegree)
{
  Standard_OutOfRange_Raise_if(theDegree > THE_MAX_DEGREE,
                               "BSplCLib: bspline degree is greater than maximum supported");
}

template <int Dimension>
struct BSplCLib_DataContainer_T
{
  double poles[(THE_MAX_DEGREE + 1) * (Dimension + 1)];
  double knots[2 * THE_MAX_DEGREE];
  double ders[Dimension * 4];
};

template <typename Array>
void BSplCLib_Reverse(Array& theArray, const int theL)
{
  const int aLower = theArray.Lower();
  const int aUpper = theArray.Upper();
  const int aL     = aLower + (theL - aLower) % theArray.Length();

  std::reverse(&theArray(aLower), &theArray(aL) + 1);
  if (aL < aUpper)
  {
    std::reverse(&theArray(aL + 1), &theArray(aUpper) + 1);
  }
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
bool BSplCLib_RemoveKnot(const int                         Index,
                         const int                         Mult,
                         const int                         Degree,
                         const bool                        Periodic,
                         const Array1OfPoints&             Poles,
                         const NCollection_Array1<double>* Weights,
                         const NCollection_Array1<double>& Knots,
                         const NCollection_Array1<int>&    Mults,
                         Array1OfPoints&                   NewPoles,
                         NCollection_Array1<double>*       NewWeights,
                         NCollection_Array1<double>&       NewKnots,
                         NCollection_Array1<int>&          NewMults,
                         const double                      Tolerance)
{
  bool rational = Weights != NULL;
  int  dim;
  dim = Dimension;
  if (rational)
    dim++;

  NCollection_Array1<double> poles(1, dim * Poles.Length());
  NCollection_Array1<double> newpoles(1, dim * NewPoles.Length());

  if (rational)
    PLib::SetPoles(Poles, *Weights, poles);
  else
    PLib::SetPoles(Poles, poles);

  if (!BSplCLib::RemoveKnot(Index,
                            Mult,
                            Degree,
                            Periodic,
                            dim,
                            poles,
                            Knots,
                            Mults,
                            newpoles,
                            NewKnots,
                            NewMults,
                            Tolerance))
    return false;

  if (rational)
    PLib::GetPoles(newpoles, NewPoles, *NewWeights);
  else
    PLib::GetPoles(newpoles, NewPoles);
  return true;
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_InsertKnots(const int                         Degree,
                          const bool                        Periodic,
                          const Array1OfPoints&             Poles,
                          const NCollection_Array1<double>* Weights,
                          const NCollection_Array1<double>& Knots,
                          const NCollection_Array1<int>&    Mults,
                          const NCollection_Array1<double>& AddKnots,
                          const NCollection_Array1<int>*    AddMults,
                          Array1OfPoints&                   NewPoles,
                          NCollection_Array1<double>*       NewWeights,
                          NCollection_Array1<double>&       NewKnots,
                          NCollection_Array1<int>&          NewMults,
                          const double                      Epsilon,
                          const bool                        Add)
{
  bool rational = Weights != NULL;
  int  dim;
  dim = Dimension;
  if (rational)
    dim++;

  NCollection_Array1<double> poles(1, dim * Poles.Length());
  NCollection_Array1<double> newpoles(1, dim * NewPoles.Length());

  if (rational)
    PLib::SetPoles(Poles, *Weights, poles);
  else
    PLib::SetPoles(Poles, poles);

  BSplCLib::InsertKnots(Degree,
                        Periodic,
                        dim,
                        poles,
                        Knots,
                        Mults,
                        AddKnots,
                        AddMults,
                        newpoles,
                        NewKnots,
                        NewMults,
                        Epsilon,
                        Add);

  if (rational)
    PLib::GetPoles(newpoles, NewPoles, *NewWeights);
  else
    PLib::GetPoles(newpoles, NewPoles);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_InsertKnot(const int,
                         const double                      U,
                         const int                         UMult,
                         const int                         Degree,
                         const bool                        Periodic,
                         const Array1OfPoints&             Poles,
                         const NCollection_Array1<double>* Weights,
                         const NCollection_Array1<double>& Knots,
                         const NCollection_Array1<int>&    Mults,
                         Array1OfPoints&                   NewPoles,
                         NCollection_Array1<double>*       NewWeights)
{
  BSplCLib_KnotArrays<1>     aSingleKnot(U, UMult);
  NCollection_Array1<double> aNewKnots(1, Knots.Length() + 1);
  NCollection_Array1<int>    aNewMults(1, Knots.Length() + 1);
  BSplCLib_InsertKnots<Point, Vector, Array1OfPoints, Dimension>(Degree,
                                                                 Periodic,
                                                                 Poles,
                                                                 Weights,
                                                                 Knots,
                                                                 Mults,
                                                                 aSingleKnot.Knot,
                                                                 &aSingleKnot.Mult,
                                                                 NewPoles,
                                                                 NewWeights,
                                                                 aNewKnots,
                                                                 aNewMults,
                                                                 Epsilon(U),
                                                                 true);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_RaiseMultiplicity(const int                         KnotIndex,
                                const int                         Mult,
                                const int                         Degree,
                                const bool                        Periodic,
                                const Array1OfPoints&             Poles,
                                const NCollection_Array1<double>* Weights,
                                const NCollection_Array1<double>& Knots,
                                const NCollection_Array1<int>&    Mults,
                                Array1OfPoints&                   NewPoles,
                                NCollection_Array1<double>*       NewWeights)
{
  BSplCLib_KnotArrays<1>     aSingleKnot(Knots(KnotIndex), Mult - Mults(KnotIndex));
  NCollection_Array1<double> aNewKnots(1, Knots.Length());
  NCollection_Array1<int>    aNewMults(1, Knots.Length());
  BSplCLib_InsertKnots<Point, Vector, Array1OfPoints, Dimension>(Degree,
                                                                 Periodic,
                                                                 Poles,
                                                                 Weights,
                                                                 Knots,
                                                                 Mults,
                                                                 aSingleKnot.Knot,
                                                                 &aSingleKnot.Mult,
                                                                 NewPoles,
                                                                 NewWeights,
                                                                 aNewKnots,
                                                                 aNewMults,
                                                                 Epsilon(Knots(KnotIndex)),
                                                                 true);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_IncreaseDegree(const int                         Degree,
                             const int                         NewDegree,
                             const bool                        Periodic,
                             const Array1OfPoints&             Poles,
                             const NCollection_Array1<double>* Weights,
                             const NCollection_Array1<double>& Knots,
                             const NCollection_Array1<int>&    Mults,
                             Array1OfPoints&                   NewPoles,
                             NCollection_Array1<double>*       NewWeights,
                             NCollection_Array1<double>&       NewKnots,
                             NCollection_Array1<int>&          NewMults)
{
  bool rational = Weights != NULL;
  int  dim;
  dim = Dimension;
  if (rational)
    dim++;

  NCollection_Array1<double> poles(1, dim * Poles.Length());
  NCollection_Array1<double> newpoles(1, dim * NewPoles.Length());

  if (rational)
    PLib::SetPoles(Poles, *Weights, poles);
  else
    PLib::SetPoles(Poles, poles);

  BSplCLib::IncreaseDegree(Degree,
                           NewDegree,
                           Periodic,
                           dim,
                           poles,
                           Knots,
                           Mults,
                           newpoles,
                           NewKnots,
                           NewMults);

  if (rational)
    PLib::GetPoles(newpoles, NewPoles, *NewWeights);
  else
    PLib::GetPoles(newpoles, NewPoles);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_Unperiodize(const int                         Degree,
                          const NCollection_Array1<int>&    Mults,
                          const NCollection_Array1<double>& Knots,
                          const Array1OfPoints&             Poles,
                          const NCollection_Array1<double>* Weights,
                          NCollection_Array1<int>&          NewMults,
                          NCollection_Array1<double>&       NewKnots,
                          Array1OfPoints&                   NewPoles,
                          NCollection_Array1<double>*       NewWeights)
{
  bool rational = Weights != NULL;
  int  dim;
  dim = Dimension;
  if (rational)
    dim++;

  NCollection_Array1<double> poles(1, dim * Poles.Length());
  NCollection_Array1<double> newpoles(1, dim * NewPoles.Length());

  if (rational)
    PLib::SetPoles(Poles, *Weights, poles);
  else
    PLib::SetPoles(Poles, poles);

  BSplCLib::Unperiodize(Degree, dim, Mults, Knots, poles, NewMults, NewKnots, newpoles);

  if (rational)
    PLib::GetPoles(newpoles, NewPoles, *NewWeights);
  else
    PLib::GetPoles(newpoles, NewPoles);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_Trimming(const int                         Degree,
                       const bool                        Periodic,
                       const NCollection_Array1<double>& Knots,
                       const NCollection_Array1<int>&    Mults,
                       const Array1OfPoints&             Poles,
                       const NCollection_Array1<double>* Weights,
                       const double                      U1,
                       const double                      U2,
                       NCollection_Array1<double>&       NewKnots,
                       NCollection_Array1<int>&          NewMults,
                       Array1OfPoints&                   NewPoles,
                       NCollection_Array1<double>*       NewWeights)
{
  bool rational = Weights != NULL;
  int  dim;
  dim = Dimension;
  if (rational)
    dim++;

  NCollection_Array1<double> poles(1, dim * Poles.Length());
  NCollection_Array1<double> newpoles(1, dim * NewPoles.Length());

  if (rational)
    PLib::SetPoles(Poles, *Weights, poles);
  else
    PLib::SetPoles(Poles, poles);

  BSplCLib::Trimming(Degree,
                     Periodic,
                     dim,
                     Knots,
                     Mults,
                     poles,
                     U1,
                     U2,
                     NewKnots,
                     NewMults,
                     newpoles);

  if (rational)
    PLib::GetPoles(newpoles, NewPoles, *NewWeights);
  else
    PLib::GetPoles(newpoles, NewPoles);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_BuildEval(const int                         Degree,
                        const int                         Index,
                        const Array1OfPoints&             Poles,
                        const NCollection_Array1<double>* Weights,
                        double&                           LP)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  double w, *pole = &LP;
  int    PLower = Poles.Lower();
  int    PUpper = Poles.Upper();
  int    i;
  int    ip = PLower + Index - 1;
  if (Weights == NULL)
  {
    for (i = 0; i <= Degree; i++)
    {
      ip++;
      if (ip > PUpper)
        ip = PLower;
      const Point& P = Poles(ip);
      Traits::PointToCoords(pole, P, 0);
      pole += Dimension;
    }
  }
  else
  {
    for (i = 0; i <= Degree; i++)
    {
      ip++;
      if (ip > PUpper)
        ip = PLower;
      const Point& P  = Poles(ip);
      pole[Dimension] = w = (*Weights)(ip);
      Traits::PointToCoordsScaled(pole, P, w);
      pole += Dimension + 1;
    }
  }
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
static void PrepareEval_T(double&                              u,
                          int&                                 index,
                          int&                                 dim,
                          bool&                                rational,
                          const int                            Degree,
                          const bool                           Periodic,
                          const Array1OfPoints&                Poles,
                          const NCollection_Array1<double>*    Weights,
                          const NCollection_Array1<double>&    Knots,
                          const NCollection_Array1<int>*       Mults,
                          BSplCLib_DataContainer_T<Dimension>& dc)
{

  BSplCLib::LocateParameter(Degree, Knots, Mults, u, Periodic, index, u);

  BSplCLib::BuildKnots(Degree, index, Periodic, Knots, Mults, *dc.knots);
  if (Mults == NULL)
    index -= Knots.Lower() + Degree;
  else
    index = BSplCLib::PoleIndex(Degree, index, Periodic, *Mults);

  rational = (Weights != NULL);
  if (rational)
  {
    int WLower = Weights->Lower() + index;
    rational   = BSplCLib::IsRational(*Weights, WLower, WLower + Degree);
  }

  if (rational)
  {
    dim = Dimension + 1;
    BSplCLib_BuildEval<Point, Vector, Array1OfPoints, Dimension>(Degree,
                                                                 index,
                                                                 Poles,
                                                                 Weights,
                                                                 *dc.poles);
  }
  else
  {
    dim = Dimension;
    BSplCLib_BuildEval<Point, Vector, Array1OfPoints, Dimension>(Degree,
                                                                 index,
                                                                 Poles,
                                                                 BSplCLib::NoWeights(),
                                                                 *dc.poles);
  }
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_D0(const double                      U,
                 const int                         Index,
                 const int                         Degree,
                 const bool                        Periodic,
                 const Array1OfPoints&             Poles,
                 const NCollection_Array1<double>* Weights,
                 const NCollection_Array1<double>& Knots,
                 const NCollection_Array1<int>*    Mults,
                 Point&                            P)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  int    dim, index = Index;
  double u = U;
  bool   rational;
  validateBSplineDegree(Degree);
  BSplCLib_DataContainer_T<Dimension> dc;
  PrepareEval_T<Point, Vector, Array1OfPoints, Dimension>(u,
                                                          index,
                                                          dim,
                                                          rational,
                                                          Degree,
                                                          Periodic,
                                                          Poles,
                                                          Weights,
                                                          Knots,
                                                          Mults,
                                                          dc);
  BSplCLib::Eval(u, Degree, *dc.knots, dim, *dc.poles);

  if (rational)
  {
    double w = dc.poles[Dimension];
    Traits::CoordsToPointScaled(P, dc.poles, w);
  }
  else
    Traits::CoordsToPointDirect(P, dc.poles);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_D1(const double                      U,
                 const int                         Index,
                 const int                         Degree,
                 const bool                        Periodic,
                 const Array1OfPoints&             Poles,
                 const NCollection_Array1<double>* Weights,
                 const NCollection_Array1<double>& Knots,
                 const NCollection_Array1<int>*    Mults,
                 Point&                            P,
                 Vector&                           V)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  int    dim, index = Index;
  double u = U;
  bool   rational;
  validateBSplineDegree(Degree);
  BSplCLib_DataContainer_T<Dimension> dc;
  PrepareEval_T<Point, Vector, Array1OfPoints, Dimension>(u,
                                                          index,
                                                          dim,
                                                          rational,
                                                          Degree,
                                                          Periodic,
                                                          Poles,
                                                          Weights,
                                                          Knots,
                                                          Mults,
                                                          dc);
  BSplCLib::Bohm(u, Degree, 1, *dc.knots, dim, *dc.poles);
  double* result = dc.poles;
  if (rational)
  {
    PLib::RationalDerivative(Degree, 1, Dimension, *dc.poles, *dc.ders);
    result = dc.ders;
  }

  Traits::CoordsToPointDirect(P, result);
  Traits::CoordsToVectorDirect(V, result + Dimension);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_D2(const double                      U,
                 const int                         Index,
                 const int                         Degree,
                 const bool                        Periodic,
                 const Array1OfPoints&             Poles,
                 const NCollection_Array1<double>* Weights,
                 const NCollection_Array1<double>& Knots,
                 const NCollection_Array1<int>*    Mults,
                 Point&                            P,
                 Vector&                           V1,
                 Vector&                           V2)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  int    dim, index = Index;
  double u = U;
  bool   rational;
  validateBSplineDegree(Degree);
  BSplCLib_DataContainer_T<Dimension> dc;
  PrepareEval_T<Point, Vector, Array1OfPoints, Dimension>(u,
                                                          index,
                                                          dim,
                                                          rational,
                                                          Degree,
                                                          Periodic,
                                                          Poles,
                                                          Weights,
                                                          Knots,
                                                          Mults,
                                                          dc);
  BSplCLib::Bohm(u, Degree, 2, *dc.knots, dim, *dc.poles);
  double* result = dc.poles;
  if (rational)
  {
    PLib::RationalDerivative(Degree, 2, Dimension, *dc.poles, *dc.ders);
    result = dc.ders;
  }

  Traits::CoordsToPointDirect(P, result);
  Traits::CoordsToVectorDirect(V1, result + Dimension);
  if (!rational && (Degree < 2))
    Traits::NullifyVector(V2);
  else
    Traits::CoordsToVectorDirect(V2, result + 2 * Dimension);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_D3(const double                      U,
                 const int                         Index,
                 const int                         Degree,
                 const bool                        Periodic,
                 const Array1OfPoints&             Poles,
                 const NCollection_Array1<double>* Weights,
                 const NCollection_Array1<double>& Knots,
                 const NCollection_Array1<int>*    Mults,
                 Point&                            P,
                 Vector&                           V1,
                 Vector&                           V2,
                 Vector&                           V3)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  int    dim, index = Index;
  double u = U;
  bool   rational;
  validateBSplineDegree(Degree);
  BSplCLib_DataContainer_T<Dimension> dc;
  PrepareEval_T<Point, Vector, Array1OfPoints, Dimension>(u,
                                                          index,
                                                          dim,
                                                          rational,
                                                          Degree,
                                                          Periodic,
                                                          Poles,
                                                          Weights,
                                                          Knots,
                                                          Mults,
                                                          dc);
  BSplCLib::Bohm(u, Degree, 3, *dc.knots, dim, *dc.poles);
  double* result = dc.poles;
  if (rational)
  {
    PLib::RationalDerivative(Degree, 3, Dimension, *dc.poles, *dc.ders);
    result = dc.ders;
  }

  Traits::CoordsToPointDirect(P, result);
  Traits::CoordsToVectorDirect(V1, result + Dimension);
  if (!rational && (Degree < 2))
    Traits::NullifyVector(V2);
  else
    Traits::CoordsToVectorDirect(V2, result + 2 * Dimension);
  if (!rational && (Degree < 3))
    Traits::NullifyVector(V3);
  else
    Traits::CoordsToVectorDirect(V3, result + 3 * Dimension);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_DN(const double                      U,
                 const int                         N,
                 const int                         Index,
                 const int                         Degree,
                 const bool                        Periodic,
                 const Array1OfPoints&             Poles,
                 const NCollection_Array1<double>* Weights,
                 const NCollection_Array1<double>& Knots,
                 const NCollection_Array1<int>*    Mults,
                 Vector&                           VN)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  int    dim, index = Index;
  double u = U;
  bool   rational;
  validateBSplineDegree(Degree);
  BSplCLib_DataContainer_T<Dimension> dc;
  PrepareEval_T<Point, Vector, Array1OfPoints, Dimension>(u,
                                                          index,
                                                          dim,
                                                          rational,
                                                          Degree,
                                                          Periodic,
                                                          Poles,
                                                          Weights,
                                                          Knots,
                                                          Mults,
                                                          dc);
  BSplCLib::Bohm(u, Degree, N, *dc.knots, dim, *dc.poles);

  if (rational)
  {
    double v[Dimension];
    PLib::RationalDerivative(Degree, N, Dimension, *dc.poles, v[0], false);
    Traits::CoordsToVectorDirect(VN, v);
  }
  else
  {
    if (N > Degree)
      Traits::NullifyVector(VN);
    else
    {
      double* DN = dc.poles + N * Dimension;
      Traits::CoordsToVectorDirect(VN, DN);
    }
  }
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
int BSplCLib_SolveBandedSystem(const math_Matrix& Matrix,
                               const int          UpperBandWidth,
                               const int          LowerBandWidth,
                               Array1OfPoints&    PolesArray)
{
  double* PArray;
  PArray = (double*)&PolesArray(PolesArray.Lower());

  return BSplCLib::SolveBandedSystem(Matrix, UpperBandWidth, LowerBandWidth, Dimension, PArray[0]);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
int BSplCLib_SolveBandedSystem(const math_Matrix&          Matrix,
                               const int                   UpperBandWidth,
                               const int                   LowerBandWidth,
                               const bool                  HomogeneousFlag,
                               Array1OfPoints&             PolesArray,
                               NCollection_Array1<double>& WeightsArray)
{
  double *PArray, *WArray;
  PArray = (double*)&PolesArray(PolesArray.Lower());
  WArray = (double*)&WeightsArray(WeightsArray.Lower());
  return BSplCLib::SolveBandedSystem(Matrix,
                                     UpperBandWidth,
                                     LowerBandWidth,
                                     HomogeneousFlag,
                                     Dimension,
                                     PArray[0],
                                     WArray[0]);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_Eval(const double                      Parameter,
                   const bool                        PeriodicFlag,
                   const bool                        HomogeneousFlag,
                   int&                              ExtrapMode,
                   const int                         Degree,
                   const NCollection_Array1<double>& FlatKnots,
                   const Array1OfPoints&             PolesArray,
                   const NCollection_Array1<double>& WeightsArray,
                   Point&                            aPoint,
                   double&                           aWeight)
{
  double Inverse, P[Dimension], *PArray, *WArray;
  int    kk;
  PArray = (double*)&PolesArray(PolesArray.Lower());
  WArray = (double*)&WeightsArray(WeightsArray.Lower());
  if (HomogeneousFlag)
  {
    BSplCLib::Eval(Parameter,
                   PeriodicFlag,
                   0,
                   ExtrapMode,
                   Degree,
                   FlatKnots,
                   Dimension,
                   PArray[0],
                   P[0]);
    BSplCLib::Eval(Parameter,
                   PeriodicFlag,
                   0,
                   ExtrapMode,
                   Degree,
                   FlatKnots,
                   1,
                   WArray[0],
                   aWeight);
  }
  else
  {
    BSplCLib::Eval(Parameter,
                   PeriodicFlag,
                   0,
                   ExtrapMode,
                   Degree,
                   FlatKnots,
                   Dimension,
                   PArray[0],
                   WArray[0],
                   P[0],
                   aWeight);
    Inverse = 1.0e0 / aWeight;

    for (kk = 0; kk < Dimension; kk++)
    {
      P[kk] *= Inverse;
    }
  }

  for (kk = 0; kk < Dimension; kk++)
    aPoint.SetCoord(kk + 1, P[kk]);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_CacheD0(const double                      Parameter,
                      const int                         Degree,
                      const double                      CacheParameter,
                      const double                      SpanLenght,
                      const Array1OfPoints&             PolesArray,
                      const NCollection_Array1<double>* WeightsArray,
                      Point&                            aPoint)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  double  NewParameter, Inverse;
  double* PArray  = (double*)&(PolesArray(PolesArray.Lower()));
  double* myPoint = (double*)&aPoint;
  NewParameter    = (Parameter - CacheParameter) / SpanLenght;
  PLib::NoDerivativeEvalPolynomial(NewParameter,
                                   Degree,
                                   Dimension,
                                   Degree * Dimension,
                                   PArray[0],
                                   myPoint[0]);
  if (WeightsArray != NULL)
  {
    const NCollection_Array1<double>& refWeights = *WeightsArray;
    double*                           WArray     = (double*)&refWeights(refWeights.Lower());
    PLib::NoDerivativeEvalPolynomial(NewParameter, Degree, 1, Degree, WArray[0], Inverse);

    Inverse = 1.0e0 / Inverse;
    Traits::ModifyCoordsScale(myPoint, Inverse);
  }
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_CacheD1(const double                      Parameter,
                      const int                         Degree,
                      const double                      CacheParameter,
                      const double                      SpanLenght,
                      const Array1OfPoints&             PolesArray,
                      const NCollection_Array1<double>* WeightsArray,
                      Point&                            aPoint,
                      Vector&                           aVector)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  double LocalPDerivatives[Dimension << 1];
  double LocalWDerivatives[2], NewParameter;

  double* PArray   = (double*)&(PolesArray(PolesArray.Lower()));
  double* myPoint  = (double*)&aPoint;
  double* myVector = (double*)&aVector;
  NewParameter     = (Parameter - CacheParameter) / SpanLenght;
  PLib::EvalPolynomial(NewParameter, 1, Degree, Dimension, PArray[0], LocalPDerivatives[0]);

  Traits::ModifyCoordsDivide(LocalPDerivatives + Dimension, SpanLenght);

  if (WeightsArray != NULL)
  {
    const NCollection_Array1<double>& refWeights = *WeightsArray;
    double*                           WArray     = (double*)&refWeights(refWeights.Lower());
    PLib::EvalPolynomial(NewParameter, 1, Degree, 1, WArray[0], LocalWDerivatives[0]);

    LocalWDerivatives[1] /= SpanLenght;

    PLib::RationalDerivatives(1,
                              Dimension,
                              LocalPDerivatives[0],
                              LocalWDerivatives[0],
                              LocalPDerivatives[0]);
  }

  Traits::CopyCoords(myPoint, LocalPDerivatives);
  Traits::CopyCoords(myVector, LocalPDerivatives + Dimension);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_CacheD2(const double                      Parameter,
                      const int                         Degree,
                      const double                      CacheParameter,
                      const double                      SpanLenght,
                      const Array1OfPoints&             PolesArray,
                      const NCollection_Array1<double>* WeightsArray,
                      Point&                            aPoint,
                      Vector&                           aVector1,
                      Vector&                           aVector2)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  int     ii, Index, EndIndex;
  double  LocalPDerivatives[(Dimension << 1) + Dimension];
  double  LocalWDerivatives[3], NewParameter, Factor;
  double* PArray    = (double*)&(PolesArray(PolesArray.Lower()));
  double* myPoint   = (double*)&aPoint;
  double* myVector1 = (double*)&aVector1;
  double* myVector2 = (double*)&aVector2;
  NewParameter      = (Parameter - CacheParameter) / SpanLenght;
  PLib::EvalPolynomial(NewParameter, 2, Degree, Dimension, PArray[0], LocalPDerivatives[0]);

  Factor   = 1.0e0 / SpanLenght;
  Index    = Dimension;
  EndIndex = std::min(2, Degree);

  for (ii = 1; ii <= EndIndex; ii++)
  {
    Traits::ModifyCoordsScale(LocalPDerivatives + Index, Factor);
    Factor /= SpanLenght;
    Index += Dimension;
  }

  Index = (Degree + 1) * Dimension;
  for (ii = Degree; ii < 2; ii++)
  {
    Traits::NullifyCoords(LocalPDerivatives + Index);
    Index += Dimension;
  }

  if (WeightsArray != NULL)
  {
    const NCollection_Array1<double>& refWeights = *WeightsArray;
    double*                           WArray     = (double*)&refWeights(refWeights.Lower());

    PLib::EvalPolynomial(NewParameter, 2, Degree, 1, WArray[0], LocalWDerivatives[0]);

    for (ii = Degree + 1; ii <= 2; ii++)
    {
      LocalWDerivatives[ii] = 0.0e0;
    }

    Factor = 1.0e0 / SpanLenght;

    for (ii = 1; ii <= EndIndex; ii++)
    {
      LocalWDerivatives[ii] *= Factor;
      Factor /= SpanLenght;
    }
    PLib::RationalDerivatives(2,
                              Dimension,
                              LocalPDerivatives[0],
                              LocalWDerivatives[0],
                              LocalPDerivatives[0]);
  }

  Traits::CopyCoords(myPoint, LocalPDerivatives);
  Traits::CopyCoords(myVector1, LocalPDerivatives + Dimension);
  Traits::CopyCoords(myVector2, LocalPDerivatives + Dimension * 2);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_CacheD3(const double                      Parameter,
                      const int                         Degree,
                      const double                      CacheParameter,
                      const double                      SpanLenght,
                      const Array1OfPoints&             PolesArray,
                      const NCollection_Array1<double>* WeightsArray,
                      Point&                            aPoint,
                      Vector&                           aVector1,
                      Vector&                           aVector2,
                      Vector&                           aVector3)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  int     ii, Index, EndIndex;
  double  LocalPDerivatives[Dimension << 2];
  double  LocalWDerivatives[4], Factor, NewParameter;
  double* PArray    = (double*)&(PolesArray(PolesArray.Lower()));
  double* myPoint   = (double*)&aPoint;
  double* myVector1 = (double*)&aVector1;
  double* myVector2 = (double*)&aVector2;
  double* myVector3 = (double*)&aVector3;
  NewParameter      = (Parameter - CacheParameter) / SpanLenght;
  PLib::EvalPolynomial(NewParameter, 3, Degree, Dimension, PArray[0], LocalPDerivatives[0]);

  Index = (Degree + 1) * Dimension;
  for (ii = Degree; ii < 3; ii++)
  {
    Traits::NullifyCoords(LocalPDerivatives + Index);
    Index += Dimension;
  }

  Factor   = 1.0e0 / SpanLenght;
  Index    = Dimension;
  EndIndex = std::min(3, Degree);

  for (ii = 1; ii <= EndIndex; ii++)
  {
    Traits::ModifyCoordsScale(LocalPDerivatives + Index, Factor);
    Factor /= SpanLenght;
    Index += Dimension;
  }

  if (WeightsArray != NULL)
  {
    const NCollection_Array1<double>& refWeights = *WeightsArray;
    double*                           WArray     = (double*)&refWeights(refWeights.Lower());

    PLib::EvalPolynomial(NewParameter, 3, Degree, 1, WArray[0], LocalWDerivatives[0]);

    Factor = 1.0e0 / SpanLenght;

    for (ii = 1; ii <= EndIndex; ii++)
    {
      LocalWDerivatives[ii] *= Factor;
      Factor /= SpanLenght;
    }

    for (ii = (Degree + 1); ii <= 3; ii++)
    {
      LocalWDerivatives[ii] = 0.0e0;
    }
    PLib::RationalDerivatives(3,
                              Dimension,
                              LocalPDerivatives[0],
                              LocalWDerivatives[0],
                              LocalPDerivatives[0]);
  }

  Traits::CopyCoords(myPoint, LocalPDerivatives);
  Traits::CopyCoords(myVector1, LocalPDerivatives + Dimension);
  Traits::CopyCoords(myVector2, LocalPDerivatives + Dimension * 2);
  Traits::CopyCoords(myVector3, LocalPDerivatives + Dimension * 3);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_BuildCache(const double                      U,
                         const double                      SpanDomain,
                         const bool                        Periodic,
                         const int                         Degree,
                         const NCollection_Array1<double>& FlatKnots,
                         const Array1OfPoints&             Poles,
                         const NCollection_Array1<double>* Weights,
                         Array1OfPoints&                   CachePoles,
                         NCollection_Array1<double>*       CacheWeights)
{
  using Traits = BSplCLib_CurveTraits<Point, Vector, Array1OfPoints, Dimension>;

  int    ii, LocalDimension, LocalIndex, index = 0;
  double u = U, LocalValue;
  bool   rational;

  validateBSplineDegree(Degree);
  BSplCLib_DataContainer_T<Dimension> dc;
  PrepareEval_T<Point, Vector, Array1OfPoints, Dimension>(u,
                                                          index,
                                                          LocalDimension,
                                                          rational,
                                                          Degree,
                                                          Periodic,
                                                          Poles,
                                                          Weights,
                                                          FlatKnots,
                                                          (BSplCLib::NoMults()),
                                                          dc);

  BSplCLib::Bohm(u, Degree, Degree, *dc.knots, LocalDimension, *dc.poles);

  LocalValue = 1.0e0;
  LocalIndex = 0;

  if (rational)
  {

    for (ii = 1; ii <= Degree + 1; ii++)
    {
      Traits::CoordsToPointMultiplied(CachePoles(ii), dc.poles + LocalIndex, LocalValue);
      LocalIndex += Dimension + 1;
      LocalValue *= SpanDomain / (double)ii;
    }

    LocalIndex = Dimension;
    LocalValue = 1.0e0;
    for (ii = 1; ii <= Degree + 1; ii++)
    {
      (*CacheWeights)(ii) = dc.poles[LocalIndex] * LocalValue;
      LocalIndex += Dimension + 1;
      LocalValue *= SpanDomain / (double)ii;
    }
  }
  else
  {

    for (ii = 1; ii <= Degree + 1; ii++)
    {
      Traits::CoordsToPointMultiplied(CachePoles(ii), dc.poles + LocalIndex, LocalValue);
      LocalIndex += Dimension;
      LocalValue *= SpanDomain / (double)ii;
    }

    if (Weights != NULL)
    {
      for (ii = 1; ii <= Degree + 1; ii++)
        (*CacheWeights)(ii) = 0.0e0;
      (*CacheWeights)(1) = 1.0e0;
    }
  }
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_BuildCache(const double                      theParameter,
                         const double                      theSpanDomain,
                         const bool                        thePeriodicFlag,
                         const int                         theDegree,
                         const int                         theSpanIndex,
                         const NCollection_Array1<double>& theFlatKnots,
                         const Array1OfPoints&             thePoles,
                         const NCollection_Array1<double>* theWeights,
                         NCollection_Array2<double>&       theCacheArray)
{
  double aParam  = theParameter;
  int    anIndex = theSpanIndex;
  int    aDimension;
  bool   isRational;

  validateBSplineDegree(theDegree);
  BSplCLib_DataContainer_T<Dimension> dc;
  PrepareEval_T<Point, Vector, Array1OfPoints, Dimension>(aParam,
                                                          anIndex,
                                                          aDimension,
                                                          isRational,
                                                          theDegree,
                                                          thePeriodicFlag,
                                                          thePoles,
                                                          theWeights,
                                                          theFlatKnots,
                                                          (BSplCLib::NoMults()),
                                                          dc);

  int aCacheShift = (theWeights != NULL && !isRational) ? aDimension + 1 : aDimension;

  BSplCLib::Bohm(aParam, theDegree, theDegree, *dc.knots, aDimension, *dc.poles);

  double  aCoeff = 1.0;
  double* aCache = (double*)&(theCacheArray(theCacheArray.LowerRow(), theCacheArray.LowerCol()));
  double* aPolyCoeffs = dc.poles;

  for (int i = 0; i <= theDegree; i++)
  {
    for (int j = 0; j < aDimension; j++)
      aCache[j] = aPolyCoeffs[j] * aCoeff;
    aCoeff *= theSpanDomain / (i + 1);
    aPolyCoeffs += aDimension;
    aCache += aDimension;
    if (aCacheShift > aDimension)
    {
      aCache[0] = 0.0;
      aCache++;
    }
  }

  if (aCacheShift > aDimension)
    theCacheArray.SetValue(theCacheArray.LowerRow(),
                           theCacheArray.LowerCol() + aCacheShift - 1,
                           1.0);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_Interpolate(const int                         Degree,
                          const NCollection_Array1<double>& FlatKnots,
                          const NCollection_Array1<double>& Parameters,
                          const NCollection_Array1<int>&    ContactOrderArray,
                          Array1OfPoints&                   Poles,
                          int&                              InversionProblem)

{
  double* PArray;

  PArray = (double*)&Poles(Poles.Lower());

  BSplCLib::Interpolate(Degree,
                        FlatKnots,
                        Parameters,
                        ContactOrderArray,
                        Dimension,
                        PArray[0],
                        InversionProblem);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_Interpolate(const int                         Degree,
                          const NCollection_Array1<double>& FlatKnots,
                          const NCollection_Array1<double>& Parameters,
                          const NCollection_Array1<int>&    ContactOrderArray,
                          Array1OfPoints&                   Poles,
                          NCollection_Array1<double>&       Weights,
                          int&                              InversionProblem)
{
  double *PArray, *WArray;
  PArray = (double*)&Poles(Poles.Lower());
  WArray = (double*)&Weights(Weights.Lower());
  BSplCLib::Interpolate(Degree,
                        FlatKnots,
                        Parameters,
                        ContactOrderArray,
                        Dimension,
                        PArray[0],
                        WArray[0],
                        InversionProblem);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_MovePoint(const double                      U,
                        const Vector&                     Displ,
                        const int                         Index1,
                        const int                         Index2,
                        const int                         Degree,
                        const Array1OfPoints&             Poles,
                        const NCollection_Array1<double>* Weights,
                        const NCollection_Array1<double>& FlatKnots,
                        int&                              FirstIndex,
                        int&                              LastIndex,
                        Array1OfPoints&                   NewPoles)
{

  int         FirstNonZeroBsplineIndex;
  math_Matrix BSplineBasis(1, 1, 1, Degree + 1);
  int         ErrorCode =
    BSplCLib::EvalBsplineBasis(0, Degree + 1, FlatKnots, U, FirstNonZeroBsplineIndex, BSplineBasis);
  if (ErrorCode != 0)
  {
    FirstIndex = 0;
    LastIndex  = 0;

    for (int i = Poles.Lower(); i <= Poles.Upper(); i++)
    {
      NewPoles(i) = Poles(i);
    }
    return;
  }

  FirstIndex = FirstNonZeroBsplineIndex;
  LastIndex  = FirstNonZeroBsplineIndex + Degree;
  if (FirstIndex < Index1)
    FirstIndex = Index1;
  if (LastIndex > Index2)
    LastIndex = Index2;

  double maxValue = 0.0;
  int    i, kk1 = 0, kk2, ii;

  for (i = FirstIndex - FirstNonZeroBsplineIndex + 1; i <= LastIndex - FirstNonZeroBsplineIndex + 1;
       i++)
  {
    if (BSplineBasis(1, i) > maxValue)
    {
      kk1      = i + FirstNonZeroBsplineIndex - 1;
      maxValue = BSplineBasis(1, i);
    }
  }

  kk2 = kk1;
  i   = kk1 - FirstNonZeroBsplineIndex + 2;
  if ((kk1 + 1) <= LastIndex)
  {
    if (std::abs(BSplineBasis(1, kk1 - FirstNonZeroBsplineIndex + 2) - maxValue) < 1.e-10)
    {
      kk2 = kk1 + 1;
    }
  }

  double D1 = 0.0;
  double D2 = 0.0;
  double hN, Coef, Dval;

  for (i = 1; i <= Degree + 1; i++)
  {
    ii = i + FirstNonZeroBsplineIndex - 1;
    if (Weights != NULL)
    {
      hN = Weights->Value(ii) * BSplineBasis(1, i);
      D2 += hN;
    }
    else
    {
      hN = BSplineBasis(1, i);
    }
    if (ii >= FirstIndex && ii <= LastIndex)
    {
      if (ii < kk1)
      {
        Dval = kk1 - ii;
      }
      else if (ii > kk2)
      {
        Dval = ii - kk2;
      }
      else
      {
        Dval = 0.0;
      }
      D1 += 1. / (Dval + 1.) * hN;
    }
  }

  if (Weights != NULL)
  {
    Coef = D2 / D1;
  }
  else
  {
    Coef = 1. / D1;
  }

  for (i = Poles.Lower(); i <= Poles.Upper(); i++)
  {
    if (i >= FirstIndex && i <= LastIndex)
    {
      if (i < kk1)
      {
        Dval = kk1 - i;
      }
      else if (i > kk2)
      {
        Dval = i - kk2;
      }
      else
      {
        Dval = 0.0;
      }
      NewPoles(i) = Poles(i).Translated((Coef / (Dval + 1.)) * Displ);
    }
    else
    {
      NewPoles(i) = Poles(i);
    }
  }
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_MovePointAndTangent(const double                      U,
                                  const Vector&                     Delta,
                                  const Vector&                     DeltaDerivatives,
                                  const double                      Tolerance,
                                  const int                         Degree,
                                  const int                         StartingCondition,
                                  const int                         EndingCondition,
                                  const Array1OfPoints&             Poles,
                                  const NCollection_Array1<double>* Weights,
                                  const NCollection_Array1<double>& FlatKnots,
                                  Array1OfPoints&                   NewPoles,
                                  int&                              ErrorStatus)
{
  double *delta_array, *delta_derivative_array, *poles_array, *new_poles_array;

  int num_poles;
  num_poles = Poles.Length();

  if (NewPoles.Length() != num_poles)
  {
    throw Standard_ConstructionError();
  }
  delta_array            = (double*)&Delta;
  delta_derivative_array = (double*)&DeltaDerivatives;
  poles_array            = (double*)&Poles(Poles.Lower());

  new_poles_array = (double*)&NewPoles(NewPoles.Lower());
  BSplCLib::MovePointAndTangent(U,
                                Dimension,
                                delta_array[0],
                                delta_derivative_array[0],
                                Tolerance,
                                Degree,
                                StartingCondition,
                                EndingCondition,
                                poles_array[0],
                                Weights,
                                FlatKnots,
                                new_poles_array[0],
                                ErrorStatus);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_Resolution(const Array1OfPoints&             Poles,
                         const NCollection_Array1<double>* Weights,
                         const int                         NumPoles,
                         const NCollection_Array1<double>& FlatKnots,
                         const int                         Degree,
                         const double                      Tolerance3D,
                         double&                           UTolerance)
{
  double* PolesArray;
  PolesArray = (double*)&Poles(Poles.Lower());
  BSplCLib::Resolution(PolesArray[0],
                       Dimension,
                       NumPoles,
                       Weights,
                       FlatKnots,
                       Degree,
                       Tolerance3D,
                       UTolerance);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_FunctionMultiply(const BSplCLib_EvaluatorFunction& FunctionPtr,
                               const int                         BSplineDegree,
                               const NCollection_Array1<double>& BSplineFlatKnots,
                               const Array1OfPoints&             Poles,
                               const NCollection_Array1<double>& FlatKnots,
                               const int                         NewDegree,
                               Array1OfPoints&                   NewPoles,
                               int&                              theStatus)
{
  int num_bspline_poles = BSplineFlatKnots.Length() - BSplineDegree - 1;
  int num_new_poles     = FlatKnots.Length() - NewDegree - 1;

  if (Poles.Length() != num_bspline_poles || NewPoles.Length() != num_new_poles)
  {
    throw Standard_ConstructionError();
  }
  double* array_of_poles     = (double*)&Poles(Poles.Lower());
  double* array_of_new_poles = (double*)&NewPoles(NewPoles.Lower());
  BSplCLib::FunctionMultiply(FunctionPtr,
                             BSplineDegree,
                             BSplineFlatKnots,
                             Dimension,
                             array_of_poles[0],
                             FlatKnots,
                             NewDegree,
                             array_of_new_poles[0],
                             theStatus);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_FunctionReparameterise(const BSplCLib_EvaluatorFunction& FunctionPtr,
                                     const int                         BSplineDegree,
                                     const NCollection_Array1<double>& BSplineFlatKnots,
                                     const Array1OfPoints&             Poles,
                                     const NCollection_Array1<double>& FlatKnots,
                                     const int                         NewDegree,
                                     Array1OfPoints&                   NewPoles,
                                     int&                              theStatus)
{
  int num_bspline_poles = BSplineFlatKnots.Length() - BSplineDegree - 1;
  int num_new_poles     = FlatKnots.Length() - NewDegree - 1;

  if (Poles.Length() != num_bspline_poles || NewPoles.Length() != num_new_poles)
  {
    throw Standard_ConstructionError();
  }
  double* array_of_poles     = (double*)&Poles(Poles.Lower());
  double* array_of_new_poles = (double*)&NewPoles(NewPoles.Lower());
  BSplCLib::FunctionReparameterise(FunctionPtr,
                                   BSplineDegree,
                                   BSplineFlatKnots,
                                   Dimension,
                                   array_of_poles[0],
                                   FlatKnots,
                                   NewDegree,
                                   array_of_new_poles[0],
                                   theStatus);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_PolesCoefficients_Bezier(const Array1OfPoints&             Poles,
                                       const NCollection_Array1<double>* Weights,
                                       Array1OfPoints&                   CachePoles,
                                       NCollection_Array1<double>*       CacheWeights)
{
  const int                  aDegree = Poles.Length() - 1;
  NCollection_Array1<double> aBidFlatKnots(BSplCLib::FlatBezierKnots(aDegree),
                                           1,
                                           2 * (aDegree + 1));
  BSplCLib_BuildCache<Point, Vector, Array1OfPoints, Dimension>(0.,
                                                                1.,
                                                                false,
                                                                aDegree,
                                                                aBidFlatKnots,
                                                                Poles,
                                                                Weights,
                                                                CachePoles,
                                                                CacheWeights);
}

template <typename Point, typename Vector, typename Array1OfPoints, int Dimension>
void BSplCLib_IncreaseDegree_Bezier(const int                         NewDegree,
                                    const Array1OfPoints&             Poles,
                                    const NCollection_Array1<double>* Weights,
                                    Array1OfPoints&                   NewPoles,
                                    NCollection_Array1<double>*       NewWeights)
{
  const int              aDegree = Poles.Length() - 1;
  BSplCLib_KnotArrays<2> aBezierKnots(aDegree);
  BSplCLib_IncreaseDegree<Point, Vector, Array1OfPoints, Dimension>(aDegree,
                                                                    NewDegree,
                                                                    false,
                                                                    Poles,
                                                                    Weights,
                                                                    aBezierKnots.Knot,
                                                                    aBezierKnots.Mult,
                                                                    NewPoles,
                                                                    NewWeights,
                                                                    aBezierKnots.Knot,
                                                                    aBezierKnots.Mult);
}
