#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IFGraph_StrongComponants.hpp>
class Interface_Graph;

//! determines strong components in a graph which are Roots
class IFGraph_SCRoots : public IFGraph_StrongComponants
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates with a Graph, and will analyse :
  //! whole True  : all the contents of the Model
  //! whole False : sub-parts which will be given later
  Standard_EXPORT IFGraph_SCRoots(const Interface_Graph& agraph, const bool whole);

  //! creates from a StrongComponants which was already computed
  Standard_EXPORT IFGraph_SCRoots(IFGraph_StrongComponants& subparts);

  //! does the computation
  Standard_EXPORT void Evaluate() override;
};
