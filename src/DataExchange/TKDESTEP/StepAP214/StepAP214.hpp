#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepAP214_Protocol;

//! Complete AP214 CC1 , Revision 4
//! Upgrading from Revision 2 to Revision 4 : 26 Mar 1997
//! Splitting in sub-schemas : 5 Nov 1997
class StepAP214
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates a Protocol
  Standard_EXPORT static occ::handle<StepAP214_Protocol> Protocol();
};

