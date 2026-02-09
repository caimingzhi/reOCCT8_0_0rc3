

#define No_Standard_OutOfRange

#include <gp_GTrsf.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Mat.hpp>
#include <gp_Trsf.hpp>
#include <gp_XYZ.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Dump.hpp>
#include <Standard_OutOfRange.hpp>

void gp_GTrsf::SetTranslationPart(const gp_XYZ& Coord)
{
  loc = Coord;
  if (Form() == gp_CompoundTrsf || Form() == gp_Other || Form() == gp_Translation)
  {
  }
  else if (Form() == gp_Identity)
  {
    shape = gp_Translation;
  }
  else
  {
    shape = gp_CompoundTrsf;
  }
}

void gp_GTrsf::Invert()
{
  if (shape == gp_Other)
  {
    matrix.Invert();
    loc.Multiply(matrix);
    loc.Reverse();
  }
  else
  {
    gp_Trsf T = Trsf();
    T.Invert();
    SetTrsf(T);
  }
}

void gp_GTrsf::Multiply(const gp_GTrsf& T)
{
  if (Form() == gp_Other || T.Form() == gp_Other)
  {
    shape = gp_Other;
    loc.Add(T.loc.Multiplied(matrix));
    matrix.Multiply(T.matrix);
  }
  else
  {
    gp_Trsf T1 = Trsf();
    gp_Trsf T2 = T.Trsf();
    T1.Multiply(T2);
    matrix = T1.matrix;
    loc    = T1.loc;
    scale  = T1.scale;
    shape  = T1.shape;
  }
}

void gp_GTrsf::Power(const int N)
{
  if (N == 0)
  {
    scale = 1.;
    shape = gp_Identity;
    matrix.SetIdentity();
    loc = gp_XYZ(0., 0., 0.);
  }
  else if (N == 1)
  {
  }
  else if (N == -1)
  {
    Invert();
  }
  else
  {
    if (shape == gp_Other)
    {
      int    Npower  = std::abs(N) - 1;
      gp_XYZ Temploc = loc;

      gp_Mat Tempmatrix(matrix);
      for (;;)
      {
        if (IsOdd(Npower))
        {
          loc.Add(Temploc.Multiplied(matrix));
          matrix.Multiply(Tempmatrix);
        }
        if (Npower == 1)
        {
          break;
        }
        Temploc.Add(Temploc.Multiplied(Tempmatrix));
        Tempmatrix.Multiply(Tempmatrix);
        Npower = Npower / 2;
      }
    }
    else
    {
      gp_Trsf T = Trsf();
      T.Power(N);
      SetTrsf(T);
    }
  }
}

void gp_GTrsf::PreMultiply(const gp_GTrsf& T)
{
  if (Form() == gp_Other || T.Form() == gp_Other)
  {
    shape = gp_Other;
    loc.Multiply(T.matrix);
    loc.Add(T.loc);
    matrix.PreMultiply(T.matrix);
  }
  else
  {
    gp_Trsf T1 = Trsf();
    gp_Trsf T2 = T.Trsf();
    T1.PreMultiply(T2);
    matrix = T1.matrix;
    loc    = T1.loc;
    scale  = T1.scale;
    shape  = T1.shape;
  }
}

void gp_GTrsf::SetForm()
{
  double tol = 1.e-12;

  gp_Mat M(matrix);
  double s = M.Determinant();

  if (std::abs(s) < gp::Resolution())
    throw Standard_ConstructionError("gp_GTrsf::SetForm, null determinant");

  if (s > 0)
    s = std::pow(s, 1. / 3.);
  else
    s = -std::pow(-s, 1. / 3.);
  M.Divide(s);

  gp_Mat TM(M);
  TM.Transpose();
  TM.Multiply(M);
  gp_Mat anIdentity;
  anIdentity.SetIdentity();
  TM.Subtract(anIdentity);
  if (shape == gp_Other)
    shape = gp_CompoundTrsf;

  for (int i = 1; i <= 3; i++)
    for (int j = 1; j <= 3; j++)
      if (std::abs(TM.Value(i, j)) > tol)
      {
        shape = gp_Other;
        return;
      }
}

void gp_GTrsf::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, gp_GTrsf)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &matrix)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &loc)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, shape)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, scale)
}
