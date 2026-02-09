#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <IFSelect_Signature.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IFSelect_SignMultiple : public IFSelect_Signature
{

public:
  Standard_EXPORT IFSelect_SignMultiple(const char* name);

  Standard_EXPORT void Add(const occ::handle<IFSelect_Signature>& subsign,
                           const int                              width = 0,
                           const bool                             maxi  = false);

  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT bool Matches(const occ::handle<Standard_Transient>&       ent,
                               const occ::handle<Interface_InterfaceModel>& model,
                               const TCollection_AsciiString&               text,
                               const bool                                   exact) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SignMultiple, IFSelect_Signature)

private:
  NCollection_Sequence<occ::handle<Standard_Transient>> thesubs;
  NCollection_Sequence<int>                             thetabs;
};
