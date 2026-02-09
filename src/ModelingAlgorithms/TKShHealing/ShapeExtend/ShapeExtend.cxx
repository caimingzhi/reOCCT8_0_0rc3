#include <ShapeExtend.hpp>

#include <Message_MsgFile.hpp>
#include <Standard_ProgramError.hpp>
#include <TCollection_AsciiString.hpp>

#include "../SHMessage/SHMessage_SHAPE_us.hpp"

void ShapeExtend::Init()
{
  static bool init = false;
  if (init)
    return;

  init = true;

  if (!Message_MsgFile::HasMsg("ShapeFix.FixSmallSolid.MSG0"))
  {
    if (!Message_MsgFile::LoadFromEnv("CSF_SHMessage", "SHAPE"))
    {
      Message_MsgFile::LoadFromString(SHMessage_SHAPE_us, sizeof(SHMessage_SHAPE_us) - 1);
    }
    if (!Message_MsgFile::HasMsg("ShapeFix.FixSmallSolid.MSG0"))
    {
      throw Standard_ProgramError(
        "Critical Error - message resources for ShapeExtend are invalid or undefined!");
    }
  }
}

int ShapeExtend::EncodeStatus(const ShapeExtend_Status status)
{
  switch (status)
  {
    case ShapeExtend_OK:
      return 0x0000;
    case ShapeExtend_DONE1:
      return 0x0001;
    case ShapeExtend_DONE2:
      return 0x0002;
    case ShapeExtend_DONE3:
      return 0x0004;
    case ShapeExtend_DONE4:
      return 0x0008;
    case ShapeExtend_DONE5:
      return 0x0010;
    case ShapeExtend_DONE6:
      return 0x0020;
    case ShapeExtend_DONE7:
      return 0x0040;
    case ShapeExtend_DONE8:
      return 0x0080;
    case ShapeExtend_DONE:
      return 0x00ff;
    case ShapeExtend_FAIL1:
      return 0x0100;
    case ShapeExtend_FAIL2:
      return 0x0200;
    case ShapeExtend_FAIL3:
      return 0x0400;
    case ShapeExtend_FAIL4:
      return 0x0800;
    case ShapeExtend_FAIL5:
      return 0x1000;
    case ShapeExtend_FAIL6:
      return 0x2000;
    case ShapeExtend_FAIL7:
      return 0x4000;
    case ShapeExtend_FAIL8:
      return 0x8000;
    case ShapeExtend_FAIL:
      return 0xff00;
  }
  return 0;
}

bool ShapeExtend::DecodeStatus(const int flag, const ShapeExtend_Status status)
{
  if (status == ShapeExtend_OK)
    return (flag == 0);
  return ((flag & ShapeExtend::EncodeStatus(status)) != 0);
}
