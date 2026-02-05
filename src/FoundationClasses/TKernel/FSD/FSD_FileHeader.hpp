#pragma once

#include <stddef.h>

#include <stdlib.h>

#include <Standard_Macro.hpp>

#include <Standard_Boolean.hpp>

#include <Standard_Integer.hpp>

#include <Standard_Real.hpp>

#include <Standard_Character.hpp>

#include <Standard_ExtCharacter.hpp>

#include <Standard_CString.hpp>

struct FSD_FileHeader
{
  int testindian;
  int binfo;
  int einfo;
  int bcomment;
  int ecomment;
  int btype;
  int etype;
  int broot;
  int eroot;
  int bref;
  int eref;
  int bdata;
  int edata;
};
