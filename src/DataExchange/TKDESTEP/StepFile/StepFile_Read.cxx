#include <StepFile_Read.hpp>

#include <StepFile_ReadData.hpp>

#include <Interface_Check.hpp>
#include <Interface_InterfaceError.hpp>
#include <Interface_ParamType.hpp>
#include <Interface_Protocol.hpp>

#include <StepData_FileRecognizer.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_StepModel.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepReaderTool.hpp>

#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>

#include <Message.hpp>
#include <Message_Messenger.hpp>

#include <OSD_FileSystem.hpp>
#include <OSD_Timer.hpp>

#include "step.tab.hpp"

#include <cstdio>
#include <mutex>

#ifdef OCCT_DEBUG
  #define CHRONOMESURE
#endif

namespace
{
  static std::mutex& GetGlobalReadMutex()
  {
    static std::mutex THE_GLOBAL_READ_MUTEX;
    return THE_GLOBAL_READ_MUTEX;
  }
} // namespace

void StepFile_Interrupt(const char* theErrorMessage, const bool theIsFail)
{
  if (theErrorMessage == nullptr)
    return;

  Message_Messenger::StreamBuffer sout = theIsFail ? Message::SendFail() : Message::SendTrace();
  sout << "**** ERR StepFile : " << theErrorMessage << "    ****" << std::endl;
}

static int StepFile_Read(const char*                                 theName,
                         std::istream*                               theIStream,
                         const occ::handle<StepData_StepModel>&      theStepModel,
                         const occ::handle<StepData_Protocol>&       theProtocol,
                         const occ::handle<StepData_FileRecognizer>& theRecogHeader,
                         const occ::handle<StepData_FileRecognizer>& theRecogData)
{
  // if stream is not provided, open file stream here
  std::istream*                 aStreamPtr = theIStream;
  std::shared_ptr<std::istream> aFileStream;
  if (aStreamPtr == nullptr)
  {
    const occ::handle<OSD_FileSystem>& aFileSystem = OSD_FileSystem::DefaultFileSystem();
    aFileStream = aFileSystem->OpenIStream(theName, std::ios::in | std::ios::binary);
    aStreamPtr  = aFileStream.get();
  }
  if (aStreamPtr == nullptr || aStreamPtr->fail())
  {
    return -1;
  }

#ifdef CHRONOMESURE
  OSD_Timer c;
  c.Reset();
  c.Start();
#endif

  Message_Messenger::StreamBuffer sout = Message::SendTrace();
  sout << "      ...    Step File Reading : '" << theName << "'";

  StepFile_ReadData aFileDataModel;
  try
  {
    OCC_CATCH_SIGNALS
    int           aLetat = 0;
    step::scanner aScanner(&aFileDataModel, aStreamPtr);
    aScanner.yyrestart(aStreamPtr);
    step::parser aParser(&aScanner);
    aLetat = aParser.parse();
    if (aLetat != 0)
    {
      StepFile_Interrupt(aFileDataModel.GetLastError(), true);
      return 1;
    }
  }
  catch (Standard_Failure const& anException)
  {
    Message::SendFail() << " ...  Exception Raised while reading Step File : '" << theName << "':\n"
                        << anException << "    ...";
    return 1;
  }

#ifdef CHRONOMESURE
  c.Show(sout);
#endif

  sout << "      ...    STEP File   Read    ...\n";

  std::lock_guard<std::mutex> aLock(GetGlobalReadMutex());

  int nbhead, nbrec, nbpar;
  aFileDataModel.GetFileNbR(&nbhead, &nbrec, &nbpar); // renvoi par lex/yacc
  occ::handle<StepData_StepReaderData> undirec =
    // clang-format off
    new StepData_StepReaderData(nbhead,nbrec,nbpar, theStepModel->SourceCodePage());  // creation tableau de records
  // clang-format on
  for (int nr = 1; nr <= nbrec; nr++)
  {
    int   nbarg;
    char* ident;
    char* typrec = nullptr;
    aFileDataModel.GetRecordDescription(&ident, &typrec, &nbarg);
    undirec->SetRecord(nr, ident, typrec, nbarg);

    if (nbarg > 0)
    {
      Interface_ParamType typa;
      char*               val;
      while (aFileDataModel.GetArgDescription(&typa, &val) == 1)
      {
        undirec->AddStepParam(nr, val, typa);
      }
    }
    undirec->InitParams(nr);
    aFileDataModel.NextRecord();
  }

  aFileDataModel.ErrorHandle(undirec->GlobalCheck());
  int anFailsCount = undirec->GlobalCheck()->NbFails();
  if (anFailsCount > 0)
  {
    Message::SendInfo() << "**** ERR StepFile : Incorrect Syntax : Fails Count : " << anFailsCount
                        << " ****";
  }

  aFileDataModel.ClearRecorder(1);

  sout << "      ... Step File loaded  ...\n";
  sout << "   " << undirec->NbRecords() << " records (entities,sub-lists,scopes), " << nbpar
       << " parameters";

#ifdef CHRONOMESURE
  c.Show(sout);
#endif

  //   Analyse : par StepReaderTool

  StepData_StepReaderTool readtool(undirec, theProtocol);
  readtool.SetErrorHandle(true);

  readtool.PrepareHeader(theRecogHeader); // Header. reco nul -> pour Protocol
  readtool.Prepare(theRecogData);         // Data.   reco nul -> pour Protocol

  sout << "      ... Parameters prepared ...\n";

#ifdef CHRONOMESURE
  c.Show(sout);
#endif

  readtool.LoadModel(theStepModel);
  if (theStepModel->Protocol().IsNull())
    theStepModel->SetProtocol(theProtocol);
  aFileDataModel.ClearRecorder(2);
  anFailsCount = undirec->GlobalCheck()->NbFails() - anFailsCount;
  if (anFailsCount > 0)
  {
    Message::SendInfo() << "*** ERR StepReaderData : Unresolved Reference : Fails Count : "
                        << anFailsCount << " ***";
  }

  readtool.Clear();
  undirec.Nullify();

  sout << "      ...   Objects analysed  ...\n";
  int n = theStepModel->NbEntities();
  sout << "  STEP Loading done : " << n << " Entities";

#ifdef CHRONOMESURE
  c.Show(sout);
#endif

  return 0;
}

int StepFile_Read(const char*                            theName,
                  std::istream*                          theIStream,
                  const occ::handle<StepData_StepModel>& theStepModel,
                  const occ::handle<StepData_Protocol>&  theProtocol)
{
  occ::handle<StepData_FileRecognizer> aNulRecog;
  return StepFile_Read(theName, theIStream, theStepModel, theProtocol, aNulRecog, aNulRecog);
}
