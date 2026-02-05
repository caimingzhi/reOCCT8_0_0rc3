#pragma once

#include <Message_ProgressScope.hpp>
#include <Message_ProgressIndicator.hpp>

class TopoDS_Shape;

//! This class creates and writes
//! STL files from Open CASCADE shapes. An STL file can be written to an existing STL file or to a
//! new one.
class StlAPI_Writer
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a writer object with default parameters: ASCIIMode.
  Standard_EXPORT StlAPI_Writer();

  //! Returns the address to the flag defining the mode for writing the file.
  //! This address may be used to either read or change the flag.
  //! If the mode returns True (default value) the generated file is an ASCII file.
  //! If the mode returns False, the generated file is a binary file.
  bool& ASCIIMode() { return myASCIIMode; }

  //! Converts a given shape to STL format and writes it to file with a given filename.
  //! \return the error state.
  Standard_EXPORT bool Write(const TopoDS_Shape&          theShape,
                             const char*                  theFileName,
                             const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Converts a given shape to STL format and writes it to the specified stream.
  //! \return the error state.
  Standard_EXPORT bool Write(const TopoDS_Shape&          theShape,
                             Standard_OStream&            theStream,
                             const Message_ProgressRange& theProgress = Message_ProgressRange());

private:
  bool myASCIIMode;
};
