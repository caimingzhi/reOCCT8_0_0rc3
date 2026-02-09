#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <IntRes2d_IntersectionPoint.hpp>

class IntRes2d_IntersectionSegment
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntRes2d_IntersectionSegment();

  IntRes2d_IntersectionSegment(const IntRes2d_IntersectionPoint& P1,
                               const IntRes2d_IntersectionPoint& P2,
                               const bool                        Oppos,
                               const bool                        ReverseFlag);

  IntRes2d_IntersectionSegment(const IntRes2d_IntersectionPoint& P,
                               const bool                        First,
                               const bool                        Oppos,
                               const bool                        ReverseFlag);

  IntRes2d_IntersectionSegment(const bool Oppos);

  bool IsOpposite() const;

  bool HasFirstPoint() const;

  const IntRes2d_IntersectionPoint& FirstPoint() const;

  bool HasLastPoint() const;

  const IntRes2d_IntersectionPoint& LastPoint() const;

private:
  bool                       oppos;
  bool                       first;
  bool                       last;
  IntRes2d_IntersectionPoint ptfirst;
  IntRes2d_IntersectionPoint ptlast;
};

#include <Standard_DomainError.hpp>

inline IntRes2d_IntersectionSegment::IntRes2d_IntersectionSegment(
  const IntRes2d_IntersectionPoint& P1,
  const IntRes2d_IntersectionPoint& P2,
  const bool                        Oppos,
  const bool                        ReverseFlag)
    :

      oppos(Oppos),
      first(true),
      last(true),
      ptfirst(P1),
      ptlast(P2)
{
  if (ReverseFlag)
  {
    if (Oppos)
    {
      ptfirst = P2;
      ptlast  = P1;
    }
  }
}

inline IntRes2d_IntersectionSegment::IntRes2d_IntersectionSegment(
  const IntRes2d_IntersectionPoint& P,
  const bool                        First,
  const bool                        Oppos,
  const bool                        ReverseFlag)
    :

      oppos(Oppos)

{
  if (ReverseFlag && Oppos)
  {
    if (First)
    {
      first  = false;
      last   = true;
      ptlast = P;
    }
    else
    {
      first   = true;
      last    = false;
      ptfirst = P;
    }
  }
  else
  {
    if (First)
    {
      first   = true;
      last    = false;
      ptfirst = P;
    }
    else
    {
      first  = false;
      last   = true;
      ptlast = P;
    }
  }
}

inline IntRes2d_IntersectionSegment::IntRes2d_IntersectionSegment(const bool Oppos)
    : oppos(Oppos),
      first(false),
      last(false)

{
}

inline bool IntRes2d_IntersectionSegment::IsOpposite() const
{
  return oppos;
}

inline bool IntRes2d_IntersectionSegment::HasFirstPoint() const
{
  return first;
}

inline bool IntRes2d_IntersectionSegment::HasLastPoint() const
{
  return last;
}

inline const IntRes2d_IntersectionPoint& IntRes2d_IntersectionSegment::FirstPoint() const
{

  if (!first)
  {
    throw Standard_DomainError();
  }
  return ptfirst;
}

inline const IntRes2d_IntersectionPoint& IntRes2d_IntersectionSegment::LastPoint() const
{

  if (!last)
  {
    throw Standard_DomainError();
  }
  return ptlast;
}
