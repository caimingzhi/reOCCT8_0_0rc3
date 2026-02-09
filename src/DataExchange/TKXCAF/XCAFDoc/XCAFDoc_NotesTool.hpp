#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_GenericEmpty.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>

class OSD_File;
class Standard_GUID;
class TCollection_AsciiString;
class TCollection_ExtendedString;
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class XCAFDoc_Note;
class XCAFDoc_AssemblyItemId;
class XCAFDoc_AssemblyItemRef;

class XCAFDoc_NotesTool : public TDataStd_GenericEmpty
{
public:
  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_NotesTool, TDataStd_GenericEmpty)

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_NotesTool> Set(const TDF_Label& theLabel);

  Standard_EXPORT XCAFDoc_NotesTool();

  Standard_EXPORT TDF_Label GetNotesLabel() const;

  Standard_EXPORT TDF_Label GetAnnotatedItemsLabel() const;

  Standard_EXPORT int NbNotes() const;

  Standard_EXPORT int NbAnnotatedItems() const;

  Standard_EXPORT void GetNotes(NCollection_Sequence<TDF_Label>& theNoteLabels) const;

  Standard_EXPORT void GetAnnotatedItems(NCollection_Sequence<TDF_Label>& theLabels) const;

  Standard_EXPORT bool IsAnnotatedItem(const XCAFDoc_AssemblyItemId& theItemId) const;

  Standard_EXPORT bool IsAnnotatedItem(const TDF_Label& theItemLabel) const;

  Standard_EXPORT TDF_Label FindAnnotatedItem(const XCAFDoc_AssemblyItemId& theItemId) const;

  Standard_EXPORT TDF_Label FindAnnotatedItem(const TDF_Label& theItemLabel) const;

  Standard_EXPORT TDF_Label FindAnnotatedItemAttr(const XCAFDoc_AssemblyItemId& theItemId,
                                                  const Standard_GUID&          theGUID) const;

  Standard_EXPORT TDF_Label FindAnnotatedItemAttr(const TDF_Label&     theItemLabel,
                                                  const Standard_GUID& theGUID) const;

  Standard_EXPORT TDF_Label FindAnnotatedItemSubshape(const XCAFDoc_AssemblyItemId& theItemId,
                                                      int theSubshapeIndex) const;

  Standard_EXPORT TDF_Label FindAnnotatedItemSubshape(const TDF_Label& theItemLabel,
                                                      int              theSubshapeIndex) const;

  Standard_EXPORT occ::handle<XCAFDoc_Note> CreateComment(
    const TCollection_ExtendedString& theUserName,
    const TCollection_ExtendedString& theTimeStamp,
    const TCollection_ExtendedString& theComment);

  Standard_EXPORT occ::handle<XCAFDoc_Note> CreateBalloon(
    const TCollection_ExtendedString& theUserName,
    const TCollection_ExtendedString& theTimeStamp,
    const TCollection_ExtendedString& theComment);

  Standard_EXPORT occ::handle<XCAFDoc_Note> CreateBinData(
    const TCollection_ExtendedString& theUserName,
    const TCollection_ExtendedString& theTimeStamp,
    const TCollection_ExtendedString& theTitle,
    const TCollection_AsciiString&    theMIMEtype,
    OSD_File&                         theFile);

  Standard_EXPORT occ::handle<XCAFDoc_Note> CreateBinData(
    const TCollection_ExtendedString&                theUserName,
    const TCollection_ExtendedString&                theTimeStamp,
    const TCollection_ExtendedString&                theTitle,
    const TCollection_AsciiString&                   theMIMEtype,
    const occ::handle<NCollection_HArray1<uint8_t>>& theData);

  Standard_EXPORT int GetNotes(const XCAFDoc_AssemblyItemId&    theItemId,
                               NCollection_Sequence<TDF_Label>& theNoteLabels) const;

  Standard_EXPORT int GetNotes(const TDF_Label&                 theItemLabel,
                               NCollection_Sequence<TDF_Label>& theNoteLabels) const;

  Standard_EXPORT int GetAttrNotes(const XCAFDoc_AssemblyItemId&    theItemId,
                                   const Standard_GUID&             theGUID,
                                   NCollection_Sequence<TDF_Label>& theNoteLabels) const;

  Standard_EXPORT int GetAttrNotes(const TDF_Label&                 theItemLabel,
                                   const Standard_GUID&             theGUID,
                                   NCollection_Sequence<TDF_Label>& theNoteLabels) const;

  Standard_EXPORT int GetSubshapeNotes(const XCAFDoc_AssemblyItemId&    theItemId,
                                       int                              theSubshapeIndex,
                                       NCollection_Sequence<TDF_Label>& theNoteLabels) const;

  Standard_EXPORT occ::handle<XCAFDoc_AssemblyItemRef> AddNote(
    const TDF_Label&              theNoteLabel,
    const XCAFDoc_AssemblyItemId& theItemId);

  Standard_EXPORT occ::handle<XCAFDoc_AssemblyItemRef> AddNote(const TDF_Label& theNoteLabel,
                                                               const TDF_Label& theItemLabel);

  Standard_EXPORT occ::handle<XCAFDoc_AssemblyItemRef> AddNoteToAttr(
    const TDF_Label&              theNoteLabel,
    const XCAFDoc_AssemblyItemId& theItemId,
    const Standard_GUID&          theGUID);

  Standard_EXPORT occ::handle<XCAFDoc_AssemblyItemRef> AddNoteToAttr(const TDF_Label& theNoteLabel,
                                                                     const TDF_Label& theItemLabel,
                                                                     const Standard_GUID& theGUID);

  Standard_EXPORT occ::handle<XCAFDoc_AssemblyItemRef> AddNoteToSubshape(
    const TDF_Label&              theNoteLabel,
    const XCAFDoc_AssemblyItemId& theItemId,
    int                           theSubshapeIndex);

  Standard_EXPORT occ::handle<XCAFDoc_AssemblyItemRef> AddNoteToSubshape(
    const TDF_Label& theNoteLabel,
    const TDF_Label& theItemLabel,
    int              theSubshapeIndex);

  Standard_EXPORT bool RemoveNote(const TDF_Label&              theNoteLabel,
                                  const XCAFDoc_AssemblyItemId& theItemId,
                                  bool                          theDelIfOrphan = false);

  Standard_EXPORT bool RemoveNote(const TDF_Label& theNoteLabel,
                                  const TDF_Label& theItemLabel,
                                  bool             theDelIfOrphan = false);

  Standard_EXPORT bool RemoveSubshapeNote(const TDF_Label&              theNoteLabel,
                                          const XCAFDoc_AssemblyItemId& theItemId,
                                          int                           theSubshapeIndex,
                                          bool                          theDelIfOrphan = false);

  Standard_EXPORT bool RemoveSubshapeNote(const TDF_Label& theNoteLabel,
                                          const TDF_Label& theItemLabel,
                                          int              theSubshapeIndex,
                                          bool             theDelIfOrphan = false);

  Standard_EXPORT bool RemoveAttrNote(const TDF_Label&              theNoteLabel,
                                      const XCAFDoc_AssemblyItemId& theItemId,
                                      const Standard_GUID&          theGUID,
                                      bool                          theDelIfOrphan = false);

  Standard_EXPORT bool RemoveAttrNote(const TDF_Label&     theNoteLabel,
                                      const TDF_Label&     theItemLabel,
                                      const Standard_GUID& theGUID,
                                      bool                 theDelIfOrphan = false);

  Standard_EXPORT bool RemoveAllNotes(const XCAFDoc_AssemblyItemId& theItemId,
                                      bool                          theDelIfOrphan = false);

  Standard_EXPORT bool RemoveAllNotes(const TDF_Label& theItemLabel, bool theDelIfOrphan = false);

  Standard_EXPORT bool RemoveAllSubshapeNotes(const XCAFDoc_AssemblyItemId& theItemId,
                                              int                           theSubshapeIndex,
                                              bool                          theDelIfOrphan = false);

  Standard_EXPORT bool RemoveAllAttrNotes(const XCAFDoc_AssemblyItemId& theItemId,
                                          const Standard_GUID&          theGUID,
                                          bool                          theDelIfOrphan = false);

  Standard_EXPORT bool RemoveAllAttrNotes(const TDF_Label&     theItemLabel,
                                          const Standard_GUID& theGUID,
                                          bool                 theDelIfOrphan = false);

  Standard_EXPORT bool DeleteNote(const TDF_Label& theNoteLabel);

  Standard_EXPORT int DeleteNotes(NCollection_Sequence<TDF_Label>& theNoteLabels);

  Standard_EXPORT int DeleteAllNotes();

  Standard_EXPORT int NbOrphanNotes() const;

  Standard_EXPORT void GetOrphanNotes(NCollection_Sequence<TDF_Label>& theNoteLabels) const;

  Standard_EXPORT int DeleteOrphanNotes();

public:
  Standard_EXPORT const Standard_GUID& ID() const override;
  Standard_EXPORT Standard_OStream&    Dump(Standard_OStream& theOS) const override;
};
