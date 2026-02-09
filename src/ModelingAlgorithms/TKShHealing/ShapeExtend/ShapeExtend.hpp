#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <ShapeExtend_Status.hpp>
#include <Standard_Boolean.hpp>

class ShapeExtend
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static int EncodeStatus(const ShapeExtend_Status status);

  Standard_EXPORT static bool DecodeStatus(const int flag, const ShapeExtend_Status status);
};
