#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Shape;
class Bnd_Box;
class Bnd_OBB;

class BRepBndLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const TopoDS_Shape& S,
                                  Bnd_Box&            B,
                                  const bool          useTriangulation = true);

  Standard_EXPORT static void AddClose(const TopoDS_Shape& S, Bnd_Box& B);

  Standard_EXPORT static void AddOptimal(const TopoDS_Shape& S,
                                         Bnd_Box&            B,
                                         const bool          useTriangulation  = true,
                                         const bool          useShapeTolerance = false);

  Standard_EXPORT static void AddOBB(const TopoDS_Shape& theS,
                                     Bnd_OBB&            theOBB,
                                     const bool          theIsTriangulationUsed  = true,
                                     const bool          theIsOptimal            = false,
                                     const bool          theIsShapeToleranceUsed = true);
};
