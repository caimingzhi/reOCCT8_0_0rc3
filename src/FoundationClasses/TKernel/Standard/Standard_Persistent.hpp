#pragma once


#include <Standard_Type.hpp>

//! Root of "persistent" classes, a legacy support of
//! object oriented databases, now outdated.
class Standard_Persistent : public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_Persistent()
      : _typenum(0),
        _refnum(0)
  {
  }

  DEFINE_STANDARD_RTTIEXT(Standard_Persistent, Standard_Transient)

  int& TypeNum() { return _typenum; }

private:
  int _typenum;
  int _refnum;

  friend class Storage_Schema;
};

