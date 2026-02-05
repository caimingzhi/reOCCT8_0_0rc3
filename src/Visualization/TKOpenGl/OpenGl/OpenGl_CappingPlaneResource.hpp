#pragma once

#include <OpenGl_PrimitiveArray.hpp>
#include <OpenGl_Resource.hpp>
#include <OpenGl_Aspects.hpp>
#include <OpenGl_Vec.hpp>
#include <Graphic3d_ClipPlane.hpp>

//! Container of graphical resources for rendering capping plane
//! associated to graphical clipping plane.
//! This resource holds data necessary for OpenGl_CappingAlgo.
//! This object is implemented as OpenGl resource for the following reasons:
//! - one instance should be shared between contexts.
//! - instance associated to Graphic3d_ClipPlane data by id.
//! - should created and released within context (owns OpenGl elements and resources).
class OpenGl_CappingPlaneResource : public OpenGl_Resource
{
public:
  //! Constructor.
  //! Create capping plane presentation associated to clipping plane data.
  //! @param[in] thePlane  the plane data.
  Standard_EXPORT OpenGl_CappingPlaneResource(const occ::handle<Graphic3d_ClipPlane>& thePlane);

  //! Destroy object.
  Standard_EXPORT ~OpenGl_CappingPlaneResource() override;

  //! Update resource data in the passed context.
  //! @param[in] theContext    the context
  //! @param[in] theObjAspect  object aspect
  Standard_EXPORT void Update(const occ::handle<OpenGl_Context>&    theContext,
                              const occ::handle<Graphic3d_Aspects>& theObjAspect);

  //! Release associated OpenGl resources.
  //! @param[in] theContext  the resource context.
  Standard_EXPORT void Release(OpenGl_Context* theContext) override;

  //! Returns estimated GPU memory usage - not implemented.
  size_t EstimatedDataSize() const override { return 0; }

  //! Return parent clipping plane structure.
  const occ::handle<Graphic3d_ClipPlane>& Plane() const { return myPlaneRoot; }

  //! @return aspect face for rendering capping surface.
  inline const OpenGl_Aspects* AspectFace() const { return myAspect; }

  //! @return evaluated orientation matrix to transform infinite plane.
  inline const NCollection_Mat4<float>& Orientation() const { return myOrientation; }

  //! @return primitive array of vertices to render infinite plane.
  inline const OpenGl_PrimitiveArray& Primitives() const { return myPrimitives; }

private:
  //! Update precomputed plane orientation matrix.
  void updateTransform(const occ::handle<OpenGl_Context>& theCtx);

  //! Update resources.
  void updateAspect(const occ::handle<Graphic3d_Aspects>& theObjAspect);

private:
  OpenGl_PrimitiveArray            myPrimitives; //!< vertices and texture coordinates for rendering
  NCollection_Mat4<float>          myOrientation;    //!< plane transformation matrix.
  OpenGl_Aspects*                  myAspect;         //!< capping face aspect.
  occ::handle<Graphic3d_ClipPlane> myPlaneRoot;      //!< parent clipping plane structure.
  occ::handle<Graphic3d_Aspects>   myFillAreaAspect; //!< own capping aspect
  gp_XYZ                           myLocalOrigin;    //!< layer origin
  unsigned int                     myEquationMod;    //!< modification counter for plane equation.
  unsigned int                     myAspectMod;      //!< modification counter for aspect.

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_CappingPlaneResource, OpenGl_Resource) // Type definition
};
