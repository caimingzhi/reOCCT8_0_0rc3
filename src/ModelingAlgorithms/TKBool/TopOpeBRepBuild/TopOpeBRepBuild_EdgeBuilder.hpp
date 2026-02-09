#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_Area1dBuilder.hpp>
#include <Standard_Boolean.hpp>
class TopOpeBRepBuild_PaveSet;
class TopOpeBRepBuild_PaveClassifier;
class TopOpeBRepBuild_LoopSet;
class TopOpeBRepBuild_LoopClassifier;
class TopoDS_Shape;

class TopOpeBRepBuild_EdgeBuilder : public TopOpeBRepBuild_Area1dBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_EdgeBuilder();

  Standard_EXPORT TopOpeBRepBuild_EdgeBuilder(TopOpeBRepBuild_PaveSet&        LS,
                                              TopOpeBRepBuild_PaveClassifier& LC,
                                              const bool                      ForceClass = false);

  Standard_EXPORT void InitEdgeBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                       TopOpeBRepBuild_LoopClassifier& LC,
                                       const bool                      ForceClass = false);

  Standard_EXPORT void InitEdge();

  Standard_EXPORT bool MoreEdge() const;

  Standard_EXPORT void NextEdge();

  Standard_EXPORT void InitVertex();

  Standard_EXPORT bool MoreVertex() const;

  Standard_EXPORT void NextVertex();

  Standard_EXPORT const TopoDS_Shape& Vertex() const;

  Standard_EXPORT double Parameter() const;
};
