// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <HeaderSection_FileDescription.hpp>
#include <HeaderSection_FileName.hpp>
#include <HeaderSection_FileSchema.hpp>
#include <HeaderSection_Protocol.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ReaderLib.hpp>
#include <RWHeaderSection_ReadWriteModule.hpp>
#include <RWHeaderSection_RWFileDescription.hpp>
#include <RWHeaderSection_RWFileName.hpp>
#include <RWHeaderSection_RWFileSchema.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepData_UndefinedEntity.hpp>
#include <StepData_WriterLib.hpp>
#include <TCollection_AsciiString.hpp>

#include <string_view>

IMPLEMENT_STANDARD_RTTIEXT(RWHeaderSection_ReadWriteModule, StepData_ReadWriteModule)

// -- General Declarations (Recognize, StepType) ---
static constexpr std::string_view PasReco; // neutralise StartEntity de SW
static constexpr std::string_view Reco_FileName("FILE_NAME");
static constexpr std::string_view Reco_FileDescription("FILE_DESCRIPTION");
static constexpr std::string_view Reco_FileSchema("FILE_SCHEMA");

// -- Definition of the libraries --

RWHeaderSection_ReadWriteModule::RWHeaderSection_ReadWriteModule()
{
  occ::handle<HeaderSection_Protocol> protocol = new HeaderSection_Protocol;
  StepData_WriterLib::SetGlobal(this, protocol);
  Interface_ReaderLib::SetGlobal(this, protocol);
}

// --- Case Recognition ---

int RWHeaderSection_ReadWriteModule::CaseStep(const TCollection_AsciiString& key) const
{
  if (key.IsEqual(Reco_FileName))
    return 1;
  if (key.IsEqual(Reco_FileDescription))
    return 2;
  if (key.IsEqual(Reco_FileSchema))
    return 3;
  return 0;
}

// --- External Mapping Case Recognition ---
#ifdef OCCT_DEBUG
int RWHeaderSection_ReadWriteModule::CaseStep(
  const NCollection_Sequence<TCollection_AsciiString>& types) const
{
  int NbComp = types.Length();
  if (NbComp < 2)
  {
    std::cout << "Plex Instance illegal " << std::endl;
  }
  return 0;
}
#else
int RWHeaderSection_ReadWriteModule::CaseStep(
  const NCollection_Sequence<TCollection_AsciiString>&) const
{
  return 0;
}
#endif

// --- External Mapping Recognition ---

bool RWHeaderSection_ReadWriteModule::IsComplex(const int /*CN*/) const
{
  return false;
}

const std::string_view& RWHeaderSection_ReadWriteModule::StepType(const int CN) const
{
  switch (CN)
  {
    case 1:
      return Reco_FileName;
    case 2:
      return Reco_FileDescription;
    case 3:
      return Reco_FileSchema;
    default:
      return PasReco;
  }
}

// -- Reading of a file --

void RWHeaderSection_ReadWriteModule::ReadStep(const int                                   CN,
                                               const occ::handle<StepData_StepReaderData>& data,
                                               const int                                   num,
                                               occ::handle<Interface_Check>&               ach,
                                               const occ::handle<Standard_Transient>& ent) const
{
  if (CN == 0)
    return;
  switch (CN)
  {
    case 1: {
      DeclareAndCast(HeaderSection_FileName, anent, ent);
      RWHeaderSection_RWFileName tool;
      if (anent.IsNull())
        ach->AddFail("Type Mismatch on FileName");
      else
        tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 2: {
      DeclareAndCast(HeaderSection_FileDescription, anent, ent);
      RWHeaderSection_RWFileDescription tool;
      if (anent.IsNull())
        ach->AddFail("Type Mismatch on FileDescription");
      else
        tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 3: {
      DeclareAndCast(HeaderSection_FileSchema, anent, ent);
      RWHeaderSection_RWFileSchema tool;
      if (anent.IsNull())
        ach->AddFail("Type Mismatch on FileSchema");
      else
        tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 4: {
      DeclareAndCast(StepData_UndefinedEntity, und, ent);
      if (und.IsNull())
        ach->AddFail("# Entity neither Recognized nor set as UndefinedEntity from StepData #");
      else
        und->ReadRecord(data, num, ach);
    }

    break;
    default:
      ach->AddFail("Type Mismatch when reading - Entity");
  }

  return;
}

// -- Writing of a file --

void RWHeaderSection_ReadWriteModule::WriteStep(const int                              CN,
                                                StepData_StepWriter&                   SW,
                                                const occ::handle<Standard_Transient>& ent) const
{
  if (CN == 0)
    return;
  switch (CN)
  {
    case 1: {
      DeclareAndCast(HeaderSection_FileName, anent, ent);
      RWHeaderSection_RWFileName tool;
      if (anent.IsNull())
        return;
      else
        tool.WriteStep(SW, anent);
    }

    break;
    case 2: {
      DeclareAndCast(HeaderSection_FileDescription, anent, ent);
      RWHeaderSection_RWFileDescription tool;
      if (anent.IsNull())
        return;
      else
        tool.WriteStep(SW, anent);
    }

    break;
    case 3: {
      DeclareAndCast(HeaderSection_FileSchema, anent, ent);
      RWHeaderSection_RWFileSchema tool;
      if (anent.IsNull())
        return;
      else
        tool.WriteStep(SW, anent);
    }

    break;
    case 4: {
      DeclareAndCast(StepData_UndefinedEntity, und, ent);
      if (und.IsNull())
        break;
      //  Parentheses gerees par StepWriter lui-meme
      //   car en recevant le type PasReco, StepWriter ne l'affiche pas,
      //   mais il gere les parentheses comme si de rien n etait
      if (und->IsComplex())
        SW.StartComplex();
      und->WriteParams(SW);
      if (und->IsComplex())
        SW.EndComplex();
    }

    break;
    default:
      return;
  }
}
