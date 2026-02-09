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

class ChFiDS_CommonPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFiDS_CommonPoint();

  Standard_EXPORT void Reset();

  void SetVertex(const TopoDS_Vertex& theVertex)
  {
    isvtx = true;
    vtx   = theVertex;
  }

  Standard_EXPORT void SetArc(const double             Tol,
                              const TopoDS_Edge&       A,
                              const double             Param,
                              const TopAbs_Orientation TArc);

  Standard_EXPORT void SetParameter(const double Param);

  void SetPoint(const gp_Pnt& thePoint) { point = thePoint; }

  void SetVector(const gp_Vec& theVector)
  {
    hasvector = true;
    vector    = theVector;
  }

  void SetTolerance(const double Tol)
  {
    if (Tol > tol)
    {
      tol = Tol;
    }
  }

  double Tolerance() const { return tol; }

  bool IsVertex() const { return isvtx; }

  const TopoDS_Vertex& Vertex() const
  {
    if (!isvtx)
    {
      throw Standard_DomainError();
    }
    return vtx;
  }

  bool IsOnArc() const { return isonarc; }

  Standard_EXPORT const TopoDS_Edge& Arc() const;

  Standard_EXPORT TopAbs_Orientation TransitionOnArc() const;

  Standard_EXPORT double ParameterOnArc() const;

  Standard_EXPORT double Parameter() const;

  const gp_Pnt& Point() const { return point; }

  bool HasVector() const { return hasvector; }

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
