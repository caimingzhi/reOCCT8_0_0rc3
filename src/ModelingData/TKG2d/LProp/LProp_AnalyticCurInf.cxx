#include <ElCLib.hpp>
#include <LProp_AnalyticCurInf.hpp>
#include <LProp_CurAndInf.hpp>

LProp_AnalyticCurInf::LProp_AnalyticCurInf() = default;

void LProp_AnalyticCurInf::Perform(const GeomAbs_CurveType CType,
                                   const double            UFirst,
                                   const double            ULast,
                                   LProp_CurAndInf&        Result)
{
  bool IsMin = true;
  bool IsMax = false;

  switch (CType)
  {

    case GeomAbs_Ellipse:
    {
      double U1, U2, U3, U4;
      double UFPlus2PI = UFirst + 2 * M_PI;

      U1 = ElCLib::InPeriod(0.0, UFirst, UFPlus2PI);
      U2 = ElCLib::InPeriod(M_PI / 2., UFirst, UFPlus2PI);
      U3 = ElCLib::InPeriod(M_PI, UFirst, UFPlus2PI);
      U4 = ElCLib::InPeriod(3. * M_PI / 2., UFirst, UFPlus2PI);

      if (UFirst <= U1 && U1 <= ULast)
      {
        Result.AddExtCur(U1, IsMin);
      }
      if (UFirst <= U2 && U2 <= ULast)
      {
        Result.AddExtCur(U2, IsMax);
      }
      if (UFirst <= U3 && U3 <= ULast)
      {
        Result.AddExtCur(U3, IsMin);
      }
      if (UFirst <= U4 && U4 <= ULast)
      {
        Result.AddExtCur(U4, IsMax);
      }
    }
    break;

    case GeomAbs_Hyperbola:
      if (UFirst <= 0.0 && ULast >= 0.0)
      {
        Result.AddExtCur(0.0, true);
      }
      break;

    case GeomAbs_Parabola:
      if (UFirst <= 0.0 && ULast >= 0.0)
      {
        Result.AddExtCur(0.0, true);
      }
      break;
    default:
      break;
  }
}
