#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <CPnts_RealFunction.hpp>
#include <math_Function.hpp>
#include <Standard_Real.hpp>

//! for implementation, compute values for Gauss
class CPnts_MyGaussFunction : public math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  CPnts_MyGaussFunction();

  //! F is a pointer on a function D is a client data
  //!
  //! Each value is computed with F(D)
  Standard_EXPORT void Init(const CPnts_RealFunction& F, void* const D);

  Standard_EXPORT bool Value(const double X, double& F) override;

private:
  CPnts_RealFunction myFunction;
  void*              myData;
};

inline CPnts_MyGaussFunction::CPnts_MyGaussFunction()
    : myFunction(nullptr),
      myData((void*)nullptr)
{
}
