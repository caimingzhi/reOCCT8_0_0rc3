#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_PBuilder.hpp>

class TopOpeBRepBuild_GTopo;
typedef TopOpeBRepBuild_GTopo* TopOpeBRepBuild_PGTopo;

#include <TopOpeBRepTool_Plos.hpp>
#include <TopOpeBRepBuild_PWireEdgeSet.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
class TopOpeBRepDS_Interference;

class TopOpeBRepBuild_BuilderON
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_BuilderON();

  Standard_EXPORT TopOpeBRepBuild_BuilderON(const TopOpeBRepBuild_PBuilder&     PB,
                                            const TopoDS_Shape&                 F,
                                            const TopOpeBRepBuild_PGTopo&       PG,
                                            const TopOpeBRepTool_Plos&          PLSclass,
                                            const TopOpeBRepBuild_PWireEdgeSet& PWES);

  Standard_EXPORT void Perform(const TopOpeBRepBuild_PBuilder&     PB,
                               const TopoDS_Shape&                 F,
                               const TopOpeBRepBuild_PGTopo&       PG,
                               const TopOpeBRepTool_Plos&          PLSclass,
                               const TopOpeBRepBuild_PWireEdgeSet& PWES);

  Standard_EXPORT bool GFillONCheckI(const occ::handle<TopOpeBRepDS_Interference>& I) const;

  Standard_EXPORT void GFillONPartsWES1(const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT void GFillONPartsWES2(const occ::handle<TopOpeBRepDS_Interference>& I,
                                        const TopoDS_Shape&                           EspON);

  Standard_EXPORT void Perform2d(const TopOpeBRepBuild_PBuilder&     PB,
                                 const TopoDS_Shape&                 F,
                                 const TopOpeBRepBuild_PGTopo&       PG,
                                 const TopOpeBRepTool_Plos&          PLSclass,
                                 const TopOpeBRepBuild_PWireEdgeSet& PWES);

  Standard_EXPORT void GFillONParts2dWES2(const occ::handle<TopOpeBRepDS_Interference>& I,
                                          const TopoDS_Shape&                           EspON);

private:
  TopOpeBRepBuild_PBuilder                                 myPB;
  TopOpeBRepBuild_PGTopo                                   myPG;
  TopOpeBRepTool_Plos                                      myPLSclass;
  TopOpeBRepBuild_PWireEdgeSet                             myPWES;
  TopoDS_Shape                                             myFace;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> myFEI;
};
