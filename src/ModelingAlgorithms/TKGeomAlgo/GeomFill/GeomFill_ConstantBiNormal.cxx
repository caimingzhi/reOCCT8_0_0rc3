#include <Adaptor3d_Curve.hpp>
#include <GeomFill_ConstantBiNormal.hpp>
#include <GeomFill_Frenet.hpp>
#include <GeomFill_TrihedronLaw.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_ConstantBiNormal, GeomFill_TrihedronLaw)

static gp_Vec FDeriv(const gp_Vec& F, const gp_Vec& DF)
{
  double Norma  = F.Magnitude();
  gp_Vec Result = (DF - F * (F * DF) / (Norma * Norma)) / Norma;
  return Result;
}

static gp_Vec DDeriv(const gp_Vec& F, const gp_Vec& DF, const gp_Vec& D2F)
{
  double Norma = F.Magnitude();
  gp_Vec Result =
    (D2F - 2 * DF * (F * DF) / (Norma * Norma)) / Norma
    - F
        * ((DF.SquareMagnitude() + F * D2F - 3 * (F * DF) * (F * DF) / (Norma * Norma))
           / (Norma * Norma * Norma));
  return Result;
}

GeomFill_ConstantBiNormal::GeomFill_ConstantBiNormal(const gp_Dir& BiNormal)
    : BN(BiNormal)
{
  frenet = new GeomFill_Frenet();
}

occ::handle<GeomFill_TrihedronLaw> GeomFill_ConstantBiNormal::Copy() const
{
  occ::handle<GeomFill_TrihedronLaw> copy = new GeomFill_ConstantBiNormal(gp_Dir(BN));
  if (!myCurve.IsNull())
    copy->SetCurve(myCurve);
  return copy;
}

bool GeomFill_ConstantBiNormal::SetCurve(const occ::handle<Adaptor3d_Curve>& C)
{
  bool isOK = false;
  GeomFill_TrihedronLaw::SetCurve(C);
  if (!C.IsNull())
  {
    isOK = frenet->SetCurve(C);
  }
  return isOK;
}

bool GeomFill_ConstantBiNormal::D0(const double Param,
                                   gp_Vec&      Tangent,
                                   gp_Vec&      Normal,
                                   gp_Vec&      BiNormal)
{

  frenet->D0(Param, Tangent, Normal, BiNormal);
  BiNormal = BN;
  if (BiNormal.Crossed(Tangent).Magnitude() > Precision::Confusion())
  {
    Normal  = BiNormal.Crossed(Tangent).Normalized();
    Tangent = Normal.Crossed(BiNormal);
  }
  else
  {
    Tangent = Normal.Crossed(BiNormal).Normalized();
    Normal  = BiNormal.Crossed(Tangent);
  }

  return true;
}

bool GeomFill_ConstantBiNormal::D1(const double Param,
                                   gp_Vec&      Tangent,
                                   gp_Vec&      DTangent,
                                   gp_Vec&      Normal,
                                   gp_Vec&      DNormal,
                                   gp_Vec&      BiNormal,
                                   gp_Vec&      DBiNormal)
{
  gp_Vec F, DF;
  frenet->D1(Param, Tangent, DTangent, Normal, DNormal, BiNormal, DBiNormal);
  BiNormal  = BN;
  DBiNormal = gp_Vec(0, 0, 0);
  if (BiNormal.Crossed(Tangent).Magnitude() > Precision::Confusion())
  {
    F       = BiNormal.Crossed(Tangent);
    DF      = BiNormal.Crossed(DTangent);
    Normal  = F.Normalized();
    DNormal = FDeriv(F, DF);

    Tangent  = Normal.Crossed(BiNormal);
    DTangent = DNormal.Crossed(BiNormal);
  }
  else
  {
    F        = Normal.Crossed(BiNormal);
    DF       = DNormal.Crossed(BiNormal);
    Tangent  = F.Normalized();
    DTangent = FDeriv(F, DF);

    Normal  = BiNormal.Crossed(Tangent);
    DNormal = BiNormal.Crossed(DTangent);
  }

  return true;
}

bool GeomFill_ConstantBiNormal::D2(const double Param,
                                   gp_Vec&      Tangent,
                                   gp_Vec&      DTangent,
                                   gp_Vec&      D2Tangent,
                                   gp_Vec&      Normal,
                                   gp_Vec&      DNormal,
                                   gp_Vec&      D2Normal,
                                   gp_Vec&      BiNormal,
                                   gp_Vec&      DBiNormal,
                                   gp_Vec&      D2BiNormal)
{
  gp_Vec F, DF, D2F;
  frenet->D2(Param,
             Tangent,
             DTangent,
             D2Tangent,
             Normal,
             DNormal,
             D2Normal,
             BiNormal,
             DBiNormal,
             D2BiNormal);
  BiNormal   = BN;
  DBiNormal  = gp_Vec(0, 0, 0);
  D2BiNormal = gp_Vec(0, 0, 0);
  if (BiNormal.Crossed(Tangent).Magnitude() > Precision::Confusion())
  {
    F        = BiNormal.Crossed(Tangent);
    DF       = BiNormal.Crossed(DTangent);
    D2F      = BiNormal.Crossed(D2Tangent);
    Normal   = F.Normalized();
    DNormal  = FDeriv(F, DF);
    D2Normal = DDeriv(F, DF, D2F);

    Tangent   = Normal.Crossed(BiNormal);
    DTangent  = DNormal.Crossed(BiNormal);
    D2Tangent = D2Normal.Crossed(BiNormal);
  }
  else
  {
    F         = Normal.Crossed(BiNormal);
    DF        = DNormal.Crossed(BiNormal);
    D2F       = D2Normal.Crossed(BiNormal);
    Tangent   = F.Normalized();
    DTangent  = FDeriv(F, DF);
    D2Tangent = DDeriv(F, DF, D2F);

    Normal   = BiNormal.Crossed(Tangent);
    DNormal  = BiNormal.Crossed(DTangent);
    D2Normal = BiNormal.Crossed(D2Tangent);
  }

  return true;
}

int GeomFill_ConstantBiNormal::NbIntervals(const GeomAbs_Shape S) const
{
  return frenet->NbIntervals(S);
}

void GeomFill_ConstantBiNormal::Intervals(NCollection_Array1<double>& T,
                                          const GeomAbs_Shape         S) const
{
  frenet->Intervals(T, S);
}

void GeomFill_ConstantBiNormal::GetAverageLaw(gp_Vec& ATangent, gp_Vec& ANormal, gp_Vec& ABiNormal)
{
  frenet->GetAverageLaw(ATangent, ANormal, ABiNormal);
  ABiNormal = BN;
  if (ABiNormal.Crossed(ATangent).Magnitude() > Precision::Confusion())
  {
    ANormal  = ABiNormal.Crossed(ATangent).Normalized();
    ATangent = ANormal.Crossed(ABiNormal);
  }
  else
  {
    ATangent = ANormal.Crossed(ABiNormal).Normalized();
    ANormal  = ABiNormal.Crossed(ATangent);
  }
}

bool GeomFill_ConstantBiNormal::IsConstant() const
{
  return frenet->IsConstant();
}

bool GeomFill_ConstantBiNormal::IsOnlyBy3dCurve() const
{
  GeomAbs_CurveType TheType = myCurve->GetType();
  gp_Ax1            TheAxe;

  switch (TheType)
  {
    case GeomAbs_Circle:
    {
      TheAxe = myCurve->Circle().Axis();
      break;
    }
    case GeomAbs_Ellipse:
    {
      TheAxe = myCurve->Ellipse().Axis();
      break;
    }
    case GeomAbs_Hyperbola:
    {
      TheAxe = myCurve->Hyperbola().Axis();
      break;
    }
    case GeomAbs_Parabola:
    {
      TheAxe = myCurve->Parabola().Axis();
      break;
    }
    case GeomAbs_Line:
    {
      gp_Vec V;
      V.SetXYZ(myCurve->Line().Direction().XYZ());
      return V.IsNormal(BN, Precision::Angular());
    }
    default:
      return false;
  }

  gp_Vec V;
  V.SetXYZ(TheAxe.Direction().XYZ());
  return V.IsParallel(BN, Precision::Angular());
}
