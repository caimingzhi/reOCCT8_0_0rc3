#include <ChFiDS_ChamfSpine.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ChFiDS_ChamfSpine, ChFiDS_Spine)

ChFiDS_ChamfSpine::ChFiDS_ChamfSpine()
    : d1(0.0),
      d2(0.0),
      angle(0.0),
      mChamf(ChFiDS_Sym)
{
  myMode = ChFiDS_ClassicChamfer;
}

ChFiDS_ChamfSpine::ChFiDS_ChamfSpine(const double Tol)
    : ChFiDS_Spine(Tol),
      d1(0.0),
      d2(0.0),
      angle(0.0),
      mChamf(ChFiDS_Sym)
{
  myMode = ChFiDS_ClassicChamfer;
}

void ChFiDS_ChamfSpine::GetDist(double& Dis) const
{
  if (mChamf != ChFiDS_Sym)
  {
    throw Standard_Failure("Chamfer is not symmetric");
  }
  Dis = d1;
}

void ChFiDS_ChamfSpine::SetDist(const double Dis)
{

  mChamf = ChFiDS_Sym;
  d1     = Dis;
}

void ChFiDS_ChamfSpine::Dists(double& Dis1, double& Dis2) const
{
  if (mChamf != ChFiDS_TwoDist)
    throw Standard_Failure("Chamfer is not a Two Dists Chamfer");
  Dis1 = d1;
  Dis2 = d2;
}

void ChFiDS_ChamfSpine::SetDists(const double Dis1, const double Dis2)
{

  mChamf = ChFiDS_TwoDist;
  d1     = Dis1;
  d2     = Dis2;
}

void ChFiDS_ChamfSpine::GetDistAngle(double& Dis, double& Angle) const

{
  if (mChamf != ChFiDS_DistAngle)
    throw Standard_Failure("Chamfer is not a Two Dists Chamfer");
  Dis   = d1;
  Angle = angle;
}

void ChFiDS_ChamfSpine::SetDistAngle(const double Dis, const double Angle)

{

  mChamf = ChFiDS_DistAngle;
  d1     = Dis;
  angle  = Angle;
}

void ChFiDS_ChamfSpine::SetMode(const ChFiDS_ChamfMode theMode)
{
  myMode = theMode;
}

ChFiDS_ChamfMethod ChFiDS_ChamfSpine::IsChamfer() const
{

  return mChamf;
}
