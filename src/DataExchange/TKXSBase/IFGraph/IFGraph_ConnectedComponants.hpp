#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IFGraph_SubPartsIterator.hpp>
class Interface_Graph;

//! determines Connected Components in a Graph.
//! They define disjoined sets of Entities.
class IFGraph_ConnectedComponants : public IFGraph_SubPartsIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates with a Graph, and will analyse :
  //! whole True  : all the contents of the Model
  //! whole False : sub-parts which will be given later
  Standard_EXPORT IFGraph_ConnectedComponants(const Interface_Graph& agraph, const bool whole);

  //! does the computation
  Standard_EXPORT void Evaluate() override;
};
