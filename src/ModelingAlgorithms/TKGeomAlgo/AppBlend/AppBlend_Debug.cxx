#include <Standard_Boolean.hpp>

//****************************************************
// Functions to change the type of approx.
//****************************************************

static bool AppBlend_ContextSplineApprox = false;

Standard_EXPORT void AppBlend_SetContextSplineApprox(const bool b)
{
  AppBlend_ContextSplineApprox = b;
}

Standard_EXPORT bool AppBlend_GetContextSplineApprox()
{
  return AppBlend_ContextSplineApprox;
}

static bool AppBlend_ContextApproxWithNoTgt = false;

Standard_EXPORT void AppBlend_SetContextApproxWithNoTgt(const bool b)
{
  AppBlend_ContextApproxWithNoTgt = b;
}

Standard_EXPORT bool AppBlend_GetContextApproxWithNoTgt()
{
  return AppBlend_ContextApproxWithNoTgt;
}
