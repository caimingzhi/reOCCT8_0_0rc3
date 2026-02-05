#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Macro.hpp>
#include <BRepMesh_DiscretRoot.hpp>

class TopoDS_Shape;

class XBRepMesh
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int Discret(const TopoDS_Shape&    theShape,
                                     const double           theDeflection,
                                     const double           theAngle,
                                     BRepMesh_DiscretRoot*& theAlgo);
};
