#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESData_Protocol;

//! basic description of an IGES Interface
class IGESData
{
public:
  DEFINE_STANDARD_ALLOC

  //! Prepares General dynamic data used for IGESData specifically :
  //! Protocol and Modules, which treat UndefinedEntity
  Standard_EXPORT static void Init();

  //! Returns a Protocol from IGESData (avoids to create it)
  Standard_EXPORT static occ::handle<IGESData_Protocol> Protocol();
};

