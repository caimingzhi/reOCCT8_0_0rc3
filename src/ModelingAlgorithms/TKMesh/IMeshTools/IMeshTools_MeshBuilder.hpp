#pragma once

#include <IMeshTools_Context.hpp>
#include <Standard_Type.hpp>
#include <Message_ProgressRange.hpp>

class IMeshTools_MeshBuilder : public Message_Algorithm
{
public:
  Standard_EXPORT IMeshTools_MeshBuilder();

  Standard_EXPORT IMeshTools_MeshBuilder(const occ::handle<IMeshTools_Context>& theContext);

  Standard_EXPORT ~IMeshTools_MeshBuilder() override;

  void SetContext(const occ::handle<IMeshTools_Context>& theContext) { myContext = theContext; }

  const occ::handle<IMeshTools_Context>& GetContext() const { return myContext; }

  Standard_EXPORT virtual void Perform(const Message_ProgressRange& theRange);

  DEFINE_STANDARD_RTTIEXT(IMeshTools_MeshBuilder, Message_Algorithm)

private:
  occ::handle<IMeshTools_Context> myContext;
};
