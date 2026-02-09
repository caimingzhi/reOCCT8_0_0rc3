#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>
#include <Standard_Integer.hpp>
#include <IGESData_IGESType.hpp>
#include <IGESData_ReadStage.hpp>
#include <Interface_FileReaderTool.hpp>
class Interface_ParamList;
class IGESData_FileRecognizer;
class Interface_Check;
class IGESData_IGESReaderData;
class IGESData_Protocol;
class Standard_Transient;
class Interface_InterfaceModel;
class IGESData_IGESEntity;
class IGESData_DirPart;
class IGESData_ParamReader;

class IGESData_IGESReaderTool : public Interface_FileReaderTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_IGESReaderTool(const occ::handle<IGESData_IGESReaderData>& reader,
                                          const occ::handle<IGESData_Protocol>&       protocol);

  Standard_EXPORT void Prepare(const occ::handle<IGESData_FileRecognizer>& reco);

  Standard_EXPORT bool Recognize(const int                        num,
                                 occ::handle<Interface_Check>&    ach,
                                 occ::handle<Standard_Transient>& ent) override;

  Standard_EXPORT void BeginRead(const occ::handle<Interface_InterfaceModel>& amodel) override;

  Standard_EXPORT bool AnalyseRecord(const int                              num,
                                     const occ::handle<Standard_Transient>& anent,
                                     occ::handle<Interface_Check>&          acheck) override;

  Standard_EXPORT void EndRead(const occ::handle<Interface_InterfaceModel>& amodel) override;

  Standard_EXPORT void ReadDir(const occ::handle<IGESData_IGESEntity>&     ent,
                               const occ::handle<IGESData_IGESReaderData>& IR,
                               const IGESData_DirPart&                     DP,
                               occ::handle<Interface_Check>&               ach) const;

  Standard_EXPORT void ReadOwnParams(const occ::handle<IGESData_IGESEntity>&     ent,
                                     const occ::handle<IGESData_IGESReaderData>& IR,
                                     IGESData_ParamReader&                       PR) const;

  Standard_EXPORT void ReadProps(const occ::handle<IGESData_IGESEntity>&     ent,
                                 const occ::handle<IGESData_IGESReaderData>& IR,
                                 IGESData_ParamReader&                       PR) const;

  Standard_EXPORT void ReadAssocs(const occ::handle<IGESData_IGESEntity>&     ent,
                                  const occ::handle<IGESData_IGESReaderData>& IR,
                                  IGESData_ParamReader&                       PR) const;

private:
  occ::handle<Interface_ParamList>     thelist;
  occ::handle<IGESData_FileRecognizer> thereco;
  Interface_GeneralLib                 theglib;
  Interface_ReaderLib                  therlib;
  int                                  thecnum;
  IGESData_IGESType                    thectyp;
  IGESData_ReadStage                   thestep;
  occ::handle<Interface_Check>         thechk;
  int                                  thegradweight;
  double                               themaxweight;
  double                               thedefweight;
};
