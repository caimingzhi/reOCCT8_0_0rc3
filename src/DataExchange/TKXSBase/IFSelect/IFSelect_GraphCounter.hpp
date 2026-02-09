#pragma once

#include <Standard.hpp>

#include <IFSelect_SignCounter.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class IFSelect_SelectDeduct;
class Interface_Graph;

class IFSelect_GraphCounter : public IFSelect_SignCounter
{

public:
  Standard_EXPORT IFSelect_GraphCounter(const bool withmap = true, const bool withlist = false);

  Standard_EXPORT occ::handle<IFSelect_SelectDeduct> Applied() const;

  Standard_EXPORT void SetApplied(const occ::handle<IFSelect_SelectDeduct>& sel);

  Standard_EXPORT void AddWithGraph(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const Interface_Graph&                                                     graph) override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_GraphCounter, IFSelect_SignCounter)

private:
  occ::handle<IFSelect_SelectDeduct> theapplied;
};
