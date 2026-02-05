#pragma once

#include <IGESData_IGESModel.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_FileRecognizer.hpp>

Standard_EXPORT int IGESFile_Read(char*                                  nomfic,
                                  const occ::handle<IGESData_IGESModel>& amodel,
                                  const occ::handle<IGESData_Protocol>&  protocol);

Standard_EXPORT int IGESFile_ReadFNES(char*                                  nomfic,
                                      const occ::handle<IGESData_IGESModel>& amodel,
                                      const occ::handle<IGESData_Protocol>&  protocol);

Standard_EXPORT int IGESFile_Read(char*                                       nomfic,
                                  const occ::handle<IGESData_IGESModel>&      amodel,
                                  const occ::handle<IGESData_Protocol>&       protocol,
                                  const occ::handle<IGESData_FileRecognizer>& reco,
                                  const bool                                  modefnes = false);
