#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <TopAbs_State.hpp>

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
