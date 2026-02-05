#pragma once

#include <Standard_Macro.hpp>
class StdObjMgt_MapOfInstantiators;

class StdPersistent
{
public:
  //! Register types.
  Standard_EXPORT static void BindTypes(StdObjMgt_MapOfInstantiators& theMap);
};
