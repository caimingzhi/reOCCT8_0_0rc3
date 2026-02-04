#pragma once


#include <StdLPersistent_HArray1.hpp>
#include <StdObject_Shape.hpp>

#include <NCollection_HArray1.hpp>

class StdPersistent_HArray1 : private StdLPersistent_HArray1
{
public:
  typedef instance<NCollection_HArray1<StdObject_Shape>> Shape1;
};

