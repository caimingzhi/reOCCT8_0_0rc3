

#include <IGESData_ColorEntity.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_LabelDisplayEntity.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_SpecificLib.hpp>
#include <IGESData_SpecificModule.hpp>
#include <IGESData_TransfEntity.hpp>
#include <IGESData_ViewKindEntity.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_MSG.hpp>
#include <TCollection_HAsciiString.hpp>

IGESData_IGESDumper::IGESData_IGESDumper(const occ::handle<IGESData_IGESModel>& model,
                                         const occ::handle<IGESData_Protocol>&  protocol)
    : thelib(protocol)
{
  themodel = model;
}

void IGESData_IGESDumper::PrintDNum(const occ::handle<IGESData_IGESEntity>& ent,
                                    Standard_OStream&                       S) const
{

  int num = 0;
  if (!ent.IsNull())
  {
    if (themodel.IsNull())
      S << "    D???    ";
    else if ((num = themodel->Number(ent)) == 0)
      S << "    0:D?????";

    else
    {
      S << Interface_MSG::Blanks(num, 9) << num << ":D" << 2 * num - 1
        << Interface_MSG::Blanks(2 * num - 1, 9);
    }
  }
  else
    S << "  D0(Null)  ";
}

void IGESData_IGESDumper::PrintShort(const occ::handle<IGESData_IGESEntity>& ent,
                                     Standard_OStream&                       S) const
{

  if (!ent.IsNull())
  {
    int num = 0;
    if (!themodel.IsNull())
      num = themodel->Number(ent);
    if (num > 0)
      S << num << ":D" << 2 * num - 1;
    S << "  Type:" << ent->TypeNumber() << "  Form:" << ent->FormNumber()
      << Interface_MSG::Blanks(ent->FormNumber(), 3)
      << " Class:" << Interface_InterfaceModel::ClassName(ent->DynamicType()->Name());
  }
}

void IGESData_IGESDumper::Dump(const occ::handle<IGESData_IGESEntity>& ent,
                               Standard_OStream&                       S,
                               const int                               own,
                               const int                               attached) const
{
  int att    = attached;
  int diratt = 1;
  if (own < 3)
    diratt = own - 1;
  if (att == 0)
    att = diratt;

  if (own < 0)
    return;

  if (own > 1)
    S << "\n";
  if (ent.IsNull())
  {
    S << "(Null)";
    if (own > 1)
      S << "\n";
    return;
  }
  if (own == 0)
  {
    PrintDNum(ent, S);
    return;
  }
  if (own == 1)
  {
    PrintShort(ent, S);
    return;
  }

  if (own > 0)
    S << "****    Dump IGES, level " << own << " ( ";
  switch (own)
  {
    case 0:
      break;
    case 1:
      S << "D.E. Number + Type + Name";
      break;
    case 2:
      S << "D.E. Number + Type, Name + Transf, View";
      break;
    case 3:
      S << "Complete Directory Part";
      break;
    case 4:
      S << "Directory Part + Parameters, no Arrays";
      break;
    case 5:
      S << "Complete";
      break;
    default:
      S << "Complete + Transformed Values";
      break;
  }
  S << " )    ****\n";

  S << "\n****    Entity ";
  PrintShort(ent, S);
  S << "\n";

  S << "              Directory Part\n";

  if (own >= 2)
    S << "**      Status Number :   Blank:" << ent->BlankStatus()
      << "    Subordinate:" << ent->SubordinateStatus() << "    UseFlag:" << ent->UseFlag()
      << "    Hierarchy:" << ent->HierarchyStatus() << "\n";
  if (own >= 1)
  {
    if (ent->HasShortLabel())
      S << "****    Label         :" << ent->ShortLabel()->ToCString();
    if (ent->HasSubScriptNumber())
      S << "    SubScript:" << ent->SubScriptNumber();
    if (ent->HasShortLabel())
      S << std::endl;

    if (ent->HasTransf())
    {
      S << "**      Transf.Matrix :";
      PrintDNum(ent->Transf(), S);
      S << "\n";
    }
    IGESData_DefList viewkind = ent->DefView();
    if (viewkind == IGESData_DefOne)
    {
      S << "**      View          :";
      PrintDNum(ent->View(), S);
      S << "\n";
    }
    if (viewkind == IGESData_DefSeveral)
    {
      S << "**      View (List)   :";
      PrintDNum(ent->ViewList(), S);
      S << "\n";
    }
  }

  if (own >= 2)
  {

    if (ent->HasStructure())
    {
      S << "**      Structure     :";
      PrintDNum(ent->Structure(), S);
      S << "\n";
    }

    S << "\n              Graphic Attributes\n";
    if (ent->DefLineFont() == IGESData_DefValue)
    {
      S << "**      LineFont Value:" << ent->RankLineFont() << "\n";
    }
    else if (ent->DefLineFont() == IGESData_DefReference)
    {
      S << "**      LineFont Ref  :";
      PrintDNum(ent->LineFont(), S);
      S << "\n";
    }

    if (ent->Level() > 0)
      S << "**      Level Value   :" << ent->Level() << "\n";
    else if (ent->Level() < 0)
    {
      S << "**      Level List    :";
      PrintDNum(ent->LevelList(), S);
      S << "\n";
    }

    if (ent->HasLabelDisplay())
    {
      S << "**      Label Display :";
      PrintDNum(ent->LabelDisplay(), S);
      S << "\n";
    }
    if (ent->LineWeightNumber() != 0)
    {
      S << "**      LineWeight Num:" << ent->LineWeightNumber();
      if (diratt > 0)
        S << "    ->  Value:" << ent->LineWeight();
      S << std::endl;
    }
    if (ent->DefColor() == IGESData_DefValue)
    {
      S << "**      Color Value   :" << ent->RankColor();
    }
    else if (ent->DefColor() == IGESData_DefReference)
    {
      S << "**      Color Ref     :";
      PrintDNum(ent->Color(), S);
    }
    S << std::endl;

    if (own > 3)
    {
      S << "****             Own Data             ****\n\n";
      OwnDump(ent, S, own);
    }
  }

  if (att < 0)
    return;
  Interface_EntityIterator iter   = ent->Properties();
  int                      nb     = iter.NbEntities();
  bool                     iasuit = (nb > 0);
  if (nb > 0)
  {
    S << "\n****     Properties (nb:" << nb << ")          ****\n";
    for (; iter.More(); iter.Next())
    {
      DeclareAndCast(IGESData_IGESEntity, ent2, iter.Value());
      Dump(ent2, S, att, -1);
    }
  }
  iter = ent->Associativities();
  nb   = iter.NbEntities();
  if (nb > 0)
    iasuit = true;
  if (nb > 0)
  {
    S << "\n****   Associativities (nb:" << nb << ")        ****\n";
    for (; iter.More(); iter.Next())
    {
      DeclareAndCast(IGESData_IGESEntity, ent2, iter.Value());
      Dump(ent2, S, att, -1);
    }
  }
  if (iasuit)
  {
    if (att <= 1)
      S << "\n";
  }
  S << "\n****             End of Dump          ****\n" << std::endl;
}

void IGESData_IGESDumper::OwnDump(const occ::handle<IGESData_IGESEntity>& ent,
                                  Standard_OStream&                       S,
                                  const int                               own) const
{
  occ::handle<IGESData_SpecificModule> module;
  int                                  CN;
  if (thelib.Select(ent, module, CN))
    module->OwnDump(CN, ent, *this, S, own);
  else if (themodel.IsNull())
    S << "  ****  Dump impossible. Type " << ent->DynamicType()->Name() << std::endl;
  else
    S << "  ****  Dump Impossible, n0:id:" << themodel->Number(ent) << ":D" << themodel->DNum(ent)
      << " Type " << ent->DynamicType()->Name() << std::endl;
}
