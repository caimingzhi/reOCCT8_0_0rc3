#include <BRepAdaptor_Surface.hpp>
#include <gp_Pnt2d.hpp>
#include <TopoDS_Face.hpp>
#include <TopOpeBRep_PointClassifier.hpp>

TopOpeBRep_PointClassifier::TopOpeBRep_PointClassifier()
{
  myHSurface = new BRepAdaptor_Surface();
  Init();
}

void TopOpeBRep_PointClassifier::Init()
{
  myTopolToolMap.Clear();
  myState = TopAbs_UNKNOWN;
}

void TopOpeBRep_PointClassifier::Load(const TopoDS_Face& F)
{
  bool found = myTopolToolMap.IsBound(F);
  if (!found)
  {
    myHSurface->Initialize(F);
    myTopolTool = new BRepTopAdaptor_TopolTool(myHSurface);
    myTopolToolMap.Bind(F, myTopolTool);
  }
  else
  {
    myTopolTool = myTopolToolMap.Find(F);
  }
}

TopAbs_State TopOpeBRep_PointClassifier::Classify(const TopoDS_Face& F,
                                                  const gp_Pnt2d&    P2d,
                                                  const double       Tol)
{
  myState = TopAbs_UNKNOWN;
  Load(F);
  myState = myTopolTool->Classify(P2d, Tol);

  return myState;
}

TopAbs_State TopOpeBRep_PointClassifier::State() const
{
  return myState;
}
