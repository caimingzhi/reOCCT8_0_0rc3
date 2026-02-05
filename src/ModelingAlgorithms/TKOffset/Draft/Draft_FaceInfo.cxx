#include <Draft_FaceInfo.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <TopoDS_Face.hpp>

//=================================================================================================

Draft_FaceInfo::Draft_FaceInfo() = default;

//=================================================================================================

Draft_FaceInfo::Draft_FaceInfo(const occ::handle<Geom_Surface>& S, const bool HasNewGeometry)
    : myNewGeom(HasNewGeometry)
{
  occ::handle<Geom_RectangularTrimmedSurface> T = occ::down_cast<Geom_RectangularTrimmedSurface>(S);
  if (!T.IsNull())
    myGeom = T->BasisSurface();
  else
    myGeom = S;
}

//=================================================================================================

void Draft_FaceInfo::RootFace(const TopoDS_Face& F)
{
  myRootFace = F;
}

//=================================================================================================

void Draft_FaceInfo::Add(const TopoDS_Face& F)
{
  if (myF1.IsNull())
  {
    myF1 = F;
  }
  else if (myF2.IsNull())
  {
    myF2 = F;
  }
}

//=================================================================================================

const TopoDS_Face& Draft_FaceInfo::FirstFace() const
{
  return myF1;
}

//=================================================================================================

const TopoDS_Face& Draft_FaceInfo::SecondFace() const
{
  return myF2;
}

//=================================================================================================

bool Draft_FaceInfo::NewGeometry() const
{
  return myNewGeom;
}

//=================================================================================================

const occ::handle<Geom_Surface>& Draft_FaceInfo::Geometry() const
{
  return myGeom;
}

//=================================================================================================

occ::handle<Geom_Surface>& Draft_FaceInfo::ChangeGeometry()
{
  return myGeom;
}

//=================================================================================================

const occ::handle<Geom_Curve>& Draft_FaceInfo::Curve() const
{
  return myCurv;
}

//=================================================================================================

occ::handle<Geom_Curve>& Draft_FaceInfo::ChangeCurve()
{
  return myCurv;
}

//=================================================================================================

const TopoDS_Face& Draft_FaceInfo::RootFace() const
{
  return myRootFace;
}
