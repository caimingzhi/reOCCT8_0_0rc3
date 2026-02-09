

#include <IGESData_UndefinedEntity.hpp>
#include <IGESSelect_IGESTypeForm.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_IGESTypeForm, IFSelect_Signature)

static char falsetype[] = "?";
static char typeval[30];

IGESSelect_IGESTypeForm::IGESSelect_IGESTypeForm(const bool withform)

    : IFSelect_Signature((const char*)(withform ? "IGES Type & Form Numbers" : "IGES Type Number"))

{
  theform = withform;
}

void IGESSelect_IGESTypeForm::SetForm(const bool withform)
{
  theform = withform;
  thename.Clear();

  const char* astr = (const char*)(withform ? "IGES Type & Form Numbers" : "IGES Type Number");
  thename.AssignCat(astr);
}

const char* IGESSelect_IGESTypeForm::Value(const occ::handle<Standard_Transient>& ent,
                                           const occ::handle<Interface_InterfaceModel>&) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return &falsetype[0];
  bool unk     = ent->IsKind(STANDARD_TYPE(IGESData_UndefinedEntity));
  int  typenum = igesent->TypeNumber();
  int  formnum = igesent->FormNumber();
  if (unk)
  {
    if (theform)
      Sprintf(typeval, "%d %d (?)", typenum, formnum);
    else
      Sprintf(typeval, "%d (?)", typenum);
  }
  else
  {
    if (theform)
      Sprintf(typeval, "%d %d", typenum, formnum);
    else
      Sprintf(typeval, "%d", typenum);
  }
  return &typeval[0];
}
