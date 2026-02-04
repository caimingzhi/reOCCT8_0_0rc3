#pragma once


#include <StdLPersistent_Void.hpp>
#include <StdObject_gp_Vectors.hpp>

#include <TDataXtd_Shape.hpp>
#include <TDataXtd_Point.hpp>
#include <TDataXtd_Axis.hpp>
#include <TDataXtd_Plane.hpp>
#include <TDataXtd_Placement.hpp>
#include <TDataXtd_Geometry.hpp>
#include <TDataXtd_Position.hpp>

class StdPersistent_DataXtd
{
  class _void : private StdLPersistent_Void
  {
  public:
    template <class AttribClass>
    struct Instance : instance<AttribClass>
    {
    };
  };

public:
  typedef _void::Instance<TDataXtd_Shape>     Shape;
  typedef _void::Instance<TDataXtd_Point>     Point;
  typedef _void::Instance<TDataXtd_Axis>      Axis;
  typedef _void::Instance<TDataXtd_Plane>     Plane;
  typedef _void::Instance<TDataXtd_Placement> Placement;

  class Geometry : public StdObjMgt_Attribute<TDataXtd_Geometry>::SingleInt
  {
  public:
    //! Import transient attribute from the persistent data.
    Standard_EXPORT void ImportAttribute() override;
  };

  class Position : public StdObjMgt_Attribute<TDataXtd_Position>::Simple<gp_Pnt>
  {
  public:
    //! Import transient attribute from the persistent data.
    Standard_EXPORT void ImportAttribute() override;
  };
};

template <>
inline const char* StdLPersistent_Void::instance<TDataXtd_Shape>::PName() const
{
  return "PDataXtd_Shape";
}

template <>
inline const char* StdLPersistent_Void::instance<TDataXtd_Point>::PName() const
{
  return "PDataXtd_Point";
}

template <>
inline const char* StdLPersistent_Void::instance<TDataXtd_Axis>::PName() const
{
  return "PDataXtd_Axis";
}

template <>
inline const char* StdLPersistent_Void::instance<TDataXtd_Plane>::PName() const
{
  return "PDataXtd_Plane";
}

template <>
inline const char* StdLPersistent_Void::instance<TDataXtd_Placement>::PName() const
{
  return "PDataXtd_Placement";
}

template <>
template <>
inline const char* StdObjMgt_Attribute<TDataXtd_Geometry>::Simple<int>::PName() const
{
  return "PDataXtd_Geometry";
}

template <>
template <>
inline const char* StdObjMgt_Attribute<TDataXtd_Position>::Simple<gp_Pnt>::PName() const
{
  return "PDataXtd_Position";
}

