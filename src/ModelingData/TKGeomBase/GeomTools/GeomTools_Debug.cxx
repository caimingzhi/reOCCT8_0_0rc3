#include <GeomTools.hpp>
#include <GeomTools_SurfaceSet.hpp>
#include <GeomTools_CurveSet.hpp>
#include <GeomTools_Curve2dSet.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Geom_Surface.hpp>
#include <Geom_Curve.hpp>
#include <Geom2d_Curve.hpp>

const char* GeomTools_Dump(void* theHandlePtr)
{
  if (theHandlePtr == nullptr)
  {
    return "Error: argument is null";
  }
  try
  {
    OCC_CATCH_SIGNALS
    const occ::handle<Standard_Transient>& aHandle =
      *(occ::handle<Standard_Transient>*)theHandlePtr;

    occ::handle<Geom_Surface> GS = occ::down_cast<Geom_Surface>(aHandle);
    if (!GS.IsNull())
    {
      std::cout << "\n\n";
      GeomTools_SurfaceSet::PrintSurface(GS, std::cout);
      std::cout << std::endl;
      return "Found Geom_Surface, see dump in std::cout";
    }

    occ::handle<Geom_Curve> GC = occ::down_cast<Geom_Curve>(aHandle);
    if (!GC.IsNull())
    {
      std::cout << "\n\n";
      GeomTools_CurveSet::PrintCurve(GC, std::cout);
      std::cout << std::endl;
      return "Found Geom_Curve, see dump in std::cout";
    }

    occ::handle<Geom2d_Curve> GC2d = occ::down_cast<Geom2d_Curve>(aHandle);
    if (!GC2d.IsNull())
    {
      std::cout << "\n\n";
      GeomTools_Curve2dSet::PrintCurve2d(GC2d, std::cout);
      std::cout << std::endl;
      return "Found Geom2d_Curve, see dump in std::cout";
    }

    return "Error: Not a geometric object";
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}

#ifndef _MSC_VER

const char* GeomTools_Dump(const occ::handle<Standard_Transient>& theGeom)
{
  return GeomTools_Dump((void*)&theGeom);
}

#endif
