#pragma once

#include <Standard.hpp>
#include <Standard_Handle.hpp>
#include <Standard_DefineAlloc.hpp>
#include <NCollection_IncAllocator.hpp>

#include <Interface_ParamType.hpp>

class Interface_Check;

class StepFile_ReadData
{
public:
  DEFINE_STANDARD_ALLOC

private:
  class Record;
  class Argument;
  class Scope;
  class ErrorsPage;

public:
  StepFile_ReadData();

  ~StepFile_ReadData() { ClearRecorder(3); }

  void CreateNewText(const char* theNewText, int theLenText);

  void RecordNewEntity();

  void RecordIdent();

  void RecordType();

  void RecordListStart();

  void CreateNewArg();

  void CreateErrorArg();

  void AddNewScope();

  void FinalOfScope();

  void ClearRecorder(const int theMode);

  bool GetArgDescription(Interface_ParamType* theType, char** theValue);

  void GetFileNbR(int* theNbHead, int* theNbRec, int* theNbPage);

  bool GetRecordDescription(char** theIdent, char** theType, int* theNbArg);

  void RecordTypeText();

  void NextRecord();

  void PrintCurrentRecord();

  void PrepareNewArg();

  void FinalOfHead();

  void SetTypeArg(const Interface_ParamType theArgType);

  void SetModePrint(const int theMode);

  int GetModePrint() const;

  int GetNbRecord() const;

  void AddError(const char* theErrorMessage);

  bool ErrorHandle(const occ::handle<Interface_Check>& theCheck) const;

  const char* GetLastError() const;

private:
  char* RecordNewText(char* theText);

  void GetResultText(char** theText);

  void AddNewRecord(Record* theNewRecord);

  Record* CreateNewRecord();

  void PrintRecord(Record* theRecord);

private:
  NCollection_IncAllocator myTextAlloc;
  NCollection_IncAllocator myOtherAlloc;
  int                      myModePrint;
  int                      myNbRec;
  int                      myNbHead;
  int                      myNbPar;
  int                      myYaRec;
  int                      myNumSub;

  bool  myErrorArg;
  char* myResText;

  char*               myCurrType;
  char*               mySubArg;
  Interface_ParamType myTypeArg;
  Argument*           myCurrArg;
  Record*             myFirstRec;
  Record*             myCurRec;
  Record*             myLastRec;
  Scope*              myCurScope;
  ErrorsPage*         myFirstError;
  ErrorsPage*         myCurError;
};
