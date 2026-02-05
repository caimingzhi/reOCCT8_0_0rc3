#pragma once

#include <Standard.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Type.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>

//! used to store constraints on a (Ui,Vj) point
class AdvApp2Var_Node : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(AdvApp2Var_Node, Standard_Transient)
public:
  Standard_EXPORT AdvApp2Var_Node();

  Standard_EXPORT AdvApp2Var_Node(const int iu, const int iv);

  Standard_EXPORT AdvApp2Var_Node(const gp_XY& UV, const int iu, const int iv);

  //! Returns the coordinates (U,V) of the node
  const gp_XY& Coord() const { return myCoord; }

  //! changes the coordinates (U,V) to (x1,x2)
  void SetCoord(const double x1, const double x2)
  {
    myCoord.SetX(x1);
    myCoord.SetY(x2);
  }

  //! returns the continuity order in U of the node
  int UOrder() const { return myOrdInU; }

  //! returns the continuity order in V of the node
  int VOrder() const { return myOrdInV; }

  //! affects the value F(U,V) or its derivates on the node (U,V)
  void SetPoint(const int iu, const int iv, const gp_Pnt& Pt) { myTruePoints.SetValue(iu, iv, Pt); }

  //! returns the value F(U,V) or its derivates on the node (U,V)
  const gp_Pnt& Point(const int iu, const int iv) const { return myTruePoints.Value(iu, iv); }

  //! affects the error between F(U,V) and its approximation
  void SetError(const int iu, const int iv, const double error)
  {
    myErrors.SetValue(iu, iv, error);
  }

  //! returns the error between F(U,V) and its approximation
  double Error(const int iu, const int iv) const { return myErrors.Value(iu, iv); }

  //! Assign operator.
  AdvApp2Var_Node& operator=(const AdvApp2Var_Node& theOther)
  {
    myTruePoints = theOther.myTruePoints;
    myErrors     = theOther.myErrors;
    myCoord      = theOther.myCoord;
    myOrdInU     = theOther.myOrdInU;
    myOrdInV     = theOther.myOrdInV;
    return *this;
  }

private:
  AdvApp2Var_Node(const AdvApp2Var_Node& theOther) = delete;

private:
  NCollection_Array2<gp_Pnt> myTruePoints;
  NCollection_Array2<double> myErrors;
  gp_XY                      myCoord;
  int                        myOrdInU;
  int                        myOrdInV;
};
