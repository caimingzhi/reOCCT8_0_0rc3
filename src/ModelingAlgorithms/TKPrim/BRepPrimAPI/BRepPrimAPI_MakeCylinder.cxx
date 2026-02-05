#include <BRepPrimAPI_MakeCylinder.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>

//=================================================================================================

BRepPrimAPI_MakeCylinder::BRepPrimAPI_MakeCylinder(const double R, const double H)
    : myCylinder(gp::XOY(), R, H)
{
}

//=================================================================================================

BRepPrimAPI_MakeCylinder::BRepPrimAPI_MakeCylinder(const double R,
                                                   const double H,
                                                   const double Angle)
    : myCylinder(R, H)
{
  myCylinder.Angle(Angle);
}

//=================================================================================================

BRepPrimAPI_MakeCylinder::BRepPrimAPI_MakeCylinder(const gp_Ax2& Axes,
                                                   const double  R,
                                                   const double  H)
    : myCylinder(Axes, R, H)
{
}

//=================================================================================================

BRepPrimAPI_MakeCylinder::BRepPrimAPI_MakeCylinder(const gp_Ax2& Axes,
                                                   const double  R,
                                                   const double  H,
                                                   const double  Angle)
    : myCylinder(Axes, R, H)
{
  myCylinder.Angle(Angle);
}

//=================================================================================================

void* BRepPrimAPI_MakeCylinder::OneAxis()
{
  return &myCylinder;
}

//=================================================================================================

BRepPrim_Cylinder& BRepPrimAPI_MakeCylinder::Cylinder()
{
  return myCylinder;
}
