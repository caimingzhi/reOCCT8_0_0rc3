#pragma once

#include <Blend_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <BRepBlend_Extremity.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

class Blend_Point;

class BRepBlend_Line : public Standard_Transient
{

public:
  Standard_EXPORT BRepBlend_Line();

  Standard_EXPORT void Clear();

  void Append(const Blend_Point& P);

  void Prepend(const Blend_Point& P);

  void InsertBefore(const int Index, const Blend_Point& P);

  void Remove(const int FromIndex, const int ToIndex);

  Standard_EXPORT void Set(const IntSurf_TypeTrans TranS1, const IntSurf_TypeTrans TranS2);

  Standard_EXPORT void Set(const IntSurf_TypeTrans Trans);

  void SetStartPoints(const BRepBlend_Extremity& StartPt1, const BRepBlend_Extremity& StartPt2);

  void SetEndPoints(const BRepBlend_Extremity& EndPt1, const BRepBlend_Extremity& EndPt2);

  int NbPoints() const;

  const Blend_Point& Point(const int Index) const;

  IntSurf_TypeTrans TransitionOnS1() const;

  IntSurf_TypeTrans TransitionOnS2() const;

  const BRepBlend_Extremity& StartPointOnFirst() const;

  const BRepBlend_Extremity& StartPointOnSecond() const;

  const BRepBlend_Extremity& EndPointOnFirst() const;

  const BRepBlend_Extremity& EndPointOnSecond() const;

  IntSurf_TypeTrans TransitionOnS() const;

  DEFINE_STANDARD_RTTIEXT(BRepBlend_Line, Standard_Transient)

private:
  NCollection_Sequence<Blend_Point> seqpt;
  IntSurf_TypeTrans                 tras1;
  IntSurf_TypeTrans                 tras2;
  BRepBlend_Extremity               stp1;
  BRepBlend_Extremity               stp2;
  BRepBlend_Extremity               endp1;
  BRepBlend_Extremity               endp2;
  bool                              hass1;
  bool                              hass2;
};

#include <Blend_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_DomainError.hpp>

inline void BRepBlend_Line::Append(const Blend_Point& P)
{
  seqpt.Append(P);
}

inline void BRepBlend_Line::Prepend(const Blend_Point& P)
{
  seqpt.Prepend(P);
}

inline void BRepBlend_Line::InsertBefore(const int Index, const Blend_Point& P)
{
  seqpt.InsertBefore(Index, P);
}

inline void BRepBlend_Line::Remove(const int FromIndex, const int ToIndex)
{
  seqpt.Remove(FromIndex, ToIndex);
}

inline void BRepBlend_Line::SetStartPoints(const BRepBlend_Extremity& StartPtOnS1,
                                           const BRepBlend_Extremity& StartPtOnS2)

{
  stp1 = StartPtOnS1;
  stp2 = StartPtOnS2;
}

inline void BRepBlend_Line::SetEndPoints(const BRepBlend_Extremity& EndPtOnS1,
                                         const BRepBlend_Extremity& EndPtOnS2)

{
  endp1 = EndPtOnS1;
  endp2 = EndPtOnS2;
}

inline int BRepBlend_Line::NbPoints() const
{
  return seqpt.Length();
}

inline const Blend_Point& BRepBlend_Line::Point(const int Index) const
{
  return seqpt(Index);
}

inline IntSurf_TypeTrans BRepBlend_Line::TransitionOnS1() const
{
  if (!hass1)
  {
    throw Standard_DomainError();
  }
  return tras1;
}

inline IntSurf_TypeTrans BRepBlend_Line::TransitionOnS2() const
{
  if (!hass2)
  {
    throw Standard_DomainError();
  }
  return tras2;
}

inline const BRepBlend_Extremity& BRepBlend_Line::StartPointOnFirst() const
{
  return stp1;
}

inline const BRepBlend_Extremity& BRepBlend_Line::StartPointOnSecond() const
{
  return stp2;
}

inline const BRepBlend_Extremity& BRepBlend_Line::EndPointOnFirst() const
{
  return endp1;
}

inline const BRepBlend_Extremity& BRepBlend_Line::EndPointOnSecond() const
{
  return endp2;
}

inline IntSurf_TypeTrans BRepBlend_Line::TransitionOnS() const
{
  if (!hass1)
  {
    throw Standard_DomainError();
  }
  return tras1;
}
