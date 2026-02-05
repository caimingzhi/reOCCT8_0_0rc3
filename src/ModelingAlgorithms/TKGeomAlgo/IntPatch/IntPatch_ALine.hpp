#pragma once

#include <Standard_Handle.hpp>

#include <IntAna_Curve.hpp>
#include <IntPatch_Line.hpp>
#include <IntPatch_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_List.hpp>

class IntPatch_Point;

//! Implementation of an intersection line described by a
//! parametrized curve.
class IntPatch_ALine : public IntPatch_Line
{

public:
  //! Creates an analytic intersection line
  //! when the transitions are In or Out.
  Standard_EXPORT IntPatch_ALine(const IntAna_Curve&     C,
                                 const bool              Tang,
                                 const IntSurf_TypeTrans Trans1,
                                 const IntSurf_TypeTrans Trans2);

  //! Creates an analytic intersection line
  //! when the transitions are Touch.
  Standard_EXPORT IntPatch_ALine(const IntAna_Curve&     C,
                                 const bool              Tang,
                                 const IntSurf_Situation Situ1,
                                 const IntSurf_Situation Situ2);

  //! Creates an analytic intersection line
  //! when the transitions are Undecided.
  Standard_EXPORT IntPatch_ALine(const IntAna_Curve& C, const bool Tang);

  //! To add a vertex in the list.
  Standard_EXPORT void AddVertex(const IntPatch_Point& Pnt);

  //! Replaces the element of range Index in the list
  //! of points.
  void Replace(const int Index, const IntPatch_Point& Pnt);

  void SetFirstPoint(const int IndFirst);

  void SetLastPoint(const int IndLast);

  //! Returns the first parameter on the intersection line.
  //! If IsIncluded returns True, Value and D1 methods can
  //! be call with a parameter equal to FirstParameter.
  //! Otherwise, the parameter must be greater than
  //! FirstParameter.
  double FirstParameter(bool& IsIncluded) const;

  //! Returns the last parameter on the intersection line.
  //! If IsIncluded returns True, Value and D1 methods can
  //! be call with a parameter equal to LastParameter.
  //! Otherwise, the parameter must be less than LastParameter.
  double LastParameter(bool& IsIncluded) const;

  //! Returns the point of parameter U on the analytic
  //! intersection line.
  gp_Pnt Value(const double U);

  //! Returns true when the derivative at parameter U
  //! is defined on the analytic intersection line.
  //! In that case, Du is the derivative.
  //! Returns false when it is not possible to
  //! evaluate the derivative.
  //! In both cases, P is the point at parameter U on the
  //! intersection.
  bool D1(const double U, gp_Pnt& P, gp_Vec& Du);

  //! Tries to find the parameters of the point P on the curve.
  //! If the method returns False, the "projection" is
  //! impossible.
  //! If the method returns True at least one parameter has been found.
  //! theParams is always sorted in ascending order.
  void FindParameter(const gp_Pnt& P, NCollection_List<double>& theParams) const;

  //! Returns True if the line has a known First point.
  //! This point is given by the method FirstPoint().
  bool HasFirstPoint() const;

  //! Returns True if the line has a known Last point.
  //! This point is given by the method LastPoint().
  bool HasLastPoint() const;

  //! Returns the IntPoint corresponding to the FirstPoint.
  //! An exception is raised when HasFirstPoint returns False.
  const IntPatch_Point& FirstPoint() const;

  //! Returns the IntPoint corresponding to the LastPoint.
  //! An exception is raised when HasLastPoint returns False.
  const IntPatch_Point& LastPoint() const;

  int NbVertex() const;

  //! Returns the vertex of range Index on the line.
  const IntPatch_Point& Vertex(const int Index) const;

  //! Allows modifying the vertex with index theIndex on the line.
  IntPatch_Point& ChangeVertex(const int theIndex) { return svtx.ChangeValue(theIndex); }

  //! Set the parameters of all the vertex on the line.
  //! if a vertex is already in the line,
  //! its parameter is modified
  //! else a new point in the line is inserted.
  Standard_EXPORT void ComputeVertexParameters(const double Tol);

  Standard_EXPORT const IntAna_Curve& Curve() const;

  DEFINE_STANDARD_RTTIEXT(IntPatch_ALine, IntPatch_Line)

private:
  IntAna_Curve                         curv;
  bool                                 fipt;
  bool                                 lapt;
  int                                  indf;
  int                                  indl;
  NCollection_Sequence<IntPatch_Point> svtx;
};

#include <Standard_DomainError.hpp>
#include <Precision.hpp>
#include <IntPatch_Point.hpp>

inline void IntPatch_ALine::Replace(const int Index, const IntPatch_Point& Pnt)
{
  svtx(Index) = Pnt;
}

inline void IntPatch_ALine::SetFirstPoint(const int IndFirst)
{
  fipt = true;
  indf = IndFirst;
}

inline void IntPatch_ALine::SetLastPoint(const int IndLast)
{
  lapt = true;
  indl = IndLast;
}

inline double IntPatch_ALine::FirstParameter(bool& IsIncluded) const
{
  double bid, first;
  curv.Domain(first, bid);
  IsIncluded = !curv.IsFirstOpen();
  return first;
}

inline double IntPatch_ALine::LastParameter(bool& IsIncluded) const
{
  double bid, last;
  curv.Domain(bid, last);
  IsIncluded = !curv.IsLastOpen();
  return last;
}

inline gp_Pnt IntPatch_ALine::Value(const double U)
{
  return curv.Value(U); // Value leve l exception DomainError
}

inline bool IntPatch_ALine::D1(const double U, gp_Pnt& P, gp_Vec& Du)
{
  return curv.D1u(U, P, Du); // D1u leve l exception DomainError
}

inline void IntPatch_ALine::FindParameter(const gp_Pnt&             theP,
                                          NCollection_List<double>& theParams) const
{
  curv.FindParameter(theP, theParams);
}

inline bool IntPatch_ALine::HasFirstPoint() const
{
  return fipt;
}

inline bool IntPatch_ALine::HasLastPoint() const
{
  return lapt;
}

inline const IntPatch_Point& IntPatch_ALine::FirstPoint() const
{
  if (!fipt)
  {
    throw Standard_DomainError();
  }
  return svtx(indf);
}

inline const IntPatch_Point& IntPatch_ALine::LastPoint() const
{
  if (!lapt)
  {
    throw Standard_DomainError();
  }
  return svtx(indl);
}

inline int IntPatch_ALine::NbVertex() const
{
  return svtx.Length();
}

inline const IntPatch_Point& IntPatch_ALine::Vertex(const int Index) const
{
  return svtx(Index);
}
