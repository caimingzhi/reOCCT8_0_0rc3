#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Interface_CheckIterator.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Vector.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_CString.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TCollection_HAsciiString.hpp>

enum IFSelect_RemainMode
{
  IFSelect_RemainForget,
  IFSelect_RemainCompute,
  IFSelect_RemainDisplay,
  IFSelect_RemainUndo
};

#include <IFSelect_PrintCount.hpp>
class IFSelect_ShareOut;
class IFSelect_WorkLibrary;
class Interface_Protocol;
class Interface_InterfaceModel;
class Interface_HGraph;
class Interface_GTool;

class IFSelect_ModelCopier;
class IFSelect_Signature;
class TCollection_HAsciiString;
class Interface_Graph;
class IFSelect_IntParam;
class IFSelect_Selection;
class Interface_EntityIterator;
class IFSelect_SelectionIterator;
class IFSelect_SignCounter;
class IFSelect_Dispatch;
class IFSelect_GeneralModifier;
class IFSelect_Modifier;
class IFSelect_Transformer;
class IFSelect_PacketList;
class IFSelect_SignatureList;

class IFSelect_WorkSession : public Standard_Transient
{

public:
  Standard_EXPORT IFSelect_WorkSession();

  Standard_EXPORT void SetErrorHandle(const bool toHandle);

  bool ErrorHandle() const { return theerrhand; }

  const occ::handle<IFSelect_ShareOut>& ShareOut() const { return theshareout; }

  Standard_EXPORT void SetShareOut(const occ::handle<IFSelect_ShareOut>& shareout);

  void SetModeStat(const bool theMode) { themodelstat = theMode; }

  bool GetModeStat() const { return themodelstat; }

  void SetLibrary(const occ::handle<IFSelect_WorkLibrary>& theLib) { thelibrary = theLib; }

  const occ::handle<IFSelect_WorkLibrary>& WorkLibrary() const { return thelibrary; }

  Standard_EXPORT void SetProtocol(const occ::handle<Interface_Protocol>& protocol);

  const occ::handle<Interface_Protocol>& Protocol() const { return theprotocol; }

  Standard_EXPORT void SetSignType(const occ::handle<IFSelect_Signature>& signtype);

  Standard_EXPORT occ::handle<IFSelect_Signature> SignType() const;

  bool HasModel() const { return (!myModel.IsNull()); }

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& model,
                                const bool                                   clearpointed = true);

  const occ::handle<Interface_InterfaceModel>& Model() const { return myModel; }

  void SetLoadedFile(const char* theFileName) { theloaded = theFileName; }

  const char* LoadedFile() const { return theloaded.ToCString(); }

  Standard_EXPORT IFSelect_ReturnStatus ReadFile(const char* filename);

  Standard_EXPORT IFSelect_ReturnStatus ReadStream(const char* theName, std::istream& theIStream);

  Standard_EXPORT int NbStartingEntities() const;

  Standard_EXPORT occ::handle<Standard_Transient> StartingEntity(const int num) const;

  Standard_EXPORT int StartingNumber(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT int NumberFromLabel(const char* val, const int afternum = 0) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> EntityLabel(
    const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> EntityName(
    const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT int CategoryNumber(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT const char* CategoryName(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT const char* ValidityName(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT virtual void ClearData(const int mode);

  Standard_EXPORT bool ComputeGraph(const bool enforce = false);

  Standard_EXPORT occ::handle<Interface_HGraph> HGraph();

  Standard_EXPORT const Interface_Graph& Graph();

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Shareds(
    const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Sharings(
    const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT bool IsLoaded() const;

  Standard_EXPORT bool ComputeCheck(const bool enforce = false);

  Standard_EXPORT Interface_CheckIterator ModelCheckList(const bool complete = true);

  Standard_EXPORT Interface_CheckIterator CheckOne(const occ::handle<Standard_Transient>& ent,
                                                   const bool complete = true);

  Interface_CheckIterator LastRunCheckList() const { return thecheckrun; }

  Standard_EXPORT int MaxIdent() const;

  Standard_EXPORT occ::handle<Standard_Transient> Item(const int id) const;

  Standard_EXPORT int ItemIdent(const occ::handle<Standard_Transient>& item) const;

  Standard_EXPORT occ::handle<Standard_Transient> NamedItem(const char* name) const;

  Standard_EXPORT occ::handle<Standard_Transient> NamedItem(
    const occ::handle<TCollection_HAsciiString>& name) const;

  Standard_EXPORT int NameIdent(const char* name) const;

  Standard_EXPORT bool HasName(const occ::handle<Standard_Transient>& item) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name(
    const occ::handle<Standard_Transient>& item) const;

  Standard_EXPORT int AddItem(const occ::handle<Standard_Transient>& item,
                              const bool                             active = true);

  Standard_EXPORT int AddNamedItem(const char*                            name,
                                   const occ::handle<Standard_Transient>& item,
                                   const bool                             active = true);

  Standard_EXPORT bool SetActive(const occ::handle<Standard_Transient>& item, const bool mode);

  Standard_EXPORT bool RemoveNamedItem(const char* name);

  Standard_EXPORT bool RemoveName(const char* name);

  Standard_EXPORT bool RemoveItem(const occ::handle<Standard_Transient>& item);

  Standard_EXPORT void ClearItems();

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ItemLabel(const int id) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<int>> ItemIdents(
    const occ::handle<Standard_Type>& type) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  ItemNames(const occ::handle<Standard_Type>& type) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  ItemNamesForLabel(const char* label) const;

  Standard_EXPORT int NextIdentForLabel(const char* label, const int id, const int mode = 0) const;

  Standard_EXPORT occ::handle<Standard_Transient> NewParamFromStatic(const char* statname,
                                                                     const char* name = "");

  Standard_EXPORT occ::handle<IFSelect_IntParam> IntParam(const int id) const;

  Standard_EXPORT int IntValue(const occ::handle<IFSelect_IntParam>& it) const;

  Standard_EXPORT occ::handle<IFSelect_IntParam> NewIntParam(const char* name = "");

  Standard_EXPORT bool SetIntValue(const occ::handle<IFSelect_IntParam>& it, const int val);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> TextParam(const int id) const;

  Standard_EXPORT TCollection_AsciiString
    TextValue(const occ::handle<TCollection_HAsciiString>& par) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> NewTextParam(const char* name = "");

  Standard_EXPORT bool SetTextValue(const occ::handle<TCollection_HAsciiString>& par,
                                    const char*                                  val);

  Standard_EXPORT occ::handle<IFSelect_Signature> Signature(const int id) const;

  Standard_EXPORT const char* SignValue(const occ::handle<IFSelect_Signature>& sign,
                                        const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT occ::handle<IFSelect_Selection> Selection(const int id) const;

  Standard_EXPORT Interface_EntityIterator
    EvalSelection(const occ::handle<IFSelect_Selection>& sel) const;

  Standard_EXPORT IFSelect_SelectionIterator
    Sources(const occ::handle<IFSelect_Selection>& sel) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
                  SelectionResult(const occ::handle<IFSelect_Selection>& sel) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
                  SelectionResultFromList(
                    const occ::handle<IFSelect_Selection>&                                     sel,
                    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list) const;

  Standard_EXPORT bool SetItemSelection(const occ::handle<Standard_Transient>& item,
                                        const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT bool ResetItemSelection(const occ::handle<Standard_Transient>& item);

  Standard_EXPORT occ::handle<IFSelect_Selection> ItemSelection(
    const occ::handle<Standard_Transient>& item) const;

  Standard_EXPORT occ::handle<IFSelect_SignCounter> SignCounter(const int id) const;

  Standard_EXPORT bool ComputeCounter(const occ::handle<IFSelect_SignCounter>& counter,
                                      const bool                               forced = false);

  Standard_EXPORT bool ComputeCounterFromList(
    const occ::handle<IFSelect_SignCounter>&                                   counter,
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const bool                                                                 clear = true);

  Standard_EXPORT occ::handle<NCollection_HSequence<int>> AppliedDispatches() const;

  Standard_EXPORT void ClearShareOut(const bool onlydisp);

  Standard_EXPORT occ::handle<IFSelect_Dispatch> Dispatch(const int id) const;

  Standard_EXPORT int DispatchRank(const occ::handle<IFSelect_Dispatch>& disp) const;

  const occ::handle<IFSelect_ModelCopier>& ModelCopier() const { return thecopier; }

  Standard_EXPORT void SetModelCopier(const occ::handle<IFSelect_ModelCopier>& copier);

  Standard_EXPORT int NbFinalModifiers(const bool formodel) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<int>> FinalModifierIdents(
    const bool formodel) const;

  Standard_EXPORT occ::handle<IFSelect_GeneralModifier> GeneralModifier(const int id) const;

  Standard_EXPORT occ::handle<IFSelect_Modifier> ModelModifier(const int id) const;

  Standard_EXPORT int ModifierRank(const occ::handle<IFSelect_GeneralModifier>& item) const;

  Standard_EXPORT bool ChangeModifierRank(const bool formodel, const int before, const int after);

  Standard_EXPORT void ClearFinalModifiers();

  Standard_EXPORT bool SetAppliedModifier(const occ::handle<IFSelect_GeneralModifier>& modif,
                                          const occ::handle<Standard_Transient>&       item);

  Standard_EXPORT bool ResetAppliedModifier(const occ::handle<IFSelect_GeneralModifier>& modif);

  Standard_EXPORT occ::handle<Standard_Transient> UsesAppliedModifier(
    const occ::handle<IFSelect_GeneralModifier>& modif) const;

  Standard_EXPORT occ::handle<IFSelect_Transformer> Transformer(const int id) const;

  Standard_EXPORT int RunTransformer(const occ::handle<IFSelect_Transformer>& transf);

  Standard_EXPORT int RunModifier(const occ::handle<IFSelect_Modifier>& modif, const bool copy);

  Standard_EXPORT int RunModifierSelected(const occ::handle<IFSelect_Modifier>&  modif,
                                          const occ::handle<IFSelect_Selection>& sel,
                                          const bool                             copy);

  Standard_EXPORT occ::handle<IFSelect_Transformer> NewTransformStandard(const bool  copy,
                                                                         const char* name = "");

  Standard_EXPORT bool SetModelContent(const occ::handle<IFSelect_Selection>& sel, const bool keep);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FilePrefix() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> DefaultFileRoot() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FileExtension() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FileRoot(
    const occ::handle<IFSelect_Dispatch>& disp) const;

  Standard_EXPORT void SetFilePrefix(const char* name);

  Standard_EXPORT bool SetDefaultFileRoot(const char* name);

  Standard_EXPORT void SetFileExtension(const char* name);

  Standard_EXPORT bool SetFileRoot(const occ::handle<IFSelect_Dispatch>& disp, const char* name);

  Standard_EXPORT const char* GiveFileRoot(const char* file) const;

  Standard_EXPORT const char* GiveFileComplete(const char* file) const;

  Standard_EXPORT void ClearFile();

  Standard_EXPORT void EvaluateFile();

  Standard_EXPORT int NbFiles() const;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> FileModel(const int num) const;

  Standard_EXPORT TCollection_AsciiString FileName(const int num) const;

  Standard_EXPORT void BeginSentFiles(const bool record);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  SentFiles() const;

  Standard_EXPORT bool SendSplit();

  Standard_EXPORT occ::handle<IFSelect_PacketList> EvalSplit() const;

  Standard_EXPORT Interface_EntityIterator SentList(const int count = -1) const;

  Standard_EXPORT int MaxSendingCount() const;

  Standard_EXPORT bool SetRemaining(const IFSelect_RemainMode mode);

  Standard_EXPORT IFSelect_ReturnStatus SendAll(const char* filename,
                                                const bool  computegraph = false);

  Standard_EXPORT IFSelect_ReturnStatus SendSelected(const char* filename,
                                                     const occ::handle<IFSelect_Selection>& sel,
                                                     const bool computegraph = false);

  Standard_EXPORT IFSelect_ReturnStatus WriteFile(const char* filename);

  Standard_EXPORT IFSelect_ReturnStatus WriteFile(const char*                            filename,
                                                  const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT int NbSources(const occ::handle<IFSelect_Selection>& sel) const;

  Standard_EXPORT occ::handle<IFSelect_Selection> Source(const occ::handle<IFSelect_Selection>& sel,
                                                         const int num = 1) const;

  Standard_EXPORT bool IsReversedSelectExtract(const occ::handle<IFSelect_Selection>& sel) const;

  Standard_EXPORT bool ToggleSelectExtract(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT bool SetInputSelection(const occ::handle<IFSelect_Selection>& sel,
                                         const occ::handle<IFSelect_Selection>& input);

  Standard_EXPORT bool SetControl(const occ::handle<IFSelect_Selection>& sel,
                                  const occ::handle<IFSelect_Selection>& sc,
                                  const bool                             formain = true);

  Standard_EXPORT int CombineAdd(const occ::handle<IFSelect_Selection>& selcomb,
                                 const occ::handle<IFSelect_Selection>& seladd,
                                 const int                              atnum = 0);

  Standard_EXPORT bool CombineRemove(const occ::handle<IFSelect_Selection>& selcomb,
                                     const occ::handle<IFSelect_Selection>& selrem);

  Standard_EXPORT occ::handle<IFSelect_Selection> NewSelectPointed(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const char*                                                                name);

  Standard_EXPORT bool SetSelectPointed(
    const occ::handle<IFSelect_Selection>&                                     sel,
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const int                                                                  mode) const;

  Standard_EXPORT occ::handle<IFSelect_Selection> GiveSelection(const char* selname) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> GiveList(
    const occ::handle<Standard_Transient>& obj) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> GiveList(
    const char* first,
    const char* second = "") const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
    GiveListFromList(const char* selname, const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
    GiveListCombined(const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& l1,
                     const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& l2,
                     const int mode) const;

  Standard_EXPORT void QueryCheckList(const Interface_CheckIterator& chl);

  Standard_EXPORT int QueryCheckStatus(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT int QueryParent(const occ::handle<Standard_Transient>& entdad,
                                  const occ::handle<Standard_Transient>& entson) const;

  Standard_EXPORT void SetParams(const NCollection_Vector<occ::handle<Standard_Transient>>& params,
                                 const NCollection_Vector<int>& uselist);

  Standard_EXPORT void TraceStatics(const int use, const int mode = 0) const;

  Standard_EXPORT void DumpShare() const;

  Standard_EXPORT void ListItems(const char* label = "") const;

  Standard_EXPORT void ListFinalModifiers(const bool formodel) const;

  Standard_EXPORT void DumpSelection(const occ::handle<IFSelect_Selection>& sel) const;

  Standard_EXPORT void DumpModel(const int level, Standard_OStream& S);

  Standard_EXPORT void TraceDumpModel(const int mode);

  Standard_EXPORT void DumpEntity(const occ::handle<Standard_Transient>& ent,
                                  const int                              level,
                                  Standard_OStream&                      S) const;

  Standard_EXPORT void PrintEntityStatus(const occ::handle<Standard_Transient>& ent,
                                         Standard_OStream&                      S);

  Standard_EXPORT void TraceDumpEntity(const occ::handle<Standard_Transient>& ent,
                                       const int                              level) const;

  Standard_EXPORT void PrintCheckList(Standard_OStream&              S,
                                      const Interface_CheckIterator& checklist,
                                      const bool                     failsonly,
                                      const IFSelect_PrintCount      mode) const;

  Standard_EXPORT void PrintSignatureList(Standard_OStream&                          S,
                                          const occ::handle<IFSelect_SignatureList>& signlist,
                                          const IFSelect_PrintCount                  mode) const;

  Standard_EXPORT void EvaluateSelection(const occ::handle<IFSelect_Selection>& sel) const;

  Standard_EXPORT void EvaluateDispatch(const occ::handle<IFSelect_Dispatch>& disp,
                                        const int                             mode = 0) const;

  Standard_EXPORT void EvaluateComplete(const int mode = 0) const;

  Standard_EXPORT void ListEntities(const Interface_EntityIterator& iter,
                                    const int                       mode,
                                    Standard_OStream&               S) const;

  DEFINE_STANDARD_RTTIEXT(IFSelect_WorkSession, Standard_Transient)

protected:
  occ::handle<Interface_HGraph> thegraph;
  Interface_CheckIterator       thecheckrun;
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>
                                                                                theitems;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> thenames;

private:
  bool                                  theerrhand;
  occ::handle<IFSelect_ShareOut>        theshareout;
  occ::handle<IFSelect_WorkLibrary>     thelibrary;
  occ::handle<Interface_Protocol>       theprotocol;
  occ::handle<Interface_InterfaceModel> myModel;
  TCollection_AsciiString               theloaded;
  occ::handle<Interface_GTool>          thegtool;
  bool                                  thecheckdone;
  Interface_CheckIterator               thechecklist;
  TCollection_AsciiString               thecheckana;
  occ::handle<IFSelect_ModelCopier>     thecopier;
  occ::handle<Interface_InterfaceModel> theoldel;
  bool                                  themodelstat;
};
