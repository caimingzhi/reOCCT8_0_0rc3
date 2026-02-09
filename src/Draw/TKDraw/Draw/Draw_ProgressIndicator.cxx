

#include <Draw_ProgressIndicator.hpp>

#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Message_ProgressScope.hpp>
#include <NCollection_List.hpp>
#include <Precision.hpp>
#include <OSD.hpp>
#include <OSD_Exception_CTRL_BREAK.hpp>
#include <OSD_Thread.hpp>

#include <cstdio>
#include <ctime>
IMPLEMENT_STANDARD_RTTIEXT(Draw_ProgressIndicator, Message_ProgressIndicator)

Draw_ProgressIndicator::Draw_ProgressIndicator(const Draw_Interpretor& di,
                                               double                  theUpdateThreshold)
    : myTclMode(DefaultTclMode()),
      myConsoleMode(DefaultConsoleMode()),
      myGraphMode(DefaultGraphMode()),
      myDraw((Draw_Interpretor*)&di),
      myShown(false),
      myBreak(false),
      myUpdateThreshold(0.01 * theUpdateThreshold),
      myLastPosition(-1.),
      myStartTime(0),
      myGuiThreadId(OSD_Thread::Current())
{
}

Draw_ProgressIndicator::~Draw_ProgressIndicator()
{
  Reset();
}

void Draw_ProgressIndicator::Reset()
{
  Message_ProgressIndicator::Reset();
  if (myShown)
  {

    const TCollection_AsciiString aTclResStr(myDraw->Result());
    myDraw->Eval("destroy .xprogress");
    *myDraw << aTclResStr;
    myShown = false;
  }
  myBreak        = false;
  myLastPosition = -1.;
  myStartTime    = 0;
}

void Draw_ProgressIndicator::Show(const Message_ProgressScope& theScope, const bool force)
{
  if (!myGraphMode && !myTclMode && !myConsoleMode)
    return;

  if (!myStartTime)
  {
    if (!myStartTime)
    {
      time_t aTimeT;
      time(&aTimeT);
      myStartTime = (size_t)aTimeT;
    }
  }

  double aPosition = GetPosition();
  if (!force && (1. - aPosition) > Precision::Confusion()
      && std::abs(aPosition - myLastPosition) < myUpdateThreshold)
    return;

  myLastPosition = aPosition;

  std::stringstream aText;
  aText.setf(std::ios::fixed, std::ios::floatfield);
  aText.precision(0);
  aText << "Progress: " << 100. * GetPosition() << "%";
  NCollection_List<const Message_ProgressScope*> aScopes;
  for (const Message_ProgressScope* aPS = &theScope; aPS; aPS = aPS->Parent())
    aScopes.Prepend(aPS);
  for (NCollection_List<const Message_ProgressScope*>::Iterator it(aScopes); it.More(); it.Next())
  {
    const Message_ProgressScope* aPS = it.Value();
    if (!aPS->Name())
      continue;
    aText << " " << aPS->Name() << ": ";

    double aVal = aPS->Value();
    if (aPS->IsInfinite())
    {
      if (Precision::IsInfinite(aVal))
      {
        aText << "finished";
      }
      else
      {
        aText << aVal;
      }
    }
    else
    {
      aText << aVal << " / " << aPS->MaxValue();
    }
  }

  if (myGraphMode && myGuiThreadId == OSD_Thread::Current())
  {

    if (GetPosition() > 0.01)
    {
      time_t aTimeT;
      time(&aTimeT);
      size_t aTime = (size_t)aTimeT;
      aText << "\nElapsed/estimated time: " << (long)(aTime - myStartTime) << "/"
            << (aTime - myStartTime) / GetPosition() << " sec";
    }

    const TCollection_AsciiString aTclResStr(myDraw->Result());
    if (!myShown)
    {
      char command[1024];
      Sprintf(command,
              "toplevel .xprogress -height 100 -width 410;"
              "wm title .xprogress \"Progress\";"
              "set xprogress_stop 0;"
              "canvas .xprogress.bar -width 402 -height 22;"
              ".xprogress.bar create rectangle 2 2 2 21 -fill blue -tags progress;"
              ".xprogress.bar create rectangle 2 2 2 21 -outline black -tags progress_next;"
              "message .xprogress.text -width 400 -text \"Progress 0%%\";"
              "button .xprogress.stop -text \"Break\" -relief groove -width 9 -command {XProgress "
              "-stop %p};"
              "pack .xprogress.bar .xprogress.text .xprogress.stop -side top;",
              this);
      myDraw->Eval(command);
      myShown = true;
    }
    std::stringstream aCommand;
    aCommand.setf(std::ios::fixed, std::ios::floatfield);
    aCommand.precision(0);
    aCommand << ".xprogress.bar coords progress 2 2 " << (1 + 400 * GetPosition()) << " 21;";
    aCommand << ".xprogress.bar coords progress_next 2 2 " << (1 + 400 * theScope.GetPortion())
             << " 21;";
    aCommand << ".xprogress.text configure -text \"" << aText.str() << "\";";
    aCommand << "update";

    myDraw->Eval(aCommand.str().c_str());
    *myDraw << aTclResStr;
  }

  if (myTclMode && myDraw)
  {
    *myDraw << aText.str().c_str() << "\n";
  }
  if (myConsoleMode)
  {
    std::cout << aText.str().c_str() << "\n";
  }
}

bool Draw_ProgressIndicator::UserBreak()
{
  if (StopIndicator() == this)
  {

    myBreak = true;
    myDraw->Eval("XProgress -stop 0");
  }
  else
  {

    try
    {
      OSD::ControlBreak();
    }
    catch (const OSD_Exception_CTRL_BREAK&)
    {
      myBreak = true;
    }
  }
  return myBreak;
}

void Draw_ProgressIndicator::SetTclMode(const bool theTclMode)
{
  myTclMode = theTclMode;
}

bool Draw_ProgressIndicator::GetTclMode() const
{
  return myTclMode;
}

void Draw_ProgressIndicator::SetConsoleMode(const bool theMode)
{
  myConsoleMode = theMode;
}

bool Draw_ProgressIndicator::GetConsoleMode() const
{
  return myConsoleMode;
}

void Draw_ProgressIndicator::SetGraphMode(const bool theGraphMode)
{
  myGraphMode = theGraphMode;
}

bool Draw_ProgressIndicator::GetGraphMode() const
{
  return myGraphMode;
}

bool& Draw_ProgressIndicator::DefaultTclMode()
{
  static bool defTclMode = false;
  return defTclMode;
}

bool& Draw_ProgressIndicator::DefaultConsoleMode()
{
  static bool defConsoleMode = false;
  return defConsoleMode;
}

bool& Draw_ProgressIndicator::DefaultGraphMode()
{
  static bool defGraphMode = false;
  return defGraphMode;
}

void*& Draw_ProgressIndicator::StopIndicator()
{
  static void* stopIndicator = nullptr;
  return stopIndicator;
}
