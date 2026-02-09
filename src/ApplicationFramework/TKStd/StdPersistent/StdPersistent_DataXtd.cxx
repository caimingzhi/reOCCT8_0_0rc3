

#include <StdPersistent_DataXtd.hpp>

void StdPersistent_DataXtd::Geometry::ImportAttribute()
{
  myTransient->SetType(static_cast<TDataXtd_GeometryEnum>(myData));
}

void StdPersistent_DataXtd::Position::ImportAttribute()
{
  myTransient->SetPosition(myData);
}
