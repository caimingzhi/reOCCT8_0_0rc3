

#include <IGESBasic_Protocol.hpp>

#include <IGESBasic_AssocGroupType.hpp>
#include <IGESBasic_ExternalRefFile.hpp>
#include <IGESBasic_ExternalRefFileIndex.hpp>
#include <IGESBasic_ExternalRefFileName.hpp>
#include <IGESBasic_ExternalRefLibName.hpp>
#include <IGESBasic_ExternalRefName.hpp>
#include <IGESBasic_ExternalReferenceFile.hpp>
#include <IGESBasic_GroupWithoutBackP.hpp>
#include <IGESBasic_Hierarchy.hpp>
#include <IGESBasic_Name.hpp>
#include <IGESBasic_OrderedGroup.hpp>
#include <IGESBasic_OrderedGroupWithoutBackP.hpp>
#include <IGESBasic_SingleParent.hpp>
#include <IGESBasic_SingularSubfigure.hpp>
#include <IGESBasic_SubfigureDef.hpp>
#include <IGESData.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_Protocol, IGESData_Protocol)

IGESBasic_Protocol::IGESBasic_Protocol() = default;

int IGESBasic_Protocol::NbResources() const
{
  return 1;
}

occ::handle<Interface_Protocol> IGESBasic_Protocol::Resource(const int) const
{
  occ::handle<Interface_Protocol> res = IGESData::Protocol();
  return res;
}

int IGESBasic_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(IGESBasic_AssocGroupType))
    return 1;
  else if (atype == STANDARD_TYPE(IGESBasic_ExternalRefFile))
    return 2;
  else if (atype == STANDARD_TYPE(IGESBasic_ExternalRefFileIndex))
    return 3;
  else if (atype == STANDARD_TYPE(IGESBasic_ExternalRefFileName))
    return 4;
  else if (atype == STANDARD_TYPE(IGESBasic_ExternalRefLibName))
    return 5;
  else if (atype == STANDARD_TYPE(IGESBasic_ExternalRefName))
    return 6;
  else if (atype == STANDARD_TYPE(IGESBasic_ExternalReferenceFile))
    return 7;
  else if (atype == STANDARD_TYPE(IGESBasic_Group))
    return 8;
  else if (atype == STANDARD_TYPE(IGESBasic_GroupWithoutBackP))
    return 9;
  else if (atype == STANDARD_TYPE(IGESBasic_Hierarchy))
    return 10;
  else if (atype == STANDARD_TYPE(IGESBasic_Name))
    return 11;
  else if (atype == STANDARD_TYPE(IGESBasic_OrderedGroup))
    return 12;
  else if (atype == STANDARD_TYPE(IGESBasic_OrderedGroupWithoutBackP))
    return 13;
  else if (atype == STANDARD_TYPE(IGESBasic_SingleParent))
    return 14;
  else if (atype == STANDARD_TYPE(IGESBasic_SingularSubfigure))
    return 15;
  else if (atype == STANDARD_TYPE(IGESBasic_SubfigureDef))
    return 16;
  return 0;
}
