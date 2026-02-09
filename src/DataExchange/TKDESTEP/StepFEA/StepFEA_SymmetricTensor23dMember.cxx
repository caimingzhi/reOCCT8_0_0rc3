#include <StepFEA_SymmetricTensor23dMember.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_SymmetricTensor23dMember, StepData_SelectArrReal)

static const char* IST = "ISOTROPIC_SYMMETRIC_TENSOR2_3D";
static const char* OST = "ORTHOTROPIC_SYMMETRIC_TENSOR2_3D";
static const char* AST = "ANISOTROPIC_SYMMETRIC_TENSOR2_3D";

StepFEA_SymmetricTensor23dMember::StepFEA_SymmetricTensor23dMember()
    : mycase(0)
{
}

bool StepFEA_SymmetricTensor23dMember::HasName() const
{
  return mycase > 0;
}

const char* StepFEA_SymmetricTensor23dMember::Name() const
{
  switch (mycase)
  {
    case 1:
      return IST;
    case 2:
      return OST;
    case 3:
      return AST;
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
  else if (!strcmp(name, IST))
    thecase = 1;
  else if (!strcmp(name, OST))
    thecase = 2;
  else if (!strcmp(name, AST))
    thecase = 3;
  return thecase;
}

bool StepFEA_SymmetricTensor23dMember::SetName(const char* name)
{
  mycase = CompareNames(name);
  return (mycase > 0);
}

bool StepFEA_SymmetricTensor23dMember::Matches(const char* name) const
{
  int thecase = CompareNames(name);
  return (mycase == thecase);
}
