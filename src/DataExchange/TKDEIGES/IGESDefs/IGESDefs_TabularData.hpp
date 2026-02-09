#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESBasic_HArray1OfHArray1OfReal;

class IGESDefs_TabularData : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_TabularData();

  Standard_EXPORT void Init(const int                                            nbProps,
                            const int                                            propType,
                            const occ::handle<NCollection_HArray1<int>>&         typesInd,
                            const occ::handle<NCollection_HArray1<int>>&         nbValuesInd,
                            const occ::handle<IGESBasic_HArray1OfHArray1OfReal>& valuesInd,
                            const occ::handle<IGESBasic_HArray1OfHArray1OfReal>& valuesDep);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int ComputedNbPropertyValues() const;

  Standard_EXPORT bool OwnCorrect();

  Standard_EXPORT int PropertyType() const;

  Standard_EXPORT int NbDependents() const;

  Standard_EXPORT int NbIndependents() const;

  Standard_EXPORT int TypeOfIndependents(const int num) const;

  Standard_EXPORT int NbValues(const int num) const;

  Standard_EXPORT double IndependentValue(const int variablenum, const int valuenum) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> DependentValues(const int num) const;

  Standard_EXPORT double DependentValue(const int variablenum, const int valuenum) const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_TabularData, IGESData_IGESEntity)

private:
  int                                           theNbPropertyValues;
  int                                           thePropertyType;
  occ::handle<NCollection_HArray1<int>>         theTypeOfIndependentVariables;
  occ::handle<NCollection_HArray1<int>>         theNbValues;
  occ::handle<IGESBasic_HArray1OfHArray1OfReal> theIndependentValues;
  occ::handle<IGESBasic_HArray1OfHArray1OfReal> theDependentValues;
};
