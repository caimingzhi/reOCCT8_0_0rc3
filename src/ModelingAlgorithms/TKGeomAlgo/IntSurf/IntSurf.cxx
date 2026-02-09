

#include <IntSurf.hpp>

#include <Adaptor3d_Surface.hpp>
#include <IntSurf_Transition.hpp>
#include <Precision.hpp>
#include <gp_Vec.hpp>

void IntSurf::MakeTransition(const gp_Vec&       TgFirst,
                             const gp_Vec&       TgSecond,
                             const gp_Dir&       Normale,
                             IntSurf_Transition& TFirst,
                             IntSurf_Transition& TSecond)

{

  gp_Vec pvect(TgSecond.Crossed(TgFirst));

  double NTgSecond                = TgSecond.Magnitude();
  double NTgFirst                 = TgFirst.Magnitude();
  double NTgSecondNTgFirstAngular = NTgSecond * NTgFirst * Precision::Angular();

  if (NTgFirst <= Precision::Confusion())
  {
    TFirst.SetValue(true, IntSurf_Undecided);
    TSecond.SetValue(true, IntSurf_Undecided);
  }
  else if ((NTgSecond <= Precision::Confusion()) || (pvect.Magnitude() <= NTgSecondNTgFirstAngular))
  {
    TFirst.SetValue(true, IntSurf_Unknown, TgFirst.Dot(TgSecond) < 0.0);
    TSecond.SetValue(true, IntSurf_Unknown, TgFirst.Dot(TgSecond) < 0.0);
  }
  else
  {
    double yu = pvect.Dot(Normale);
    yu /= NTgSecond * NTgFirst;
    if (yu > 0.0001)
    {
      TFirst.SetValue(false, IntSurf_In);
      TSecond.SetValue(false, IntSurf_Out);
    }
    else if (yu < -0.0001)
    {
      TFirst.SetValue(false, IntSurf_Out);
      TSecond.SetValue(false, IntSurf_In);
    }
    else
    {
      TFirst.SetValue(true, IntSurf_Undecided);
      TSecond.SetValue(true, IntSurf_Undecided);
    }
  }
}

void IntSurf::SetPeriod(const occ::handle<Adaptor3d_Surface>& theFirstSurf,
                        const occ::handle<Adaptor3d_Surface>& theSecondSurf,
                        double                                theArrOfPeriod[4])
{
  theArrOfPeriod[0] = theFirstSurf->IsUPeriodic() ? theFirstSurf->UPeriod() : 0.0;
  theArrOfPeriod[1] = theFirstSurf->IsVPeriodic() ? theFirstSurf->VPeriod() : 0.0;
  theArrOfPeriod[2] = theSecondSurf->IsUPeriodic() ? theSecondSurf->UPeriod() : 0.0;
  theArrOfPeriod[3] = theSecondSurf->IsVPeriodic() ? theSecondSurf->VPeriod() : 0.0;
}
