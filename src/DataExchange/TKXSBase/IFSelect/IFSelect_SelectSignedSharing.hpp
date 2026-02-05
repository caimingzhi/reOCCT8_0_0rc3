#pragma once

#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
class IFSelect_Signature;
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;

//! In the graph, explore the sharings of the input entities,
//! until it encounters some which match a given Signature
//! (for a limited level, filters the returned list)
//! By default, fitted for any level
class IFSelect_SelectSignedSharing : public IFSelect_SelectExplore
{

public:
  //! Creates a SelectSignedSharing, defaulted for any level
  //! with a given Signature and text to match
  Standard_EXPORT IFSelect_SelectSignedSharing(const occ::handle<IFSelect_Signature>& matcher,
                                               const char*                            signtext,
                                               const bool                             exact = true,
                                               const int                              level = 0);

  //! Returns the used Signature, then it is possible to access it,
  //! modify it as required
  Standard_EXPORT occ::handle<IFSelect_Signature> Signature() const;

  //! Returns Text used to Sort Entity on its Signature
  Standard_EXPORT const TCollection_AsciiString& SignatureText() const;

  //! Returns True if match must be exact
  Standard_EXPORT bool IsExact() const;

  //! Explores an entity : its sharing entities
  //! <ent> to take if it matches the Signature
  //! At level max, filters the result. Else gives all sharings
  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium.
  //! (it refers to the text and exact flag to be matched, and is
  //! qualified by the Name provided by the Signature)
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectSignedSharing, IFSelect_SelectExplore)

private:
  occ::handle<IFSelect_Signature> thematcher;
  TCollection_AsciiString         thesigntext;
  bool                            theexact;
};
