#include <BRepBuilderAPI_MakeShell.hpp>
#include <Geom_Surface.hpp>
#include <TopoDS_Shell.hpp>

BRepBuilderAPI_MakeShell::BRepBuilderAPI_MakeShell() = default;

BRepBuilderAPI_MakeShell::BRepBuilderAPI_MakeShell(const occ::handle<Geom_Surface>& S,
                                                   const bool                       Segment)
    : myMakeShell(S, Segment)
{
  if (myMakeShell.IsDone())
  {
    Done();
    myShape = myMakeShell.Shape();
  }
}

BRepBuilderAPI_MakeShell::BRepBuilderAPI_MakeShell(const occ::handle<Geom_Surface>& S,
                                                   const double                     UMin,
                                                   const double                     UMax,
                                                   const double                     VMin,
                                                   const double                     VMax,
                                                   const bool                       Segment)
    : myMakeShell(S, UMin, UMax, VMin, VMax, Segment)
{
  if (myMakeShell.IsDone())
  {
    Done();
    myShape = myMakeShell.Shape();
  }
}

void BRepBuilderAPI_MakeShell::Init(const occ::handle<Geom_Surface>& S,
                                    const double                     UMin,
                                    const double                     UMax,
                                    const double                     VMin,
                                    const double                     VMax,
                                    const bool                       Segment)
{
  myMakeShell.Init(S, UMin, UMax, VMin, VMax, Segment);
  if (myMakeShell.IsDone())
  {
    Done();
    myShape = myMakeShell.Shape();
  }
}

bool BRepBuilderAPI_MakeShell::IsDone() const
{
  return myMakeShell.IsDone();
}

BRepBuilderAPI_ShellError BRepBuilderAPI_MakeShell::Error() const
{
  switch (myMakeShell.Error())
  {

    case BRepLib_ShellDone:
      return BRepBuilderAPI_ShellDone;

    case BRepLib_EmptyShell:
      return BRepBuilderAPI_EmptyShell;

    case BRepLib_DisconnectedShell:
      return BRepBuilderAPI_DisconnectedShell;

    case BRepLib_ShellParametersOutOfRange:
      return BRepBuilderAPI_ShellParametersOutOfRange;
  }

  return BRepBuilderAPI_ShellDone;
}

const TopoDS_Shell& BRepBuilderAPI_MakeShell::Shell() const
{
  return myMakeShell.Shell();
}

BRepBuilderAPI_MakeShell::operator TopoDS_Shell() const
{
  return Shell();
}
