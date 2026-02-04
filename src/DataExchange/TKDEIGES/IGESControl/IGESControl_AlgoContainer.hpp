#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESToBRep_AlgoContainer.hpp>

class IGESControl_AlgoContainer : public IGESToBRep_AlgoContainer
{

public:
  //! Empty constructor
  Standard_EXPORT IGESControl_AlgoContainer();

  DEFINE_STANDARD_RTTIEXT(IGESControl_AlgoContainer, IGESToBRep_AlgoContainer)
};

