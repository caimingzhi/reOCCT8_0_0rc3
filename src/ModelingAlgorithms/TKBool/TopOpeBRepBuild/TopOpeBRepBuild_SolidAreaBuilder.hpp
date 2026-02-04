#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopOpeBRepBuild_Area3dBuilder.hpp>
class TopOpeBRepBuild_LoopSet;
class TopOpeBRepBuild_LoopClassifier;

//! The SolidAreaBuilder algorithm is used to construct Solids from a LoopSet,
//! where the Loop is the composite topological object of the boundary,
//! here wire or block of edges.
//! The LoopSet gives an iteration on Loops.
//! For each Loop it indicates if it is on the boundary (wire) or if it
//! results from an interference (block of edges).
//! The result of the SolidAreaBuilder is an iteration on areas.
//! An area is described by a set of Loops.
class TopOpeBRepBuild_SolidAreaBuilder : public TopOpeBRepBuild_Area3dBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_SolidAreaBuilder();

  //! Creates a SolidAreaBuilder to build Solids on
  //! the (shells,blocks of face) of <LS>, using the classifier <LC>.
  Standard_EXPORT TopOpeBRepBuild_SolidAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                   TopOpeBRepBuild_LoopClassifier& LC,
                                                   const bool ForceClass = false);

  Standard_EXPORT void InitSolidAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                            TopOpeBRepBuild_LoopClassifier& LC,
                                            const bool                      ForceClass = false);
};

