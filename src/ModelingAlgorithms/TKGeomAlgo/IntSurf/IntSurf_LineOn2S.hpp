#pragma once

#include <Standard.hpp>

#include <Bnd_Box.hpp>
#include <Bnd_Box2d.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Transient.hpp>
#include <IntSurf_Allocator.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
class IntSurf_PntOn2S;

class IntSurf_LineOn2S : public Standard_Transient
{

public:
  Standard_EXPORT IntSurf_LineOn2S(const IntSurf_Allocator& theAllocator = nullptr);

  Standard_EXPORT void Add(const IntSurf_PntOn2S& P);

  int NbPoints() const;

  const IntSurf_PntOn2S& Value(const int Index) const;

  void Reverse();

  Standard_EXPORT occ::handle<IntSurf_LineOn2S> Split(const int Index);

  void Value(const int Index, const IntSurf_PntOn2S& P);

  Standard_EXPORT void SetPoint(const int Index, const gp_Pnt& thePnt);

  Standard_EXPORT void SetUV(const int Index, const bool OnFirst, const double U, const double V);

  void Clear();

  Standard_EXPORT void InsertBefore(const int I, const IntSurf_PntOn2S& P);

  Standard_EXPORT void RemovePoint(const int I);

  Standard_EXPORT bool IsOutSurf1Box(const gp_Pnt2d& theP);

  Standard_EXPORT bool IsOutSurf2Box(const gp_Pnt2d& theP);

  Standard_EXPORT bool IsOutBox(const gp_Pnt& theP);

  DEFINE_STANDARD_RTTIEXT(IntSurf_LineOn2S, Standard_Transient)

private:
  NCollection_Sequence<IntSurf_PntOn2S> mySeq;
  Bnd_Box2d                             myBuv1;
  Bnd_Box2d                             myBuv2;
  Bnd_Box                               myBxyz;
};

#include <IntSurf_PntOn2S.hpp>

inline int IntSurf_LineOn2S::NbPoints() const
{

  return mySeq.Length();
}

inline void IntSurf_LineOn2S::Reverse()
{
  mySeq.Reverse();
}

inline const IntSurf_PntOn2S& IntSurf_LineOn2S::Value(const int Index) const
{
  return mySeq(Index);
}

inline void IntSurf_LineOn2S::Value(const int Index, const IntSurf_PntOn2S& P)
{
  mySeq(Index) = P;
}

inline void IntSurf_LineOn2S::SetPoint(const int Index, const gp_Pnt& thePnt)
{
  mySeq(Index).SetValue(thePnt);
}

inline void IntSurf_LineOn2S::Clear()
{
  mySeq.Clear();
  myBuv1.SetWhole();
  myBuv2.SetWhole();
  myBxyz.SetWhole();
}
