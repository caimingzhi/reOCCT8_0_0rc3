#include <IGESBasic_HArray1OfHArray1OfReal.hpp>
#include <IGESDefs_TabularData.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDefs_TabularData, IGESData_IGESEntity)

IGESDefs_TabularData::IGESDefs_TabularData() = default;

void IGESDefs_TabularData::Init(const int nbProps,
                                const int propType,

                                const occ::handle<NCollection_HArray1<int>>&         typesInd,
                                const occ::handle<NCollection_HArray1<int>>&         nbValuesInd,
                                const occ::handle<IGESBasic_HArray1OfHArray1OfReal>& valuesInd,
                                const occ::handle<IGESBasic_HArray1OfHArray1OfReal>& valuesDep)
{
  int num = typesInd->Length();
  if (typesInd->Lower() != 1 || nbValuesInd->Lower() != 1 || nbValuesInd->Length() != num
      || valuesInd->Lower() != 1 || valuesInd->Length() != num || valuesDep->Lower() != 1)
    throw Standard_DimensionMismatch("IGESDefs_TabularData : Init");
  theNbPropertyValues = nbProps;
  thePropertyType     = propType;

  theTypeOfIndependentVariables = typesInd;
  theNbValues                   = nbValuesInd;
  theIndependentValues          = valuesInd;
  theDependentValues            = valuesDep;
  InitTypeAndForm(406, 11);
}

int IGESDefs_TabularData::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESDefs_TabularData::ComputedNbPropertyValues() const
{
  return theNbPropertyValues;
}

bool IGESDefs_TabularData::OwnCorrect()
{
  int newnb = ComputedNbPropertyValues();
  if (newnb == theNbPropertyValues)
    return false;
  theNbPropertyValues = newnb;
  return true;
}

int IGESDefs_TabularData::PropertyType() const
{
  return thePropertyType;
}

int IGESDefs_TabularData::NbDependents() const
{
  return theDependentValues->Length();
}

int IGESDefs_TabularData::NbIndependents() const
{
  return theTypeOfIndependentVariables->Length();
}

int IGESDefs_TabularData::TypeOfIndependents(const int num) const
{
  return theTypeOfIndependentVariables->Value(num);
}

int IGESDefs_TabularData::NbValues(const int num) const
{
  return theNbValues->Value(num);
}

double IGESDefs_TabularData::IndependentValue(const int variablenum, const int valuenum) const
{
  return (theIndependentValues->Value(variablenum))->Value(valuenum);
}

occ::handle<NCollection_HArray1<double>> IGESDefs_TabularData::DependentValues(const int num) const
{
  return theDependentValues->Value(num);
}

double IGESDefs_TabularData::DependentValue(const int, const int) const
{
  double val = 0.;
  return val;
}
