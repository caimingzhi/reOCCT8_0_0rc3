#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
class TopOpeBRepDS_Interference;

//! mother-class of SurfaceData, CurveData, PointData
class TopOpeBRepDS_GeometryData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_GeometryData();

  Standard_EXPORT TopOpeBRepDS_GeometryData(const TopOpeBRepDS_GeometryData& Other);

  Standard_EXPORT void Assign(const TopOpeBRepDS_GeometryData& Other);

  void operator=(const TopOpeBRepDS_GeometryData& Other) { Assign(Other); }

  Standard_EXPORT const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& Interferences()
    const;

  Standard_EXPORT NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& ChangeInterferences();

  Standard_EXPORT void AddInterference(const occ::handle<TopOpeBRepDS_Interference>& I);

private:
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> myInterferences;
};
