#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

//! defines BooleanTree, Type <180> Form Number <0>
//! in package IGESSolid
//! The Boolean tree describes a binary tree structure
//! composed of regularized Boolean operations and operands,
//! in post-order notation.
class IGESSolid_BooleanTree : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_BooleanTree();

  //! This method is used to set the fields of the class
  //! BooleanTree
  //! - operands   : Array containing pointer to DE of operands
  //! - operations : Array containing integer type for operations
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& operands,
    const occ::handle<NCollection_HArray1<int>>&                              operations);

  //! returns the length of the post-order list
  Standard_EXPORT int Length() const;

  //! returns True if Index'th value in the post-order list is an Operand;
  //! else returns False if it is an Integer Operations
  //! raises exception if Index < 1 or Index > Length()
  Standard_EXPORT bool IsOperand(const int Index) const;

  //! returns the Index'th value in the post-order list only if it is
  //! an operand else returns NULL
  //! raises exception if Index < 1 or Index > Length()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Operand(const int Index) const;

  //! returns the Index'th value in the post-order list only if it is
  //! an operation else returns 0
  //! raises exception if Index < 1 or Index > Length()
  Standard_EXPORT int Operation(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_BooleanTree, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theOperands;
  occ::handle<NCollection_HArray1<int>>                              theOperations;
};
