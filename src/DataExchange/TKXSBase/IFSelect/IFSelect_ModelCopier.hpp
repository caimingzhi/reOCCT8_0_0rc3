#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_InterfaceModel.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_AsciiString.hpp>
#include <IFSelect_AppliedModifiers.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>
class IFSelect_ShareOut;
class TCollection_AsciiString;
class Interface_InterfaceModel;
class IFSelect_AppliedModifiers;
class Interface_CheckIterator;
class IFSelect_ShareOutResult;
class IFSelect_WorkLibrary;
class Interface_Protocol;
class Interface_CopyTool;
class Interface_Graph;
class Interface_EntityIterator;

class IFSelect_ModelCopier : public Standard_Transient
{

public:
  Standard_EXPORT IFSelect_ModelCopier();

  Standard_EXPORT void SetShareOut(const occ::handle<IFSelect_ShareOut>& sho);

  Standard_EXPORT void ClearResult();

  Standard_EXPORT bool AddFile(const TCollection_AsciiString&               filename,
                               const occ::handle<Interface_InterfaceModel>& content);

  Standard_EXPORT bool NameFile(const int num, const TCollection_AsciiString& filename);

  Standard_EXPORT bool ClearFile(const int num);

  Standard_EXPORT bool SetAppliedModifiers(const int                                     num,
                                           const occ::handle<IFSelect_AppliedModifiers>& applied);

  Standard_EXPORT bool ClearAppliedModifiers(const int num);

  Standard_EXPORT Interface_CheckIterator Copy(IFSelect_ShareOutResult&                 eval,
                                               const occ::handle<IFSelect_WorkLibrary>& WL,
                                               const occ::handle<Interface_Protocol>&   protocol);

  Standard_EXPORT Interface_CheckIterator
    SendCopied(const occ::handle<IFSelect_WorkLibrary>& WL,
               const occ::handle<Interface_Protocol>&   protocol);

  Standard_EXPORT Interface_CheckIterator Send(IFSelect_ShareOutResult&                 eval,
                                               const occ::handle<IFSelect_WorkLibrary>& WL,
                                               const occ::handle<Interface_Protocol>&   protocol);

  Standard_EXPORT Interface_CheckIterator SendAll(const char*                              filename,
                                                  const Interface_Graph&                   G,
                                                  const occ::handle<IFSelect_WorkLibrary>& WL,
                                                  const occ::handle<Interface_Protocol>& protocol);

  Standard_EXPORT Interface_CheckIterator
    SendSelected(const char*                              filename,
                 const Interface_Graph&                   G,
                 const occ::handle<IFSelect_WorkLibrary>& WL,
                 const occ::handle<Interface_Protocol>&   protocol,
                 const Interface_EntityIterator&          iter);

  Standard_EXPORT void CopiedRemaining(const Interface_Graph&                   G,
                                       const occ::handle<IFSelect_WorkLibrary>& WL,
                                       Interface_CopyTool&                      TC,
                                       occ::handle<Interface_InterfaceModel>&   newmod);

  Standard_EXPORT bool SetRemaining(Interface_Graph& CG) const;

  Standard_EXPORT int NbFiles() const;

  Standard_EXPORT TCollection_AsciiString FileName(const int num) const;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> FileModel(const int num) const;

  Standard_EXPORT occ::handle<IFSelect_AppliedModifiers> AppliedModifiers(const int num) const;

  Standard_EXPORT void BeginSentFiles(const occ::handle<IFSelect_ShareOut>& sho, const bool record);

  Standard_EXPORT void AddSentFile(const char* filename);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  SentFiles() const;

  DEFINE_STANDARD_RTTIEXT(IFSelect_ModelCopier, Standard_Transient)

protected:
  Standard_EXPORT Interface_CheckIterator Copying(IFSelect_ShareOutResult&                 eval,
                                                  const occ::handle<IFSelect_WorkLibrary>& WL,
                                                  const occ::handle<Interface_Protocol>&   protocol,
                                                  Interface_CopyTool&                      TC);

  Standard_EXPORT Interface_CheckIterator Sending(IFSelect_ShareOutResult&                 eval,
                                                  const occ::handle<IFSelect_WorkLibrary>& WL,
                                                  const occ::handle<Interface_Protocol>&   protocol,
                                                  Interface_CopyTool&                      TC);

  Standard_EXPORT void CopiedModel(const Interface_Graph&                   G,
                                   const occ::handle<IFSelect_WorkLibrary>& WL,
                                   const occ::handle<Interface_Protocol>&   protocol,
                                   const Interface_EntityIterator&          topcopy,
                                   const TCollection_AsciiString&           filename,
                                   const int                                dispnum,
                                   const int                                numod,
                                   Interface_CopyTool&                      TC,
                                   occ::handle<Interface_InterfaceModel>&   newmod,
                                   occ::handle<IFSelect_AppliedModifiers>&  applied,
                                   Interface_CheckIterator&                 checks) const;

private:
  NCollection_Sequence<occ::handle<Interface_InterfaceModel>>               thefilemodels;
  NCollection_Sequence<TCollection_AsciiString>                             thefilenames;
  NCollection_Sequence<occ::handle<IFSelect_AppliedModifiers>>              theapplieds;
  occ::handle<IFSelect_ShareOut>                                            theshareout;
  occ::handle<NCollection_HArray1<int>>                                     theremain;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thesentfiles;
};
