#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Standard_Transient;

//! Representation of STEP SELECT type SymmetricTensor22d
class StepFEA_SymmetricTensor22d : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepFEA_SymmetricTensor22d();

  //! Recognizes a kind of SymmetricTensor22d select type
  //! 1 -> HArray1OfReal from TColStd
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as AnisotropicSymmetricTensor22d (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> AnisotropicSymmetricTensor22d() const;
};

