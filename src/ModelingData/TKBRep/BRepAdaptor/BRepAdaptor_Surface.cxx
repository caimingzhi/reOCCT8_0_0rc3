#include <BRepAdaptor_Surface.hpp>

#include <BRep_Tool.hpp>
#include <BRepTools.hpp>
#include <Geom_Surface.hpp>
#include <TopoDS_Face.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepAdaptor_Surface, GeomAdaptor_TransformedSurface)

//=================================================================================================

BRepAdaptor_Surface::BRepAdaptor_Surface() = default;

//=================================================================================================

BRepAdaptor_Surface::BRepAdaptor_Surface(const TopoDS_Face& F, const bool R)
{
  Initialize(F, R);
}

//=================================================================================================

occ::handle<Adaptor3d_Surface> BRepAdaptor_Surface::ShallowCopy() const
{
  occ::handle<BRepAdaptor_Surface> aCopy = new BRepAdaptor_Surface();

  const occ::handle<Adaptor3d_Surface> aSurface = mySurf.ShallowCopy();
  const GeomAdaptor_Surface& aGeomSurface       = *occ::down_cast<GeomAdaptor_Surface>(aSurface);
  aCopy->mySurf                                 = aGeomSurface;

  aCopy->myTrsf = myTrsf;
  aCopy->myFace = myFace;

  return aCopy;
}

//=================================================================================================

void BRepAdaptor_Surface::Initialize(const TopoDS_Face& F, const bool Restriction)
{
  if (F.IsNull())
  {
    return;
  }

  myFace = F;
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& aSurface = BRep_Tool::Surface(F, L);
  if (aSurface.IsNull())
    return;

  if (Restriction)
  {
    double umin, umax, vmin, vmax;
    BRepTools::UVBounds(F, umin, umax, vmin, vmax);
    mySurf.Load(aSurface, umin, umax, vmin, vmax);
  }
  else
    mySurf.Load(aSurface);
  myTrsf = L.Transformation();
}

//=================================================================================================

const TopoDS_Face& BRepAdaptor_Surface::Face() const
{
  return myFace;
}

//=================================================================================================

double BRepAdaptor_Surface::Tolerance() const
{
  return BRep_Tool::Tolerance(myFace);
}
