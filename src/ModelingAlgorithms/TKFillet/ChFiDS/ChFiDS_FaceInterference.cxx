#include <ChFiDS_FaceInterference.hpp>
#include <Geom2d_Curve.hpp>

//=================================================================================================

ChFiDS_FaceInterference::ChFiDS_FaceInterference()
    : firstParam(0.0),
      lastParam(0.0),
      lineindex(0),
      LineTransition(TopAbs_FORWARD)
{
}

void ChFiDS_FaceInterference::SetParameter(const double U1, const bool IsFirst)
{
  if (IsFirst)
    SetFirstParameter(U1);
  else
    SetLastParameter(U1);
}

void ChFiDS_FaceInterference::SetTransition(const TopAbs_Orientation Trans)
{
  LineTransition = Trans;
}

double ChFiDS_FaceInterference::Parameter(const bool IsFirst) const
{
  if (IsFirst)
    return FirstParameter();
  else
    return LastParameter();
}
