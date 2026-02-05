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

//! Representation of STEP SELECT type SymmetricTensor23d
class StepFEA_SymmetricTensor23d : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepFEA_SymmetricTensor23d();

  //! Recognizes a kind of SymmetricTensor23d select type
  //! return 0
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Recognizes a items of select member SymmetricTensor23dMember
  //! 1 -> IsotropicSymmetricTensor23d
  //! 2 -> OrthotropicSymmetricTensor23d
  //! 3 -> AnisotropicSymmetricTensor23d
  //! 0 else
  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  //! Returns a new select member the type SymmetricTensor23dMember
  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  //! Set Value for IsotropicSymmetricTensor23d
  Standard_EXPORT void SetIsotropicSymmetricTensor23d(const double aVal);

  //! Returns Value as IsotropicSymmetricTensor23d (or Null if another type)
  Standard_EXPORT double IsotropicSymmetricTensor23d() const;

  //! Set Value for OrthotropicSymmetricTensor23d
  Standard_EXPORT void SetOrthotropicSymmetricTensor23d(
    const occ::handle<NCollection_HArray1<double>>& aVal);

  //! Returns Value as OrthotropicSymmetricTensor23d (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> OrthotropicSymmetricTensor23d() const;

  //! Set Value for AnisotropicSymmetricTensor23d
  Standard_EXPORT void SetAnisotropicSymmetricTensor23d(
    const occ::handle<NCollection_HArray1<double>>& aVal);

  //! Returns Value as AnisotropicSymmetricTensor23d (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> AnisotropicSymmetricTensor23d() const;
};
