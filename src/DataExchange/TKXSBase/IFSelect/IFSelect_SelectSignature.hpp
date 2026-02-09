#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <IFSelect_SelectExtract.hpp>
class IFSelect_Signature;
class IFSelect_SignCounter;
class Standard_Transient;
class Interface_Graph;
class Interface_InterfaceModel;

class IFSelect_SelectSignature : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT IFSelect_SelectSignature(const occ::handle<IFSelect_Signature>& matcher,
                                           const char*                            signtext,
                                           const bool                             exact = true);

  Standard_EXPORT IFSelect_SelectSignature(const occ::handle<IFSelect_Signature>& matcher,
                                           const TCollection_AsciiString&         signtext,
                                           const bool                             exact = true);

  Standard_EXPORT IFSelect_SelectSignature(const occ::handle<IFSelect_SignCounter>& matcher,
                                           const char*                              signtext,
                                           const bool                               exact = true);

  Standard_EXPORT occ::handle<IFSelect_Signature> Signature() const;

  Standard_EXPORT occ::handle<IFSelect_SignCounter> Counter() const;

  Standard_EXPORT bool SortInGraph(const int                              rank,
                                   const occ::handle<Standard_Transient>& ent,
                                   const Interface_Graph&                 G) const override;

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT const TCollection_AsciiString& SignatureText() const;

  Standard_EXPORT bool IsExact() const;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectSignature, IFSelect_SelectExtract)

private:
  occ::handle<IFSelect_Signature>               thematcher;
  occ::handle<IFSelect_SignCounter>             thecounter;
  TCollection_AsciiString                       thesigntext;
  int                                           theexact;
  NCollection_Sequence<TCollection_AsciiString> thesignlist;
  NCollection_Sequence<int>                     thesignmode;
};
