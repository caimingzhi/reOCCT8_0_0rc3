#pragma once

#include <Standard_Macro.hpp>

class StdObjMgt_MapOfInstantiators;

class StdLPersistent
{
public:
  Standard_EXPORT static void BindTypes(StdObjMgt_MapOfInstantiators& theMap);
};
