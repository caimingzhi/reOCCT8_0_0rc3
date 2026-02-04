#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IFGraph_SubPartsIterator.hpp>
#include <Standard_Boolean.hpp>
class Interface_Graph;

//! determines strong components of a graph, that is
//! isolated entities (single components) or loops
class IFGraph_StrongComponants : public IFGraph_SubPartsIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates with a Graph, and will analyse :
  //! whole True  : all the contents of the Model
  //! whole False : sub-parts which will be given later
  Standard_EXPORT IFGraph_StrongComponants(const Interface_Graph& agraph, const bool whole);

  //! does the computation
  Standard_EXPORT void Evaluate() override;
};

