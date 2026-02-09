#pragma once

#include <DE_ConfigurationNode.hpp>
#include <DE_Provider.hpp>
#include <Message_ProgressRange.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_List.hpp>

#include <mutex>

class TopoDS_Shape;
class XSControl_WorkSession;
class TDocStd_Document;

class DE_Wrapper : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(DE_Wrapper, Standard_Transient)

public:
  Standard_EXPORT DE_Wrapper();

  Standard_EXPORT DE_Wrapper(const occ::handle<DE_Wrapper>& theWrapper);

  Standard_EXPORT static const occ::handle<DE_Wrapper>& GlobalWrapper();

  Standard_EXPORT static void SetGlobalWrapper(const occ::handle<DE_Wrapper>& theWrapper);

  Standard_EXPORT static std::mutex& GlobalLoadMutex();

public:
  Standard_EXPORT bool Read(const TCollection_AsciiString&       thePath,
                            const occ::handle<TDocStd_Document>& theDocument,
                            occ::handle<XSControl_WorkSession>&  theWS,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Write(const TCollection_AsciiString&       thePath,
                             const occ::handle<TDocStd_Document>& theDocument,
                             occ::handle<XSControl_WorkSession>&  theWS,
                             const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Read(const TCollection_AsciiString&       thePath,
                            const occ::handle<TDocStd_Document>& theDocument,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Write(const TCollection_AsciiString&       thePath,
                             const occ::handle<TDocStd_Document>& theDocument,
                             const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Read(const TCollection_AsciiString&      thePath,
                            TopoDS_Shape&                       theShape,
                            occ::handle<XSControl_WorkSession>& theWS,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Write(const TCollection_AsciiString&      thePath,
                             const TopoDS_Shape&                 theShape,
                             occ::handle<XSControl_WorkSession>& theWS,
                             const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Read(const TCollection_AsciiString& thePath,
                            TopoDS_Shape&                  theShape,
                            const Message_ProgressRange&   theProgress = Message_ProgressRange());

  Standard_EXPORT bool Write(const TCollection_AsciiString& thePath,
                             const TopoDS_Shape&            theShape,
                             const Message_ProgressRange&   theProgress = Message_ProgressRange());

  Standard_EXPORT bool Read(DE_Provider::ReadStreamList&         theStreams,
                            const occ::handle<TDocStd_Document>& theDocument,
                            occ::handle<XSControl_WorkSession>&  theWS,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Write(DE_Provider::WriteStreamList&        theStreams,
                             const occ::handle<TDocStd_Document>& theDocument,
                             occ::handle<XSControl_WorkSession>&  theWS,
                             const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Read(DE_Provider::ReadStreamList&         theStreams,
                            const occ::handle<TDocStd_Document>& theDocument,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Write(DE_Provider::WriteStreamList&        theStreams,
                             const occ::handle<TDocStd_Document>& theDocument,
                             const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Read(DE_Provider::ReadStreamList&        theStreams,
                            TopoDS_Shape&                       theShape,
                            occ::handle<XSControl_WorkSession>& theWS,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Write(DE_Provider::WriteStreamList&       theStreams,
                             const TopoDS_Shape&                 theShape,
                             occ::handle<XSControl_WorkSession>& theWS,
                             const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Read(DE_Provider::ReadStreamList& theStreams,
                            TopoDS_Shape&                theShape,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Write(DE_Provider::WriteStreamList& theStreams,
                             const TopoDS_Shape&           theShape,
                             const Message_ProgressRange&  theProgress = Message_ProgressRange());

public:
  Standard_EXPORT bool Load(const TCollection_AsciiString& theResource    = "",
                            const bool                     theIsRecursive = true);

  Standard_EXPORT bool Load(const occ::handle<DE_ConfigurationContext>& theResource,
                            const bool                                  theIsRecursive = true);

  Standard_EXPORT bool Save(const TCollection_AsciiString&                   theResourcePath,
                            const bool                                       theIsRecursive = true,
                            const NCollection_List<TCollection_AsciiString>& theFormats =
                              NCollection_List<TCollection_AsciiString>(),
                            const NCollection_List<TCollection_AsciiString>& theVendors =
                              NCollection_List<TCollection_AsciiString>());

  Standard_EXPORT TCollection_AsciiString
    Save(const bool                                       theIsRecursive = true,
         const NCollection_List<TCollection_AsciiString>& theFormats =
           NCollection_List<TCollection_AsciiString>(),
         const NCollection_List<TCollection_AsciiString>& theVendors =
           NCollection_List<TCollection_AsciiString>());

  Standard_EXPORT bool Bind(const occ::handle<DE_ConfigurationNode>& theNode);

  Standard_EXPORT bool UnBind(const occ::handle<DE_ConfigurationNode>& theNode);

  Standard_EXPORT bool Find(const TCollection_AsciiString&     theFormat,
                            const TCollection_AsciiString&     theVendor,
                            occ::handle<DE_ConfigurationNode>& theNode) const;

  Standard_EXPORT void ChangePriority(
    const TCollection_AsciiString&                   theFormat,
    const NCollection_List<TCollection_AsciiString>& theVendorPriority,
    const bool                                       theToDisable = false);

  Standard_EXPORT void ChangePriority(
    const NCollection_List<TCollection_AsciiString>& theVendorPriority,
    const bool                                       theToDisable = false);

  Standard_EXPORT virtual bool FindProvider(const TCollection_AsciiString& thePath,
                                            const bool                     theToImport,
                                            occ::handle<DE_Provider>&      theProvider) const;

  Standard_EXPORT virtual bool FindReadProvider(const TCollection_AsciiString& thePath,
                                                const bool                     theCheckContent,
                                                occ::handle<DE_Provider>&      theProvider) const;

  Standard_EXPORT virtual bool FindReadProvider(const TCollection_AsciiString& thePath,
                                                std::istream&                  theStream,
                                                occ::handle<DE_Provider>&      theProvider) const;

  Standard_EXPORT virtual bool FindWriteProvider(const TCollection_AsciiString& thePath,
                                                 occ::handle<DE_Provider>&      theProvider) const;

  Standard_EXPORT void UpdateLoad(const bool theToForceUpdate = false) const;

  bool KeepUpdates() const { return myKeepUpdates; }

  void SetKeepUpdates(const bool theToKeepUpdates) { myKeepUpdates = theToKeepUpdates; }

  Standard_EXPORT const NCollection_DataMap<
    TCollection_AsciiString,
    NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<DE_ConfigurationNode>>>&
    Nodes() const;

  Standard_EXPORT virtual occ::handle<DE_Wrapper> Copy() const;

protected:
  void sort(const occ::handle<DE_ConfigurationContext>& theResource);

public:
  DE_ConfigurationNode::DE_SectionGlobal GlobalParameters;

private:
  bool myKeepUpdates;

  NCollection_DataMap<
    TCollection_AsciiString,
    NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<DE_ConfigurationNode>>>
    myConfiguration;
};
