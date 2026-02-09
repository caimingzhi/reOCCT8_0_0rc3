

#include <Interface_Static.hpp>

#include <Message_MsgFile.hpp>

#include "../XSMessage/XSMessage_XSTEP_us.hpp"

static int THE_Interface_Static_deja = 0;

void Interface_Static::Standards()
{
  if (THE_Interface_Static_deja)
  {
    return;
  }

  THE_Interface_Static_deja = 1;

  Interface_Static::Init("XSTEP", "read.precision.mode", 'e', "");
  Interface_Static::Init("XSTEP", "read.precision.mode", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "read.precision.mode", '&', "eval File");
  Interface_Static::Init("XSTEP", "read.precision.mode", '&', "eval User");
  Interface_Static::SetIVal("read.precision.mode", 0);

  Interface_Static::Init("XSTEP", "read.precision.val", 'r', "1.e-03");

  Interface_Static::Init("XSTEP", "read.maxprecision.mode", 'e', "");
  Interface_Static::Init("XSTEP", "read.maxprecision.mode", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "read.maxprecision.mode", '&', "eval Preferred");
  Interface_Static::Init("XSTEP", "read.maxprecision.mode", '&', "eval Forced");
  Interface_Static::SetIVal("read.maxprecision.mode", 0);

  Interface_Static::Init("XSTEP", "read.maxprecision.val", 'r', "1.");

  Interface_Static::Init("XSTEP", "read.encoderegularity.angle", 'r', "0.01");

  Interface_Static::Init("XSTEP", "read.surfacecurve.mode", 'e', "");
  Interface_Static::Init("XSTEP", "read.surfacecurve.mode", '&', "ematch -3");
  Interface_Static::Init("XSTEP", "read.surfacecurve.mode", '&', "eval 3DUse_Forced");
  Interface_Static::Init("XSTEP", "read.surfacecurve.mode", '&', "eval 2DUse_Forced");
  Interface_Static::Init("XSTEP", "read.surfacecurve.mode", '&', "eval ?");
  Interface_Static::Init("XSTEP", "read.surfacecurve.mode", '&', "eval Default");
  Interface_Static::Init("XSTEP", "read.surfacecurve.mode", '&', "eval ?");
  Interface_Static::Init("XSTEP", "read.surfacecurve.mode", '&', "eval 2DUse_Preferred");
  Interface_Static::Init("XSTEP", "read.surfacecurve.mode", '&', "eval 3DUse_Preferred");
  Interface_Static::SetIVal("read.surfacecurve.mode", 0);

  Interface_Static::Init("XSTEP", "write.precision.mode", 'e', "");
  Interface_Static::Init("XSTEP", "write.precision.mode", '&', "ematch -1");
  Interface_Static::Init("XSTEP", "write.precision.mode", '&', "eval Min");
  Interface_Static::Init("XSTEP", "write.precision.mode", '&', "eval Average");
  Interface_Static::Init("XSTEP", "write.precision.mode", '&', "eval Max");
  Interface_Static::Init("XSTEP", "write.precision.mode", '&', "eval User");
  Interface_Static::SetIVal("write.precision.mode", 0);

  Interface_Static::Init("XSTEP", "write.precision.val", 'r', "1.e-03");

  Interface_Static::Init("XSTEP", "write.surfacecurve.mode", 'e', "");
  Interface_Static::Init("XSTEP", "write.surfacecurve.mode", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "write.surfacecurve.mode", '&', "eval Off");
  Interface_Static::Init("XSTEP", "write.surfacecurve.mode", '&', "eval On");

  Interface_Static::SetIVal("write.surfacecurve.mode", 1);

  if (!Message_MsgFile::HasMsg("XSTEP_1"))
  {
    if (!Message_MsgFile::LoadFromEnv("CSF_XSMessage", "XSTEP"))
    {
      Message_MsgFile::LoadFromString(XSMessage_XSTEP_us, sizeof(XSMessage_XSTEP_us) - 1);
    }
    if (!Message_MsgFile::HasMsg("XSTEP_1"))
    {
      throw Standard_ProgramError(
        "Critical Error - message resources for Interface_Static are invalid or undefined!");
    }
  }
}
