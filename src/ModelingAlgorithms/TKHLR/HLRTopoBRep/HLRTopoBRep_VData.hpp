#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>

class HLRTopoBRep_VData
{
public:
  DEFINE_STANDARD_ALLOC

  HLRTopoBRep_VData();

  Standard_EXPORT HLRTopoBRep_VData(const double P, const TopoDS_Shape& V);

  double Parameter() const;

  const TopoDS_Shape& Vertex() const;

private:
  double       myParameter;
  TopoDS_Shape myVertex;
};

inline HLRTopoBRep_VData::HLRTopoBRep_VData()
    : myParameter(0.0)
{
}

inline double HLRTopoBRep_VData::Parameter() const
{
  return myParameter;
}

inline const TopoDS_Shape& HLRTopoBRep_VData::Vertex() const
{
  return myVertex;
}
