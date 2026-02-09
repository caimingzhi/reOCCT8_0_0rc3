

#include <IGESAppli_Protocol.hpp>

#include <IGESAppli_DrilledHole.hpp>
#include <IGESAppli_ElementResults.hpp>
#include <IGESAppli_FiniteElement.hpp>
#include <IGESAppli_Flow.hpp>
#include <IGESAppli_FlowLineSpec.hpp>
#include <IGESAppli_LevelFunction.hpp>
#include <IGESAppli_LevelToPWBLayerMap.hpp>
#include <IGESAppli_LineWidening.hpp>
#include <IGESAppli_NodalConstraint.hpp>
#include <IGESAppli_NodalDisplAndRot.hpp>
#include <IGESAppli_NodalResults.hpp>
#include <IGESAppli_Node.hpp>
#include <IGESAppli_PWBArtworkStackup.hpp>
#include <IGESAppli_PWBDrilledHole.hpp>
#include <IGESAppli_PartNumber.hpp>
#include <IGESAppli_PinNumber.hpp>
#include <IGESAppli_PipingFlow.hpp>
#include <IGESAppli_ReferenceDesignator.hpp>
#include <IGESAppli_RegionRestriction.hpp>
#include <IGESDefs.hpp>
#include <IGESDefs_Protocol.hpp>
#include <IGESDraw.hpp>
#include <IGESDraw_Protocol.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_Protocol, IGESData_Protocol)

IGESAppli_Protocol::IGESAppli_Protocol() = default;

int IGESAppli_Protocol::NbResources() const
{
  return 2;
}

occ::handle<Interface_Protocol> IGESAppli_Protocol::Resource(const int num) const
{
  occ::handle<Interface_Protocol> res;
  if (num == 1)
    res = IGESDefs::Protocol();
  if (num == 2)
    res = IGESDraw::Protocol();
  return res;
}

int IGESAppli_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(IGESAppli_DrilledHole))
    return 1;
  else if (atype == STANDARD_TYPE(IGESAppli_ElementResults))
    return 2;
  else if (atype == STANDARD_TYPE(IGESAppli_FiniteElement))
    return 3;
  else if (atype == STANDARD_TYPE(IGESAppli_Flow))
    return 4;
  else if (atype == STANDARD_TYPE(IGESAppli_FlowLineSpec))
    return 5;
  else if (atype == STANDARD_TYPE(IGESAppli_LevelFunction))
    return 6;
  else if (atype == STANDARD_TYPE(IGESAppli_LevelToPWBLayerMap))
    return 7;
  else if (atype == STANDARD_TYPE(IGESAppli_LineWidening))
    return 8;
  else if (atype == STANDARD_TYPE(IGESAppli_NodalConstraint))
    return 9;
  else if (atype == STANDARD_TYPE(IGESAppli_NodalDisplAndRot))
    return 10;
  else if (atype == STANDARD_TYPE(IGESAppli_NodalResults))
    return 11;
  else if (atype == STANDARD_TYPE(IGESAppli_Node))
    return 12;
  else if (atype == STANDARD_TYPE(IGESAppli_PWBArtworkStackup))
    return 13;
  else if (atype == STANDARD_TYPE(IGESAppli_PWBDrilledHole))
    return 14;
  else if (atype == STANDARD_TYPE(IGESAppli_PartNumber))
    return 15;
  else if (atype == STANDARD_TYPE(IGESAppli_PinNumber))
    return 16;
  else if (atype == STANDARD_TYPE(IGESAppli_PipingFlow))
    return 17;
  else if (atype == STANDARD_TYPE(IGESAppli_ReferenceDesignator))
    return 18;
  else if (atype == STANDARD_TYPE(IGESAppli_RegionRestriction))
    return 19;
  return 0;
}
