#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>

class TopoDS_Shape;
class GProp_GProps;
class gp_Pln;

class BRepGProp
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void LinearProperties(const TopoDS_Shape& S,
                                               GProp_GProps&       LProps,
                                               const bool          SkipShared       = false,
                                               const bool          UseTriangulation = false);

  Standard_EXPORT static void SurfaceProperties(const TopoDS_Shape& S,
                                                GProp_GProps&       SProps,
                                                const bool          SkipShared       = false,
                                                const bool          UseTriangulation = false);

  Standard_EXPORT static double SurfaceProperties(const TopoDS_Shape& S,
                                                  GProp_GProps&       SProps,
                                                  const double        Eps,
                                                  const bool          SkipShared = false);

  Standard_EXPORT static void VolumeProperties(const TopoDS_Shape& S,
                                               GProp_GProps&       VProps,
                                               const bool          OnlyClosed       = false,
                                               const bool          SkipShared       = false,
                                               const bool          UseTriangulation = false);

  Standard_EXPORT static double VolumeProperties(const TopoDS_Shape& S,
                                                 GProp_GProps&       VProps,
                                                 const double        Eps,
                                                 const bool          OnlyClosed = false,
                                                 const bool          SkipShared = false);

  Standard_EXPORT static double VolumePropertiesGK(const TopoDS_Shape& S,
                                                   GProp_GProps&       VProps,
                                                   const double        Eps        = 0.001,
                                                   const bool          OnlyClosed = false,
                                                   const bool          IsUseSpan  = false,
                                                   const bool          CGFlag     = false,
                                                   const bool          IFlag      = false,
                                                   const bool          SkipShared = false);

  Standard_EXPORT static double VolumePropertiesGK(const TopoDS_Shape& S,
                                                   GProp_GProps&       VProps,
                                                   const gp_Pln&       thePln,
                                                   const double        Eps        = 0.001,
                                                   const bool          OnlyClosed = false,
                                                   const bool          IsUseSpan  = false,
                                                   const bool          CGFlag     = false,
                                                   const bool          IFlag      = false,
                                                   const bool          SkipShared = false);
};
