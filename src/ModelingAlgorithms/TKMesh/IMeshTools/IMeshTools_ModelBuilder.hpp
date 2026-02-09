#pragma once

#include <Message_Algorithm.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Type.hpp>
#include <IMeshData_Model.hpp>

struct IMeshTools_Parameters;

class IMeshTools_ModelBuilder : public Message_Algorithm
{
public:
  ~IMeshTools_ModelBuilder() override = default;

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
  IMeshTools_ModelBuilder() {}

  Standard_EXPORT virtual occ::handle<IMeshData_Model> performInternal(
    const TopoDS_Shape&          theShape,
    const IMeshTools_Parameters& theParameters) = 0;
};
