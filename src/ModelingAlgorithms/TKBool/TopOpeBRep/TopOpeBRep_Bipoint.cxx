#include <Standard_ProgramError.hpp>
#include <TopOpeBRep_Bipoint.hpp>

TopOpeBRep_Bipoint::TopOpeBRep_Bipoint()
    : myI1(0),
      myI2(0)
{
}

TopOpeBRep_Bipoint::TopOpeBRep_Bipoint(const int I1, const int I2)
    : myI1(I1),
      myI2(I2)
{
}

int TopOpeBRep_Bipoint::I1() const
{
  if (myI1 <= 0)
    throw Standard_ProgramError("TopOpeBRep_Bipoint I1=0");
  return myI1;
}

int TopOpeBRep_Bipoint::I2() const
{
  if (myI2 <= 0)
    throw Standard_ProgramError("TopOpeBRep_Bipoint I2=0");
  return myI2;
}
