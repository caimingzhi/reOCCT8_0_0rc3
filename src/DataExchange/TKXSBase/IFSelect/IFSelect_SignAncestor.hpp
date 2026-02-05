#pragma once

#include <Standard.hpp>

#include <IFSelect_SignType.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IFSelect_SignAncestor : public IFSelect_SignType
{

public:
  Standard_EXPORT IFSelect_SignAncestor(const bool nopk = false);

  Standard_EXPORT bool Matches(const occ::handle<Standard_Transient>&       ent,
                               const occ::handle<Interface_InterfaceModel>& model,
                               const TCollection_AsciiString&               text,
                               const bool                                   exact) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SignAncestor, IFSelect_SignType)
};
