#pragma once

#include <Message_Messenger.hpp>
#include <TObj_Partition.hpp>
#include <TCollection_ExtendedString.hpp>

class TObj_TNameContainer;
class TCollection_HExtendedString;
class TDocStd_Document;
class TObj_CheckModel;
class TObj_Application;

class TObj_Model : public Standard_Transient
{
protected:
  enum DataTag
  {
    DataTag_FormatVersion = TObj_Partition::DataTag_Last,
    DataTag_Last
  };

protected:
  Standard_EXPORT TObj_Model();

  Standard_EXPORT ~TObj_Model() override;

  Standard_EXPORT virtual bool checkDocumentEmpty(const TCollection_ExtendedString& theFile);

public:
  void SetMessenger(const occ::handle<Message_Messenger>& theMsgr) { myMessenger = theMsgr; }

  occ::handle<Message_Messenger> Messenger() const { return myMessenger; }

public:
  Standard_EXPORT virtual bool Load(const TCollection_ExtendedString& theFile);

  Standard_EXPORT virtual bool Load(Standard_IStream& theIStream);

  Standard_EXPORT virtual bool SaveAs(const TCollection_ExtendedString& theFile);

  Standard_EXPORT virtual bool SaveAs(Standard_OStream& theOStream);

  Standard_EXPORT bool Save();

public:
  virtual Standard_EXPORT bool Close();

  Standard_EXPORT void CloseDocument(const occ::handle<TDocStd_Document>& theDoc);

  static Standard_EXPORT occ::handle<TObj_Model> GetDocumentModel(const TDF_Label& theLabel);

  virtual Standard_EXPORT occ::handle<TCollection_HExtendedString> GetFile() const;

public:
  virtual Standard_EXPORT occ::handle<TObj_ObjectIterator> GetObjects() const;

  virtual Standard_EXPORT occ::handle<TObj_ObjectIterator> GetChildren() const;

  virtual Standard_EXPORT occ::handle<TObj_Object> FindObject(
    const occ::handle<TCollection_HExtendedString>& theName,
    const occ::handle<TObj_TNameContainer>&         theDictionary) const;

  virtual Standard_EXPORT occ::handle<TObj_CheckModel> GetChecker() const;

public:
  virtual Standard_EXPORT occ::handle<TObj_Object> GetRoot() const;

  Standard_EXPORT occ::handle<TObj_Partition> GetMainPartition() const;

public:
  TDF_Label GetLabel() const { return myLabel; }

public:
  virtual Standard_EXPORT occ::handle<TCollection_HExtendedString> GetModelName() const;

  static Standard_EXPORT void SetNewName(const occ::handle<TObj_Object>& theObject);

  Standard_EXPORT bool IsRegisteredName(
    const occ::handle<TCollection_HExtendedString>& theName,
    const occ::handle<TObj_TNameContainer>&         theDictionary) const;

  Standard_EXPORT void RegisterName(const occ::handle<TCollection_HExtendedString>& theName,
                                    const TDF_Label&                                theLabel,
                                    const occ::handle<TObj_TNameContainer>& theDictionary) const;

  Standard_EXPORT void UnRegisterName(const occ::handle<TCollection_HExtendedString>& theName,
                                      const occ::handle<TObj_TNameContainer>& theDictionary) const;

public:
  Standard_EXPORT bool HasOpenCommand() const;

  Standard_EXPORT void OpenCommand() const;

  Standard_EXPORT void CommitCommand() const;

  Standard_EXPORT void AbortCommand() const;

  virtual Standard_EXPORT bool IsModified() const;

  Standard_EXPORT void SetModified(const bool theModified);

public:
  virtual Standard_EXPORT const occ::handle<TObj_Application> GetApplication();

public:
  virtual Standard_EXPORT TCollection_ExtendedString GetFormat() const;

  Standard_EXPORT int GetFormatVersion() const;

protected:
  Standard_EXPORT void SetFormatVersion(const int theVersion);

public:
  virtual Standard_EXPORT bool Update();

public:
  virtual Standard_EXPORT Standard_GUID GetGUID() const;

public:
  Standard_EXPORT occ::handle<TObj_TNameContainer> GetDictionary() const;

protected:
  Standard_EXPORT occ::handle<TObj_Partition> getPartition(const TDF_Label& theLabel,
                                                           const bool theHidden = false) const;

  Standard_EXPORT occ::handle<TObj_Partition> getPartition(
    const TDF_Label&                  theLabel,
    const int                         theIndex,
    const TCollection_ExtendedString& theName,
    const bool                        theHidden = false) const;

  Standard_EXPORT occ::handle<TObj_Partition> getPartition(
    const int                         theIndex,
    const TCollection_ExtendedString& theName,
    const bool                        theHidden = false) const;

public:
  Standard_EXPORT occ::handle<TDocStd_Document> GetDocument() const;

protected:
  Standard_EXPORT TDF_Label GetDataLabel() const;

public:
  void SetLabel(const TDF_Label& theLabel) { myLabel = theLabel; }

protected:
  virtual Standard_EXPORT bool initNewModel(const bool IsNew);

  virtual Standard_EXPORT void updateBackReferences(const occ::handle<TObj_Object>& theObject);

  virtual bool isToCheck() const { return true; }

public:
  virtual Standard_EXPORT bool Paste(occ::handle<TObj_Model>          theModel,
                                     occ::handle<TDF_RelocationTable> theRelocTable = nullptr);

  virtual Standard_EXPORT occ::handle<TObj_Model> NewEmpty() = 0;

  Standard_EXPORT void CopyReferences(const occ::handle<TObj_Model>&          theTarget,
                                      const occ::handle<TDF_RelocationTable>& theRelocTable);

private:
  TDF_Label                      myLabel;
  occ::handle<Message_Messenger> myMessenger;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_Model, Standard_Transient)
};
