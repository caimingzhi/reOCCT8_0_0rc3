

#include <Interface_EntityIterator.hpp>
#include <Standard_OutOfRange.hpp>
#include <StepData_Field.hpp>
#include <StepData_FieldList.hpp>

static StepData_Field nulfild;

StepData_FieldList::~StepData_FieldList() = default;

StepData_FieldList::StepData_FieldList() = default;

int StepData_FieldList::NbFields() const
{
  return 0;
}

const StepData_Field& StepData_FieldList::Field(const int) const
{
  throw Standard_OutOfRange("StepData_FieldList : Field");
}

StepData_Field& StepData_FieldList::CField(const int)
{
  throw Standard_OutOfRange("StepData_FieldList : CField");
}

void StepData_FieldList::FillShared(Interface_EntityIterator& iter) const
{
  int i, nb = NbFields();
  for (i = 1; i <= nb; i++)
  {
    const StepData_Field& fi = Field(i);
    if (fi.Kind() != 7)
      continue;
    int i1, i2, nb1 = 1, nb2 = 1, ari = fi.Arity();
    if (ari == 1)
      nb1 = fi.Length();
    if (ari == 2)
    {
      nb1 = fi.Length(1);
      nb2 = fi.Length(2);
    }
    for (i1 = 1; i1 <= nb1; i1++)
      for (i2 = 1; i2 <= nb2; i2++)
        iter.AddItem(fi.Entity(i1, i2));
  }
}
