#pragma once

#include <Standard_Transient.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Message_ProgressRange.hpp>

class IMeshData_Model;
struct IMeshTools_Parameters;

//! Interface class providing API for algorithms intended to update or modify discrete model.
class IMeshTools_ModelAlgo : public Standard_Transient
{
public:
  //! Destructor.
  ~IMeshTools_ModelAlgo() override = default;

  //! Exceptions protected processing of the given model.
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
  //! Constructor.
  IMeshTools_ModelAlgo() {}

  //! Performs processing of the given model.
  Standard_EXPORT virtual bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                               const IMeshTools_Parameters&        theParameters,
                                               const Message_ProgressRange&        theRange) = 0;
};
