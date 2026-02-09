

#include <StdPrs_ToolRFace.hpp>

#include <BRep_Tool.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <TopoDS.hpp>

StdPrs_ToolRFace::StdPrs_ToolRFace()
    : myHasNullCurves(false)
{
}

StdPrs_ToolRFace::StdPrs_ToolRFace(const occ::handle<BRepAdaptor_Surface>& theSurface)
    : myFace(theSurface->Face()),
      myHasNullCurves(false)
{
  myFace.Orientation(TopAbs_FORWARD);
}

const TopoDS_Edge& StdPrs_ToolRFace::Edge() const
{
  return TopoDS::Edge(myExplorer.Current());
}

void StdPrs_ToolRFace::next()
{
  double aParamU1, aParamU2;
  for (; myExplorer.More(); myExplorer.Next())
  {

    if (myExplorer.Current().Orientation() != TopAbs_FORWARD
        && myExplorer.Current().Orientation() != TopAbs_REVERSED)
    {
      continue;
    }

    if (occ::handle<Geom2d_Curve> aCurve =
          BRep_Tool::CurveOnSurface(TopoDS::Edge(myExplorer.Current()), myFace, aParamU1, aParamU2))
    {
      myCurve.Load(aCurve, aParamU1, aParamU2);
      return;
    }
    else
    {
      myHasNullCurves = true;
    }
  }

  myCurve.Reset();
}
