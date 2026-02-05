#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <STEPSelections_AssemblyComponent.hpp>
#include <NCollection_Sequence.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_OStream.hpp>
#include <Standard_Integer.hpp>
class StepShape_ShapeDefinitionRepresentation;
class StepBasic_ProductDefinition;
class STEPSelections_AssemblyComponent;
class Standard_Transient;
class StepRepr_NextAssemblyUsageOccurrence;

class STEPSelections_AssemblyExplorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPSelections_AssemblyExplorer(const Interface_Graph& G);

  Standard_EXPORT void Init(const Interface_Graph& G);

  Standard_EXPORT void Dump(Standard_OStream& os) const;

  Standard_EXPORT occ::handle<StepShape_ShapeDefinitionRepresentation> FindSDRWithProduct(
    const occ::handle<StepBasic_ProductDefinition>& product) const;

  Standard_EXPORT void FillListWithGraph(const occ::handle<STEPSelections_AssemblyComponent>& cmp);

  Standard_EXPORT occ::handle<Standard_Transient> FindItemWithNAUO(
    const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& nauo) const;

  //! Returns the number of root assemblies;
  int NbAssemblies() const;

  //! Returns root of assenbly by its rank;
  occ::handle<STEPSelections_AssemblyComponent> Root(const int rank = 1) const;

private:
  NCollection_Sequence<occ::handle<STEPSelections_AssemblyComponent>> myRoots;
  Interface_Graph                                                     myGraph;
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>
    myMap;
};

inline int STEPSelections_AssemblyExplorer::NbAssemblies() const
{
  return myRoots.Length();
}

//=================================================================================================

inline occ::handle<STEPSelections_AssemblyComponent> STEPSelections_AssemblyExplorer::Root(
  const int rank) const
{
  return myRoots.Value(rank);
}
