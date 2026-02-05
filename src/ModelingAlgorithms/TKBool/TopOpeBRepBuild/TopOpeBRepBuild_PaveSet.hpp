#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Edge.hpp>
#include <TopOpeBRepBuild_Pave.hpp>
#include <NCollection_List.hpp>
#include <TopOpeBRepBuild_LoopSet.hpp>
class TopoDS_Shape;
class TopOpeBRepBuild_Pave;
class TopOpeBRepBuild_Loop;

//! class providing an exploration of a set of vertices to build edges.
//! It is similar to LoopSet from TopOpeBRepBuild where Loop is Pave.
class TopOpeBRepBuild_PaveSet : public TopOpeBRepBuild_LoopSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Create a Pave set on edge <E>. It contains <E> vertices.
  Standard_EXPORT TopOpeBRepBuild_PaveSet(const TopoDS_Shape& E);

  Standard_EXPORT void RemovePV(const bool B);

  //! Add <PV> in the Pave set.
  Standard_EXPORT void Append(const occ::handle<TopOpeBRepBuild_Pave>& PV);

  Standard_EXPORT void InitLoop() override;

  Standard_EXPORT bool MoreLoop() const override;

  Standard_EXPORT void NextLoop() override;

  Standard_EXPORT occ::handle<TopOpeBRepBuild_Loop> Loop() const override;

  Standard_EXPORT const TopoDS_Edge& Edge() const;

  Standard_EXPORT bool HasEqualParameters();

  Standard_EXPORT double EqualParameters() const;

  Standard_EXPORT bool ClosedVertices();

  Standard_EXPORT static void SortPave(
    const NCollection_List<occ::handle<TopOpeBRepBuild_Pave>>& Lin,
    NCollection_List<occ::handle<TopOpeBRepBuild_Pave>>&       Lout);

private:
  Standard_EXPORT void Prepare();

  TopoDS_Edge                                                   myEdge;
  NCollection_List<occ::handle<TopOpeBRepBuild_Pave>>           myVertices;
  NCollection_List<occ::handle<TopOpeBRepBuild_Pave>>::Iterator myVerticesIt;
  bool                                                          myHasEqualParameters;
  double                                                        myEqualParameters;
  bool                                                          myClosed;
  bool                                                          myPrepareDone;
  bool                                                          myRemovePV;
};
