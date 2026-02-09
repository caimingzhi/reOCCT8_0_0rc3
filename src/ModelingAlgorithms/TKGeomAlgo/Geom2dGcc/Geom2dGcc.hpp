#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2dGcc_QualifiedCurve;
class Geom2dAdaptor_Curve;

class Geom2dGcc
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static Geom2dGcc_QualifiedCurve Unqualified(const Geom2dAdaptor_Curve& Obj);

  Standard_EXPORT static Geom2dGcc_QualifiedCurve Enclosing(const Geom2dAdaptor_Curve& Obj);

  Standard_EXPORT static Geom2dGcc_QualifiedCurve Enclosed(const Geom2dAdaptor_Curve& Obj);

  Standard_EXPORT static Geom2dGcc_QualifiedCurve Outside(const Geom2dAdaptor_Curve& Obj);
};
