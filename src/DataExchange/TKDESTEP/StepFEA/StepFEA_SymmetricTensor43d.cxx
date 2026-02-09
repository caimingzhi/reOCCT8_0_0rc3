#include <Standard_Transient.hpp>
#include <StepData_SelectMember.hpp>
#include <StepFEA_SymmetricTensor43d.hpp>
#include <StepFEA_SymmetricTensor43dMember.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

StepFEA_SymmetricTensor43d::StepFEA_SymmetricTensor43d() = default;

int StepFEA_SymmetricTensor43d::CaseNum(const occ::handle<Standard_Transient>&) const
{
  return 0;
}

int StepFEA_SymmetricTensor43d::CaseMem(const occ::handle<StepData_SelectMember>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->Matches("ANISOTROPIC_SYMMETRIC_TENSOR4_3D"))
    return 1;
  else if (ent->Matches("FEA_ISOTROPIC_SYMMETRIC_TENSOR4_3D"))
    return 2;
  else if (ent->Matches("FEA_ISO_ORTHOTROPIC_SYMMETRIC_TENSOR4_3D"))
    return 3;
  else if (ent->Matches("FEA_TRANSVERSE_ISOTROPIC_SYMMETRIC_TENSOR4_3D"))
    return 4;
  else if (ent->Matches("FEA_COLUMN_NORMALISED_ORTHOTROPIC_SYMMETRIC_TENSOR4_3D"))
    return 5;
  else if (ent->Matches("FEA_COLUMN_NORMALISED_MONOCLINIC_SYMMETRIC_TENSOR4_3D"))
    return 6;
  else
    return 0;
}

occ::handle<StepData_SelectMember> StepFEA_SymmetricTensor43d::NewMember() const
{

  return new StepFEA_SymmetricTensor43dMember;
}

occ::handle<NCollection_HArray1<double>> StepFEA_SymmetricTensor43d::AnisotropicSymmetricTensor43d()
  const
{
  occ::handle<NCollection_HArray1<double>>      anArr;
  occ::handle<StepFEA_SymmetricTensor43dMember> SelMem =
    occ::down_cast<StepFEA_SymmetricTensor43dMember>(Value());
  if (SelMem.IsNull())
    return anArr;

  return anArr;
}

occ::handle<NCollection_HArray1<double>> StepFEA_SymmetricTensor43d::
  FeaIsotropicSymmetricTensor43d() const
{
  occ::handle<NCollection_HArray1<double>>      anArr;
  occ::handle<StepFEA_SymmetricTensor43dMember> SelMem =
    occ::down_cast<StepFEA_SymmetricTensor43dMember>(Value());
  if (SelMem.IsNull())
    return anArr;

  return anArr;
}

occ::handle<NCollection_HArray1<double>> StepFEA_SymmetricTensor43d::
  FeaIsoOrthotropicSymmetricTensor43d() const
{
  return occ::down_cast<NCollection_HArray1<double>>(Value());
}

occ::handle<NCollection_HArray1<double>> StepFEA_SymmetricTensor43d::
  FeaTransverseIsotropicSymmetricTensor43d() const
{
  return occ::down_cast<NCollection_HArray1<double>>(Value());
}

occ::handle<NCollection_HArray1<double>> StepFEA_SymmetricTensor43d::
  FeaColumnNormalisedOrthotropicSymmetricTensor43d() const
{
  return occ::down_cast<NCollection_HArray1<double>>(Value());
}

occ::handle<NCollection_HArray1<double>> StepFEA_SymmetricTensor43d::
  FeaColumnNormalisedMonoclinicSymmetricTensor43d() const
{
  return occ::down_cast<NCollection_HArray1<double>>(Value());
}
