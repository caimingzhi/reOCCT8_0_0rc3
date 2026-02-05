#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESDimen_FlagNote.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_FlagNote, IGESData_IGESEntity)

IGESDimen_FlagNote::IGESDimen_FlagNote() = default;

void IGESDimen_FlagNote::Init(
  const gp_XYZ&                                                               leftCorner,
  const double                                                                anAngle,
  const occ::handle<IGESDimen_GeneralNote>&                                   aNote,
  const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>& someLeaders)
{
  if (!someLeaders.IsNull())
    if (someLeaders->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDimen_FlagNote : Init");
  theLowerLeftcorner = leftCorner;
  theAngle           = anAngle;
  theNote            = aNote;
  theLeaders         = someLeaders;
  InitTypeAndForm(208, 0);
}

gp_Pnt IGESDimen_FlagNote::LowerLeftCorner() const
{
  gp_Pnt lowerleft(theLowerLeftcorner);
  return lowerleft;
}

gp_Pnt IGESDimen_FlagNote::TransformedLowerLeftCorner() const
{
  gp_XYZ tempXYZ = theLowerLeftcorner;
  if (HasTransf())
    Location().Transforms(tempXYZ);
  return gp_Pnt(tempXYZ);
}

double IGESDimen_FlagNote::Angle() const
{
  return theAngle;
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_FlagNote::Note() const
{
  return theNote;
}

int IGESDimen_FlagNote::NbLeaders() const
{
  return (theLeaders.IsNull() ? 0 : theLeaders->Length());
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_FlagNote::Leader(const int Index) const
{
  return theLeaders->Value(Index);
}

double IGESDimen_FlagNote::Height() const
{
  return (2 * CharacterHeight());
}

double IGESDimen_FlagNote::CharacterHeight() const
{
  double Max = theNote->BoxHeight(1);
  for (int i = 2; i <= theNote->NbStrings(); i++)
  {
    if (Max < theNote->BoxHeight(i))
      Max = theNote->BoxHeight(i);
  }
  return (Max);
}

double IGESDimen_FlagNote::Length() const
{
  return (TextWidth() + (0.4 * CharacterHeight()));
}

double IGESDimen_FlagNote::TextWidth() const
{
  double width = 0;
  for (int i = 1; i <= theNote->NbStrings(); i++)
    width += theNote->BoxWidth(i);
  return (width);
}

double IGESDimen_FlagNote::TipLength() const
{
  return (0.5 * (Height() / std::tan((35. / 180.) * M_PI)));
}
