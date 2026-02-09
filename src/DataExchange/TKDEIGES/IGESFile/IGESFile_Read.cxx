

#include <cstdio>

#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESReaderTool.hpp>
#include <IGESData_GeneralModule.hpp>
#include <Interface_Check.hpp>

#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>

#include <IGESFile_Read.hpp>

#include "igesread.h"

#include <Message_Msg.hpp>

static int recupne, recupnp;

static occ::handle<Interface_Check>& checkread()
{
  static occ::handle<Interface_Check> chrd = new Interface_Check;
  return chrd;
}

static void IGESFile_ReadHeader(const occ::handle<IGESData_IGESReaderData>& IR);
static void IGESFile_ReadContent(const occ::handle<IGESData_IGESReaderData>& IR);
void        IGESFile_Check(int mode, Message_Msg& amsg);

static Interface_ParamType LesTypes[10];

int IGESFile_Read(char*                                  nomfic,
                  const occ::handle<IGESData_IGESModel>& amodel,
                  const occ::handle<IGESData_Protocol>&  protocol)
{
  occ::handle<IGESData_FileRecognizer> nulreco;
  return IGESFile_Read(nomfic, amodel, protocol, nulreco, false);
}

int IGESFile_ReadFNES(char*                                  nomfic,
                      const occ::handle<IGESData_IGESModel>& amodel,
                      const occ::handle<IGESData_Protocol>&  protocol)
{
  occ::handle<IGESData_FileRecognizer> nulreco;
  return IGESFile_Read(nomfic, amodel, protocol, nulreco, true);
}

int IGESFile_Read(char*                                       nomfic,
                  const occ::handle<IGESData_IGESModel>&      amodel,
                  const occ::handle<IGESData_Protocol>&       protocol,
                  const occ::handle<IGESData_FileRecognizer>& reco,
                  const bool                                  modefnes)
{

  Message_Msg Msg1  = Message_Msg("XSTEP_1");
  Message_Msg Msg15 = Message_Msg("XSTEP_15");

  char* ficnom = nomfic;
  int   lesect[6];

  IGESFile_Check(2, Msg1);

  checkread()->Clear();
  int result = igesread(ficnom, lesect, modefnes);

  if (result != 0)
    return result;

  LesTypes[ArgVide] = Interface_ParamVoid;
  LesTypes[ArgQuid] = Interface_ParamMisc;
  LesTypes[ArgChar] = Interface_ParamText;
  LesTypes[ArgInt]  = Interface_ParamInteger;
  LesTypes[ArgSign] = Interface_ParamInteger;
  LesTypes[ArgReal] = Interface_ParamReal;
  LesTypes[ArgExp]  = Interface_ParamMisc;
  LesTypes[ArgRexp] = Interface_ParamReal;
  LesTypes[ArgMexp] = Interface_ParamEnum;

  int nbparts, nbparams;
  iges_stats(&nbparts, &nbparams);
  occ::handle<IGESData_IGESReaderData> IR =

    new IGESData_IGESReaderData((lesect[3] + 1) / 2, nbparams);
  {
    {
      try
      {
        OCC_CATCH_SIGNALS
        IGESFile_ReadHeader(IR);
      }
      catch (Standard_Failure const&)
      {

        Message_Msg Msg11 = Message_Msg("XSTEP_11");
        IGESFile_Check(1, Msg11);
      }
    }

    {
      try
      {
        OCC_CATCH_SIGNALS
        if (nbparts > 0)
          IGESFile_ReadContent(IR);
      }
      catch (Standard_Failure const&)
      {

        if (recupnp == 0)
        {
          Message_Msg Msg13 = Message_Msg("XSTEP_13");
          Msg13.Arg(recupne);
          IGESFile_Check(1, Msg13);
        }
        else
        {
          Message_Msg Msg14 = Message_Msg("XSTEP_14");
          Msg14.Arg(recupne);
          Msg14.Arg(recupnp);
          IGESFile_Check(1, Msg14);
        }
      }
    }
  }

  int nbr = IR->NbRecords();

  Msg15.Arg(nbr);
  IGESFile_Check(2, Msg15);
  iges_finfile(1);
  IGESData_IGESReaderTool IT(IR, protocol);
  IT.Prepare(reco);
  IT.SetErrorHandle(true);

  IT.LoadModel(amodel);
  if (amodel->Protocol().IsNull())
    amodel->SetProtocol(protocol);
  iges_finfile(2);

  int nbWarn = checkread()->NbWarnings(), nbFail = checkread()->NbFails();
  const occ::handle<Interface_Check>& oldglob = amodel->GlobalCheck();
  if (nbWarn + nbFail > 0)
  {
    checkread()->GetMessages(oldglob);
    amodel->SetGlobalCheck(checkread());
  }

  checkread()->Trace(0, 1);

  return 0;
}

void IGESFile_ReadHeader(const occ::handle<IGESData_IGESReaderData>& IR)
{
  int   l = 0;
  char* parval;
  int   typarg;

  while (iges_lirparam(&typarg, &parval) != 0)
  {
    int j;
    for (j = 72; j >= 0; j--)
      if (parval[j] > 32)
        break;
    parval[j + 1] = '\0';
    if (j >= 0 || l > 0)
      IR->AddStartLine(parval);
    l++;
  }

  iges_setglobal();
  while (iges_lirparam(&typarg, &parval) != 0)
    IR->AddGlobal(LesTypes[typarg], parval);
  IR->SetGlobalSection();
}

void IGESFile_ReadContent(const occ::handle<IGESData_IGESReaderData>& IR)
{
  char *res1, *res2, *nom, *num;
  char* parval;
  int*  v;
  int   typarg;
  int   nbparam;

  int ns;
  while ((ns = iges_lirpart(&v, &res1, &res2, &nom, &num, &nbparam)) != 0)
  {
    recupnp = 0;
    recupne = (ns + 1) / 2;

    IR->SetDirPart(recupne,
                   v[0],
                   v[1],
                   v[2],
                   v[3],
                   v[4],
                   v[5],
                   v[6],
                   v[7],
                   v[8],
                   v[9],
                   v[10],
                   v[11],
                   v[12],
                   v[13],
                   v[14],
                   v[15],
                   v[16],
                   res1,
                   res2,
                   nom,
                   num);
    while (iges_lirparam(&typarg, &parval) != 0)
    {
      recupnp++;
      if (typarg == ArgInt || typarg == ArgSign)
      {
        int nument = atoi(parval);
        if (nument < 0)
          nument = -nument;
        if (nument & 1)
          nument = (nument + 1) / 2;
        else
          nument = 0;
        IR->AddParam(recupne, parval, LesTypes[typarg], nument);
      }
      else
        IR->AddParam(recupne, parval, LesTypes[typarg]);
    }
    IR->InitParams(recupne);
    iges_nextpart();
  }
}

void IGESFile_Check(int mode, Message_Msg& amsg)
{

  switch (mode)
  {
    case 0:
      checkread()->SendFail(amsg);
      break;
    case 1:
      checkread()->SendWarning(amsg);
      break;
    case 2:
      checkread()->SendMsg(amsg);
      break;
    default:
      checkread()->SendMsg(amsg);
  }
}

void IGESFile_Check2(int mode, char* code, int num, char* str)
{

  Message_Msg amsg(code);
  amsg.Arg(num);
  amsg.Arg(str);

  switch (mode)
  {
    case 0:
      checkread()->SendFail(amsg);
      break;
    case 1:
      checkread()->SendWarning(amsg);
      break;
    case 2:
      checkread()->SendMsg(amsg);
      break;
    default:
      checkread()->SendMsg(amsg);
  }
}

void IGESFile_Check3(int mode, char* code)
{

  Message_Msg amsg(code);
  switch (mode)
  {
    case 0:
      checkread()->SendFail(amsg);
      break;
    case 1:
      checkread()->SendWarning(amsg);
      break;
    case 2:
      checkread()->SendMsg(amsg);
      break;
    default:
      checkread()->SendMsg(amsg);
  }
}
