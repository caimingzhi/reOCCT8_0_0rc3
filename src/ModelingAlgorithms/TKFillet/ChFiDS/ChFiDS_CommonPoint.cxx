#include <ChFiDS_CommonPoint.hpp>
#include <Standard_DomainError.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>

//=================================================================================================

ChFiDS_CommonPoint::ChFiDS_CommonPoint()
    : tol(0.0),
      prmarc(0.0),
      prmtg(0.0),
      traarc(TopAbs_FORWARD),
      isonarc(false),
      isvtx(false),
      hasvector(false)
{
}

//=================================================================================================

void ChFiDS_CommonPoint::Reset()
{
  tol       = 0.;
  isvtx     = false;
  isonarc   = false;
  hasvector = false;
}

//=======================================================================
// function : SetArc
// purpose  :
// 30/09/1997 : PMN On n'ecrabouille plus la tolerance
//=======================================================================

void ChFiDS_CommonPoint::SetArc(const double             Tol,
                                const TopoDS_Edge&       A,
                                const double             Param,
                                const TopAbs_Orientation TArc)
{
  isonarc = true;
  if (Tol > tol)
    tol = Tol;
  arc    = A;
  prmarc = Param;
  traarc = TArc;
}

//=================================================================================================

void ChFiDS_CommonPoint::SetParameter(const double Param)
{
  prmtg = Param;
}

//=================================================================================================

const TopoDS_Edge& ChFiDS_CommonPoint::Arc() const
{
  if (!isonarc)
  {
    throw Standard_DomainError("CommonPoint not on Arc");
  }
  return arc;
}

//=================================================================================================

TopAbs_Orientation ChFiDS_CommonPoint::TransitionOnArc() const
{
  if (!isonarc)
  {
    throw Standard_DomainError("CommonPoint not on Arc");
  }
  return traarc;
}

//=================================================================================================

double ChFiDS_CommonPoint::ParameterOnArc() const
{
  if (!isonarc)
  {
    throw Standard_DomainError("CommonPoint not on Arc");
  }
  return prmarc;
}

//=================================================================================================

double ChFiDS_CommonPoint::Parameter() const
{
  return prmtg;
}
