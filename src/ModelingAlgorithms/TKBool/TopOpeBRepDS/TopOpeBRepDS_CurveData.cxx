#include <TopOpeBRepDS_CurveData.hpp>
#include <TopOpeBRepDS_DataStructure.hpp>

TopOpeBRepDS_CurveData::TopOpeBRepDS_CurveData() = default;

TopOpeBRepDS_CurveData::TopOpeBRepDS_CurveData(const TopOpeBRepDS_Curve& C)
    : myCurve(C)
{
}
