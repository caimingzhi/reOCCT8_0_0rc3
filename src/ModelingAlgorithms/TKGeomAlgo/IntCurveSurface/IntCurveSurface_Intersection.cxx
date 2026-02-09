#include <IntCurveSurface_Intersection.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <IntCurveSurface_IntersectionSegment.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>
#include <StdFail_NotDone.hpp>

#define PARAMEQUAL(a, b) (std::abs((a) - (b)) < (1e-8))

IntCurveSurface_Intersection::IntCurveSurface_Intersection()
    : done(false),
      myIsParallel(false)
{
}

bool IntCurveSurface_Intersection::IsDone() const
{
  return (done);
}

bool IntCurveSurface_Intersection::IsParallel() const
{
  return (myIsParallel);
}

int IntCurveSurface_Intersection::NbPoints() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lpnt.Length();
}

int IntCurveSurface_Intersection::NbSegments() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lseg.Length();
}

const IntCurveSurface_IntersectionPoint& IntCurveSurface_Intersection::Point(const int N) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lpnt.Value(N);
}

const IntCurveSurface_IntersectionSegment& IntCurveSurface_Intersection::Segment(const int N) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lseg.Value(N);
}

void IntCurveSurface_Intersection::SetValues(const IntCurveSurface_Intersection& Other)
{
  if (Other.done)
  {
    lseg.Clear();
    lpnt.Clear();
    int N = Other.lpnt.Length();
    int i;
    for (i = 1; i <= N; i++)
    {
      lpnt.Append(Other.lpnt.Value(i));
    }
    N = Other.lseg.Length();
    for (i = 1; i <= N; i++)
    {
      lseg.Append(Other.lseg.Value(i));
    }
    done = true;
  }
  else
  {
    done = false;
  }
}

void IntCurveSurface_Intersection::Append(const IntCurveSurface_Intersection& Other,

                                          const double,

                                          const double)
{
  int i, ni;
  if (Other.done)
  {
    ni = Other.lpnt.Length();
    for (i = 1; i <= ni; i++)
    {
      Append(Other.Point(i));
    }
    ni = Other.lseg.Length();
    for (i = 1; i <= ni; i++)
    {
      Append(Other.Segment(i));
    }
  }
}

void IntCurveSurface_Intersection::Append(const IntCurveSurface_IntersectionPoint& OtherPoint)
{
  int                               i, ni;
  double                            anu, anv, anw, u, v, w;
  IntCurveSurface_TransitionOnCurve TrOnCurve, anTrOnCurve;
  gp_Pnt                            P, anP;
  ni = lpnt.Length();
  for (i = 1; i <= ni; i++)
  {
    OtherPoint.Values(P, u, v, w, TrOnCurve);
    lpnt(i).Values(anP, anu, anv, anw, anTrOnCurve);
    if (PARAMEQUAL(u, anu))
    {
      if (PARAMEQUAL(v, anv))
      {
        if (PARAMEQUAL(w, anw))
        {
          if (anTrOnCurve == TrOnCurve)
          {
            return;
          }
        }
      }
    }
  }
  lpnt.Append(OtherPoint);
}

void IntCurveSurface_Intersection::Append(const IntCurveSurface_IntersectionSegment& OtherSegment)
{
  lseg.Append(OtherSegment);
}

void IntCurveSurface_Intersection::ResetFields()
{
  if (done)
  {
    lseg.Clear();
    lpnt.Clear();
    done         = false;
    myIsParallel = false;
  }
}

void IntCurveSurface_Intersection::Dump() const
{
  if (done)
  {
    int i, ni;
    ni = lpnt.Length();
    for (i = 1; i <= ni; i++)
    {
      Point(i).Dump();
    }
    ni = lseg.Length();
    for (i = 1; i <= ni; i++)
    {
      Segment(i).Dump();
    }
  }
  else
  {
    std::cout << " Intersection NotDone" << std::endl;
  }
}
