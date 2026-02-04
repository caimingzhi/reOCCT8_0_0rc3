#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Dispatch.hpp>
#include <Standard_Integer.hpp>
class IFSelect_IntParam;
class TCollection_AsciiString;
class Interface_Graph;
class IFGraph_SubPartsIterator;

//! A DispPerCount gathers all the input Entities into one or
//! several Packets, each containing a defined count of Entity
//! This count is a Parameter of the DispPerCount, given as an
//! IntParam, thus allowing external control of its Value
class IFSelect_DispPerCount : public IFSelect_Dispatch
{

public:
  //! Creates a DispPerCount with no Count (default value 1)
  Standard_EXPORT IFSelect_DispPerCount();

  //! Returns the Count Parameter used for splitting
  Standard_EXPORT occ::handle<IFSelect_IntParam> Count() const;

  //! Sets a new Parameter for Count
  Standard_EXPORT void SetCount(const occ::handle<IFSelect_IntParam>& count);

  //! Returns the effective value of the count parameter
  //! (if Count Parameter not Set or value not positive, returns 1)
  Standard_EXPORT int CountValue() const;

  //! Returns as Label, "One File per <count> Input Entities"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  //! Returns True, maximum count is given as <nbent>
  Standard_EXPORT bool LimitedMax(const int nbent, int& max) const override;

  //! Computes the list of produced Packets. It defines Packets in
  //! order to have at most <Count> Entities per Packet, Entities
  //! are given by RootResult from the Final Selection.
  Standard_EXPORT void Packets(const Interface_Graph&    G,
                               IFGraph_SubPartsIterator& packs) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_DispPerCount, IFSelect_Dispatch)

private:
  occ::handle<IFSelect_IntParam> thecount;
};

