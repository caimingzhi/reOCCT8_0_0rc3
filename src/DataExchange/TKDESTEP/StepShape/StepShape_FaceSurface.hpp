#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Face.hpp>
#include <StepShape_FaceBound.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class StepGeom_Surface;
class TCollection_HAsciiString;

class StepShape_FaceSurface : public StepShape_Face
{

public:
  //! Returns a FaceSurface
  Standard_EXPORT StepShape_FaceSurface();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                              aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>& aBounds,
    const occ::handle<StepGeom_Surface>&                                      aFaceGeometry,
    const bool                                                                aSameSense);

  Standard_EXPORT void SetFaceGeometry(const occ::handle<StepGeom_Surface>& aFaceGeometry);

  Standard_EXPORT occ::handle<StepGeom_Surface> FaceGeometry() const;

  Standard_EXPORT void SetSameSense(const bool aSameSense);

  Standard_EXPORT bool SameSense() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_FaceSurface, StepShape_Face)

private:
  occ::handle<StepGeom_Surface> faceGeometry;
  bool                          sameSense;
};

