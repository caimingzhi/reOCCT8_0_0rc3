#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! commands for presentation based on AIS
//! ======================================
class DPrsStd
{
public:
  DEFINE_STANDARD_ALLOC

  //! Presentation commands
  //! =====================
  //! to load all sketch commands
  Standard_EXPORT static void AllCommands(Draw_Interpretor& I);

  //! to display....etc... ais presentation
  Standard_EXPORT static void AISPresentationCommands(Draw_Interpretor& I);

  //! to repaint...etc... ais viewer
  Standard_EXPORT static void AISViewerCommands(Draw_Interpretor& I);

  //! set/get position attribute
  Standard_EXPORT static void BasicCommands(Draw_Interpretor& I);

  //! Loads all Draw commands of TKDCAF. Used for plugin.
  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};
