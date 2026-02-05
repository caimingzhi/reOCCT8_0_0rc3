#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS_Point.hpp>
#include <TopOpeBRepTool_ShapeTool.hpp>

//=================================================================================================

TopOpeBRepDS_Point::TopOpeBRepDS_Point()
    : myKeep(true)
{
}

//=================================================================================================

TopOpeBRepDS_Point::TopOpeBRepDS_Point(const gp_Pnt& P, const double T)
    : myPoint(P),
      myTolerance(T),
      myKeep(true)
{
}

//=================================================================================================

TopOpeBRepDS_Point::TopOpeBRepDS_Point(const TopoDS_Shape& S)
{
  myPoint     = TopOpeBRepTool_ShapeTool::Pnt(S);
  myTolerance = TopOpeBRepTool_ShapeTool::Tolerance(S);
}

//=================================================================================================

bool TopOpeBRepDS_Point::IsEqual(const TopOpeBRepDS_Point& P) const
{
  double t = std::max(myTolerance, P.Tolerance());
  bool   b = myPoint.IsEqual(P.Point(), t);
  return b;
}

//=================================================================================================

const gp_Pnt& TopOpeBRepDS_Point::Point() const
{
  return myPoint;
}

//=================================================================================================

gp_Pnt& TopOpeBRepDS_Point::ChangePoint()
{
  return myPoint;
}

//=================================================================================================

double TopOpeBRepDS_Point::Tolerance() const
{
  return myTolerance;
}

//=================================================================================================

void TopOpeBRepDS_Point::Tolerance(const double Tol)
{
  myTolerance = Tol;
}

//=================================================================================================

bool TopOpeBRepDS_Point::Keep() const
{
  return myKeep;
}

//=================================================================================================

void TopOpeBRepDS_Point::ChangeKeep(const bool b)
{
  myKeep = b;
}
