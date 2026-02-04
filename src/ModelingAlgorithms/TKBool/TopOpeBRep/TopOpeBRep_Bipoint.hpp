#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>

class TopOpeBRep_Bipoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_Bipoint();

  Standard_EXPORT TopOpeBRep_Bipoint(const int I1, const int I2);

  Standard_EXPORT int I1() const;

  Standard_EXPORT int I2() const;

private:
  int myI1;
  int myI2;
};

