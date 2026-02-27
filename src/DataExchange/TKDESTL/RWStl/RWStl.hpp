#pragma once

#include <OSD_Path.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_Macro.hpp>
#include <Message_ProgressScope.hpp>
#include <NCollection_Sequence.hpp>

class RWStl
{
public:
  Standard_EXPORT static bool WriteBinary(
    const occ::handle<Poly_Triangulation>& theMesh,
    const System::os::OSD_Path&                        thePath,
    const System::log::Message_ProgressRange&           theProgress = System::log::Message_ProgressRange());

  Standard_EXPORT static bool WriteBinary(
    const occ::handle<Poly_Triangulation>& theMesh,
    Standard_OStream&                      theStream,
    const System::log::Message_ProgressRange&           theProgress = System::log::Message_ProgressRange());

  Standard_EXPORT static bool WriteAscii(
    const occ::handle<Poly_Triangulation>& theMesh,
    const System::os::OSD_Path&                        thePath,
    const System::log::Message_ProgressRange&           theProgress = System::log::Message_ProgressRange());

  Standard_EXPORT static bool WriteAscii(
    const occ::handle<Poly_Triangulation>& theMesh,
    Standard_OStream&                      theStream,
    const System::log::Message_ProgressRange&           theProgress = System::log::Message_ProgressRange());

  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadFile(
    const System::os::OSD_Path&              theFile,
    const System::log::Message_ProgressRange& theProgress = System::log::Message_ProgressRange());

  static occ::handle<Poly_Triangulation> ReadFile(
    const char*                  theFile,
    const System::log::Message_ProgressRange& theProgress = System::log::Message_ProgressRange())
  {
    return ReadFile(theFile, M_PI / 2.0, theProgress);
  }

  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadFile(
    const char*                  theFile,
    const double                 theMergeAngle,
    const System::log::Message_ProgressRange& theProgress = System::log::Message_ProgressRange());

  Standard_EXPORT static void ReadFile(
    const char*                                            theFile,
    const double                                           theMergeAngle,
    NCollection_Sequence<occ::handle<Poly_Triangulation>>& theTriangList,
    const System::log::Message_ProgressRange&                           theProgress = System::log::Message_ProgressRange());

  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadBinary(
    const System::os::OSD_Path&              thePath,
    const System::log::Message_ProgressRange& theProgress = System::log::Message_ProgressRange());

  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadAscii(
    const System::os::OSD_Path&              thePath,
    const System::log::Message_ProgressRange& theProgress = System::log::Message_ProgressRange());

  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadBinaryStream(
    Standard_IStream&            theStream,
    const double                 theMergeAngle = M_PI / 2.0,
    const System::log::Message_ProgressRange& theProgress   = System::log::Message_ProgressRange());

  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadAsciiStream(
    Standard_IStream&            theStream,
    const double                 theMergeAngle = M_PI / 2.0,
    const System::log::Message_ProgressRange& theProgress   = System::log::Message_ProgressRange());

  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadStream(
    Standard_IStream&            theStream,
    const double                 theMergeAngle = M_PI / 2.0,
    const System::log::Message_ProgressRange& theProgress   = System::log::Message_ProgressRange());
};
