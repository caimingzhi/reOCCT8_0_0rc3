#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESDefs_TabularData.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESAppli_Node;
class IGESDefs_TabularData;

class IGESAppli_NodalConstraint : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_NodalConstraint();

  Standard_EXPORT void Init(
    const int                                                                  aType,
    const occ::handle<IGESAppli_Node>&                                         aNode,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDefs_TabularData>>>& allTabData);

  Standard_EXPORT int NbCases() const;

  Standard_EXPORT int Type() const;

  Standard_EXPORT occ::handle<IGESAppli_Node> NodeEntity() const;

  Standard_EXPORT occ::handle<IGESDefs_TabularData> TabularData(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_NodalConstraint, IGESData_IGESEntity)

private:
  int                                                                 theType;
  occ::handle<IGESAppli_Node>                                         theNode;
  occ::handle<NCollection_HArray1<occ::handle<IGESDefs_TabularData>>> theTabularDataProps;
};
