#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_GeneralLib.hpp>
#include <StepData_WriterLib.hpp>
#include <StepData_StepWriter.hpp>
#include <Standard_Integer.hpp>
class StepData_StepModel;
class StepData_Protocol;

class StepData_StepDumper
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepData_StepDumper(const occ::handle<StepData_StepModel>& amodel,
                                      const occ::handle<StepData_Protocol>&  protocol,
                                      const int                              mode = 0);

  Standard_EXPORT StepData_StepWriter& StepWriter();

  Standard_EXPORT bool Dump(Standard_OStream&                      S,
                            const occ::handle<Standard_Transient>& ent,
                            const int                              level);

  Standard_EXPORT bool Dump(Standard_OStream& S, const int num, const int level);

private:
  occ::handle<StepData_StepModel> themodel;
  Interface_GeneralLib            theslib;
  StepData_WriterLib              thewlib;
  StepData_StepWriter             thewriter;
};
