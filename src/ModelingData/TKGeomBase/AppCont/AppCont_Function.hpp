#pragma once

#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

class AppCont_Function
{
public:
  AppCont_Function()
  {
    myNbPnt   = -1;
    myNbPnt2d = -1;
  }

  void GetNumberOfPoints(int& theNbPnt, int& theNbPnt2d) const
  {
    theNbPnt   = myNbPnt;
    theNbPnt2d = myNbPnt2d;
  }

  int GetNbOf3dPoints() const { return myNbPnt; }

  int GetNbOf2dPoints() const { return myNbPnt2d; }

  virtual ~AppCont_Function() = default;

  virtual double FirstParameter() const = 0;

  virtual double LastParameter() const = 0;

  virtual bool Value(const double                  theU,
                     NCollection_Array1<gp_Pnt2d>& thePnt2d,
                     NCollection_Array1<gp_Pnt>&   thePnt) const = 0;

  virtual bool D1(const double                  theU,
                  NCollection_Array1<gp_Vec2d>& theVec2d,
                  NCollection_Array1<gp_Vec>&   theVec) const = 0;

  virtual void PeriodInformation(const int, bool& IsPeriodic, double& thePeriod) const
  {
    IsPeriodic = false;
    thePeriod  = 0.0;
  };

protected:
  int myNbPnt;
  int myNbPnt2d;
};
