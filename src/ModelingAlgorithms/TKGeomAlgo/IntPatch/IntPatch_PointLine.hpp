#pragma once


#include <Adaptor3d_Surface.hpp>
#include <IntPatch_Line.hpp>

class gp_Pnt;
class gp_Pnt2d;
class IntSurf_PntOn2S;
class IntSurf_LineOn2S;
class IntPatch_Point;

//! Definition of an intersection line between two
//! surfaces.
//! A line defined by a set of points
//! (e.g. coming from a walking algorithm) as
//! defined in the class WLine or RLine (Restriction line).
class IntPatch_PointLine : public IntPatch_Line
{
public:
  //! Adds a vertex in the list. If theIsPrepend == TRUE the new
  //! vertex will be added before the first element of vertices sequence.
  //! Otherwise, to the end of the sequence
  Standard_EXPORT virtual void AddVertex(const IntPatch_Point& Pnt,
                                         const bool            theIsPrepend = false) = 0;

  //! Returns the number of intersection points.
  Standard_EXPORT virtual int NbPnts() const = 0;

  //! Returns number of vertices (IntPatch_Point) of the line
  Standard_EXPORT virtual int NbVertex() const = 0;

  //! Returns the intersection point of range Index.
  Standard_EXPORT virtual const IntSurf_PntOn2S& Point(const int Index) const = 0;

  //! Returns the vertex of range Index on the line.
  Standard_EXPORT virtual const IntPatch_Point& Vertex(const int Index) const = 0;

  //! Returns the vertex of range Index on the line.
  virtual IntPatch_Point& ChangeVertex(const int Index) = 0;

  //! Removes vertices from the line
  Standard_EXPORT virtual void ClearVertexes() = 0;

  //! Removes single vertex from the line
  Standard_EXPORT virtual void RemoveVertex(const int theIndex) = 0;

  //! Returns set of intersection points
  Standard_EXPORT virtual occ::handle<IntSurf_LineOn2S> Curve() const = 0;

  //! Returns TRUE if P1 is out of the box built from
  //! the points on 1st surface
  Standard_EXPORT virtual bool IsOutSurf1Box(const gp_Pnt2d& P1) const = 0;

  //! Returns TRUE if P2 is out of the box built from
  //! the points on 2nd surface
  Standard_EXPORT virtual bool IsOutSurf2Box(const gp_Pnt2d& P2) const = 0;

  //! Returns TRUE if P is out of the box built from 3D-points.
  Standard_EXPORT virtual bool IsOutBox(const gp_Pnt& P) const = 0;

  //! Returns the radius of curvature of
  //! the intersection line in given point.
  //! Returns negative value if computation is not possible.
  Standard_EXPORT static double CurvatureRadiusOfIntersLine(
    const occ::handle<Adaptor3d_Surface>& theS1,
    const occ::handle<Adaptor3d_Surface>& theS2,
    const IntSurf_PntOn2S&                theUVPoint);

  DEFINE_STANDARD_RTTIEXT(IntPatch_PointLine, IntPatch_Line)

protected:
  //! To initialize the fields, when the transitions
  //! are In or Out.
  Standard_EXPORT IntPatch_PointLine(const bool              Tang,
                                     const IntSurf_TypeTrans Trans1,
                                     const IntSurf_TypeTrans Trans2);

  //! To initialize the fields, when the transitions
  //! are Touch.
  Standard_EXPORT IntPatch_PointLine(const bool              Tang,
                                     const IntSurf_Situation Situ1,
                                     const IntSurf_Situation Situ2);

  //! To initialize the fields, when the transitions
  //! are Undecided.
  Standard_EXPORT IntPatch_PointLine(const bool Tang);
};

