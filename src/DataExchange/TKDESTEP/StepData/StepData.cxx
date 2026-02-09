

#include <StepData.hpp>

#include <MoniTool_Macros.hpp>
#include <Interface_Statics.hpp>
#include <StepData_DefaultGeneral.hpp>
#include <StepData_FileProtocol.hpp>
#include <StepData_Protocol.hpp>

StaticHandle(StepData_Protocol, proto);

StaticHandleA(StepData_Protocol, theheader);

void StepData::Init() {}

occ::handle<StepData_Protocol> StepData::Protocol()
{
  InitHandleVoid(StepData_Protocol, proto);

  return proto;
}

void StepData::AddHeaderProtocol(const occ::handle<StepData_Protocol>& header)
{
  InitHandle(StepData_Protocol, theheader);
  if (theheader.IsNull())
    theheader = header;
  else
  {
    DeclareAndCast(StepData_FileProtocol, headmult, theheader);
    if (headmult.IsNull())
    {
      headmult = new StepData_FileProtocol;
      headmult->Add(theheader);
    }
    headmult->Add(header);
    theheader = headmult;
  }
}

occ::handle<StepData_Protocol> StepData::HeaderProtocol()
{
  UseHandle(StepData_Protocol, theheader);
  return theheader;
}
