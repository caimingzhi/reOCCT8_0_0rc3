#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopOpeBRepDS_Point.hpp>
#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_GeometryData.hpp>

class TopOpeBRepDS_PointData : public TopOpeBRepDS_GeometryData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_PointData();

  Standard_EXPORT TopOpeBRepDS_PointData(const TopOpeBRepDS_Point& P);

  Standard_EXPORT TopOpeBRepDS_PointData(const TopOpeBRepDS_Point& P, const int I1, const int I2);

  Standard_EXPORT void SetShapes(const int I1, const int I2);

  Standard_EXPORT void GetShapes(int& I1, int& I2) const;

  friend class TopOpeBRepDS_DataStructure;

private:
  TopOpeBRepDS_Point myPoint;
  int                myS1;
  int                myS2;
};
