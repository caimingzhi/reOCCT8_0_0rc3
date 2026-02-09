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

class StdSelect_FaceFilter : public SelectMgr_Filter
{

public:
  Standard_EXPORT StdSelect_FaceFilter(const StdSelect_TypeOfFace aTypeOfFace);

  Standard_EXPORT void SetType(const StdSelect_TypeOfFace aNewType);

  Standard_EXPORT StdSelect_TypeOfFace Type() const;

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aStandardMode) const override;

  DEFINE_STANDARD_RTTIEXT(StdSelect_FaceFilter, SelectMgr_Filter)

private:
  StdSelect_TypeOfFace mytype;
};
