#include <DrawTrSurf.hpp>
#include <GeomTools.hpp>
#include <GeomTools_SurfaceSet.hpp>
#include <GeomTools_CurveSet.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Geom_Geometry.hpp>
#include <Geom2d_Curve.hpp>

Standard_EXPORT const char* DrawTrSurf_Set(const char* theNameStr, void* theHandlePtr)
{
  if (theNameStr == nullptr || theHandlePtr == nullptr)
  {
    return "Error: argument is null";
  }
  try
  {
    const occ::handle<Standard_Transient>& aHandle =
      *(occ::handle<Standard_Transient>*)theHandlePtr;
    occ::handle<Geom_Geometry> aGeom3d = occ::down_cast<Geom_Geometry>(aHandle);
    if (!aGeom3d.IsNull())
    {
      DrawTrSurf::Set(theNameStr, aGeom3d);
      return theNameStr;
    }
    occ::handle<Geom2d_Curve> aGeom2d = occ::down_cast<Geom2d_Curve>(aHandle);
    if (!aGeom2d.IsNull())
    {
      DrawTrSurf::Set(theNameStr, aGeom2d);
      return theNameStr;
    }

    return "Error: Not a geometric object";
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}

Standard_EXPORT const char* DrawTrSurf_SetPnt(const char* theNameStr, void* thePntPtr)
{
  if (theNameStr == nullptr || thePntPtr == nullptr)
  {
    return "Error: argument is null";
  }
  try
  {
    const gp_Pnt& aP = *(gp_Pnt*)thePntPtr;
    static char   buff[256];
    Sprintf(buff,
            "Point (%.16g, %.16g, %.16g) set to DRAW variable %.80s",
            aP.X(),
            aP.Y(),
            aP.Z(),
            theNameStr);
    DrawTrSurf::Set(theNameStr, aP);
    return buff;
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}

Standard_EXPORT const char* DrawTrSurf_SetPnt2d(const char* theNameStr, void* thePnt2dPtr)
{
  if (theNameStr == nullptr || thePnt2dPtr == nullptr)
  {
    return "Error: argument is null";
  }
  try
  {
    const gp_Pnt2d& aP = *(gp_Pnt2d*)thePnt2dPtr;
    static char     buff[256];
    Sprintf(buff, "Point (%.16g, %.16g) set to DRAW variable %.80s", aP.X(), aP.Y(), theNameStr);
    DrawTrSurf::Set(theNameStr, aP);
    return buff;
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}

#ifndef _MSC_VER

Standard_EXPORT const char* DrawTrSurf_Set(const char*                            name,
                                           const occ::handle<Standard_Transient>& G)
{
  return DrawTrSurf_Set(name, (void*)&G);
}

Standard_EXPORT const char* DrawTrSurf_Set(const char* theName, const gp_Pnt& thePnt)
{
  return DrawTrSurf_SetPnt(theName, (void*)&thePnt);
}

Standard_EXPORT const char* DrawTrSurf_Set(const char* theName, const gp_Pnt2d& thePnt2d)
{
  return DrawTrSurf_SetPnt2d(theName, (void*)&thePnt2d);
}

#endif
