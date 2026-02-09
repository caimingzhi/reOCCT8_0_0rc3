

#include <StepData_SelectNamed.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_SelectNamed, StepData_SelectMember)

#define KindInteger 1
#define KindBoolean 2
#define KindLogical 3
#define KindEnum 4
#define KindReal 5
#define KindString 6

StepData_SelectNamed::StepData_SelectNamed()
{
  theval.Clear();
  thename.Clear();
}

bool StepData_SelectNamed::HasName() const
{
  return (thename.Length() > 0);
}

const char* StepData_SelectNamed::Name() const
{
  return thename.ToCString();
}

bool StepData_SelectNamed::SetName(const char* name)
{
  thename.Clear();
  thename.AssignCat(name);
  return true;
}

const StepData_Field& StepData_SelectNamed::Field() const
{
  return theval;
}

StepData_Field& StepData_SelectNamed::CField()
{
  return theval;
}

int StepData_SelectNamed::Kind() const
{
  return theval.Kind();
}

void StepData_SelectNamed::SetKind(const int kind)
{
  theval.Clear(kind);
}

int StepData_SelectNamed::Int() const
{
  return theval.Int();
}

void StepData_SelectNamed::SetInt(const int val)
{
  theval.SetInt(val);
}

double StepData_SelectNamed::Real() const
{
  return theval.Real();
}

void StepData_SelectNamed::SetReal(const double val)
{
  theval.SetReal(val);
}

const char* StepData_SelectNamed::String() const
{
  return theval.String();
}

void StepData_SelectNamed::SetString(const char* val)
{
  theval.SetString(val);
}
