

#include <IGESData_IGESEntity.hpp>
#include <IGESSelect_SignStatus.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SignStatus, IFSelect_Signature)

static char theval[10];

IGESSelect_SignStatus::IGESSelect_SignStatus()
    : IFSelect_Signature("D.E. Status")
{
}

const char* IGESSelect_SignStatus::Value(const occ::handle<Standard_Transient>& ent,
                                         const occ::handle<Interface_InterfaceModel>&) const
{
  occ::handle<IGESData_IGESEntity> igesent = occ::down_cast<IGESData_IGESEntity>(ent);
  if (igesent.IsNull())
    return "";
  int i, j, k, l;
  i = igesent->BlankStatus();
  j = igesent->SubordinateStatus();
  k = igesent->UseFlag();
  l = igesent->HierarchyStatus();
  Sprintf(theval, "%d,%d,%d,%d", i, j, k, l);
  return theval;
}

bool IGESSelect_SignStatus::Matches(const occ::handle<Standard_Transient>& ent,
                                    const occ::handle<Interface_InterfaceModel>&,
                                    const TCollection_AsciiString& text,
                                    const bool                     exact) const
{
  occ::handle<IGESData_IGESEntity> igesent = occ::down_cast<IGESData_IGESEntity>(ent);
  if (igesent.IsNull())
    return false;
  int i, j, k, l;
  i = igesent->BlankStatus();
  j = igesent->SubordinateStatus();
  k = igesent->UseFlag();
  l = igesent->HierarchyStatus();
  int n, nb = text.Length();
  if (nb > 9)
    nb = 9;
  for (n = 1; n <= nb; n++)
    theval[n - 1] = text.Value(n);
  theval[nb] = '\0';

  int vir = 0, val = 0;
  for (n = 0; n < nb; n++)
  {
    char car = theval[n];
    if (car == ',')
    {
      vir++;
      continue;
    }
    val = int(car - 48);
    if (car == 'V' && vir == 0)
      val = 0;
    if (car == 'B' && vir == 0)
      val = 1;
    if (car == 'I' && vir == 1)
      val = 0;
    if (car == 'P' && vir == 1)
      val = 1;
    if (car == 'L' && vir == 1)
      val = 2;
    if (car == 'D' && vir == 1)
      val = 3;

    if (vir == 0)
    {
      if (i == val && !exact)
        return true;
      if (i != val && exact)
        return false;
    }
    if (vir == 1)
    {
      if (j == val && !exact)
        return true;
      if (j != val && exact)
        return false;
    }
    if (vir == 2)
    {
      if (k == val && !exact)
        return true;
      if (k != val && exact)
        return false;
    }
    if (vir == 3)
    {
      if (l == val && !exact)
        return true;
      if (l != val && exact)
        return false;
    }
  }
  return exact;
}
