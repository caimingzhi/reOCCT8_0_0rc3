#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_Loop.hpp>
#include <NCollection_List.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_State.hpp>
#include <TopOpeBRepBuild_LoopEnum.hpp>
#include <Standard_Integer.hpp>
class TopOpeBRepBuild_LoopSet;
class TopOpeBRepBuild_LoopClassifier;
class TopOpeBRepBuild_Loop;

//! The AreaBuilder algorithm is used to
//! reconstruct complex topological objects as Faces
//! or Solids.
//! * Loop is the composite topological object of
//! the boundary. Wire for a Face. Shell for a Solid.
//! * LoopSet is a tool describing the object to
//! build. It gives an iteration on Loops. For each
//! Loop it tells if it is on the boundary or if it is
//! an interference.
//! * LoopClassifier is an algorithm used to test
//! if a Loop is inside another Loop.
//! The result of the reconstruction is an iteration
//! on the reconstructed areas. An area is described
//! by a set of Loops.
//! A AreaBuilder is built with:
//! - a LoopSet describing the object to reconstruct.
//! - a LoopClassifier providing the classification algorithm.
class TopOpeBRepBuild_AreaBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_AreaBuilder();

  //! Creates a AreaBuilder to build the areas on
  //! the shapes described by <LS> using the classifier <LC>.
  Standard_EXPORT TopOpeBRepBuild_AreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                              TopOpeBRepBuild_LoopClassifier& LC,
                                              const bool                      ForceClass = false);

  Standard_EXPORT virtual ~TopOpeBRepBuild_AreaBuilder();

  //! Sets a AreaBuilder to find the areas on
  //! the shapes described by <LS> using the classifier <LC>.
  Standard_EXPORT virtual void InitAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                               TopOpeBRepBuild_LoopClassifier& LC,
                                               const bool                      ForceClass = false);

  //! Initialize iteration on areas.
  Standard_EXPORT int InitArea();

  Standard_EXPORT bool MoreArea() const;

  Standard_EXPORT void NextArea();

  //! Initialize iteration on loops of current Area.
  Standard_EXPORT int InitLoop();

  Standard_EXPORT bool MoreLoop() const;

  Standard_EXPORT void NextLoop();

  //! Returns the current Loop in the current area.
  Standard_EXPORT const occ::handle<TopOpeBRepBuild_Loop>& Loop() const;

  Standard_EXPORT virtual void ADD_Loop_TO_LISTOFLoop(
    const occ::handle<TopOpeBRepBuild_Loop>&             L,
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LOL,
    void* const                                          s = nullptr) const;

  Standard_EXPORT virtual void REM_Loop_FROM_LISTOFLoop(
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>::Iterator& ITLOL,
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>&           LOL,
    void* const                                                    s = nullptr) const;

  Standard_EXPORT virtual void ADD_LISTOFLoop_TO_LISTOFLoop(
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LOL1,
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LOL2,
    void* const                                          s  = nullptr,
    void* const                                          s1 = nullptr,
    void* const                                          s2 = nullptr) const;

protected:
  Standard_EXPORT TopAbs_State
    CompareLoopWithListOfLoop(TopOpeBRepBuild_LoopClassifier&                            LC,
                              const occ::handle<TopOpeBRepBuild_Loop>&                   L,
                              const NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LOL,
                              const TopOpeBRepBuild_LoopEnum                             le) const;

  Standard_EXPORT void Atomize(TopAbs_State& state, const TopAbs_State newstate) const;

  NCollection_List<NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>>           myArea;
  NCollection_List<NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>>::Iterator myAreaIterator;
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>::Iterator                   myLoopIterator;
  bool                                                                            myUNKNOWNRaise;
};
