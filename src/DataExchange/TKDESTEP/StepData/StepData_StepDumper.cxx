

#include <Interface_EntityIterator.hpp>
#include <Interface_GeneralModule.hpp>
#include <Message.hpp>
#include <Standard_Transient.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_ReadWriteModule.hpp>
#include <StepData_StepDumper.hpp>
#include <StepData_StepModel.hpp>
#include <StepData_StepWriter.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>

#include <cstdio>

StepData_StepDumper::StepData_StepDumper(const occ::handle<StepData_StepModel>& amodel,
                                         const occ::handle<StepData_Protocol>&  protocol,
                                         const int                              mode)
    : theslib(protocol),
      thewlib(protocol),
      thewriter(amodel)
{
  themodel = amodel;
  if (mode > 0)
    thewriter.LabelMode() = 2;
}

StepData_StepWriter& StepData_StepDumper::StepWriter()
{
  return thewriter;
}

bool StepData_StepDumper::Dump(Standard_OStream&                      S,
                               const occ::handle<Standard_Transient>& ent,
                               const int                              level)
{
  int                     i, nb = themodel->NbEntities();
  NCollection_Array1<int> ids(0, nb);
  ids.Init(0);
  int num  = themodel->Number(ent);
  int nlab = themodel->IdentLabel(ent);
  ids.SetValue(num, (nlab > 0 ? nlab : -1));

  if (level <= 0)
  {

    occ::handle<StepData_ReadWriteModule> module;
    int                                   CN;
    if (num > 0)
      S << "#" << num << " = ";
    else
      S << "#??? = ";
    if (thewlib.Select(ent, module, CN))
    {
      if (module->IsComplex(CN))
      {
        NCollection_Sequence<TCollection_AsciiString> listypes;
        if (!module->ComplexType(CN, listypes))
          S << "(Complex Type : ask level > 0) cdl = " << ent->DynamicType()->Name() << " (...);"
            << std::endl;
        else
        {
          int n = listypes.Length();
          for (i = 1; i <= n; i++)
            S << listypes.Value(i) << " (...)";
          S << std::endl;
        }
      }
      else
        S << module->StepType(CN) << " (...);" << std::endl;
    }
    else
      S << "(Unrecognized Type for protocol) cdl = " << ent->DynamicType()->Name() << " (...);"
        << std::endl;
    if (nlab > 0)
      S << "/*   Ident in file for " << num << " : #" << nlab << "   */" << std::endl;
  }

  else if (level == 1)
  {

    occ::handle<Standard_Transient>      anent;
    occ::handle<Interface_GeneralModule> module;
    int                                  CN;
    if (theslib.Select(ent, module, CN))
    {
      Interface_EntityIterator iter;
      module->FillSharedCase(CN, ent, iter);
      module->ListImpliedCase(CN, ent, iter);
      for (; iter.More(); iter.Next())
      {
        anent = iter.Value();
        nlab  = themodel->IdentLabel(anent);
        ids.SetValue(themodel->Number(anent), (nlab > 0 ? nlab : -1));
      }
    }

    thewriter.SendEntity(num, thewlib);
  }
  else
  {
    occ::handle<Standard_Transient> anent;

    NCollection_Array1<int> tab(0, nb);
    tab.Init(0);
    tab.SetValue(num, 1);
    occ::handle<Interface_GeneralModule> module;
    int                                  CN;
    if (theslib.Select(ent, module, CN))
    {
      Interface_EntityIterator iter;
      module->FillSharedCase(CN, ent, iter);
      module->ListImpliedCase(CN, ent, iter);
      for (; iter.More(); iter.Next())
      {
        tab.SetValue(themodel->Number(iter.Value()), 1);
      }
    }
    for (i = 1; i <= nb; i++)
    {

      if (tab.Value(i) == 0)
        continue;
      anent = themodel->Value(i);
      thewriter.SendEntity(i, thewlib);
      if (theslib.Select(anent, module, CN))
      {
        Interface_EntityIterator iter;
        module->FillSharedCase(CN, anent, iter);
        module->ListImpliedCase(CN, anent, iter);
        for (; iter.More(); iter.Next())
        {
          anent = iter.Value();
          nlab  = themodel->IdentLabel(anent);
          ids.SetValue(themodel->Number(anent), (nlab > 0 ? nlab : -1));
        }
      }
    }
  }

  int nbi = 0, nbe = 0, nbq = 0, nbu = 0;
  for (i = 1; i <= nb; i++)
  {
    nlab = ids.Value(i);
    if (nlab == 0)
      continue;
    nbe++;
    if (nlab < 0)
      nbu = 0;
    else if (nlab == i)
      nbq = 0;
    else if (nlab > 0)
      nbi++;
  }
  if (nbe > 0)
  {

    if (nbu > 0)
    {
      S << " (no ident): ";
      for (i = 1; i <= nb; i++)
      {
        if (ids.Value(i) >= 0)
          continue;
        S << " #" << i;
      }
      S << std::endl;
    }
    if (nbq > 0)
    {
      S << " (ident = num): ";
      for (i = 1; i <= nb; i++)
      {
        if (ids.Value(i) == i)
          S << " #" << i;
      }
      S << std::endl;
    }
    if (nbi < 0)
    {
      int  nbl = 0, nbr = 0, nbr0 = 0, nbc = 0;
      char unid[30];

      S << " (proper ident):  num:#ident  num:#ident  ..." << std::endl;
      for (i = 1; i <= nb; i++)
      {
        if (ids.Value(i) <= 0 || ids.Value(i) == i)
          continue;
        Sprintf(unid, "%d:#%d", i, ids.Value(i));
        nbc = (int)strlen(unid);
        nbr = ((80 - nbc) % 4) + 2;
        nbl += nbc;
        if (nbl + nbr0 > 79)
        {
          nbl = nbc;
          S << std::endl;
        }
        else
        {
          nbl += nbr0;
          for (; nbr0 > 0; nbr0--)
            S << " ";
        }
        S << unid;
        nbr0 = nbr;
      }
      if (nbl > 0)
        S << std::endl;
    }
    if (nbi > 0)
      S << "In dump, iii:#jjj means : entity rank iii has step ident #jjj" << std::endl;
  }
  if (level > 0)
  {
    thewriter.Print(S);
  }
  return true;
}

bool StepData_StepDumper::Dump(Standard_OStream& S, const int num, const int level)
{
  if (num <= 0 || num > themodel->NbEntities())
    return false;
  occ::handle<Standard_Transient> ent = themodel->Value(num);
  return Dump(S, ent, level);
}
