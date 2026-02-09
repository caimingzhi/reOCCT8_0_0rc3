#include <TopOpeBRepDS_define.hpp>
#include <TopOpeBRepDS_Point.hpp>
#include <TopOpeBRepDS_PointData.hpp>

TopOpeBRepDS_PointData::TopOpeBRepDS_PointData()
    : myS1(0),
      myS2(0)
{
}

TopOpeBRepDS_PointData::TopOpeBRepDS_PointData(const TopOpeBRepDS_Point& P)
    : myPoint(P),
      myS1(0),
      myS2(0)
{
}

TopOpeBRepDS_PointData::TopOpeBRepDS_PointData(const TopOpeBRepDS_Point& P,
                                               const int                 I1,
                                               const int                 I2)
    : myPoint(P),
      myS1(I1),
      myS2(I2)
{
}

void TopOpeBRepDS_PointData::SetShapes(const int I1, const int I2)
{
  myS1 = I1;
  myS2 = I2;
}

void TopOpeBRepDS_PointData::GetShapes(int& I1, int& I2) const
{
  I1 = myS1;
  I2 = myS2;
}
