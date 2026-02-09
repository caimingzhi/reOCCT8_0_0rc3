#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

enum StepElement_ElementVolume
{
  StepElement_Volume
};

enum StepElement_CurveEdge
{
  StepElement_ElementEdge
};

class Standard_Transient;
class StepData_SelectMember;

class StepElement_ElementAspect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepElement_ElementAspect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  Standard_EXPORT void SetElementVolume(const StepElement_ElementVolume aVal);

  Standard_EXPORT StepElement_ElementVolume ElementVolume() const;

  Standard_EXPORT void SetVolume3dFace(const int aVal);

  Standard_EXPORT int Volume3dFace() const;

  Standard_EXPORT void SetVolume2dFace(const int aVal);

  Standard_EXPORT int Volume2dFace() const;

  Standard_EXPORT void SetVolume3dEdge(const int aVal);

  Standard_EXPORT int Volume3dEdge() const;

  Standard_EXPORT void SetVolume2dEdge(const int aVal);

  Standard_EXPORT int Volume2dEdge() const;

  Standard_EXPORT void SetSurface3dFace(const int aVal);

  Standard_EXPORT int Surface3dFace() const;

  Standard_EXPORT void SetSurface2dFace(const int aVal);

  Standard_EXPORT int Surface2dFace() const;

  Standard_EXPORT void SetSurface3dEdge(const int aVal);

  Standard_EXPORT int Surface3dEdge() const;

  Standard_EXPORT void SetSurface2dEdge(const int aVal);

  Standard_EXPORT int Surface2dEdge() const;

  Standard_EXPORT void SetCurveEdge(const StepElement_CurveEdge aVal);

  Standard_EXPORT StepElement_CurveEdge CurveEdge() const;
};
