#pragma once

#include <Standard_Transient.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Message_ProgressRange.hpp>

class IMeshData_Model;
struct IMeshTools_Parameters;

class IMeshTools_ModelAlgo : public Standard_Transient
{
public:
  ~IMeshTools_ModelAlgo() override = default;

  bool Perform(const occ::handle<IMeshData_Model>& theModel,
               const IMeshTools_Parameters&        theParameters,
               const Message_ProgressRange&        theRange)
  {
    try
    {
      OCC_CATCH_SIGNALS

      return performInternal(theModel, theParameters, theRange);
    }
    catch (Standard_Failure const&)
    {
      return false;
    }
  }

  DEFINE_STANDARD_RTTIEXT(IMeshTools_ModelAlgo, Standard_Transient)

protected:
  IMeshTools_ModelAlgo() {}

  Standard_EXPORT virtual bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                               const IMeshTools_Parameters&        theParameters,
                                               const Message_ProgressRange&        theRange) = 0;
};
