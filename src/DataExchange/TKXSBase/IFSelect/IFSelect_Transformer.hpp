#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Interface_Graph;
class Interface_Protocol;
class Interface_CheckIterator;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IFSelect_Transformer : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool Perform(const Interface_Graph&                 G,
                                       const occ::handle<Interface_Protocol>& protocol,
                                       Interface_CheckIterator&               checks,
                                       occ::handle<Interface_InterfaceModel>& newmod) = 0;

  Standard_EXPORT virtual bool ChangeProtocol(occ::handle<Interface_Protocol>& newproto) const;

  Standard_EXPORT virtual bool Updated(const occ::handle<Standard_Transient>& entfrom,
                                       occ::handle<Standard_Transient>&       entto) const = 0;

  Standard_EXPORT virtual TCollection_AsciiString Label() const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_Transformer, Standard_Transient)
};
