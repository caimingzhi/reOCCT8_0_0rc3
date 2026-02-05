#include <BRepPrimAPI_MakeCone.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>

//=================================================================================================

BRepPrimAPI_MakeCone::BRepPrimAPI_MakeCone(const double R1, const double R2, const double H)
    : myCone(gp::XOY(), R1, R2, H)
{
}

//=================================================================================================

BRepPrimAPI_MakeCone::BRepPrimAPI_MakeCone(const double R1,
                                           const double R2,
                                           const double H,
                                           const double angle)
    : myCone(R1, R2, H)
{
  myCone.Angle(angle);
}

//=================================================================================================

BRepPrimAPI_MakeCone::BRepPrimAPI_MakeCone(const gp_Ax2& Axes,
                                           const double  R1,
                                           const double  R2,
                                           const double  H)
    : myCone(Axes, R1, R2, H)
{
}

//=================================================================================================

BRepPrimAPI_MakeCone::BRepPrimAPI_MakeCone(const gp_Ax2& Axes,
                                           const double  R1,
                                           const double  R2,
                                           const double  H,
                                           const double  angle)
    : myCone(Axes, R1, R2, H)
{
  myCone.Angle(angle);
}

//=================================================================================================

void* BRepPrimAPI_MakeCone::OneAxis()
{
  return &myCone;
}

//=================================================================================================

BRepPrim_Cone& BRepPrimAPI_MakeCone::Cone()
{
  return myCone;
}
