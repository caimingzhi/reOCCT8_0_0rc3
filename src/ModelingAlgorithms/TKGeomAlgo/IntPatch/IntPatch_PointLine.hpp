#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntPatch_Line.hpp>

class gp_Pnt;
class gp_Pnt2d;
class IntSurf_PntOn2S;
class IntSurf_LineOn2S;
class IntPatch_Point;

class IntPatch_PointLine : public IntPatch_Line
{
public:
  Standard_EXPORT virtual void AddVertex(const IntPatch_Point& Pnt,
                                         const bool            theIsPrepend = false) = 0;

  Standard_EXPORT virtual int NbPnts() const = 0;

  Standard_EXPORT virtual int NbVertex() const = 0;

  Standard_EXPORT virtual const IntSurf_PntOn2S& Point(const int Index) const = 0;

  Standard_EXPORT virtual const IntPatch_Point& Vertex(const int Index) const = 0;

  virtual IntPatch_Point& ChangeVertex(const int Index) = 0;

  Standard_EXPORT virtual void ClearVertexes() = 0;

  Standard_EXPORT virtual void RemoveVertex(const int theIndex) = 0;

  Standard_EXPORT virtual occ::handle<IntSurf_LineOn2S> Curve() const = 0;

  Standard_EXPORT virtual bool IsOutSurf1Box(const gp_Pnt2d& P1) const = 0;

  Standard_EXPORT virtual bool IsOutSurf2Box(const gp_Pnt2d& P2) const = 0;

  Standard_EXPORT virtual bool IsOutBox(const gp_Pnt& P) const = 0;

  Standard_EXPORT static double CurvatureRadiusOfIntersLine(
    const occ::handle<Adaptor3d_Surface>& theS1,
    const occ::handle<Adaptor3d_Surface>& theS2,
    const IntSurf_PntOn2S&                theUVPoint);

  DEFINE_STANDARD_RTTIEXT(IntPatch_PointLine, IntPatch_Line)

protected:
  Standard_EXPORT IntPatch_PointLine(const bool              Tang,
                                     const IntSurf_TypeTrans Trans1,
                                     const IntSurf_TypeTrans Trans2);

  Standard_EXPORT IntPatch_PointLine(const bool              Tang,
                                     const IntSurf_Situation Situ1,
                                     const IntSurf_Situation Situ2);

  Standard_EXPORT IntPatch_PointLine(const bool Tang);
};
