

#include <IFSelect_SessionPilot.hpp>
#include <IFSelect_SignCounter.hpp>
#include <IFSelect_WorkLibrary.hpp>
#include <IFSelect_WorkSession.hpp>
#include <Interface_EntityIterator.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <OSD_OpenFile.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SessionPilot, IFSelect_Activator)

#define MAXWORDS 200
#define MAXCARS 1000

static int THE_IFSelect_SessionPilot_initactor = 0;

IFSelect_SessionPilot::IFSelect_SessionPilot(const char* prompt)
    : theprompt(prompt),
      thewords(0, MAXWORDS - 1),
      thewordeb(0, MAXWORDS - 1)
{
  if (theprompt.Length() == 0)
  {
    theprompt.AssignCat("Test-XSTEP>");
  }
  therecord  = false;
  thenbwords = 0;
  if (THE_IFSelect_SessionPilot_initactor)
  {
    return;
  }

  THE_IFSelect_SessionPilot_initactor = 1;
  Add(1, "x");
  Add(1, "exit");
  Add(2, "?");
  Add(2, "xhelp");
  Add(3, "xcommand");
  Add(4, "xsource");
  Add(5, "xstep");
  Add(6, "xnew");
}

occ::handle<IFSelect_WorkSession> IFSelect_SessionPilot::Session() const
{
  return thesession;
}

occ::handle<IFSelect_WorkLibrary> IFSelect_SessionPilot::Library() const
{
  return thesession->WorkLibrary();
}

bool IFSelect_SessionPilot::RecordMode() const
{
  return therecord;
}

void IFSelect_SessionPilot::SetSession(const occ::handle<IFSelect_WorkSession>& WS)
{
  thesession = WS;
}

void IFSelect_SessionPilot::SetLibrary(const occ::handle<IFSelect_WorkLibrary>& WL)
{
  if (!thesession.IsNull())
    thesession->SetLibrary(WL);
}

void IFSelect_SessionPilot::SetRecordMode(const bool mode)
{
  therecord = mode;
}

void IFSelect_SessionPilot::SetCommandLine(const TCollection_AsciiString& command)
{
  int lc = command.Length();
  if (lc > 200)
    std::cout << " VERY LONG Command : " << lc << " characters :" << std::endl
              << command.ToCString() << std::endl;
  thecommand = command;
  if (thecommand.Value(lc) <= ' ')
  {
    thecommand.Remove(lc);
    lc--;
  }
  thenbwords = 0;
  int  i, nc = 0;
  char unarg[MAXCARS];
  for (i = 1; i <= lc; i++)
  {
    char val = command.Value(i);
    if (val <= ' ')
    {
      if (nc == 0)
        continue;
      if (thenbwords >= MAXWORDS)
      {
        unarg[nc] = val;
        nc++;
        continue;
      }
      unarg[nc] = '\0';
      thewords(thenbwords).Clear();
      thewords(thenbwords).AssignCat(unarg);
#ifdef DEBUG_TRACE
      std::cout << "thewords(" << thenbwords << ") =" << unarg << std::endl;
#endif
      thenbwords++;
      nc = 0;
      continue;
    }
    if (nc == 0)
      thewordeb.SetValue(thenbwords, i);
    if (nc > MAXCARS)
    {
      std::cout << "Arg." << thenbwords << " > " << MAXCARS << " car.s, tronque" << std::endl;
      continue;
    }
    unarg[nc] = val;
    nc++;
  }
  if (nc > 0)
  {
    unarg[nc] = '\0';
    thewords(thenbwords).Clear();
    thewords(thenbwords).AssignCat(unarg);
#ifdef DEBUG_TRACE
    std::cout << "thewords(" << thenbwords << ")=" << unarg << std::endl
              << " .. End with thenbwords=" << thenbwords + 1 << std::endl;
#endif
    thenbwords++;
  }

  thenumrec = 0;
  theobjrec.Nullify();
}

const TCollection_AsciiString& IFSelect_SessionPilot::CommandLine() const
{
  return thecommand;
}

const char* IFSelect_SessionPilot::CommandPart(const int numarg) const
{
  if (numarg <= 0)
    return thecommand.ToCString();
  if (numarg >= thenbwords)
    return "";
  return &(thecommand.ToCString())[thewordeb(numarg) - 1];
}

int IFSelect_SessionPilot::NbWords() const
{
  return thenbwords;
}

const TCollection_AsciiString& IFSelect_SessionPilot::Word(const int num) const
{
  if (num < thenbwords)
    return thewords(num);
  return TCollection_AsciiString::EmptyString();
}

const char* IFSelect_SessionPilot::Arg(const int num) const
{
  return Word(num).ToCString();
}

bool IFSelect_SessionPilot::RemoveWord(const int num)
{
  if (num < 0 || num > thenbwords)
    return false;
  int i;
  for (i = num; i < thenbwords; i++)
  {
    thewords(i).Clear();
    thewords(i).AssignCat(thewords(i + 1).ToCString());
  }
  thewords(thenbwords).Clear();
  thenbwords--;

  if (num == 0)
  {
    thecommand.Remove(1, thewordeb(1));
  }
  else
  {

    thecommand.Clear();
    for (i = 0; i < thenbwords; i++)
    {
      if (i > 0)
        thecommand.AssignCat(" ");
      thecommand.AssignCat(thewords(i));
    }
  }

  return true;
}

int IFSelect_SessionPilot::NbCommands() const
{
  return thecomlist.Length();
}

const TCollection_AsciiString& IFSelect_SessionPilot::Command(const int num) const
{
  return thecomlist(num);
}

IFSelect_ReturnStatus IFSelect_SessionPilot::RecordItem(const occ::handle<Standard_Transient>& item)
{
  theobjrec = item;
  return (item.IsNull() ? IFSelect_RetFail : IFSelect_RetDone);
}

occ::handle<Standard_Transient> IFSelect_SessionPilot::RecordedItem() const
{
  return theobjrec;
}

void IFSelect_SessionPilot::Clear()
{
  thecomlist.Clear();
}

IFSelect_ReturnStatus IFSelect_SessionPilot::ReadScript(const char* file)
{
  FILE* fic;
  int   lefic = 0;
  if (file != nullptr && file[0] != '\0')
  {
    fic = OSD_OpenFile(file, "r");
    if (fic)
      lefic = 1;
    else
    {
      std::cout << " ...   Script File " << file << " not found" << std::endl;
      return IFSelect_RetFail;
    }
    std::cout << " ...   Reading Script File " << file << std::endl;
  }
  else
    fic = stdin;
  IFSelect_ReturnStatus stat = IFSelect_RetVoid;

  for (;;)
  {
    char ligne[100];
    if (!lefic)
      std::cout << theprompt.ToCString();
    ligne[0] = '\0';
    if (fgets(ligne, 100, fic) == nullptr || feof(fic) != 0)
    {
      break;
    }
    if (ligne[0] == '\0')
      continue;

    TCollection_AsciiString command(ligne);
    if (lefic)
      std::cout << file << ":" << command;
    stat = Execute(command);
    if (stat == IFSelect_RetStop)
      break;
    if ((stat == IFSelect_RetError || stat == IFSelect_RetFail) && lefic)
    {
      std::cout << " ...   Error in Script File, abandon" << std::endl;
      break;
    }
  }
  if (!lefic)
    return IFSelect_RetStop;
  fclose(fic);
  std::cout << "End of Reading Script File " << file << std::endl;
  if (stat == IFSelect_RetError || stat == IFSelect_RetFail)
    return stat;
  return IFSelect_RetVoid;
}

IFSelect_ReturnStatus IFSelect_SessionPilot::Perform()
{
  IFSelect_ReturnStatus stat = IFSelect_RetVoid;
  if (thenbwords == 0)
    return stat;
  if (thewords(0).Value(1) == '#')
    return stat;

  theobjrec.Nullify();

  occ::handle<IFSelect_Activator> actor;
  int                             num;
  if (IFSelect_Activator::Select(thewords(0).ToCString(), num, actor))
  {
    stat = actor->Do(num, this);

    if (!theobjrec.IsNull())
    {
      thesession->RemoveItem(theobjrec);
      int addws = thesession->AddItem(theobjrec);
      if (addws == 0)
      {
        std::cout << "Could not add item to session, sorry" << std::endl;
        return IFSelect_RetFail;
      }
    }

    if (stat == IFSelect_RetVoid || stat == IFSelect_RetDone)
    {
      if (therecord)
        thecomlist.Append(thecommand);
    }
    else if (stat == IFSelect_RetError)
      std::cout << "Error in Command : " << thecommand << std::endl;
    else if (stat == IFSelect_RetFail)
      std::cout << "Execution Failure for : " << thecommand << std::endl;
    return stat;
  }
  std::cout << " Command : " << thewords(0) << " unknown" << std::endl;
  return IFSelect_RetError;
}

IFSelect_ReturnStatus IFSelect_SessionPilot::ExecuteAlias(const TCollection_AsciiString& alias)
{
  if (alias.Length() > 0)
    thewords(0) = alias;
  return Perform();
}

IFSelect_ReturnStatus IFSelect_SessionPilot::Execute(const TCollection_AsciiString& command)
{
  SetCommandLine(command);
  return Perform();
}

IFSelect_ReturnStatus IFSelect_SessionPilot::ExecuteCounter(
  const occ::handle<IFSelect_SignCounter>& counter,
  const int                                numword,
  const IFSelect_PrintCount                mode)
{
  if (counter.IsNull())
    return IFSelect_RetError;
  counter->Clear();
  if (NbWords() <= numword)
    counter->AddModel(thesession->Model());
  else
  {

    occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> list =
      thesession->GiveList(CommandPart(numword));
    if (list.IsNull())
    {
      std::cout << "Nothing selected from : " << CommandPart(numword) << std::endl;
      return IFSelect_RetError;
    }
    counter->AddWithGraph(list, thesession->Graph());
  }
  Message_Messenger::StreamBuffer sout = Message::SendInfo();
  counter->PrintList(sout, thesession->Model(), mode);
  return IFSelect_RetVoid;
}

int IFSelect_SessionPilot::Number(const char* val) const
{
  int num = thesession->NumberFromLabel(val);
  if (num < 0)
    std::cout << " Label:" << val << " ->" << -num << " ent.s, refus" << std::endl;
  return num;
}

#define MAXCOMPERLINE 5
#define LENGTHFORCOM 15

IFSelect_ReturnStatus IFSelect_SessionPilot::Do(const int                                 number,
                                                const occ::handle<IFSelect_SessionPilot>& session)
{

  IFSelect_ReturnStatus stat    = IFSelect_RetVoid;
  int                   argc    = NbWords();
  const char*           arg1    = Word(1).ToCString();
  int                   modhelp = -1;
  switch (number)
  {
    case -1:
      modhelp = 1;
      std::cout << "  --  Commands candidate for  xsnew  --" << std::endl;

      [[fallthrough]];
    case 0:
    {
      occ::handle<NCollection_HSequence<TCollection_AsciiString>> list;

      if (thenbwords <= 1)
      {
        list      = IFSelect_Activator::Commands(modhelp);
        int nbcom = 0;
        int nb    = list->Length();
        std::cout << " -- List of Available Commands --" << std::endl;
        for (int i = 1; i <= nb; i++)
        {
          const TCollection_AsciiString& uncom  = list->Value(i);
          int                            loncom = uncom.Length();
          nbcom++;
          if (nbcom > MAXCOMPERLINE)
          {
            std::cout << std::endl;
            nbcom = 1;
          }
          std::cout << " " << uncom;
          if (nbcom == MAXCOMPERLINE)
            continue;
          for (int j = loncom; j < LENGTHFORCOM; j++)
            std::cout << " ";
        }
        if (nbcom > 0)
          std::cout << std::endl;
        std::cout << "\nhelp *  lists all commands with help on each\n"
                  << "help <com> lists the command(s) starting with <com>"
                  << " with help on each" << std::endl;
      }
      else
      {
        if (thewords(1).IsEqual("*"))
          list = IFSelect_Activator::Commands(modhelp);

        else
          list = IFSelect_Activator::Commands(modhelp, thewords(1).ToCString());

        int nb = list->Length();
        for (int i = 1; i <= nb; i++)
        {
          occ::handle<IFSelect_Activator> actor;
          int                             num;
          if (IFSelect_Activator::Select(list->Value(i).ToCString(), num, actor))
          {
            if (IFSelect_Activator::Mode(list->Value(i).ToCString()) == 1)
              std::cout << "[xsnew name] ";
            std::cout << list->Value(i) << "	: " << actor->Help(num) << std::endl;
          }
        }
        if (nb == 0 && thenbwords > 1)
          std::cout << " Command " << Word(1) << " unknown. "
                    << " help (without command) lists all the commands" << std::endl;
      }
      return IFSelect_RetVoid;
    }
    case 1:
      return IFSelect_RetStop;
    case 2:
    {
      return Do(0, this);
    }
    case 3:
    {
      if (argc < 2)
      {
        std::cout << "Give an option :\n"
                  << "a : analyze a line  r : toggle record mode\n"
                  << "l : list recorded  c : clear  f name : save in file of name" << std::endl;
        return IFSelect_RetVoid;
      }
      switch (arg1[0])
      {
        case 'a':
        {
          std::cout << "Command n0 " << number << " : " << session->CommandLine() << std::endl;
          std::cout << "Nb Words : " << argc - 2 << " :\n";
          for (int i = 2; i < argc; i++)
          {
            std::cout << " Word." << i - 1 << " : " << session->Word(i) << std::endl;
          }
          break;
        }
        case 'c':
          session->Clear();
          break;
        case 'f':
        {
          if (argc < 3)
          {
            std::cout << "Give file name" << std::endl;
            return IFSelect_RetError;
          }
          int nb = session->NbCommands();
          if (nb == 0)
          {
            std::cout << "No command recorded" << std::endl;
            break;
          }
          std::cout << "Nb Recorded Commands : " << nb << std::endl;
          std::ofstream fout(Word(2).ToCString(), std::ios::out);
          for (int i = 1; i <= nb; i++)
            fout << session->Command(i) << std::endl;
          break;
        }
        case 'l':
        {
          if (session->RecordMode())
            std::cout << "  -- Record Mode Active" << std::endl;
          else
            std::cout << "  -- Record Mode Inactive" << std::endl;
          int nb = session->NbCommands();
          std::cout << "Nb Recorded Commands : " << nb << " :" << std::endl;
          for (int i = 1; i <= nb; i++)
          {
            std::cout << "  " << i << "	" << session->Command(i) << std::endl;
          }
          break;
        }
        case 'r':
        {
          bool mode = session->RecordMode();
          if (mode)
            std::cout << " -- Record Mode now Inactive" << std::endl;
          else
            std::cout << " -- Record Mode now Active" << std::endl;
          session->SetRecordMode(!mode);
          break;
        }
        default:
          std::cout << "Command control option not understood" << std::endl;
      }
      return IFSelect_RetVoid;
    }

    case 4:
    {
      if (argc < 2)
      {
        std::cout << "Give file name" << std::endl;
        return IFSelect_RetError;
      }
      return session->ReadScript(TCollection_AsciiString(session->Word(1)).ToCString());
    }

    case 5:
    {
      if (argc < 2)
      {
        std::cout << "xstep : neutral prefix for any xstep-draw command" << std::endl
                  << "xstep command args  equivalent to  command args" << std::endl;
        return Do(2, this);
      }
      else
      {
        RemoveWord(0);
        return Perform();
      }
    }
    case 6:
    {
      if (argc < 3)
      {
        std::cout << "xsnew varname command [args]   creates an item" << std::endl
                  << "  varname : name of item (must be a new name) in the session" << std::endl;
        return Do(-1, this);
      }
      else
      {

        theobjrec.Nullify();
        TCollection_AsciiString name = Word(1);

        if (thesession.IsNull())
        {
          std::cout << "Command with a Name and no Session defined !" << std::endl;
          return IFSelect_RetFail;
        }

        RemoveWord(0);
        RemoveWord(0);

        occ::handle<IFSelect_Activator> actor;
        int                             num;
        if (IFSelect_Activator::Select(thewords(0).ToCString(), num, actor))
        {
          theobjrec.Nullify();
          stat = actor->Do(num, this);

          if (!theobjrec.IsNull())
          {
            thesession->RemoveItem(theobjrec);
            int addws = thesession->AddNamedItem(name.ToCString(), theobjrec);
            theobjrec.Nullify();
            if (addws == 0)
            {
              std::cout << "Could not add named item:" << name << ", sorry" << std::endl;
              return IFSelect_RetFail;
            }
          }
          else
            std::cout << "Remark : xsnew with name:" << name << " and no result" << std::endl;

          return stat;
        }
        std::cout << " Command : " << thewords(0) << " unknown" << std::endl;
        return IFSelect_RetError;
      }
    }
    default:
      return IFSelect_RetError;
  }
}

const char* IFSelect_SessionPilot::Help(const int number) const
{
  switch (number)
  {
    case 1:
      return "exit or x : End of session";
    case 2:
      return "Lists the commands. ? <title> : commands starting with <title>";
    case 3:
      return "command control. command alone for complete help";
    case 4:
      return "reads commands from a file";
    case 5:
      return "neutral prefix for xstep-draw";
    case 6:
      return "item creation : give item_name then command args";
    default:
      return "";
  }
}
