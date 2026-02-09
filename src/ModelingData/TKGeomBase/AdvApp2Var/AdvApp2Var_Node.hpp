#pragma once

#include <Standard.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Type.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>

class AdvApp2Var_Node : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(AdvApp2Var_Node, Standard_Transient)
public:
  Standard_EXPORT AdvApp2Var_Node();

  Standard_EXPORT AdvApp2Var_Node(const int iu, const int iv);

  Standard_EXPORT AdvApp2Var_Node(const gp_XY& UV, const int iu, const int iv);

  const gp_XY& Coord() const { return myCoord; }

  void SetCoord(const double x1, const double x2)
  {
    myCoord.SetX(x1);
    myCoord.SetY(x2);
  }

  int UOrder() const { return myOrdInU; }

  int VOrder() const { return myOrdInV; }

  void SetPoint(const int iu, const int iv, const gp_Pnt& Pt) { myTruePoints.SetValue(iu, iv, Pt); }

  const gp_Pnt& Point(const int iu, const int iv) const { return myTruePoints.Value(iu, iv); }

  void SetError(const int iu, const int iv, const double error)
  {
    myErrors.SetValue(iu, iv, error);
  }

  double Error(const int iu, const int iv) const { return myErrors.Value(iu, iv); }

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
