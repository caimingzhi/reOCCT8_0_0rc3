#pragma once

#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

//! Class describing a continuous 3d and/or function f(u).
//! This class must be provided by the user to use the approximation algorithm FittingCurve.
class AppCont_Function
{
public:
  AppCont_Function()
  {
    myNbPnt   = -1;
    myNbPnt2d = -1;
  }

  //! Get number of 3d and 2d points returned by "Value" and "D1" functions.
  void GetNumberOfPoints(int& theNbPnt, int& theNbPnt2d) const
  {
    theNbPnt   = myNbPnt;
    theNbPnt2d = myNbPnt2d;
  }

  //! Get number of 3d points returned by "Value" and "D1" functions.
  int GetNbOf3dPoints() const { return myNbPnt; }

  //! Get number of 2d points returned by "Value" and "D1" functions.
  int GetNbOf2dPoints() const { return myNbPnt2d; }

  //! Destructor
  virtual ~AppCont_Function() = default;

  //! Returns the first parameter of the function.
  virtual double FirstParameter() const = 0;

  //! Returns the last parameter of the function.
  virtual double LastParameter() const = 0;

  //! Returns the point at parameter <theU>.
  virtual bool Value(const double                  theU,
                     NCollection_Array1<gp_Pnt2d>& thePnt2d,
                     NCollection_Array1<gp_Pnt>&   thePnt) const = 0;

  //! Returns the derivative at parameter <theU>.
  virtual bool D1(const double                  theU,
                  NCollection_Array1<gp_Vec2d>& theVec2d,
                  NCollection_Array1<gp_Vec>&   theVec) const = 0;

  //! Return information about peridicity in output paramateters space.
  //! @param theDimIdx Defines index in output parameters space. 1 <= theDimIdx <= 3 * myNbPnt + 2 *
  //! myNbPnt2d.
  virtual void PeriodInformation(const int /*theDimIdx*/, bool& IsPeriodic, double& thePeriod) const
  {
    IsPeriodic = false;
    thePeriod  = 0.0;
  };

protected:
  int myNbPnt;
  int myNbPnt2d;
};
