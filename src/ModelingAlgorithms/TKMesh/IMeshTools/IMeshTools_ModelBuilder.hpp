#pragma once

#include <Message_Algorithm.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Type.hpp>
#include <IMeshData_Model.hpp>

struct IMeshTools_Parameters;

//! Interface class represents API for tool building discrete model.
//!
//! The following statuses should be used by default:
//! Message_Done1 - model has been successfully built.
//! Message_Fail1 - empty shape.
//! Message_Fail2 - model has not been build due to unexpected reason.
class IMeshTools_ModelBuilder : public Message_Algorithm
{
public:
  //! Destructor.
  ~IMeshTools_ModelBuilder() override = default;

  //! Exceptions protected method to create discrete model for the given shape.
  //! Returns nullptr in case of failure.
  occ::handle<IMeshData_Model> Perform(const TopoDS_Shape&          theShape,
                                       const IMeshTools_Parameters& theParameters)
  {
    ClearStatus();

    try
    {
      OCC_CATCH_SIGNALS

      return performInternal(theShape, theParameters);
    }
    catch (Standard_Failure const&)
    {
      SetStatus(Message_Fail2);
      return nullptr;
    }
  }

  DEFINE_STANDARD_RTTIEXT(IMeshTools_ModelBuilder, Message_Algorithm)

protected:
  //! Constructor.
  IMeshTools_ModelBuilder() {}

  //! Creates discrete model for the given shape.
  //! Returns nullptr in case of failure.
  Standard_EXPORT virtual occ::handle<IMeshData_Model> performInternal(
    const TopoDS_Shape&          theShape,
    const IMeshTools_Parameters& theParameters) = 0;
};
