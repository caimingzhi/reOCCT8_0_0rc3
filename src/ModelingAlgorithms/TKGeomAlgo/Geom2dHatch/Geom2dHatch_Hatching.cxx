#include <Geom2dHatch_Hatching.hpp>
#include <gp_Pnt2d.hpp>
#include <HatchGen_Domain.hpp>
#include <HatchGen_PointOnElement.hpp>
#include <HatchGen_PointOnHatching.hpp>

#define RAISE_IF_NOSUCHOBJECT 0

#include <Precision.hpp>

Geom2dHatch_Hatching::Geom2dHatch_Hatching()
    : myTrimDone(false),
      myTrimFailed(false),
      myIsDone(false),
      myStatus(HatchGen_NoProblem)
{
}

Geom2dHatch_Hatching::Geom2dHatch_Hatching(const Geom2dAdaptor_Curve& Curve)
    : myCurve(Curve),
      myTrimDone(false),
      myTrimFailed(false),
      myIsDone(false),
      myStatus(HatchGen_NoProblem)
{
}

const Geom2dAdaptor_Curve& Geom2dHatch_Hatching::Curve() const
{
  return myCurve;
}

Geom2dAdaptor_Curve& Geom2dHatch_Hatching::ChangeCurve()
{
  return myCurve;
}

void Geom2dHatch_Hatching::TrimDone(const bool Flag)
{
  myTrimDone = Flag;
}

bool Geom2dHatch_Hatching::TrimDone() const
{
  return myTrimDone;
}

void Geom2dHatch_Hatching::TrimFailed(const bool Flag)
{
  myTrimFailed = Flag;
  if (myTrimFailed)
    myStatus = HatchGen_TrimFailure;
}

bool Geom2dHatch_Hatching::TrimFailed() const
{
  return myTrimFailed;
}

void Geom2dHatch_Hatching::IsDone(const bool Flag)
{
  myIsDone = Flag;
}

bool Geom2dHatch_Hatching::IsDone() const
{
  return myIsDone;
}

void Geom2dHatch_Hatching::Status(const HatchGen_ErrorStatus theStatus)
{
  myStatus = theStatus;
}

HatchGen_ErrorStatus Geom2dHatch_Hatching::Status() const
{
  return myStatus;
}

void Geom2dHatch_Hatching::AddPoint(const HatchGen_PointOnHatching& Point, const double Confusion)
{
  int NbPoints = myPoints.Length();

  int IPntH;
  for (IPntH = 1; IPntH <= NbPoints; IPntH++)
  {
    const HatchGen_PointOnHatching& PntH = myPoints.Value(IPntH);
    if (!PntH.IsLower(Point, Confusion))
      break;
  }
  if (IPntH > NbPoints)
  {
    myPoints.Append(Point);
  }
  else
  {
    HatchGen_PointOnHatching& PntH = myPoints.ChangeValue(IPntH);
    if (PntH.IsGreater(Point, Confusion))
    {
      myPoints.InsertBefore(IPntH, Point);
    }
    else
    {
      for (int IPntE = 1; IPntE <= Point.NbPoints(); IPntE++)
      {
        const HatchGen_PointOnElement& PntE = Point.Point(IPntE);
        PntH.AddPoint(PntE, Confusion);
      }
    }
  }
  if (myIsDone)
    ClrDomains();
}

int Geom2dHatch_Hatching::NbPoints() const
{
  return myPoints.Length();
}

const HatchGen_PointOnHatching& Geom2dHatch_Hatching::Point(const int Index) const
{
#if RAISE_IF_NOSUCHOBJECT
  int NbPoints = myPoints.Length();
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints, "");
#endif
  const HatchGen_PointOnHatching& Point = myPoints.Value(Index);
  return Point;
}

HatchGen_PointOnHatching& Geom2dHatch_Hatching::ChangePoint(const int Index)
{
#if RAISE_IF_NOSUCHOBJECT
  int NbPoints = myPoints.Length();
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints, "");
#endif
  HatchGen_PointOnHatching& Point = myPoints.ChangeValue(Index);
  return Point;
}

void Geom2dHatch_Hatching::RemPoint(const int Index)
{
#if RAISE_IF_NOSUCHOBJECT
  int NbPoints = myPoints.Length();
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints, "");
#endif
  if (myIsDone)
    ClrDomains();
  myPoints.Remove(Index);
}

void Geom2dHatch_Hatching::ClrPoints()
{
  if (myIsDone)
    ClrDomains();
  for (int IPntH = 1; IPntH <= myPoints.Length(); IPntH++)
  {
    HatchGen_PointOnHatching& Point = myPoints.ChangeValue(IPntH);
    Point.ClrPoints();
  }
  myPoints.Clear();
  myTrimDone   = false;
  myTrimFailed = false;
}

void Geom2dHatch_Hatching::AddDomain(const HatchGen_Domain& Domain)
{
  myDomains.Append(Domain);
}

int Geom2dHatch_Hatching::NbDomains() const
{
  return myDomains.Length();
}

const HatchGen_Domain& Geom2dHatch_Hatching::Domain(const int Index) const
{
#if RAISE_IF_NOSUCHOBJECT
  int NbDomains = myDomains.Length();
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbDomains, "");
#endif
  const HatchGen_Domain& Domain = myDomains.Value(Index);
  return Domain;
}

void Geom2dHatch_Hatching::RemDomain(const int Index)
{
#if RAISE_IF_NOSUCHOBJECT
  int NbDomains = myDomains.Length();
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbDomains, "");
#endif
  myDomains.Remove(Index);
}

void Geom2dHatch_Hatching::ClrDomains()
{
  myDomains.Clear();
  myIsDone = false;
}

gp_Pnt2d Geom2dHatch_Hatching::ClassificationPoint() const
{
  double t, a, b;
  a = myCurve.FirstParameter();
  b = myCurve.LastParameter();
  if (b >= Precision::Infinite())
  {
    if (a <= -Precision::Infinite())
    {
      t = 0;
    }
    else
    {
      t = a;
    }
  }
  else
  {
    t = b;
  }
  return (myCurve.Value(t));
}
