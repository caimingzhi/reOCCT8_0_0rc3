#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Dispatch.hpp>
#include <Standard_Integer.hpp>
class TCollection_AsciiString;
class Interface_Graph;
class IFGraph_SubPartsIterator;

//! A DispGlobal gathers all the input Entities into only one
//! global Packet
class IFSelect_DispGlobal : public IFSelect_Dispatch
{

public:
  //! Creates a DispGlobal
  Standard_EXPORT IFSelect_DispGlobal();

  //! Returns as Label, "One File for all Input"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  //! Returns True : maximum equates 1
  Standard_EXPORT bool LimitedMax(const int nbent, int& max) const override;

  //! Computes the list of produced Packets. It is made of only ONE
  //! Packet, which gets the RootResult from the Final Selection.
  //! Remark : the inherited exception raising is never activated.
  Standard_EXPORT void Packets(const Interface_Graph&    G,
                               IFGraph_SubPartsIterator& packs) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_DispGlobal, IFSelect_Dispatch)
};

