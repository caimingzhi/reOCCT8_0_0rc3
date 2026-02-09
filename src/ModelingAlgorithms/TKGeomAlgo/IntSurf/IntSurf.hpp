#pragma once

#include <Adaptor3d_Surface.hpp>

class IntSurf_Transition;
class gp_Dir;
class gp_Vec;

class IntSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void MakeTransition(const gp_Vec&       TgFirst,
                                             const gp_Vec&       TgSecond,
                                             const gp_Dir&       Normal,
                                             IntSurf_Transition& TFirst,
                                             IntSurf_Transition& TSecond);

  Standard_EXPORT static void SetPeriod(const occ::handle<Adaptor3d_Surface>& theFirstSurf,
                                        const occ::handle<Adaptor3d_Surface>& theSecondSurf,
                                        double                                theArrOfPeriod[4]);
};
