

#include <CPnts_MyGaussFunction.hpp>

void CPnts_MyGaussFunction::Init(const CPnts_RealFunction& F, void* const D)
{
  myFunction = F;
  myData     = D;
}

bool CPnts_MyGaussFunction::Value(const double X, double& F)
{
  F = myFunction(X, myData);
  return true;
}
