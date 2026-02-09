#pragma once

#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
class IFSelect_Signature;
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;

class IFSelect_SelectSignedShared : public IFSelect_SelectExplore
{

public:
  Standard_EXPORT IFSelect_SelectSignedShared(const occ::handle<IFSelect_Signature>& matcher,
                                              const char*                            signtext,
                                              const bool                             exact = true,
                                              const int                              level = 0);

  Standard_EXPORT occ::handle<IFSelect_Signature> Signature() const;

  Standard_EXPORT const TCollection_AsciiString& SignatureText() const;

  Standard_EXPORT bool IsExact() const;

  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectSignedShared, IFSelect_SelectExplore)

private:
  occ::handle<IFSelect_Signature> thematcher;
  TCollection_AsciiString         thesigntext;
  bool                            theexact;
};
