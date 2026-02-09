#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

class IGESSolid_BooleanTree : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_BooleanTree();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& operands,
    const occ::handle<NCollection_HArray1<int>>&                              operations);

  Standard_EXPORT int Length() const;

  Standard_EXPORT bool IsOperand(const int Index) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Operand(const int Index) const;

  Standard_EXPORT int Operation(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_BooleanTree, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theOperands;
  occ::handle<NCollection_HArray1<int>>                              theOperations;
};
