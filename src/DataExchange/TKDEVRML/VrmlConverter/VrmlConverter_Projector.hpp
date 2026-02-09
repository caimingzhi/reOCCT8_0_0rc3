#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <HLRAlgo_Projector.hpp>
#include <Vrml_PerspectiveCamera.hpp>
#include <Vrml_OrthographicCamera.hpp>
#include <Vrml_DirectionalLight.hpp>
#include <Vrml_PointLight.hpp>
#include <Vrml_SpotLight.hpp>

enum VrmlConverter_TypeOfCamera
{
  VrmlConverter_NoCamera,
  VrmlConverter_PerspectiveCamera,
  VrmlConverter_OrthographicCamera
};

enum VrmlConverter_TypeOfLight
{
  VrmlConverter_NoLight,
  VrmlConverter_DirectionLight,
  VrmlConverter_PointLight,
  VrmlConverter_SpotLight
};

#include <Vrml_MatrixTransform.hpp>
#include <Standard_Transient.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_OStream.hpp>

class VrmlConverter_Projector : public Standard_Transient
{

public:
  Standard_EXPORT VrmlConverter_Projector(
    const NCollection_Array1<TopoDS_Shape>& Shapes,
    const double                            Focus,
    const double                            DX,
    const double                            DY,
    const double                            DZ,
    const double                            XUp,
    const double                            YUp,
    const double                            ZUp,
    const VrmlConverter_TypeOfCamera        Camera = VrmlConverter_NoCamera,
    const VrmlConverter_TypeOfLight         Light  = VrmlConverter_NoLight);

  Standard_EXPORT void SetCamera(const VrmlConverter_TypeOfCamera aCamera);

  Standard_EXPORT VrmlConverter_TypeOfCamera Camera() const;

  Standard_EXPORT void SetLight(const VrmlConverter_TypeOfLight aLight);

  Standard_EXPORT VrmlConverter_TypeOfLight Light() const;

  Standard_EXPORT void Add(Standard_OStream& anOStream) const;

  Standard_EXPORT HLRAlgo_Projector Projector() const;

  DEFINE_STANDARD_RTTIEXT(VrmlConverter_Projector, Standard_Transient)

private:
  HLRAlgo_Projector          myProjector;
  Vrml_PerspectiveCamera     myPerspectiveCamera;
  Vrml_OrthographicCamera    myOrthographicCamera;
  Vrml_DirectionalLight      myDirectionalLight;
  Vrml_PointLight            myPointLight;
  Vrml_SpotLight             mySpotLight;
  VrmlConverter_TypeOfCamera myTypeOfCamera;
  VrmlConverter_TypeOfLight  myTypeOfLight;
  Vrml_MatrixTransform       myMatrixTransform;
};
