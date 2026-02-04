#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <OSD_Exception.hpp>

#if !defined No_Exception && !defined No_OSD_Exception_ILLEGAL_INSTRUCTION
  #define OSD_Exception_ILLEGAL_INSTRUCTION_Raise_if(CONDITION, MESSAGE)                           \
    if (CONDITION)                                                                                 \
      throw OSD_Exception_ILLEGAL_INSTRUCTION(MESSAGE);
#else
  #define OSD_Exception_ILLEGAL_INSTRUCTION_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_Exception_ILLEGAL_INSTRUCTION, OSD_Exception)

