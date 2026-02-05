#include <AdvApp2Var_Node.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AdvApp2Var_Node, Standard_Transient)

//=================================================================================================

AdvApp2Var_Node::AdvApp2Var_Node()
    : myTruePoints(0, 2, 0, 2),
      myErrors(0, 2, 0, 2),
      myOrdInU(2),
      myOrdInV(2)
{
  gp_Pnt P0(0., 0., 0.);
  myTruePoints.Init(P0);
  myErrors.Init(0.);
}

//=================================================================================================

AdvApp2Var_Node::AdvApp2Var_Node(const int iu, const int iv)
    : myTruePoints(0, std::max(0, iu), 0, std::max(0, iv)),
      myErrors(0, std::max(0, iu), 0, std::max(0, iv)),
      myOrdInU(iu),
      myOrdInV(iv)
{
  gp_Pnt P0(0., 0., 0.);
  myTruePoints.Init(P0);
  myErrors.Init(0.);
}

//=================================================================================================

AdvApp2Var_Node::AdvApp2Var_Node(const gp_XY& UV, const int iu, const int iv)
    : myTruePoints(0, iu, 0, iv),
      myErrors(0, iu, 0, iv),
      myCoord(UV),
      myOrdInU(iu),
      myOrdInV(iv)
{
  gp_Pnt P0(0., 0., 0.);
  myTruePoints.Init(P0);
  myErrors.Init(0.);
}
