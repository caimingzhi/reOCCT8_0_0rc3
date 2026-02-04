#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IFGraph_SubPartsIterator.hpp>
#include <Standard_Boolean.hpp>
class Interface_Graph;
class IFGraph_StrongComponants;

//! determines strong components in a graph which are Cycles
class IFGraph_Cycles : public IFGraph_SubPartsIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates with a Graph, and will analyse :
  //! whole True  : all the contents of the Model
  //! whole False : sub-parts which will be given later
  Standard_EXPORT IFGraph_Cycles(const Interface_Graph& agraph, const bool whole);

  //! creates from a StrongComponants which was already computed
  Standard_EXPORT IFGraph_Cycles(IFGraph_StrongComponants& subparts);

  //! does the computation. Cycles are StrongComponants which are
  //! not Single
  Standard_EXPORT void Evaluate() override;
};

