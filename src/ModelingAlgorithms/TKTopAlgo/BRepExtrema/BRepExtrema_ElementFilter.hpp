#pragma once

#include <Standard_TypeDef.hpp>

struct BRepExtrema_ElementFilter
{

  enum FilterResult
  {
    NoCheck,
    Overlap,
    DoCheck
  };

  virtual ~BRepExtrema_ElementFilter() = default;

  virtual FilterResult PreCheckElements(const int, const int) { return DoCheck; }
};
