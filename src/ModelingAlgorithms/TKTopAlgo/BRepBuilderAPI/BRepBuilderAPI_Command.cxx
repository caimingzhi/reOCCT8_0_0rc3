#include <BRepBuilderAPI_Command.hpp>
#include <StdFail_NotDone.hpp>

//=================================================================================================

BRepBuilderAPI_Command::BRepBuilderAPI_Command()
    : myDone(false)
{
}

//=================================================================================================

BRepBuilderAPI_Command::~BRepBuilderAPI_Command() = default;

//=================================================================================================

bool BRepBuilderAPI_Command::IsDone() const
{
  return myDone;
}

//=================================================================================================

void BRepBuilderAPI_Command::Check() const
{
  if (!myDone)
    throw StdFail_NotDone("BRep_API: command not done");
}

//=================================================================================================

void BRepBuilderAPI_Command::Done()
{
  myDone = true;
}

//=================================================================================================

void BRepBuilderAPI_Command::NotDone()
{
  myDone = false;
}
