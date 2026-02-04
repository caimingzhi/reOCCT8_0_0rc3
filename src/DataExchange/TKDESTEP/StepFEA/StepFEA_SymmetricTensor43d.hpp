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

//! Representation of STEP SELECT type SymmetricTensor43d
class StepFEA_SymmetricTensor43d : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepFEA_SymmetricTensor43d();

  //! return 0
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Recognizes a items of select member CurveElementFreedomMember
  //! 1 -> AnisotropicSymmetricTensor43d
  //! 2 -> FeaIsotropicSymmetricTensor43d
  //! 3 -> FeaIsoOrthotropicSymmetricTensor43d
  //! 4 -> FeaTransverseIsotropicSymmetricTensor43d
  //! 5 -> FeaColumnNormalisedOrthotropicSymmetricTensor43d
  //! 6 -> FeaColumnNormalisedMonoclinicSymmetricTensor43d
  //! 0 else
  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  //! Returns Value as AnisotropicSymmetricTensor43d (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> AnisotropicSymmetricTensor43d() const;

  Standard_EXPORT void SetFeaIsotropicSymmetricTensor43d(
    const occ::handle<NCollection_HArray1<double>>& val);

  //! Returns Value as FeaIsotropicSymmetricTensor43d (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> FeaIsotropicSymmetricTensor43d() const;

  //! Returns Value as FeaIsoOrthotropicSymmetricTensor43d (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> FeaIsoOrthotropicSymmetricTensor43d()
    const;

  //! Returns Value as FeaTransverseIsotropicSymmetricTensor43d (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>>
                  FeaTransverseIsotropicSymmetricTensor43d() const;

  //! Returns Value as FeaColumnNormalisedOrthotropicSymmetricTensor43d (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>>
                  FeaColumnNormalisedOrthotropicSymmetricTensor43d() const;

  //! Returns Value as FeaColumnNormalisedMonoclinicSymmetricTensor43d (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>>
                  FeaColumnNormalisedMonoclinicSymmetricTensor43d() const;
};

