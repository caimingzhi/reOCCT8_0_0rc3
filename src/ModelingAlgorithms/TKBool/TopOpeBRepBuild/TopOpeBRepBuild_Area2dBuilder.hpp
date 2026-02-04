#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_AreaBuilder.hpp>
#include <Standard_Boolean.hpp>
class TopOpeBRepBuild_LoopSet;
class TopOpeBRepBuild_LoopClassifier;

//! The Area2dBuilder algorithm is used to construct Faces from a LoopSet,
//! where the Loop is the composite topological object of the boundary,
//! here wire or block of edges.
//! The LoopSet gives an iteration on Loops.
//! For each Loop it indicates if it is on the boundary (wire) or if it
//! results from an interference (block of edges).
//! The result of the Area2dBuilder is an iteration on areas.
//! An area is described by a set of Loops.
class TopOpeBRepBuild_Area2dBuilder : public TopOpeBRepBuild_AreaBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_Area2dBuilder();

  //! Creates a Area2dBuilder to build faces on
  //! the (wires,blocks of edge) of <LS>, using the classifier <LC>.
  Standard_EXPORT TopOpeBRepBuild_Area2dBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                TopOpeBRepBuild_LoopClassifier& LC,
                                                const bool                      ForceClass = false);

  //! Sets a Area1dBuilder to find the areas of
  //! the shapes described by <LS> using the classifier <LC>.
  Standard_EXPORT void InitAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                       TopOpeBRepBuild_LoopClassifier& LC,
                                       const bool                      ForceClass = false) override;
};

