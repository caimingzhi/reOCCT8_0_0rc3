#pragma once

#include <Standard.hpp>

#include <Message_ProgressIndicator.hpp>
#include <Standard_ThreadId.hpp>
#include <Draw_Interpretor.hpp>

class Draw_ProgressIndicator : public Message_ProgressIndicator
{

public:
  Standard_EXPORT Draw_ProgressIndicator(const Draw_Interpretor& di,
                                         double                  theUpdateThreshold = 1.);

  Standard_EXPORT ~Draw_ProgressIndicator() override;

  Standard_EXPORT void SetTclMode(const bool theTclMode);

  Standard_EXPORT bool GetTclMode() const;

  Standard_EXPORT void SetConsoleMode(const bool theMode);

  Standard_EXPORT bool GetConsoleMode() const;

  Standard_EXPORT void SetGraphMode(const bool theGraphMode);

  Standard_EXPORT bool GetGraphMode() const;

  Standard_EXPORT void Reset() override;

  Standard_EXPORT void Show(const Message_ProgressScope& theScope,
                            const bool                   force = true) override;

  Standard_EXPORT bool UserBreak() override;

  Standard_EXPORT static bool& DefaultTclMode();

  Standard_EXPORT static bool& DefaultConsoleMode();

  Standard_EXPORT static bool& DefaultGraphMode();

  Standard_EXPORT static void*& StopIndicator();

  DEFINE_STANDARD_RTTIEXT(Draw_ProgressIndicator, Message_ProgressIndicator)

private:
  bool              myTclMode;
  bool              myConsoleMode;
  bool              myGraphMode;
  Draw_Interpretor* myDraw;
  bool              myShown;
  bool              myBreak;
  double            myUpdateThreshold;
  double            myLastPosition;
  size_t            myStartTime;
  Standard_ThreadId myGuiThreadId;
};
