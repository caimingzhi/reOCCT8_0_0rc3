#include <BRepLib_Command.hpp>
#include <StdFail_NotDone.hpp>

BRepLib_Command::BRepLib_Command()
    : myDone(false)
{
}

BRepLib_Command::~BRepLib_Command() = default;

bool BRepLib_Command::IsDone() const
{
  return myDone;
}

void BRepLib_Command::Check() const
{
  if (!myDone)
    throw StdFail_NotDone("BRep_API: command not done");
}

void BRepLib_Command::Done()
{
  myDone = true;
}

void BRepLib_Command::NotDone()
{
  myDone = false;
}
