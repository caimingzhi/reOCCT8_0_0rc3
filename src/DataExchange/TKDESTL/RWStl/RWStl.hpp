#pragma once

#include <OSD_Path.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_Macro.hpp>
#include <Message_ProgressScope.hpp>
#include <NCollection_Sequence.hpp>

//! This class provides methods to read and write triangulation from / to the STL files.
class RWStl
{
public:
  //! Write triangulation to binary STL file.
  //! binary format of an STL file.
  //! Returns false if the cannot be opened;
  Standard_EXPORT static bool WriteBinary(
    const occ::handle<Poly_Triangulation>& theMesh,
    const OSD_Path&                        thePath,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  //! Write triangulation to binary STL stream.
  Standard_EXPORT static bool WriteBinary(
    const occ::handle<Poly_Triangulation>& theMesh,
    Standard_OStream&                      theStream,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  //! write the meshing in a file following the
  //! Ascii format of an STL file.
  //! Returns false if the cannot be opened;
  Standard_EXPORT static bool WriteAscii(
    const occ::handle<Poly_Triangulation>& theMesh,
    const OSD_Path&                        thePath,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  //! Write triangulation to ASCII STL stream.
  Standard_EXPORT static bool WriteAscii(
    const occ::handle<Poly_Triangulation>& theMesh,
    Standard_OStream&                      theStream,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  //! Read specified STL file and returns its content as triangulation.
  //! In case of error, returns Null handle.
  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadFile(
    const OSD_Path&              theFile,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Read specified STL file and returns its content as triangulation.
  //! In case of error, returns Null handle.
  static occ::handle<Poly_Triangulation> ReadFile(
    const char*                  theFile,
    const Message_ProgressRange& theProgress = Message_ProgressRange())
  {
    return ReadFile(theFile, M_PI / 2.0, theProgress);
  }

  //! Read specified STL file and returns its content as triangulation.
  //! @param[in] theFile file path to read
  //! @param[in] theMergeAngle maximum angle in radians between triangles to merge equal nodes;
  //! M_PI/2 means ignore angle
  //! @param[in] theProgress progress indicator
  //! @return result triangulation or NULL in case of error
  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadFile(
    const char*                  theFile,
    const double                 theMergeAngle,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Read specified STL file and fills triangulation list for multi-domain case.
  //! @param[in] theFile file path to read
  //! @param[in] theMergeAngle maximum angle in radians between triangles to merge equal nodes;
  //! M_PI/2 means ignore angle
  //! @param[out] theTriangList triangulation list for multi-domain case
  //! @param[in] theProgress progress indicator
  Standard_EXPORT static void ReadFile(
    const char*                                            theFile,
    const double                                           theMergeAngle,
    NCollection_Sequence<occ::handle<Poly_Triangulation>>& theTriangList,
    const Message_ProgressRange&                           theProgress = Message_ProgressRange());

  //! Read triangulation from a binary STL file
  //! In case of error, returns Null handle.
  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadBinary(
    const OSD_Path&              thePath,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Read triangulation from an Ascii STL file
  //! In case of error, returns Null handle.
  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadAscii(
    const OSD_Path&              thePath,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Read triangulation from binary STL stream
  //! In case of error, returns Null handle.
  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadBinaryStream(
    Standard_IStream&            theStream,
    const double                 theMergeAngle = M_PI / 2.0,
    const Message_ProgressRange& theProgress   = Message_ProgressRange());

  //! Read triangulation from ASCII STL stream
  //! In case of error, returns Null handle.
  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadAsciiStream(
    Standard_IStream&            theStream,
    const double                 theMergeAngle = M_PI / 2.0,
    const Message_ProgressRange& theProgress   = Message_ProgressRange());

  //! Read STL data from stream (auto-detects ASCII vs Binary)
  //! In case of error, returns Null handle.
  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadStream(
    Standard_IStream&            theStream,
    const double                 theMergeAngle = M_PI / 2.0,
    const Message_ProgressRange& theProgress   = Message_ProgressRange());
};
