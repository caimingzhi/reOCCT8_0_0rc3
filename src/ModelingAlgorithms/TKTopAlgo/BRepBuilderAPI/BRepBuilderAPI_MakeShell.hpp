#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepLib_MakeShell.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <Standard_Real.hpp>

enum BRepBuilderAPI_ShellError
{
  BRepBuilderAPI_ShellDone,
  BRepBuilderAPI_EmptyShell,
  BRepBuilderAPI_DisconnectedShell,
  BRepBuilderAPI_ShellParametersOutOfRange
};

class Geom_Surface;
class TopoDS_Shell;

class BRepBuilderAPI_MakeShell : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_MakeShell();

  Standard_EXPORT BRepBuilderAPI_MakeShell(const occ::handle<Geom_Surface>& S,
                                           const bool                       Segment = false);

  Standard_EXPORT BRepBuilderAPI_MakeShell(const occ::handle<Geom_Surface>& S,
                                           const double                     UMin,
                                           const double                     UMax,
                                           const double                     VMin,
                                           const double                     VMax,
                                           const bool                       Segment = false);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S,
                            const double                     UMin,
                            const double                     UMax,
                            const double                     VMin,
                            const double                     VMax,
                            const bool                       Segment = false);

  Standard_EXPORT bool IsDone() const override;

  Standard_EXPORT BRepBuilderAPI_ShellError Error() const;

  Standard_EXPORT const TopoDS_Shell& Shell() const;
  Standard_EXPORT                     operator TopoDS_Shell() const;

private:
  BRepLib_MakeShell myMakeShell;
};
