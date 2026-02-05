#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Dispatch.hpp>
#include <Standard_Integer.hpp>
class IFSelect_SignCounter;
class TCollection_AsciiString;
class Interface_Graph;
class IFGraph_SubPartsIterator;

//! A DispPerSignature sorts input Entities according to a
//! Signature : it works with a SignCounter to do this.
class IFSelect_DispPerSignature : public IFSelect_Dispatch
{

public:
  //! Creates a DispPerSignature with no SignCounter (by default,
  //! produces only one packet)
  Standard_EXPORT IFSelect_DispPerSignature();

  //! Returns the SignCounter used for splitting
  Standard_EXPORT occ::handle<IFSelect_SignCounter> SignCounter() const;

  //! Sets a SignCounter for sort
  //! Remark : it is set to record lists of entities, not only counts
  Standard_EXPORT void SetSignCounter(const occ::handle<IFSelect_SignCounter>& sign);

  //! Returns the name of the SignCounter, which caracterises the
  //! sorting criterium for this Dispatch
  Standard_EXPORT const char* SignName() const;

  //! Returns as Label, "One File per Signature <name>"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  //! Returns True, maximum count is given as <nbent>
  Standard_EXPORT bool LimitedMax(const int nbent, int& max) const override;

  //! Computes the list of produced Packets. It defines Packets from
  //! the SignCounter, which sirts the input Entities per Signature
  //! (specific of the SignCounter).
  Standard_EXPORT void Packets(const Interface_Graph&    G,
                               IFGraph_SubPartsIterator& packs) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_DispPerSignature, IFSelect_Dispatch)

private:
  occ::handle<IFSelect_SignCounter> thesign;
};
