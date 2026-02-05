#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <IFSelect_Signature.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! Multiple Signature : ordered list of other Signatures
//! It concatenates on a same line the result of its sub-items
//! separated by sets of 3 blanks
//! It is possible to define tabulations between sub-items
//! Moreover, match rules are specific
class IFSelect_SignMultiple : public IFSelect_Signature
{

public:
  //! Creates an empty SignMultiple with a Name
  //! This name should take expected tabulations into account
  Standard_EXPORT IFSelect_SignMultiple(const char* name);

  //! Adds a Signature. Width, if given, gives the tabulation
  //! If <maxi> is True, it is a forced tabulation (overlength is
  //! replaced by a final dot)
  //! If <maxi> is False, just 3 blanks follow an overlength
  Standard_EXPORT void Add(const occ::handle<IFSelect_Signature>& subsign,
                           const int                              width = 0,
                           const bool                             maxi  = false);

  //! Concatenates the values of sub-signatures, with their
  //! tabulations
  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Specialized Match Rule
  //! If <exact> is False, simply checks if at least one sub-item
  //! matches
  //! If <exact> is True, standard match with Value
  //! (i.e. tabulations must be respected)
  Standard_EXPORT bool Matches(const occ::handle<Standard_Transient>&       ent,
                               const occ::handle<Interface_InterfaceModel>& model,
                               const TCollection_AsciiString&               text,
                               const bool                                   exact) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SignMultiple, IFSelect_Signature)

private:
  NCollection_Sequence<occ::handle<Standard_Transient>> thesubs;
  NCollection_Sequence<int>                             thetabs;
};
