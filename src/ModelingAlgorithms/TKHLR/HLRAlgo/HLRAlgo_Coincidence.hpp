#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <TopAbs_State.hpp>

//! The Coincidence class is used in an Interference to
//! store information on the "hiding" edge.
//!
//! 2D Data: The tangent and the curvature of the
//! projection of the edge at the intersection point.
//! This is necesserary when the intersection is at
//! the extremity of the edge.
//!
//! 3D Data: The state of the edge near the
//! intersection with the face (before and after).
//! This is necessary when the intersection is "ON"
//! the face.
class HLRAlgo_Coincidence
{
public:
  DEFINE_STANDARD_ALLOC

  HLRAlgo_Coincidence()
      : myFE(0),
        myParam(0.),
        myStBef(TopAbs_IN),
        myStAft(TopAbs_IN)
  {
  }

  void Set2D(const int FE, const double Param)
  {
    myFE    = FE;
    myParam = Param;
  }

  void SetState3D(const TopAbs_State stbef, const TopAbs_State staft)
  {
    myStBef = stbef;
    myStAft = staft;
  }

  void Value2D(int& FE, double& Param) const
  {
    FE    = myFE;
    Param = myParam;
  }

  void State3D(TopAbs_State& stbef, TopAbs_State& staft) const
  {
    stbef = myStBef;
    staft = myStAft;
  }

private:
  int          myFE;
  double       myParam;
  TopAbs_State myStBef;
  TopAbs_State myStAft;
};

