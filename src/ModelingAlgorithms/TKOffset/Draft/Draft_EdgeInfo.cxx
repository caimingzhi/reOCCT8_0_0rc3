#include <BRep_Tool.hpp>
#include <Draft_EdgeInfo.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Face.hpp>

Draft_EdgeInfo::Draft_EdgeInfo()
    : myNewGeom(false),
      myTgt(false),
      myTol(0)
{
}

Draft_EdgeInfo::Draft_EdgeInfo(const bool HasNewGeometry)
    : myNewGeom(HasNewGeometry),
      myTgt(false),
      myTol(0)
{
}

void Draft_EdgeInfo::Add(const TopoDS_Face& F)
{
  if (myFirstF.IsNull())
  {
    myFirstF = F;
  }
  else if (!myFirstF.IsSame(F) && mySeconF.IsNull())
  {
    mySeconF = F;
  }
  myTol = std::max(myTol, BRep_Tool::Tolerance(F));
}

void Draft_EdgeInfo::RootFace(const TopoDS_Face& F)
{
  myRootFace = F;
}

void Draft_EdgeInfo::Tangent(const gp_Pnt& P)
{
  myTgt = true;
  myPt  = P;
}

bool Draft_EdgeInfo::IsTangent(gp_Pnt& P) const
{
  P = myPt;
  return myTgt;
}

bool Draft_EdgeInfo::NewGeometry() const
{
  return myNewGeom;
}

void Draft_EdgeInfo::SetNewGeometry(const bool NewGeom)
{
  myNewGeom = NewGeom;
}

const occ::handle<Geom_Curve>& Draft_EdgeInfo::Geometry() const
{
  return myGeom;
}

const TopoDS_Face& Draft_EdgeInfo::FirstFace() const
{
  return myFirstF;
}

const TopoDS_Face& Draft_EdgeInfo::SecondFace() const
{
  return mySeconF;
}

occ::handle<Geom_Curve>& Draft_EdgeInfo::ChangeGeometry()
{
  return myGeom;
}

const occ::handle<Geom2d_Curve>& Draft_EdgeInfo::FirstPC() const
{
  return myFirstPC;
}

const occ::handle<Geom2d_Curve>& Draft_EdgeInfo::SecondPC() const
{
  return mySeconPC;
}

occ::handle<Geom2d_Curve>& Draft_EdgeInfo::ChangeFirstPC()
{
  return myFirstPC;
}

occ::handle<Geom2d_Curve>& Draft_EdgeInfo::ChangeSecondPC()
{
  return mySeconPC;
}

const TopoDS_Face& Draft_EdgeInfo::RootFace() const
{
  return myRootFace;
}

void Draft_EdgeInfo::Tolerance(const double tol)
{
  myTol = tol;
}

double Draft_EdgeInfo::Tolerance() const
{
  return myTol;
}
