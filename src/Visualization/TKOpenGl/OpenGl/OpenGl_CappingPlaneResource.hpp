#pragma once

#include <OpenGl_PrimitiveArray.hpp>
#include <OpenGl_Resource.hpp>
#include <OpenGl_Aspects.hpp>
#include <OpenGl_Vec.hpp>
#include <Graphic3d_ClipPlane.hpp>

class OpenGl_CappingPlaneResource : public OpenGl_Resource
{
public:
  Standard_EXPORT OpenGl_CappingPlaneResource(const occ::handle<Graphic3d_ClipPlane>& thePlane);

  Standard_EXPORT ~OpenGl_CappingPlaneResource() override;

  Standard_EXPORT void Update(const occ::handle<OpenGl_Context>&    theContext,
                              const occ::handle<Graphic3d_Aspects>& theObjAspect);

  Standard_EXPORT void Release(OpenGl_Context* theContext) override;

  size_t EstimatedDataSize() const override { return 0; }

  const occ::handle<Graphic3d_ClipPlane>& Plane() const { return myPlaneRoot; }

  inline const OpenGl_Aspects* AspectFace() const { return myAspect; }

  inline const NCollection_Mat4<float>& Orientation() const { return myOrientation; }

  inline const OpenGl_PrimitiveArray& Primitives() const { return myPrimitives; }

private:
  void updateTransform(const occ::handle<OpenGl_Context>& theCtx);

  void updateAspect(const occ::handle<Graphic3d_Aspects>& theObjAspect);

private:
  OpenGl_PrimitiveArray            myPrimitives;
  NCollection_Mat4<float>          myOrientation;
  OpenGl_Aspects*                  myAspect;
  occ::handle<Graphic3d_ClipPlane> myPlaneRoot;
  occ::handle<Graphic3d_Aspects>   myFillAreaAspect;
  gp_XYZ                           myLocalOrigin;
  unsigned int                     myEquationMod;
  unsigned int                     myAspectMod;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_CappingPlaneResource, OpenGl_Resource)
};
