#include <HatchGen_PointOnHatching.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>

#define RAISE_IF_NOSUCHOBJECT 0

HatchGen_PointOnHatching::HatchGen_PointOnHatching()

  = default;

HatchGen_PointOnHatching::HatchGen_PointOnHatching(const IntRes2d_IntersectionPoint& Point)
{
  myIndex = 0;
  myParam = Point.ParamOnFirst();
  switch (Point.TransitionOfFirst().PositionOnCurve())
  {
    case IntRes2d_Head:
      myPosit = TopAbs_FORWARD;
      break;
    case IntRes2d_Middle:
      myPosit = TopAbs_INTERNAL;
      break;
    case IntRes2d_End:
      myPosit = TopAbs_REVERSED;
      break;
  }
  myBefore = TopAbs_UNKNOWN;
  myAfter  = TopAbs_UNKNOWN;
  mySegBeg = false;
  mySegEnd = false;
  myPoints.Clear();
}

void HatchGen_PointOnHatching::AddPoint(const HatchGen_PointOnElement& Point,
                                        const double                   Confusion)
{
  int NbPnt = myPoints.Length();

  int IPnt;
  for (IPnt = 1; IPnt <= NbPnt && myPoints(IPnt).IsDifferent(Point, Confusion); IPnt++)
    ;
  if (IPnt > NbPnt)
    myPoints.Append(Point);
}

int HatchGen_PointOnHatching::NbPoints() const
{
  return myPoints.Length();
}

const HatchGen_PointOnElement& HatchGen_PointOnHatching::Point(const int Index) const
{
#if RAISE_IF_NOSUCHOBJECT
  int NbPnt = myPoints.Length();
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPnt, "");
#endif
  const HatchGen_PointOnElement& Point = myPoints.Value(Index);
  return Point;
}

void HatchGen_PointOnHatching::RemPoint(const int Index)
{
#if RAISE_IF_NOSUCHOBJECT
  int NbPnt = myPoints.Length();
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPnt, "");
#endif
  myPoints.Remove(Index);
}

void HatchGen_PointOnHatching::ClrPoints()
{
  myPoints.Clear();
}

bool HatchGen_PointOnHatching::IsLower(const HatchGen_PointOnHatching& Point,
                                       const double                    Confusion) const
{
  return (Point.myParam - myParam > Confusion);
}

bool HatchGen_PointOnHatching::IsEqual(const HatchGen_PointOnHatching& Point,
                                       const double                    Confusion) const
{
  return (std::abs(Point.myParam - myParam) <= Confusion);
}

bool HatchGen_PointOnHatching::IsGreater(const HatchGen_PointOnHatching& Point,
                                         const double                    Confusion) const
{
  return (myParam - Point.myParam > Confusion);
}

void HatchGen_PointOnHatching::Dump(const int Index) const
{
  std::cout << "--- Point on hatching ";
  if (Index > 0)
  {
    std::cout << "# " << std::setw(3) << Index << " ";
  }
  else
  {
    std::cout << "------";
  }
  std::cout << "------------------" << std::endl;

  std::cout << "    Index of the hatching = " << myIndex << std::endl;
  std::cout << "    Parameter on hatching = " << myParam << std::endl;
  std::cout << "    Position  on hatching = ";
  switch (myPosit)
  {
    case TopAbs_FORWARD:
      std::cout << "FORWARD  (i.e. BEGIN  )";
      break;
    case TopAbs_INTERNAL:
      std::cout << "INTERNAL (i.e. MIDDLE )";
      break;
    case TopAbs_REVERSED:
      std::cout << "REVERSED (i.e. END    )";
      break;
    case TopAbs_EXTERNAL:
      std::cout << "EXTERNAL (i.e. UNKNOWN)";
      break;
  }
  std::cout << std::endl;
  std::cout << "    State Before          = ";
  switch (myBefore)
  {
    case TopAbs_IN:
      std::cout << "IN";
      break;
    case TopAbs_OUT:
      std::cout << "OUT";
      break;
    case TopAbs_ON:
      std::cout << "ON";
      break;
    case TopAbs_UNKNOWN:
      std::cout << "UNKNOWN";
      break;
  }
  std::cout << std::endl;
  std::cout << "    State After           = ";
  switch (myAfter)
  {
    case TopAbs_IN:
      std::cout << "IN";
      break;
    case TopAbs_OUT:
      std::cout << "OUT";
      break;
    case TopAbs_ON:
      std::cout << "ON";
      break;
    case TopAbs_UNKNOWN:
      std::cout << "UNKNOWN";
      break;
  }
  std::cout << std::endl;
  std::cout << "    Beginning of segment  = " << (mySegBeg ? "TRUE" : "FALSE") << std::endl;
  std::cout << "    End       of segment  = " << (mySegEnd ? "TRUE" : "FALSE") << std::endl;

  int NbPnt = myPoints.Length();
  if (NbPnt == 0)
  {
    std::cout << "    No points on element" << std::endl;
  }
  else
  {
    std::cout << "    Contains " << NbPnt << " points on element" << std::endl;
    for (int IPnt = 1; IPnt <= NbPnt; IPnt++)
    {
      const HatchGen_PointOnElement& Point = myPoints.Value(IPnt);
      Point.Dump(IPnt);
    }
  }

  std::cout << "----------------------------------------------" << std::endl;
}
