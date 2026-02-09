

#include <IGESData_ColorEntity.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_LabelDisplayEntity.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <IGESData_ViewKindEntity.hpp>
#include <Interface_Check.hpp>
#include <Message_Msg.hpp>

#include <cstdio>

IGESData_DirChecker::IGESData_DirChecker()
{
  thetype = theform1 = theform2 = 0;
  thestructure = thelinefont = thelineweig = thecolor = IGESData_ErrorRef;
  thegraphier                                         = -100;
  theblankst = thesubordst = theuseflag = thehierst = -100;
}

IGESData_DirChecker::IGESData_DirChecker(const int atype)
{
  thetype      = atype;
  theform1     = 0;
  theform2     = -1;
  thestructure = thelinefont = thelineweig = thecolor = IGESData_ErrorRef;
  thegraphier                                         = -100;
  theblankst = thesubordst = theuseflag = thehierst = -100;
}

IGESData_DirChecker::IGESData_DirChecker(const int atype, const int aform)
{
  thetype  = atype;
  theform1 = theform2 = aform;
  thestructure = thelinefont = thelineweig = thecolor = IGESData_ErrorRef;
  thegraphier                                         = -100;
  theblankst = thesubordst = theuseflag = thehierst = -100;
}

IGESData_DirChecker::IGESData_DirChecker(const int atype, const int aform1, const int aform2)
{
  thetype      = atype;
  theform1     = aform1;
  theform2     = aform2;
  thestructure = thelinefont = thelineweig = thecolor = IGESData_ErrorRef;
  thegraphier                                         = -100;
  theblankst = thesubordst = theuseflag = thehierst = -100;
}

bool IGESData_DirChecker::IsSet() const
{
  return isitset;
}

void IGESData_DirChecker::SetDefault()
{
  Structure(IGESData_DefVoid);
}

void IGESData_DirChecker::Structure(const IGESData_DefType crit)
{
  isitset      = true;
  thestructure = crit;
}

void IGESData_DirChecker::LineFont(const IGESData_DefType crit)
{
  isitset     = true;
  thelinefont = crit;
}

void IGESData_DirChecker::LineWeight(const IGESData_DefType crit)
{
  isitset     = true;
  thelineweig = crit;
}

void IGESData_DirChecker::Color(const IGESData_DefType crit)
{
  isitset  = true;
  thecolor = crit;
}

void IGESData_DirChecker::GraphicsIgnored(const int hierarchy)
{
  isitset     = true;
  thegraphier = hierarchy;
}

void IGESData_DirChecker::BlankStatusIgnored()
{
  isitset    = true;
  theblankst = -10;
}

void IGESData_DirChecker::BlankStatusRequired(const int val)
{
  isitset    = true;
  theblankst = val;
}

void IGESData_DirChecker::SubordinateStatusIgnored()
{
  isitset     = true;
  thesubordst = -10;
}

void IGESData_DirChecker::SubordinateStatusRequired(const int val)
{
  isitset     = true;
  thesubordst = val;
}

void IGESData_DirChecker::UseFlagIgnored()
{
  isitset    = true;
  theuseflag = -10;
}

void IGESData_DirChecker::UseFlagRequired(const int val)
{
  isitset    = true;
  theuseflag = val;
}

void IGESData_DirChecker::HierarchyStatusIgnored()
{
  isitset   = true;
  thehierst = -10;
}

void IGESData_DirChecker::HierarchyStatusRequired(const int val)
{
  isitset   = true;
  thehierst = val;
}

void IGESData_DirChecker::Check(occ::handle<Interface_Check>&           ach,
                                const occ::handle<IGESData_IGESEntity>& ent) const
{

  if (thetype != 0)
  {

    if (ent->TypeNumber() != thetype)
    {
      Message_Msg Msg58("XSTEP_58");
      ach->SendFail(Msg58);
    }

    if (theform1 <= theform2)
    {
      if (ent->FormNumber() < theform1 || ent->FormNumber() > theform2)
      {
        Message_Msg Msg71("XSTEP_71");
        ach->SendFail(Msg71);
      }
    }
  }

  if (thestructure == IGESData_DefReference && !ent->HasStructure())
  {
    Message_Msg Msg59("XSTEP_59");
    ach->SendFail(Msg59);
  }

  if (thegraphier == -1 || thegraphier == ent->HierarchyStatus())
  {
  }
  else
  {
    IGESData_DefType df = ent->DefLineFont();

    if (df == IGESData_ErrorVal || df == IGESData_ErrorRef)
    {
      Message_Msg Msg60("XSTEP_60");
      ach->SendFail(Msg60);
    }
    else if (thelinefont == IGESData_DefValue && df != IGESData_DefValue)
    {
      Message_Msg Msg60("XSTEP_60");
      ach->SendWarning(Msg60);
    }

    int         dlw = ent->LineWeightNumber();
    Message_Msg Msg69("XSTEP_69");

    if (thelineweig == IGESData_DefValue && dlw == 0)
    {

      ach->SendWarning(Msg69);
    }

    df = ent->DefColor();

    if (df == IGESData_ErrorVal || df == IGESData_ErrorRef)
    {

      ach->SendFail(Msg69);
    }
    else if (thecolor == IGESData_DefValue && df != IGESData_DefValue)
    {

      ach->SendWarning(Msg69);
    }
  }

  int st = ent->BlankStatus();

  if (st < 0 || st > 1)
  {
    Message_Msg Msg65("XSTEP_65");
    ach->SendFail(Msg65);
  }

  st = ent->SubordinateStatus();

  if (st < 0 || st > 3)
  {
    Message_Msg Msg66("XSTEP_66");
    ach->SendFail(Msg66);
  }

  st = ent->UseFlag();

  if (st < 0 || st > 5)
  {
    Message_Msg Msg67("XSTEP_67");
    ach->SendFail(Msg67);
  }

  st = ent->HierarchyStatus();

  if (st < 0 || st > 2)
  {
    Message_Msg Msg68("XSTEP_68");
    ach->SendFail(Msg68);
  }
}

void IGESData_DirChecker::CheckTypeAndForm(occ::handle<Interface_Check>&           ach,
                                           const occ::handle<IGESData_IGESEntity>& ent) const
{

  if (thetype != 0)
  {
    if (ent->TypeNumber() != thetype)
    {
      Message_Msg Msg58("XSTEP_58");
      ach->SendWarning(Msg58);
    }

    if (theform1 <= theform2)
      if (ent->FormNumber() < theform1 || ent->FormNumber() > theform2)
      {
        Message_Msg Msg71("XSTEP_71");
        ach->SendWarning(Msg71);
      }
  }
}

bool IGESData_DirChecker::Correct(const occ::handle<IGESData_IGESEntity>& ent) const
{
  bool done = false;
  int  type = ent->TypeNumber();
  int  form = ent->FormNumber();
  if (thetype != 0)
  {
    if (theform1 >= 0 && theform1 == theform2 && theform1 != form)
    {
      ent->InitTypeAndForm(thetype, theform1);
      done = true;
    }
    else if (thetype != type)
    {
      ent->InitTypeAndForm(thetype, form);
      done = true;
    }
  }

  occ::handle<IGESData_IGESEntity> structure;
  if (thestructure != IGESData_DefVoid)
    structure = ent->Structure();
  occ::handle<IGESData_ViewKindEntity>     nulview;
  occ::handle<IGESData_LineFontEntity>     nulfont;
  occ::handle<IGESData_LevelListEntity>    nulevel;
  occ::handle<IGESData_ColorEntity>        nulcolor;
  occ::handle<IGESData_LabelDisplayEntity> label;
  if (thegraphier != -1)
    label = ent->LabelDisplay();
  int linew = 0;
  if (thegraphier != -1 && thelineweig != IGESData_DefVoid)
    linew = ent->LineWeightNumber();

  if (thegraphier == -1 || (ent->RankLineFont() != 0 && thelinefont == IGESData_DefVoid))
  {
    ent->InitLineFont(nulfont);
    done = true;
  }
  if (thegraphier == -1 || (ent->RankColor() != 0 && thecolor == IGESData_DefVoid))
  {
    ent->InitColor(nulcolor);
    done = true;
  }
  if (thegraphier == -1 && (!ent->View().IsNull() || ent->Level() != 0))
  {
    ent->InitView(nulview);
    ent->InitLevel(nulevel);
    done = true;
  }
  if ((thegraphier == -1 && (!ent->LabelDisplay().IsNull() || ent->LineWeightNumber() != 0))
      || (ent->HasStructure() && thestructure == IGESData_DefVoid))
  {
    ent->InitMisc(structure, label, linew);
    done = true;
  }

  bool force = false;
  int  stb   = ent->BlankStatus();
  int  sts   = ent->SubordinateStatus();
  int  stu   = ent->UseFlag();
  int  sth   = ent->HierarchyStatus();
  if (theblankst >= 0 && theblankst != stb)
  {
    force = true;
    stb   = theblankst;
  }
  if (thesubordst >= 0 && thesubordst != sts)
  {
    force = true;
    sts   = thesubordst;
  }
  if (theuseflag >= 0 && theuseflag != stu)
  {
    force = true;
    stu   = theuseflag;
  }
  if (thehierst >= 0 && thehierst != sth)
  {
    force = true;
    sth   = thehierst;
  }
  if (force)
  {
    ent->InitStatus(stb, sts, stu, sth);
    done = true;
  }
  return done;
}
