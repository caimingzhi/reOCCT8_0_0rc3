#pragma once

#include <Standard_Transient.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <IMeshTools_MeshAlgo.hpp>

struct IMeshTools_Parameters;

class IMeshTools_MeshAlgoFactory : public Standard_Transient
{
public:
  ~IMeshTools_MeshAlgoFactory() override = default;

  Standard_EXPORT virtual occ::handle<IMeshTools_MeshAlgo> GetAlgo(
    const GeomAbs_SurfaceType    theSurfaceType,
    const IMeshTools_Parameters& theParameters) const = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshTools_MeshAlgoFactory, Standard_Transient)

protected:
  IMeshTools_MeshAlgoFactory() {}
};
