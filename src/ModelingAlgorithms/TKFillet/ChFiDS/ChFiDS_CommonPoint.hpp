#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_Orientation.hpp>

//! point start/end of fillet common to 2 adjacent filets
//! and to an edge on one of 2 faces participating
//! in the construction of the fillet
class ChFiDS_CommonPoint
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT ChFiDS_CommonPoint();

  //! default value for all fields
  Standard_EXPORT void Reset();

  //! Sets the values of a point which is a vertex on
  //! the initial facet of restriction of one
  //! of the surface.
  void SetVertex(const TopoDS_Vertex& theVertex)
  {
    isvtx = true;
    vtx   = theVertex;
  }

  //! Sets the values of a point which is on the arc
  //! A, at parameter Param.
  Standard_EXPORT void SetArc(const double             Tol,
                              const TopoDS_Edge&       A,
                              const double             Param,
                              const TopAbs_Orientation TArc);

  //! Sets the value of the parameter on the spine
  Standard_EXPORT void SetParameter(const double Param);

  //! Set the 3d point for a commonpoint that is not
  //! a vertex or on an arc.
  void SetPoint(const gp_Pnt& thePoint) { point = thePoint; }

  //! Set the output 3d vector
  void SetVector(const gp_Vec& theVector)
  {
    hasvector = true;
    vector    = theVector;
  }

  //! This method set the fuzziness on the point.
  void SetTolerance(const double Tol)
  {
    if (Tol > tol)
    {
      tol = Tol;
    }
  }

  //! This method returns the fuzziness on the point.
  double Tolerance() const { return tol; }

  //! Returns TRUE if the point is a vertex on the initial
  //! restriction facet of the surface.
  bool IsVertex() const { return isvtx; }

  //! Returns the information about the point when it is
  //! on the domain of the first patch, i-e when the function
  //! IsVertex returns True.
  //! Otherwise, an exception is raised.
  const TopoDS_Vertex& Vertex() const
  {
    if (!isvtx)
    {
      throw Standard_DomainError();
    }
    return vtx;
  }

  //! Returns TRUE if the point is a on an edge of the initial
  //! restriction facet of the surface.
  bool IsOnArc() const { return isonarc; }

  //! Returns the arc of restriction containing the
  //! vertex.
  Standard_EXPORT const TopoDS_Edge& Arc() const;

  //! Returns the transition of the point on the arc
  //! returned by Arc().
  Standard_EXPORT TopAbs_Orientation TransitionOnArc() const;

  //! Returns the parameter of the point on the
  //! arc returned by the method Arc().
  Standard_EXPORT double ParameterOnArc() const;

  //! Returns the parameter on the spine
  Standard_EXPORT double Parameter() const;

  //! Returns the 3d point
  const gp_Pnt& Point() const { return point; }

  //! Returns TRUE if the output vector is stored.
  bool HasVector() const { return hasvector; }

  //! Returns the output 3d vector
  const gp_Vec& Vector() const
  {
    if (!hasvector)
    {
      throw Standard_DomainError("ChFiDS_CommonPoint::Vector");
    }
    return vector;
  }

private:
  TopoDS_Edge        arc;
  TopoDS_Vertex      vtx;
  gp_Pnt             point;
  gp_Vec             vector;
  double             tol;
  double             prmarc;
  double             prmtg;
  TopAbs_Orientation traarc;
  bool               isonarc;
  bool               isvtx;
  bool               hasvector;
};

