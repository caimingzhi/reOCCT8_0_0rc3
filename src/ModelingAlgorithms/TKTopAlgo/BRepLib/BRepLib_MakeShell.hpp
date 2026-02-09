#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

enum BRepLib_ShellError
{
  BRepLib_ShellDone,
  BRepLib_EmptyShell,
  BRepLib_DisconnectedShell,
  BRepLib_ShellParametersOutOfRange
};

#include <BRepLib_MakeShape.hpp>
class Geom_Surface;
class TopoDS_Shell;

class BRepLib_MakeShell : public BRepLib_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepLib_MakeShell();

  Standard_EXPORT BRepLib_MakeShell(const occ::handle<Geom_Surface>& S, const bool Segment = false);

  Standard_EXPORT BRepLib_MakeShell(const occ::handle<Geom_Surface>& S,
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

  Standard_EXPORT BRepLib_ShellError Error() const;

  Standard_EXPORT const TopoDS_Shell& Shell() const;
  Standard_EXPORT                     operator TopoDS_Shell() const;

private:
  BRepLib_ShellError myError;
};
