#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESDefs_TabularData.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESAppli_Node;
class IGESDefs_TabularData;

//! defines NodalConstraint, Type <418> Form <0>
//! in package IGESAppli
//! Relates loads and/or constraints to specific nodes in
//! the Finite Element Model by creating a relation between
//! Node entities and Tabular Data Property that contains
//! the load or constraint data
class IGESAppli_NodalConstraint : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_NodalConstraint();

  //! This method is used to set the fields of the class
  //! NodalConstraint
  //! - aType      : Loads / Constraints
  //! - aNode      : the Node
  //! - allTabData : Tabular Data Property carrying the load
  //! or constraint vector
  Standard_EXPORT void Init(
    const int                                                                  aType,
    const occ::handle<IGESAppli_Node>&                                         aNode,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDefs_TabularData>>>& allTabData);

  //! returns total number of cases
  Standard_EXPORT int NbCases() const;

  //! returns whether Loads (1) or Constraints (2)
  Standard_EXPORT int Type() const;

  //! returns the Node
  Standard_EXPORT occ::handle<IGESAppli_Node> NodeEntity() const;

  //! returns Tabular Data Property carrying load or constraint vector
  //! raises exception if Index <= 0 or Index > NbCases
  Standard_EXPORT occ::handle<IGESDefs_TabularData> TabularData(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_NodalConstraint, IGESData_IGESEntity)

private:
  int                                                                 theType;
  occ::handle<IGESAppli_Node>                                         theNode;
  occ::handle<NCollection_HArray1<occ::handle<IGESDefs_TabularData>>> theTabularDataProps;
};

