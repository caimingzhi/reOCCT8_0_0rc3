#include <GeomFill_DiscreteTrihedron.hpp>

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomFill_Frenet.hpp>
#include <gp_Ax2.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <GeomFill_TrihedronLaw.hpp>
#include <gp_Vec.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_DiscreteTrihedron, GeomFill_TrihedronLaw)

static const double TolConf = Precision::Confusion();

GeomFill_DiscreteTrihedron::GeomFill_DiscreteTrihedron()
    : myUseFrenet(false)
{
  myFrenet     = new GeomFill_Frenet();
  myKnots      = new NCollection_HSequence<double>();
  myTrihedrons = new NCollection_HSequence<gp_Ax2>();
}

occ::handle<GeomFill_TrihedronLaw> GeomFill_DiscreteTrihedron::Copy() const
{
  occ::handle<GeomFill_DiscreteTrihedron> copy = new (GeomFill_DiscreteTrihedron)();
  if (!myCurve.IsNull())
    copy->SetCurve(myCurve);
  return copy;
}

bool GeomFill_DiscreteTrihedron::SetCurve(const occ::handle<Adaptor3d_Curve>& C)
{
  GeomFill_TrihedronLaw::SetCurve(C);
  if (!C.IsNull())
  {
    GeomAbs_CurveType type;
    type = C->GetType();
    switch (type)
    {
      case GeomAbs_Circle:
      case GeomAbs_Ellipse:
      case GeomAbs_Hyperbola:
      case GeomAbs_Parabola:
      case GeomAbs_Line:
      {

        myUseFrenet = true;
        myFrenet->SetCurve(C);
        break;
      }
      default:
      {
        myUseFrenet = false;

        Init();
        break;
      }
    }
  }
  return myUseFrenet;
}

void GeomFill_DiscreteTrihedron::Init()
{
  int                        NbIntervals = myTrimmed->NbIntervals(GeomAbs_CN);
  NCollection_Array1<double> Knots(1, NbIntervals + 1);
  myTrimmed->Intervals(Knots, GeomAbs_CN);

  int NbSamples = 10;

  int i, j;
  for (i = 1; i <= NbIntervals; i++)
  {
    double delta = (Knots(i + 1) - Knots(i)) / NbSamples;
    for (j = 0; j < NbSamples; j++)
    {
      double Param = Knots(i) + j * delta;
      myKnots->Append(Param);
    }
  }
  myKnots->Append(Knots(NbIntervals + 1));

  gp_Pnt Origin(0., 0., 0.), Pnt, SubPnt;
  gp_Vec Tangent;
  gp_Dir TangDir;
  double norm;
  for (i = 1; i <= myKnots->Length(); i++)
  {
    double Param = myKnots->Value(i);
    myTrimmed->D1(Param, Pnt, Tangent);
    norm = Tangent.Magnitude();
    if (norm < TolConf)
    {
      double subdelta = (myKnots->Value(i + 1) - myKnots->Value(i)) / NbSamples;
      if (subdelta < Precision::PConfusion())
        subdelta = myKnots->Value(i + 1) - myKnots->Value(i);
      SubPnt = myTrimmed->Value(Param + subdelta);
      Tangent.SetXYZ(SubPnt.XYZ() - Pnt.XYZ());
    }

    TangDir = Tangent;
    Tangent = TangDir;
    if (i == 1)
    {
      gp_Ax2 FirstAxis(Origin, TangDir);
      myTrihedrons->Append(FirstAxis);
    }
    else
    {
      gp_Ax2 LastAxis       = myTrihedrons->Value(myTrihedrons->Length());
      gp_Vec LastTangent    = LastAxis.Direction();
      gp_Vec AxisOfRotation = LastTangent ^ Tangent;
      if (AxisOfRotation.Magnitude() <= gp::Resolution())
      {
        double ScalarProduct = LastTangent * Tangent;
        if (ScalarProduct > 0.)
          myTrihedrons->Append(LastAxis);
        else
        {
          double NewParam = (myKnots->Value(i - 1) + myKnots->Value(i)) / 2.;
          if (NewParam - myKnots->Value(i - 1) < gp::Resolution())
            throw Standard_ConstructionError(
              "GeomFill_DiscreteTrihedron : impassable singularities on path curve");
          myKnots->InsertBefore(i, NewParam);
          i--;
        }
      }
      else
      {
        double theAngle = LastTangent.AngleWithRef(Tangent, AxisOfRotation);
        gp_Ax1 theAxisOfRotation(Origin, AxisOfRotation);
        gp_Ax2 NewAxis = LastAxis.Rotated(theAxisOfRotation, theAngle);
        NewAxis.SetDirection(TangDir);
        myTrihedrons->Append(NewAxis);
      }
    }
  }
}

bool GeomFill_DiscreteTrihedron::D0(const double Param,
                                    gp_Vec&      Tangent,
                                    gp_Vec&      Normal,
                                    gp_Vec&      BiNormal)
{
  if (myUseFrenet)
  {
    myFrenet->D0(Param, Tangent, Normal, BiNormal);
  }
  else
  {

    int              Index  = -1;
    constexpr double TolPar = Precision::PConfusion();

    int    NbSamples = 10;
    gp_Pnt Origin(0., 0., 0.);

    int i;

    int I1, I2;
    I1 = 1;
    I2 = myKnots->Length();
    for (;;)
    {
      i = (I1 + I2) / 2;
      if (Param <= myKnots->Value(i))
        I2 = i;
      else
        I1 = i;
      if (I2 - I1 <= 1)
        break;
    }
    Index = I1;
    if (std::abs(Param - myKnots->Value(I2)) < TolPar)
      Index = I2;

    double PrevParam = myKnots->Value(Index);
    gp_Ax2 PrevAxis  = myTrihedrons->Value(Index);
    gp_Ax2 theAxis;
    if (std::abs(Param - PrevParam) < TolPar)
      theAxis = PrevAxis;
    else
    {
      myTrimmed->D1(Param, myPoint, Tangent);
      double norm = Tangent.Magnitude();
      if (norm < TolConf)
      {
        double subdelta = (myKnots->Value(Index + 1) - Param) / NbSamples;
        if (subdelta < Precision::PConfusion())
          subdelta = myKnots->Value(Index + 1) - Param;
        gp_Pnt SubPnt = myTrimmed->Value(Param + subdelta);
        Tangent.SetXYZ(SubPnt.XYZ() - myPoint.XYZ());
      }

      gp_Dir TangDir(Tangent);
      Tangent               = TangDir;
      gp_Vec PrevTangent    = PrevAxis.Direction();
      gp_Vec AxisOfRotation = PrevTangent ^ Tangent;
      if (AxisOfRotation.Magnitude() <= gp::Resolution())
      {

        theAxis = PrevAxis;
      }
      else
      {
        double theAngle = PrevTangent.AngleWithRef(Tangent, AxisOfRotation);
        gp_Ax1 theAxisOfRotation(Origin, AxisOfRotation);
        theAxis = PrevAxis.Rotated(theAxisOfRotation, theAngle);
      }
      theAxis.SetDirection(TangDir);
    }

    Tangent  = theAxis.Direction();
    Normal   = theAxis.XDirection();
    BiNormal = theAxis.YDirection();
  }
  return true;
}

bool GeomFill_DiscreteTrihedron::D1(const double Param,
                                    gp_Vec&      Tangent,
                                    gp_Vec&      DTangent,
                                    gp_Vec&      Normal,
                                    gp_Vec&      DNormal,
                                    gp_Vec&      BiNormal,
                                    gp_Vec&      DBiNormal)
{
  if (myUseFrenet)
  {
    myFrenet->D1(Param, Tangent, DTangent, Normal, DNormal, BiNormal, DBiNormal);
  }
  else
  {
    D0(Param, Tangent, Normal, BiNormal);

    DTangent.SetCoord(0., 0., 0.);
    DNormal.SetCoord(0., 0., 0.);
    DBiNormal.SetCoord(0., 0., 0.);
  }
  return true;
}

bool GeomFill_DiscreteTrihedron::D2(const double Param,
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
  if (myUseFrenet)
  {
    myFrenet->D2(Param,
                 Tangent,
                 DTangent,
                 D2Tangent,
                 Normal,
                 DNormal,
                 D2Normal,
                 BiNormal,
                 DBiNormal,
                 D2BiNormal);
  }
  else
  {
    D0(Param, Tangent, Normal, BiNormal);

    DTangent.SetCoord(0., 0., 0.);
    DNormal.SetCoord(0., 0., 0.);
    DBiNormal.SetCoord(0., 0., 0.);
    D2Tangent.SetCoord(0., 0., 0.);
    D2Normal.SetCoord(0., 0., 0.);
    D2BiNormal.SetCoord(0., 0., 0.);
  }
  return true;
}

int GeomFill_DiscreteTrihedron::NbIntervals(const GeomAbs_Shape) const
{
  return (myTrimmed->NbIntervals(GeomAbs_CN));
}

void GeomFill_DiscreteTrihedron::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape) const
{
  myTrimmed->Intervals(T, GeomAbs_CN);
}

void GeomFill_DiscreteTrihedron::GetAverageLaw(gp_Vec& ATangent, gp_Vec& ANormal, gp_Vec& ABiNormal)
{
  int    Num = 20;
  gp_Vec T, N, BN;
  ATangent    = gp_Vec(0, 0, 0);
  ANormal     = gp_Vec(0, 0, 0);
  ABiNormal   = gp_Vec(0, 0, 0);
  double Step = (myTrimmed->LastParameter() - myTrimmed->FirstParameter()) / Num;
  double Param;
  for (int i = 0; i <= Num; i++)
  {
    Param = myTrimmed->FirstParameter() + i * Step;
    if (Param > myTrimmed->LastParameter())
      Param = myTrimmed->LastParameter();
    D0(Param, T, N, BN);
    ATangent += T;
    ANormal += N;
    ABiNormal += BN;
  }
  ATangent /= Num + 1;
  ANormal /= Num + 1;

  ATangent.Normalize();
  ABiNormal = ATangent.Crossed(ANormal).Normalized();
  ANormal   = ABiNormal.Crossed(ATangent);
}

bool GeomFill_DiscreteTrihedron::IsConstant() const
{
  return (myCurve->GetType() == GeomAbs_Line);
}

bool GeomFill_DiscreteTrihedron::IsOnlyBy3dCurve() const
{
  return true;
}
