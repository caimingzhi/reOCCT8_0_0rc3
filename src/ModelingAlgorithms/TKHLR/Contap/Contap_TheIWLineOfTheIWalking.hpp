#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IntSurf_Couple.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <IntSurf_PathPoint.hpp>
#include <gp_Vec.hpp>
#include <Standard_Transient.hpp>
#include <IntSurf_Allocator.hpp>
#include <IntSurf_LineOn2S.hpp>
class Standard_OutOfRange;
class Standard_DomainError;
class IntSurf_PathPoint;
class IntSurf_PntOn2S;
class gp_Vec;

class Contap_TheIWLineOfTheIWalking : public Standard_Transient
{

public:
  Standard_EXPORT Contap_TheIWLineOfTheIWalking(const IntSurf_Allocator& theAllocator = nullptr);

  //! reverse the points in the line. Hasfirst, HasLast are kept.
  Standard_EXPORT void Reverse();

  //! Cut the line at the point of rank Index.
  void Cut(const int Index);

  //! Add a point in the line.
  void AddPoint(const IntSurf_PntOn2S& P);

  void AddStatusFirst(const bool Closed, const bool HasFirst);

  void AddStatusFirst(const bool               Closed,
                      const bool               HasLast,
                      const int                Index,
                      const IntSurf_PathPoint& P);

  void AddStatusFirstLast(const bool Closed, const bool HasFirst, const bool HasLast);

  void AddStatusLast(const bool HasLast);

  void AddStatusLast(const bool HasLast, const int Index, const IntSurf_PathPoint& P);

  //! associate the index of the point on the line with the index of the point
  //! passing through the starting iterator
  void AddIndexPassing(const int Index);

  void SetTangentVector(const gp_Vec& V, const int Index);

  void SetTangencyAtBegining(const bool IsTangent);

  void SetTangencyAtEnd(const bool IsTangent);

  //! Returns the number of points of the line (including first
  //! point and end point : see HasLastPoint and HasFirstPoint).
  int NbPoints() const;

  //! Returns the point of range Index.
  //! If index <= 0 or Index > NbPoints, an exception is raised.
  const IntSurf_PntOn2S& Value(const int Index) const;

  //! Returns the LineOn2S contained in the walking line.
  const occ::handle<IntSurf_LineOn2S>& Line() const;

  //! Returns True if the line is closed.
  bool IsClosed() const;

  //! Returns True if the first point of the line is a
  //! marching point. when is HasFirstPoint==False ,the line
  //! begins on the natural bound of the surface. The line can
  //! be too long
  bool HasFirstPoint() const;

  //! Returns True if the end point of the line is a
  //! marching point (Point from IntWS).
  //! when is HasFirstPoint==False the line ends
  //! on the natural bound of the surface. The line can be
  //! too long.
  bool HasLastPoint() const;

  //! Returns the first point of the line when it is a
  //! marching point.
  //! An exception is raised if HasFirstPoint returns False.
  const IntSurf_PathPoint& FirstPoint() const;

  //! Returns the Index of first point of the line when it is a
  //! marching point. This index is the index in the
  //! PointStartIterator.
  //! An exception is raised if HasFirstPoint returns False.
  int FirstPointIndex() const;

  //! Returns the last point of the line when it is a
  //! marching point.
  //! An exception is raised if HasLastPoint returns False.
  const IntSurf_PathPoint& LastPoint() const;

  //! Returns the index of last point of the line when it is a
  //! marching point. This index is the index in the
  //! PointStartIterator.
  //! An exception is raised if HasLastPoint returns False.
  int LastPointIndex() const;

  //! returns the number of points belonging to Pnts1 which are
  //! passing point.
  int NbPassingPoint() const;

  //! returns the index of the point belonging to the line which
  //! is associated to the passing point belonging to Pnts1
  //! an exception is raised if Index > NbPassingPoint()
  void PassingPoint(const int Index, int& IndexLine, int& IndexPnts) const;

  const gp_Vec& TangentVector(int& Index) const;

  bool IsTangentAtBegining() const;

  bool IsTangentAtEnd() const;

  DEFINE_STANDARD_RTTI_INLINE(Contap_TheIWLineOfTheIWalking, Standard_Transient)

private:
  occ::handle<IntSurf_LineOn2S>        line;
  NCollection_Sequence<IntSurf_Couple> couple;
  bool                                 closed;
  bool                                 hasFirst;
  bool                                 hasLast;
  int                                  firstIndex;
  int                                  lastIndex;
  IntSurf_PathPoint                    theFirstPoint;
  IntSurf_PathPoint                    theLastPoint;
  int                                  indextg;
  gp_Vec                               vcttg;
  bool                                 istgtbeg;
  bool                                 istgtend;
};

//=================================================================================================
// Inline implementations
//=================================================================================================

inline void Contap_TheIWLineOfTheIWalking::Cut(const int Index)
{
  occ::handle<IntSurf_LineOn2S> lost = line->Split(Index);
}

inline void Contap_TheIWLineOfTheIWalking::AddPoint(const IntSurf_PntOn2S& P)
{
  line->Add(P);
}

inline void Contap_TheIWLineOfTheIWalking::AddStatusFirst(const bool Closed, const bool HasFirst)
{
  closed   = Closed;
  hasFirst = HasFirst;
}

inline void Contap_TheIWLineOfTheIWalking::AddStatusLast(const bool HasLast)
{
  hasLast = HasLast;
}

inline void Contap_TheIWLineOfTheIWalking::AddStatusFirst(const bool               Closed,
                                                          const bool               HasFirst,
                                                          const int                Index,
                                                          const IntSurf_PathPoint& P)
{
  closed        = Closed;
  hasFirst      = HasFirst;
  firstIndex    = Index;
  theFirstPoint = P;
}

inline void Contap_TheIWLineOfTheIWalking::AddStatusLast(const bool               HasLast,
                                                         const int                Index,
                                                         const IntSurf_PathPoint& P)
{
  hasLast      = HasLast;
  lastIndex    = Index;
  theLastPoint = P;
}

inline void Contap_TheIWLineOfTheIWalking::AddStatusFirstLast(const bool Closed,
                                                              const bool HasFirst,
                                                              const bool HasLast)
{
  closed   = Closed;
  hasFirst = HasFirst;
  hasLast  = HasLast;
}

inline void Contap_TheIWLineOfTheIWalking::AddIndexPassing(const int Index)
{
  couple.Append(IntSurf_Couple(line->NbPoints() + 1, Index));
}

inline int Contap_TheIWLineOfTheIWalking::NbPoints() const
{
  return line->NbPoints();
}

inline const IntSurf_PntOn2S& Contap_TheIWLineOfTheIWalking::Value(const int Index) const
{
  return line->Value(Index);
}

inline const occ::handle<IntSurf_LineOn2S>& Contap_TheIWLineOfTheIWalking::Line() const
{
  return line;
}

inline bool Contap_TheIWLineOfTheIWalking::IsClosed() const
{
  return closed;
}

inline bool Contap_TheIWLineOfTheIWalking::HasFirstPoint() const
{
  return hasFirst;
}

inline int Contap_TheIWLineOfTheIWalking::FirstPointIndex() const
{
  if (!hasFirst)
    throw Standard_DomainError();
  return firstIndex;
}

inline const IntSurf_PathPoint& Contap_TheIWLineOfTheIWalking::FirstPoint() const
{
  if (!hasFirst)
    throw Standard_DomainError();
  return theFirstPoint;
}

inline bool Contap_TheIWLineOfTheIWalking::HasLastPoint() const
{
  return hasLast;
}

inline const IntSurf_PathPoint& Contap_TheIWLineOfTheIWalking::LastPoint() const
{
  if (!hasLast)
    throw Standard_DomainError();
  return theLastPoint;
}

inline int Contap_TheIWLineOfTheIWalking::LastPointIndex() const
{
  if (!hasLast)
    throw Standard_DomainError();
  return lastIndex;
}

inline int Contap_TheIWLineOfTheIWalking::NbPassingPoint() const
{
  return couple.Length();
}

inline void Contap_TheIWLineOfTheIWalking::PassingPoint(const int Index,
                                                        int&      IndexLine,
                                                        int&      IndexPnts) const
{
  IndexLine = couple(Index).First();
  IndexPnts = couple(Index).Second();
}

inline void Contap_TheIWLineOfTheIWalking::SetTangentVector(const gp_Vec& V, const int Index)
{
  indextg = Index;
  vcttg   = V;
}

inline void Contap_TheIWLineOfTheIWalking::SetTangencyAtBegining(const bool IsTangent)
{
  istgtend = IsTangent;
}

inline void Contap_TheIWLineOfTheIWalking::SetTangencyAtEnd(const bool IsTangent)
{
  istgtend = IsTangent;
}

inline const gp_Vec& Contap_TheIWLineOfTheIWalking::TangentVector(int& Index) const
{
  Index = indextg;
  return vcttg;
}

inline bool Contap_TheIWLineOfTheIWalking::IsTangentAtBegining() const
{
  return istgtbeg;
}

inline bool Contap_TheIWLineOfTheIWalking::IsTangentAtEnd() const
{
  return istgtend;
}

