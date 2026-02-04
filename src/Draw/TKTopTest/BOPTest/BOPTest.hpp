#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <BOPAlgo_Operation.hpp>

#include <Draw_Interpretor.hpp>
class Message_Report;

class BOPTest
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void AllCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void BOPCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void CheckCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void TolerCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void LowCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void ObjCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void PartitionCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void APICommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void OptionCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void Factory(Draw_Interpretor& aDI);

  Standard_EXPORT static void DebugCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void CellsCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void UtilityCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void RemoveFeaturesCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void PeriodicityCommands(Draw_Interpretor& aDI);

  Standard_EXPORT static void MkConnectedCommands(Draw_Interpretor& aDI);

  //! Prints errors and warnings if any and draws attached shapes
  //! if flag BOPTest_Objects::DrawWarnShapes() is set
  Standard_EXPORT static void ReportAlerts(const occ::handle<Message_Report>& theReport);

  //! Returns operation type according to the given string.
  //! For numeric values, the number correspond to the order in enum.
  Standard_EXPORT static BOPAlgo_Operation GetOperationType(const char* theOp);
};

