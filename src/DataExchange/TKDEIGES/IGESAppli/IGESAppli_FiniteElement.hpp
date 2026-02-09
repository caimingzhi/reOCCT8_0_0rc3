#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESAppli_Node.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;
class IGESAppli_Node;

class IGESAppli_FiniteElement : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_FiniteElement();

  Standard_EXPORT void Init(
    const int                                                            aType,
    const occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>>& allNodes,
    const occ::handle<TCollection_HAsciiString>&                         aName);

  Standard_EXPORT int Topology() const;

  Standard_EXPORT int NbNodes() const;

  Standard_EXPORT occ::handle<IGESAppli_Node> Node(const int Index) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_FiniteElement, IGESData_IGESEntity)

private:
  int                                                           theTopology;
  occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>> theNodes;
  occ::handle<TCollection_HAsciiString>                         theName;
};
