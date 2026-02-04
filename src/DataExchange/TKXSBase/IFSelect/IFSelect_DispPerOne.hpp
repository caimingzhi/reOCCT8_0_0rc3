#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Dispatch.hpp>
#include <Standard_Integer.hpp>
class TCollection_AsciiString;
class Interface_Graph;
class IFGraph_SubPartsIterator;

//! A DispPerOne gathers all the input Entities into as many
//! Packets as there Root Entities from the Final Selection,
//! that is, one Packet per Entity
class IFSelect_DispPerOne : public IFSelect_Dispatch
{

public:
  //! Creates a DispPerOne
  Standard_EXPORT IFSelect_DispPerOne();

  //! Returns as Label, "One File per Input Entity"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  //! Returns True, maximum limit is given as <nbent>
  Standard_EXPORT bool LimitedMax(const int nbent, int& max) const override;

  //! Returns the list of produced Packets. It defines one Packet
  //! per Entity given by RootResult from the Final Selection.
  Standard_EXPORT void Packets(const Interface_Graph&    G,
                               IFGraph_SubPartsIterator& packs) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_DispPerOne, IFSelect_Dispatch)
};

