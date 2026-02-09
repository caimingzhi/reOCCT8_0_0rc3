#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Interface_Protocol;
class Interface_FileReaderData;
class Interface_InterfaceModel;
class Message_Messenger;
class Interface_Check;
class Standard_Transient;
class Interface_GeneralLib;
class Interface_ReaderLib;

class Interface_FileReaderTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT void SetData(const occ::handle<Interface_FileReaderData>& reader,
                               const occ::handle<Interface_Protocol>&       protocol);

  Standard_EXPORT occ::handle<Interface_Protocol> Protocol() const;

  Standard_EXPORT occ::handle<Interface_FileReaderData> Data() const;

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& amodel);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT void SetMessenger(const occ::handle<Message_Messenger>& messenger);

  Standard_EXPORT occ::handle<Message_Messenger> Messenger() const;

  Standard_EXPORT void SetTraceLevel(const int tracelev);

  Standard_EXPORT int TraceLevel() const;

  Standard_EXPORT void SetErrorHandle(const bool err);

  Standard_EXPORT bool ErrorHandle() const;

  Standard_EXPORT void SetEntities();

  Standard_EXPORT virtual bool Recognize(const int                        num,
                                         occ::handle<Interface_Check>&    ach,
                                         occ::handle<Standard_Transient>& ent) = 0;

  Standard_EXPORT bool RecognizeByLib(const int                        num,
                                      Interface_GeneralLib&            glib,
                                      Interface_ReaderLib&             rlib,
                                      occ::handle<Interface_Check>&    ach,
                                      occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT occ::handle<Standard_Transient> UnknownEntity() const;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewModel() const;

  Standard_EXPORT void LoadModel(const occ::handle<Interface_InterfaceModel>& amodel);

  Standard_EXPORT occ::handle<Standard_Transient> LoadedEntity(const int num);

  Standard_EXPORT virtual void BeginRead(const occ::handle<Interface_InterfaceModel>& amodel) = 0;

  Standard_EXPORT virtual bool AnalyseRecord(const int                              num,
                                             const occ::handle<Standard_Transient>& anent,
                                             occ::handle<Interface_Check>&          acheck) = 0;

  Standard_EXPORT virtual ~Interface_FileReaderTool();

  Standard_EXPORT virtual void EndRead(const occ::handle<Interface_InterfaceModel>& amodel);

  Standard_EXPORT void Clear();

protected:
  Standard_EXPORT Interface_FileReaderTool();

private:
  occ::handle<Interface_Protocol>                                   theproto;
  occ::handle<Interface_FileReaderData>                             thereader;
  occ::handle<Interface_InterfaceModel>                             themodel;
  occ::handle<Message_Messenger>                                    themessenger;
  int                                                               thetrace;
  bool                                                              theerrhand;
  int                                                               thenbrep0;
  int                                                               thenbreps;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> thereports;
};
