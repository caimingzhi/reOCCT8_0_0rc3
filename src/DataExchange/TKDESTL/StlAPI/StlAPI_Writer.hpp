#pragma once

#include <Message_ProgressScope.hpp>
#include <Message_ProgressIndicator.hpp>

class TopoDS_Shape;

class StlAPI_Writer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StlAPI_Writer();

  bool& ASCIIMode() { return myASCIIMode; }

  Standard_EXPORT bool Write(const TopoDS_Shape&          theShape,
                             const char*                  theFileName,
                             const System::log::Message_ProgressRange& theProgress = System::log::Message_ProgressRange());

  Standard_EXPORT bool Write(const TopoDS_Shape&          theShape,
                             Standard_OStream&            theStream,
                             const System::log::Message_ProgressRange& theProgress = System::log::Message_ProgressRange());

private:
  bool myASCIIMode;
};
