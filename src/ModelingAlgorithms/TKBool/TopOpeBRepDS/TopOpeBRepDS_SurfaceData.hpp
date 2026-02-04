#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopOpeBRepDS_Surface.hpp>
#include <TopOpeBRepDS_GeometryData.hpp>

class TopOpeBRepDS_SurfaceData : public TopOpeBRepDS_GeometryData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_SurfaceData();

  Standard_EXPORT TopOpeBRepDS_SurfaceData(const TopOpeBRepDS_Surface& S);

  friend class TopOpeBRepDS_DataStructure;

private:
  TopOpeBRepDS_Surface mySurface;
};

