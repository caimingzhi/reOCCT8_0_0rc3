

#include <IGESData_IGESEntity.hpp>
#include <IGESGraph_DefinitionLevel.hpp>
#include <IGESSelect_CounterOfLevelNumber.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_CounterOfLevelNumber, IFSelect_SignCounter)

IGESSelect_CounterOfLevelNumber::IGESSelect_CounterOfLevelNumber(const bool withmap,
                                                                 const bool withlist)
    : IFSelect_SignCounter(withmap, withlist)
{
  thehigh = thenblists = 0;
  SetName("IGES Level Number");
}

void IGESSelect_CounterOfLevelNumber::Clear()
{
  IFSelect_SignCounter::Clear();
  thelevels.Nullify();
  thehigh = thenblists = 0;
}

void IGESSelect_CounterOfLevelNumber::AddSign(const occ::handle<Standard_Transient>& ent,
                                              const occ::handle<Interface_InterfaceModel>&)
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return;
  DeclareAndCast(IGESGraph_DefinitionLevel, levelist, igesent->LevelList());
  int level = igesent->Level();
  if (levelist.IsNull() && level < 0)
    return;

  if (levelist.IsNull())
    AddLevel(ent, level);
  else
  {
    int nb = levelist->NbPropertyValues();
    for (int i = 1; i <= nb; i++)
    {
      level = levelist->LevelNumber(i);
      AddLevel(ent, level);
    }
    AddLevel(ent, -1);
  }
}

void IGESSelect_CounterOfLevelNumber::AddLevel(const occ::handle<Standard_Transient>& ent,
                                               const int                              level)
{
  if (level < 0)
  {
    thenblists++;
    Add(ent, "LEVEL LIST");
    return;
  }
  if (thelevels.IsNull())
  {
    thelevels = new NCollection_HArray1<int>(0, (level > 100 ? level : 100));
    thelevels->Init(0);
  }
  int upper = thelevels->Upper();
  if (level > upper)
  {
    occ::handle<NCollection_HArray1<int>> levels = new NCollection_HArray1<int>(0, level + 100);
    levels->Init(0);
    for (int i = 1; i <= upper; i++)
      levels->SetValue(i, thelevels->Value(i));
    thelevels = levels;
  }
  thelevels->SetValue(level, thelevels->Value(level) + 1);
  if (level > thehigh)
    thehigh = level;

  char signature[30];
  Sprintf(signature, "%7d", level);
  Add(ent, signature);
}

int IGESSelect_CounterOfLevelNumber::HighestLevel() const
{
  return thehigh;
}

int IGESSelect_CounterOfLevelNumber::NbTimesLevel(const int level) const
{
  if (level < 0)
    return thenblists;
  if (level > thehigh)
    return 0;
  return thelevels->Value(level);
}

occ::handle<NCollection_HSequence<int>> IGESSelect_CounterOfLevelNumber::Levels() const
{
  occ::handle<NCollection_HSequence<int>> list = new NCollection_HSequence<int>();
  for (int i = 1; i <= thehigh; i++)
  {
    if (thelevels->Value(i) > 0)
      list->Append(i);
  }
  return list;
}

occ::handle<TCollection_HAsciiString> IGESSelect_CounterOfLevelNumber::Sign(
  const occ::handle<Standard_Transient>& ent,
  const occ::handle<Interface_InterfaceModel>&) const
{
  occ::handle<TCollection_HAsciiString> res;

  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return res;
  DeclareAndCast(IGESGraph_DefinitionLevel, levelist, igesent->LevelList());
  int level = igesent->Level();
  if (levelist.IsNull() && level < 0)
    return res;

  if (level < 0)
    return new TCollection_HAsciiString("LEVEL LIST");
  char signature[30];
  Sprintf(signature, "%7d", level);
  return new TCollection_HAsciiString(signature);
}

void IGESSelect_CounterOfLevelNumber::PrintCount(Standard_OStream& S) const
{
  IFSelect_SignatureList::PrintCount(S);
  S << " Highest value : " << thehigh << std::endl;
  if (thenblists > 0)
    S << "REMARK for LEVEL LIST : Entities are counted in"
      << " <LEVEL LIST>\n, and in each Level value of their list" << std::endl;
}
