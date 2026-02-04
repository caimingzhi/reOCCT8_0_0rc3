#pragma once


#include <Standard_Transient.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <IMeshTools_MeshAlgo.hpp>

struct IMeshTools_Parameters;

//! Base interface for factories producing instances of triangulation
//! algorithms taking into account type of surface of target face.
class IMeshTools_MeshAlgoFactory : public Standard_Transient
{
public:
  //! Destructor.
  ~IMeshTools_MeshAlgoFactory() override = default;

  //! Creates instance of meshing algorithm for the given type of surface.
  Standard_EXPORT virtual occ::handle<IMeshTools_MeshAlgo> GetAlgo(
    const GeomAbs_SurfaceType    theSurfaceType,
    const IMeshTools_Parameters& theParameters) const = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshTools_MeshAlgoFactory, Standard_Transient)

protected:
  //! Constructor.
  IMeshTools_MeshAlgoFactory() {}
};

