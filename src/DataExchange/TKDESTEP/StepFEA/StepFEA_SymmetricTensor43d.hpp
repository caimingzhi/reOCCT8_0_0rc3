#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Standard_Transient;
class StepData_SelectMember;

class StepFEA_SymmetricTensor43d : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepFEA_SymmetricTensor43d();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> AnisotropicSymmetricTensor43d() const;

  Standard_EXPORT void SetFeaIsotropicSymmetricTensor43d(
    const occ::handle<NCollection_HArray1<double>>& val);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> FeaIsotropicSymmetricTensor43d() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> FeaIsoOrthotropicSymmetricTensor43d()
    const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>>
                  FeaTransverseIsotropicSymmetricTensor43d() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>>
                  FeaColumnNormalisedOrthotropicSymmetricTensor43d() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>>
                  FeaColumnNormalisedMonoclinicSymmetricTensor43d() const;
};
