#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESControl_Reader.hpp>
#include <TCollection_AsciiString.hpp>
class XSControl_WorkSession;
class TDocStd_Document;

class IGESCAFControl_Reader : public IGESControl_Reader
{
public:
  DEFINE_STANDARD_ALLOC

  IGESCAFControl_Reader()
      : myColorMode(true),
        myNameMode(true),
        myLayerMode(true)
  {
  }

  IGESCAFControl_Reader(const occ::handle<XSControl_WorkSession>& theWS,
                        const bool                                FromScratch = true)
      : myColorMode(true),
        myNameMode(true),
        myLayerMode(true)
  {
    SetWS(theWS, FromScratch);
  }

  Standard_EXPORT bool Transfer(const occ::handle<TDocStd_Document>& theDoc,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  bool Perform(const TCollection_AsciiString&       theFileName,
               const occ::handle<TDocStd_Document>& theDoc,
               const Message_ProgressRange&         theProgress = Message_ProgressRange())
  {
    return Perform(theFileName.ToCString(), theDoc, theProgress);
  }

  Standard_EXPORT bool Perform(const char*                          theFileName,
                               const occ::handle<TDocStd_Document>& theDoc,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  void SetColorMode(const bool theMode) { myColorMode = theMode; }

  bool GetColorMode() const { return myColorMode; }

  void SetNameMode(const bool theMode) { myNameMode = theMode; }

  bool GetNameMode() const { return myNameMode; }

  void SetLayerMode(const bool theMode) { myLayerMode = theMode; }

  bool GetLayerMode() const { return myLayerMode; }

private:
  bool myColorMode;
  bool myNameMode;
  bool myLayerMode;
};
