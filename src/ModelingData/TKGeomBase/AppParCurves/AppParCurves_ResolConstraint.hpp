#define No_Standard_RangeError
#define No_Standard_OutOfRange

#include <math_Vector.hpp>
#include <math_Matrix.hpp>
#include <AppParCurves_Constraint.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <AppParCurves_MultiPoint.hpp>
#include <AppParCurves.hpp>
#include <Standard_DimensionError.hpp>
#include <math_Uzawa.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

AppParCurves_ResolConstraint::AppParCurves_ResolConstraint(
  const MultiLine&                                                       SSP,
  AppParCurves_MultiCurve&                                               SCurv,
  const int                                                              FirstPoint,
  const int                                                              LastPoint,
  const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
  const math_Matrix&                                                     Bern,
  const math_Matrix&                                                     DerivativeBern,
  const double                                                           Tolerance)
    : Cont(1,
           NbConstraints(SSP, FirstPoint, LastPoint, TheConstraints),
           1,
           NbColumns(SSP, SCurv.NbPoles() - 1),
           0.0),
      DeCont(1,
             NbConstraints(SSP, FirstPoint, LastPoint, TheConstraints),
             1,
             NbColumns(SSP, SCurv.NbPoles() - 1),
             0.0),
      Secont(1, NbConstraints(SSP, FirstPoint, LastPoint, TheConstraints), 0.0),
      CTCinv(1,
             NbConstraints(SSP, FirstPoint, LastPoint, TheConstraints),
             1,
             NbConstraints(SSP, FirstPoint, LastPoint, TheConstraints)),
      Vardua(1, NbConstraints(SSP, FirstPoint, LastPoint, TheConstraints)),
      IPas(1, LastPoint - FirstPoint + 1),
      ITan(1, LastPoint - FirstPoint + 1),
      ICurv(1, LastPoint - FirstPoint + 1)
{
  int                           i, j, k, NbCu = SCurv.NbCurves();
  int                           Npt;
  int                           Inc3, IncSec, IncCol, IP = 0, CCol;
  int                           myindex, Def = SCurv.NbPoles() - 1;
  int                           nb3d, nb2d, Npol = Def + 1, Npol2 = 2 * Npol;
  double                        T1 = 0., T2 = 0., T3, Tmax, Daij;
  gp_Vec                        V;
  gp_Vec2d                      V2d;
  gp_Pnt                        Poi;
  gp_Pnt2d                      Poi2d;
  AppParCurves_ConstraintCouple mycouple;
  AppParCurves_Constraint FC = AppParCurves_NoConstraint, LC = AppParCurves_NoConstraint, Cons;

  IncPass = 0;
  IncTan  = 0;
  IncCurv = 0;
  for (i = TheConstraints->Lower(); i <= TheConstraints->Upper(); i++)
  {
    mycouple = TheConstraints->Value(i);
    myindex  = mycouple.Index();
    Cons     = mycouple.Constraint();
    if (myindex == FirstPoint)
      FC = Cons;
    if (myindex == LastPoint)
      LC = Cons;
    if (Cons >= 1)
    {
      IncPass++;
      IPas(IncPass) = myindex;
    }
    if (Cons >= 2)
    {
      IncTan++;
      ITan(IncTan) = myindex;
    }
    if (Cons == 3)
    {
      IncCurv++;
      ICurv(IncCurv) = myindex;
    }
  }

  if (IncPass == 0)
  {
    Done = true;
    return;
  }

  nb3d       = ToolLine::NbP3d(SSP);
  nb2d       = ToolLine::NbP2d(SSP);
  int mynb3d = nb3d, mynb2d = nb2d;
  if (nb3d == 0)
    mynb3d = 1;
  if (nb2d == 0)
    mynb2d = 1;
  CCol = nb3d * 3 + nb2d * 2;

  math_Matrix             ContInit(1, IncPass, 1, Npol);
  math_Vector             Start(1, CCol * Npol);
  NCollection_Array2<int> Ibont(1, NbCu, 1, IncTan);

  for (i = 1; i <= IncPass; i++)
  {
    Npt = IPas(i);
    for (j = 1; j <= Npol; j++)
    {
      ContInit(i, j) = Bern(Npt, j);
    }
  }
  for (i = 1; i <= CCol; i++)
  {
    Cont.Set(IncPass * (i - 1) + 1, IncPass * i, Npol * (i - 1) + 1, Npol * i, ContInit);
  }

  NCollection_Array1<gp_Vec>   tabV(1, mynb3d);
  NCollection_Array1<gp_Vec2d> tabV2d(1, mynb2d);
  NCollection_Array1<gp_Pnt>   tabP(1, mynb3d);
  NCollection_Array1<gp_Pnt2d> tabP2d(1, mynb2d);

  Inc3   = CCol * IncPass + 1;
  IncCol = 0;
  IncSec = 0;
  for (k = 1; k <= NbCu; k++)
  {
    if (k <= nb3d)
    {
      for (i = 1; i <= IncTan; i++)
      {
        Npt = ITan(i);

        ToolLine::Tangency(SSP, Npt, tabV);
        V = tabV(k);
        V.Coord(T1, T2, T3);
        Tmax        = std::abs(T1);
        Ibont(k, i) = 1;
        if (std::abs(T2) > Tmax)
        {
          Tmax        = std::abs(T2);
          Ibont(k, i) = 2;
        }
        if (std::abs(T3) > Tmax)
        {
          Tmax        = std::abs(T3);
          Ibont(k, i) = 3;
        }
        if (Ibont(k, i) == 3)
        {
          for (j = 1; j <= Npol; j++)
          {
            Daij                               = DerivativeBern(Npt, j);
            Cont(Inc3, j + Npol + IncCol)      = Daij * T3 / Tmax;
            Cont(Inc3, j + Npol2 + IncCol)     = -Daij * T2 / Tmax;
            Cont(Inc3 + 1, j + IncCol)         = Daij * T3 / Tmax;
            Cont(Inc3 + 1, j + Npol2 + IncCol) = -Daij * T1 / Tmax;
          }
        }
        else if (Ibont(k, i) == 1)
        {
          for (j = 1; j <= Npol; j++)
          {
            Daij                              = DerivativeBern(Npt, j);
            Cont(Inc3, j + IncCol)            = Daij * T3 / Tmax;
            Cont(Inc3, j + Npol2 + IncCol)    = -Daij * T1 / Tmax;
            Cont(Inc3 + 1, j + IncCol)        = Daij * T2 / Tmax;
            Cont(Inc3 + 1, j + Npol + IncCol) = -Daij * T1 / Tmax;
          }
        }
        else if (Ibont(k, i) == 2)
        {
          for (j = 1; j <= Def + 1; j++)
          {
            Daij                              = DerivativeBern(Npt, j);
            Cont(Inc3, j + Npol + IncCol)     = Daij * T3 / Tmax;
            Cont(Inc3, j + Npol2 + IncCol)    = -Daij * T2 / Tmax;
            Cont(Inc3 + 1, j + IncCol)        = Daij * T2 / Tmax;
            Cont(Inc3 + 1, j + Npol + IncCol) = -Daij * T1 / Tmax;
          }
        }
        Inc3 = Inc3 + 2;
      }

      for (i = 1; i <= IncPass; i++)
      {
        ToolLine::Value(SSP, IPas(i), tabP);
        Poi                              = tabP(k);
        Secont(i + IncSec)               = Poi.X();
        Secont(i + IncPass + IncSec)     = Poi.Y();
        Secont(i + 2 * IncPass + IncSec) = Poi.Z();
      }
      IncSec = IncSec + 3 * IncPass;

      for (j = 1; j <= Npol; j++)
      {
        Poi                       = SCurv.Value(j).Point(k);
        Start(j + IncCol)         = Poi.X();
        Start(j + Npol + IncCol)  = Poi.Y();
        Start(j + Npol2 + IncCol) = Poi.Z();
      }
      IncCol = IncCol + 3 * Npol;
    }

    else
    {
      for (i = 1; i <= IncTan; i++)
      {
        Npt = ITan(i);
        ToolLine::Tangency(SSP, Npt, tabV2d);
        V2d         = tabV2d(k - nb3d);
        T1          = V2d.X();
        T2          = V2d.Y();
        Tmax        = std::abs(T1);
        Ibont(k, i) = 1;
        if (std::abs(T2) > Tmax)
        {
          Tmax        = std::abs(T2);
          Ibont(k, i) = 2;
        }
        for (j = 1; j <= Npol; j++)
        {
          Daij                          = DerivativeBern(Npt, j);
          Cont(Inc3, j + IncCol)        = Daij * T2;
          Cont(Inc3, j + Npol + IncCol) = -Daij * T1;
        }
        Inc3 = Inc3 + 1;
      }

      for (i = 1; i <= IncPass; i++)
      {
        ToolLine::Value(SSP, IPas(i), tabP2d);
        Poi2d                        = tabP2d(i - nb3d);
        Secont(i + IncSec)           = Poi2d.X();
        Secont(i + IncPass + IncSec) = Poi2d.Y();
      }
      IncSec = IncSec + 2 * IncPass;

      for (j = 1; j <= Npol; j++)
      {
        Poi2d                    = SCurv.Value(j).Point2d(k);
        Start(j + IncCol)        = Poi2d.X();
        Start(j + Npol + IncCol) = Poi2d.Y();
      }
      IncCol = IncCol + Npol2;
    }
  }

  --Inc3;
  for (i = 1; i <= IncTan; ++i)
  {
    IncCol = 0;
    Npt    = ITan(i);
    for (k = 1; k <= NbCu - 1; ++k)
    {
      ++Inc3;

      int addIndex_1 = 0, aVal = Ibont(k, i);
      switch (aVal)
      {
        case 1:
        {
          if (k <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k);
            T1 = V.X();
            IP = 3 * Npol;
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k - nb3d);
            T1  = V2d.X();
            IP  = 2 * Npol;
          }
          addIndex_1 = 0;
          break;
        }
        case 2:
        {
          if (k <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k);
            IP = 3 * Npol;
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k - nb3d);
            T1  = V2d.Y();
            IP  = 2 * Npol;
          }
          addIndex_1 = Npol;
          break;
        }
        case 3:
        {
          ToolLine::Tangency(SSP, Npt, tabV);
          V          = tabV(k);
          T1         = V.Z();
          IP         = 3 * Npol;
          addIndex_1 = 2 * Npol;
          break;
        }
      }

      int addIndex_2 = 0, aNextVal = Ibont(k + 1, i);
      switch (aNextVal)
      {
        case 1:
        {
          if ((k + 1) <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k + 1);
            T2 = V.X();
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k + 1 - nb3d);
            T2  = V2d.X();
          }
          addIndex_2 = 0;
          break;
        }
        case 2:
        {
          if ((k + 1) <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k + 1);
            T2 = V.Y();
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k + 1 - nb3d);
            T2  = V2d.Y();
          }
          addIndex_2 = Npol;
          break;
        }
        case 3:
        {
          ToolLine::Tangency(SSP, Npt, tabV);
          V          = tabV(k + 1);
          T2         = V.Z();
          addIndex_2 = 2 * Npol;
          break;
        }
      }

      for (j = 1; j <= Npol; j++)
      {
        Daij                                     = DerivativeBern(Npt, j);
        Cont(Inc3, j + IncCol + addIndex_1)      = Daij * T2;
        Cont(Inc3, j + IP + IncCol + addIndex_2) = -Daij * T1;
      }
      IncCol += IP;
    }
  }

  math_Uzawa UzaResol(Cont, Secont, Start, Tolerance);
  if (!(UzaResol.IsDone()))
  {
    Done = false;
    return;
  }
  CTCinv = UzaResol.InverseCont();
  UzaResol.Duale(Vardua);
  for (i = 1; i <= CTCinv.RowNumber(); i++)
  {
    for (j = i; j <= CTCinv.RowNumber(); j++)
    {
      CTCinv(i, j) = CTCinv(j, i);
    }
  }
  Done = true;
  math_Vector VecPoles(1, CCol * Npol);
  VecPoles = UzaResol.Value();

  int polinit = 1, polfin = Npol;
  if (FC >= 1)
    polinit = 2;
  if (LC >= 1)
    polfin = Npol - 1;

  for (i = polinit; i <= polfin; i++)
  {
    IncCol = 0;
    AppParCurves_MultiPoint MPol(nb3d, nb2d);
    for (k = 1; k <= NbCu; k++)
    {
      if (k <= nb3d)
      {
        gp_Pnt Pol(VecPoles(IncCol + i),
                   VecPoles(IncCol + Npol + i),
                   VecPoles(IncCol + 2 * Npol + i));
        MPol.SetPoint(k, Pol);
        IncCol = IncCol + 3 * Npol;
      }
      else
      {
        gp_Pnt2d Pol2d(VecPoles(IncCol + i), VecPoles(IncCol + Npol + i));
        MPol.SetPoint2d(k, Pol2d);
        IncCol = IncCol + 2 * Npol;
      }
    }
    SCurv.SetValue(i, MPol);
  }
}

bool AppParCurves_ResolConstraint::IsDone() const
{
  return Done;
}

int AppParCurves_ResolConstraint::NbConstraints(
  const MultiLine& SSP,
  const int,
  const int,
  const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints) const
{

  int                     aIncPass, aIncTan, aIncCurv, aCCol;
  int                     i;
  AppParCurves_Constraint Cons;

  aIncPass = 0;
  aIncTan  = 0;
  aIncCurv = 0;

  for (i = TheConstraints->Lower(); i <= TheConstraints->Upper(); i++)
  {
    Cons = (TheConstraints->Value(i)).Constraint();
    if (Cons >= 1)
    {
      aIncPass++;
    }
    if (Cons >= 2)
    {
      aIncTan++;
    }
    if (Cons == 3)
    {
      aIncCurv++;
    }
  }
  int nb3d = ToolLine::NbP3d(SSP);
  int nb2d = ToolLine::NbP2d(SSP);
  aCCol    = nb3d * 3 + nb2d * 2;

  return aCCol * aIncPass + aIncTan * (aCCol - 1) + 3 * aIncCurv;
}

int AppParCurves_ResolConstraint::NbColumns(const MultiLine& SSP, const int Deg) const
{
  int nb3d = ToolLine::NbP3d(SSP);
  int nb2d = ToolLine::NbP2d(SSP);
  int CCol = nb3d * 3 + nb2d * 2;

  return CCol * (Deg + 1);
}

const math_Matrix& AppParCurves_ResolConstraint::ConstraintMatrix() const
{
  return Cont;
}

const math_Matrix& AppParCurves_ResolConstraint::InverseMatrix() const
{
  return CTCinv;
}

const math_Vector& AppParCurves_ResolConstraint::Duale() const
{
  return Vardua;
}

const math_Matrix& AppParCurves_ResolConstraint::ConstraintDerivative(const MultiLine&   SSP,
                                                                      const math_Vector& Parameters,
                                                                      const int          Deg,
                                                                      const math_Matrix& DA)
{
  int    i, j, k, nb2d, nb3d, CCol, Inc3, IncCol, Npt;
  int    Npol, Npol2, NbCu = ToolLine::NbP3d(SSP) + ToolLine::NbP2d(SSP);
  int    IP;
  double Daij;
  Npol  = Deg + 1;
  Npol2 = 2 * Npol;
  NCollection_Array2<int> Ibont(1, NbCu, 1, IncTan);
  math_Matrix             DeCInit(1, IncPass, 1, Npol);
  math_Vector             DDA(1, Npol);
  gp_Vec                  V;
  gp_Vec2d                V2d;
  double                  T1, T2, T3, Tmax, DDaij;

  nb3d       = ToolLine::NbP3d(SSP);
  nb2d       = ToolLine::NbP2d(SSP);
  int mynb3d = nb3d, mynb2d = nb2d;
  if (nb3d == 0)
    mynb3d = 1;
  if (nb2d == 0)
    mynb2d = 1;
  CCol = nb3d * 3 + nb2d * 2;

  NCollection_Array1<gp_Vec>   tabV(1, mynb3d);
  NCollection_Array1<gp_Vec2d> tabV2d(1, mynb2d);
  NCollection_Array1<gp_Pnt>   tabP(1, mynb3d);
  NCollection_Array1<gp_Pnt2d> tabP2d(1, mynb2d);

  for (i = 1; i <= DeCont.RowNumber(); i++)
    for (j = 1; j <= DeCont.ColNumber(); j++)
      DeCont(i, j) = 0.0;

  for (i = 1; i <= IncPass; i++)
  {
    Npt = IPas(i);
    for (j = 1; j <= Npol; j++)
      DeCInit(i, j) = DA(Npt, j);
  }
  for (i = 1; i <= CCol; i++)
  {
    DeCont.Set(IncPass * (i - 1) + 1, IncPass * i, Npol * (i - 1) + 1, Npol * i, DeCInit);
  }

  Inc3   = CCol * IncPass + 1;
  IncCol = 0;

  for (k = 1; k <= NbCu; k++)
  {
    if (k <= nb3d)
    {
      for (i = 1; i <= IncTan; i++)
      {
        Npt = ITan(i);

        ToolLine::Tangency(SSP, Npt, tabV);
        V = tabV(k);
        V.Coord(T1, T2, T3);
        Tmax        = std::abs(T1);
        Ibont(k, i) = 1;
        if (std::abs(T2) > Tmax)
        {
          Tmax        = std::abs(T2);
          Ibont(k, i) = 2;
        }
        if (std::abs(T3) > Tmax)
        {
          Tmax        = std::abs(T3);
          Ibont(k, i) = 3;
        }
        AppParCurves::SecondDerivativeBernstein(Parameters(Npt), DDA);
        if (Ibont(k, i) == 3)
        {
          for (j = 1; j <= Npol; j++)
          {
            DDaij                                = DDA(j);
            DeCont(Inc3, j + Npol + IncCol)      = DDaij * T3 / Tmax;
            DeCont(Inc3, j + Npol2 + IncCol)     = -DDaij * T2 / Tmax;
            DeCont(Inc3 + 1, j + IncCol)         = DDaij * T3 / Tmax;
            DeCont(Inc3 + 1, j + Npol2 + IncCol) = -DDaij * T1 / Tmax;
          }
        }
        else if (Ibont(k, i) == 1)
        {
          for (j = 1; j <= Npol; j++)
          {
            DDaij                               = DDA(j);
            DeCont(Inc3, j + IncCol)            = DDaij * T3 / Tmax;
            DeCont(Inc3, j + Npol2 + IncCol)    = -DDaij * T1 / Tmax;
            DeCont(Inc3 + 1, j + IncCol)        = DDaij * T2 / Tmax;
            DeCont(Inc3 + 1, j + Npol + IncCol) = -DDaij * T1 / Tmax;
          }
        }
        else if (Ibont(k, i) == 2)
        {
          for (j = 1; j <= Npol; j++)
          {
            DDaij                               = DDA(j);
            DeCont(Inc3, j + Npol + IncCol)     = DDaij * T3 / Tmax;
            DeCont(Inc3, j + Npol2 + IncCol)    = -DDaij * T2 / Tmax;
            DeCont(Inc3 + 1, j + IncCol)        = DDaij * T2 / Tmax;
            DeCont(Inc3 + 1, j + Npol + IncCol) = -DDaij * T1 / Tmax;
          }
        }
        Inc3 = Inc3 + 2;
      }
      IncCol = IncCol + 3 * Npol;
    }
    else
    {
      for (i = 1; i <= IncTan; i++)
      {
        Npt = ITan(i);
        AppParCurves::SecondDerivativeBernstein(Parameters(Npt), DDA);
        ToolLine::Tangency(SSP, Npt, tabV2d);
        V2d = tabV2d(k);
        V2d.Coord(T1, T2);
        Tmax        = std::abs(T1);
        Ibont(k, i) = 1;
        if (std::abs(T2) > Tmax)
        {
          Tmax        = std::abs(T2);
          Ibont(k, i) = 2;
        }
        for (j = 1; j <= Npol; j++)
        {
          DDaij                           = DDA(j);
          DeCont(Inc3, j + IncCol)        = DDaij * T2;
          DeCont(Inc3, j + Npol + IncCol) = -DDaij * T1;
        }
        Inc3 = Inc3 + 1;
      }
    }
  }

  Inc3 = Inc3 - 1;
  for (i = 1; i <= IncTan; i++)
  {
    IncCol = 0;
    Npt    = ITan(i);
    AppParCurves::SecondDerivativeBernstein(Parameters(Npt), DDA);

    for (k = 1; k <= NbCu - 1; k++)
    {
      Inc3 = Inc3 + 1;
      if (Ibont(k, i) == 1)
      {
        if (k <= nb3d)
        {
          ToolLine::Tangency(SSP, Npt, tabV);
          V  = tabV(k);
          T1 = V.X();
          IP = 3 * Npol;
        }
        else
        {
          ToolLine::Tangency(SSP, Npt, tabV2d);
          V2d = tabV2d(k);
          T1  = V2d.X();
          IP  = 2 * Npol;
        }
        if (Ibont(k + 1, i) == 1)
        {
          if ((k + 1) <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k + 1);
            T2 = V.X();
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k + 1);
            T2  = V2d.X();
          }
          for (j = 1; j <= Npol; j++)
          {
            Daij                        = DDA(j);
            Cont(Inc3, j + IncCol)      = Daij * T2;
            Cont(Inc3, j + IP + IncCol) = -Daij * T1;
          }
          IncCol = IncCol + IP;
        }
        else if (Ibont(k + 1, i) == 2)
        {
          if ((k + 1) <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k + 1);
            T2 = V.Y();
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k + 1);
            T2  = V2d.Y();
          }
          for (j = 1; j <= Npol; j++)
          {
            Daij                               = DDA(j);
            Cont(Inc3, j + IncCol)             = Daij * T2;
            Cont(Inc3, j + IP + Npol + IncCol) = -Daij * T1;
          }
          IncCol = IncCol + IP;
        }
        else if (Ibont(k + 1, i) == 3)
        {
          ToolLine::Tangency(SSP, Npt, tabV);
          V  = tabV(k + 1);
          T2 = V.Z();
          for (j = 1; j <= Npol; j++)
          {
            Daij                                   = DDA(j);
            Cont(Inc3, j + IncCol)                 = Daij * T2;
            Cont(Inc3, j + IP + 2 * Npol + IncCol) = -Daij * T1;
          }
          IncCol = IncCol + IP;
        }
      }
      else if (Ibont(k, i) == 2)
      {
        if (k <= nb3d)
        {
          ToolLine::Tangency(SSP, Npt, tabV);
          V  = tabV(k);
          T1 = V.Y();
          IP = 3 * Npol;
        }
        else
        {
          ToolLine::Tangency(SSP, Npt, tabV2d);
          V2d = tabV2d(k);
          T1  = V2d.Y();
          IP  = 2 * Npol;
        }
        if (Ibont(k + 1, i) == 1)
        {
          if ((k + 1) <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k + 1);
            T2 = V.X();
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k + 1);
            T2  = V2d.X();
          }
          for (j = 1; j <= Npol; j++)
          {
            Daij                          = DDA(j);
            Cont(Inc3, j + Npol + IncCol) = Daij * T2;
            Cont(Inc3, j + IP + IncCol)   = -Daij * T1;
          }
          IncCol = IncCol + IP;
        }
        else if (Ibont(k + 1, i) == 2)
        {
          if ((k + 1) <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k + 1);
            T2 = V.Y();
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k + 1);
            T2  = V2d.Y();
          }
          for (j = 1; j <= Npol; j++)
          {
            Daij                               = DDA(j);
            Cont(Inc3, j + Npol + IncCol)      = Daij * T2;
            Cont(Inc3, j + IP + Npol + IncCol) = -Daij * T1;
          }
          IncCol = IncCol + IP;
        }
        else if (Ibont(k + 1, i) == 3)
        {
          ToolLine::Tangency(SSP, Npt, tabV);
          V  = tabV(k + 1);
          T2 = V.Z();
          for (j = 1; j <= Npol; j++)
          {
            Daij                                   = DDA(j);
            Cont(Inc3, j + Npol + IncCol)          = Daij * T2;
            Cont(Inc3, j + IP + 2 * Npol + IncCol) = -Daij * T1;
          }
          IncCol = IncCol + IP;
        }
      }

      else
      {
        ToolLine::Tangency(SSP, Npt, tabV);
        V  = tabV(k);
        T1 = V.Z();
        IP = 3 * Npol;
        if (Ibont(k + 1, i) == 1)
        {
          if ((k + 1) <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k + 1);
            T2 = V.X();
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k + 1);
            T2  = V2d.X();
          }
          for (j = 1; j <= Npol; j++)
          {
            Daij                              = DDA(j);
            Cont(Inc3, j + 2 * Npol + IncCol) = Daij * T2;
            Cont(Inc3, j + IP + IncCol)       = -Daij * T1;
          }
          IncCol = IncCol + IP;
        }

        else if (Ibont(k + 1, i) == 2)
        {
          if ((k + 1) <= nb3d)
          {
            ToolLine::Tangency(SSP, Npt, tabV);
            V  = tabV(k + 1);
            T2 = V.Y();
          }
          else
          {
            ToolLine::Tangency(SSP, Npt, tabV2d);
            V2d = tabV2d(k + 1);
            T2  = V2d.Y();
          }
          for (j = 1; j <= Npol; j++)
          {
            Daij                               = DDA(j);
            Cont(Inc3, j + 2 * Npol + IncCol)  = Daij * T2;
            Cont(Inc3, j + IP + Npol + IncCol) = -Daij * T1;
          }
          IncCol = IncCol + IP;
        }

        else if (Ibont(k + 1, i) == 3)
        {
          ToolLine::Tangency(SSP, Npt, tabV);
          V  = tabV(k + 1);
          T2 = V.Z();
          for (j = 1; j <= Npol; j++)
          {
            Daij                                   = DDA(j);
            Cont(Inc3, j + 2 * Npol + IncCol)      = Daij * T2;
            Cont(Inc3, j + IP + 2 * Npol + IncCol) = -Daij * T1;
          }
          IncCol = IncCol + IP;
        }
      }
    }
  }

  return DeCont;
}
