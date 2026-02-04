#pragma once


#include <Adaptor3d_Surface.hpp>

class IntSurf_Transition;
class gp_Dir;
class gp_Vec;

//! This package provides resources for
//! all the packages concerning the intersection
//! between surfaces.
class IntSurf
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the transition of the intersection point
  //! between the two lines.
  //! TgFirst is the tangent vector of the first line.
  //! TgSecond is the tangent vector of the second line.
  //! Normal is the direction used to orientate the cross
  //! product TgFirst^TgSecond.
  //! TFirst is the transition of the point on the first line.
  //! TSecond is the transition of the point on the second line.
  Standard_EXPORT static void MakeTransition(const gp_Vec&       TgFirst,
                                             const gp_Vec&       TgSecond,
                                             const gp_Dir&       Normal,
                                             IntSurf_Transition& TFirst,
                                             IntSurf_Transition& TSecond);

  //! Fills theArrOfPeriod array by the period values of theFirstSurf and theSecondSurf.
  //! [0] = U-period of theFirstSurf,
  //! [1] = V-period of theFirstSurf,
  //! [2] = U-period of theSecondSurf,
  //! [3] = V-period of theSecondSurf.
  //!
  //! If surface is not periodic in correspond direction then
  //! its period is considered to be equal to 0.
  Standard_EXPORT static void SetPeriod(const occ::handle<Adaptor3d_Surface>& theFirstSurf,
                                        const occ::handle<Adaptor3d_Surface>& theSecondSurf,
                                        double                                theArrOfPeriod[4]);
};

