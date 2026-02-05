#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_Curve.hpp>
#include <TopOpeBRepDS_GeometryData.hpp>

class TopOpeBRepDS_CurveData : public TopOpeBRepDS_GeometryData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_CurveData();

  Standard_EXPORT TopOpeBRepDS_CurveData(const TopOpeBRepDS_Curve& C);

  friend class TopOpeBRepDS_DataStructure;

private:
  TopOpeBRepDS_Curve myCurve;
};
