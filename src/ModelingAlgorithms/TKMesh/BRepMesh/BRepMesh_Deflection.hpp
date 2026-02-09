#pragma once

#include <Standard_Handle.hpp>
#include <Standard_Transient.hpp>
#include <IMeshData_Types.hpp>

struct IMeshTools_Parameters;

class BRepMesh_Deflection : public Standard_Transient
{
public:
  Standard_EXPORT static double ComputeAbsoluteDeflection(const TopoDS_Shape& theShape,
                                                          const double        theRelativeDeflection,
                                                          const double        theMaxShapeSize);

  Standard_EXPORT static void ComputeDeflection(const IMeshData::IEdgeHandle& theDEdge,
                                                const double                  theMaxShapeSize,
                                                const IMeshTools_Parameters&  theParameters);

  Standard_EXPORT static void ComputeDeflection(const IMeshData::IWireHandle& theDWire,
                                                const IMeshTools_Parameters&  theParameters);

  Standard_EXPORT static void ComputeDeflection(const IMeshData::IFaceHandle& theDFace,
                                                const IMeshTools_Parameters&  theParameters);

  Standard_EXPORT static bool IsConsistent(const double theCurrent,
                                           const double theRequired,
                                           const bool   theAllowDecrease,
                                           const double theRatio = 0.1);

  DEFINE_STANDARD_RTTIEXT(BRepMesh_Deflection, Standard_Transient)
};
