#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

enum StdSelect_TypeOfFace
{
  StdSelect_AnyFace,
  StdSelect_Plane,
  StdSelect_Cylinder,
  StdSelect_Sphere,
  StdSelect_Torus,
  StdSelect_Revol,
  StdSelect_Cone
};

#include <SelectMgr_Filter.hpp>
#include <TopAbs_ShapeEnum.hpp>
class SelectMgr_EntityOwner;

//! A framework to define a filter to select a specific type of face.
//! The types available include:
//! -   any face
//! -   a planar face
//! -   a cylindrical face
//! -   a spherical face
//! -   a toroidal face
//! -   a revol face.
class StdSelect_FaceFilter : public SelectMgr_Filter
{

public:
  //! Constructs a face filter object defined by the type of face aTypeOfFace.
  Standard_EXPORT StdSelect_FaceFilter(const StdSelect_TypeOfFace aTypeOfFace);

  //! Sets the type of face aNewType. aNewType is to be highlighted in selection.
  Standard_EXPORT void SetType(const StdSelect_TypeOfFace aNewType);

  //! Returns the type of face to be highlighted in selection.
  Standard_EXPORT StdSelect_TypeOfFace Type() const;

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aStandardMode) const override;

  DEFINE_STANDARD_RTTIEXT(StdSelect_FaceFilter, SelectMgr_Filter)

private:
  StdSelect_TypeOfFace mytype;
};
