#pragma once

#include <Standard_TypeDef.hpp>

//! Filtering tool used to detect if two given mesh elements
//! should be tested for overlapping/intersection or not.
struct BRepExtrema_ElementFilter
{
  //! Result of filtering function.
  enum FilterResult
  {
    NoCheck,
    Overlap,
    DoCheck
  };

  //! Releases resources of element filter.
  virtual ~BRepExtrema_ElementFilter() = default;

  //! Checks if two mesh elements should be tested for overlapping/intersection
  //! (used for detection correct/incorrect cases of shared edges and vertices).
  virtual FilterResult PreCheckElements(const int /*theIndex1*/, const int /*theIndex2*/)
  {
    return DoCheck;
  }
};
