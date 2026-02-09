

#include <StepFEA_SymmetricTensor43dMember.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_SymmetricTensor43dMember, StepData_SelectArrReal)

static const char* AST   = "ANISOTROPIC_SYMMETRIC_TENSOR4_3D";
static const char* IST   = "FEA_ISOTROPIC_SYMMETRIC_TENSOR4_3D";
static const char* IOST  = "FEA_ISO_ORTHOTROPIC_SYMMETRIC_TENSOR4_3D";
static const char* TIST  = "FEA_TRANSVERSE_ISOTROPIC_SYMMETRIC_TENSOR4_3D";
static const char* CNOST = "FEA_COLUMN_NORMALISED_ORTHOTROPIC_SYMMETRIC_TENSOR4_3D";
static const char* CNMST = "FEA_COLUMN_NORMALISED_MONOCLINIC_SYMMETRIC_TENSOR4_3D";

StepFEA_SymmetricTensor43dMember::StepFEA_SymmetricTensor43dMember()
    : mycase(0)
{
}

bool StepFEA_SymmetricTensor43dMember::HasName() const
{
  return mycase > 0;
}

const char* StepFEA_SymmetricTensor43dMember::Name() const
{
  switch (mycase)
  {
    case 1:
      return AST;
    case 2:
      return IST;
    case 3:
      return IOST;
    case 4:
      return TIST;
    case 5:
      return CNOST;
    case 6:
      return CNMST;
    default:
      break;
  }
  return "";
}

static int CompareNames(const char* name)
{
  int thecase = 0;
  if (!name || name[0] == '\0')
    thecase = 0;
  else if (!strcmp(name, AST))
    thecase = 1;
  else if (!strcmp(name, IST))
    thecase = 2;
  else if (!strcmp(name, IOST))
    thecase = 3;
  else if (!strcmp(name, TIST))
    thecase = 4;
  else if (!strcmp(name, CNOST))
    thecase = 5;
  else if (!strcmp(name, CNMST))
    thecase = 6;
  return thecase;
}

bool StepFEA_SymmetricTensor43dMember::SetName(const char* name)
{
  mycase = CompareNames(name);
  return (mycase > 0);
}

bool StepFEA_SymmetricTensor43dMember::Matches(const char* name) const
{
  int thecase = CompareNames(name);
  return (mycase == thecase);
}
