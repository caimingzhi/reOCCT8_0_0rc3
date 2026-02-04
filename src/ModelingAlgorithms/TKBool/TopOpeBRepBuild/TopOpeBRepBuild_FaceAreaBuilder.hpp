#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_Area2dBuilder.hpp>
#include <Standard_Boolean.hpp>
class TopOpeBRepBuild_LoopSet;
class TopOpeBRepBuild_LoopClassifier;

//! The FaceAreaBuilder algorithm is used to construct Faces from a LoopSet,
//! where the Loop is the composite topological object of the boundary,
//! here wire or block of edges.
//! The LoopSet gives an iteration on Loops.
//! For each Loop it indicates if it is on the boundary (wire) or if it
//! results from an interference (block of edges).
//! The result of the FaceAreaBuilder is an iteration on areas.
//! An area is described by a set of Loops.
class TopOpeBRepBuild_FaceAreaBuilder : public TopOpeBRepBuild_Area2dBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_FaceAreaBuilder();

  //! Creates a FaceAreaBuilder to build faces on
  //! the (wires,blocks of edge) of <LS>, using the classifier <LC>.
  Standard_EXPORT TopOpeBRepBuild_FaceAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                  TopOpeBRepBuild_LoopClassifier& LC,
                                                  const bool ForceClass = false);

  Standard_EXPORT void InitFaceAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                           TopOpeBRepBuild_LoopClassifier& LC,
                                           const bool                      ForceClass = false);
};

