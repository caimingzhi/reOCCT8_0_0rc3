#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Config.hpp>
#include <TopAbs_Orientation.hpp>

class TopOpeBRepDS_ShapeData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_ShapeData();

  Standard_EXPORT const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& Interferences()
    const;

  Standard_EXPORT NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& ChangeInterferences();

  Standard_EXPORT bool Keep() const;

  Standard_EXPORT void ChangeKeep(const bool B);

  friend class TopOpeBRepDS_DataStructure;

private:
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> myInterferences;
  NCollection_List<TopoDS_Shape>                           mySameDomain;
  int                                                      mySameDomainRef;
  TopOpeBRepDS_Config                                      mySameDomainOri;
  int                                                      mySameDomainInd;
  TopAbs_Orientation                                       myOrientation;
  bool                                                     myOrientationDef;
  int                                                      myAncestorRank;
  bool                                                     myKeep;
};

