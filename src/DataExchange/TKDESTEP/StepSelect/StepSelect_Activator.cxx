

#include <IFSelect_SessionPilot.hpp>
#include <IFSelect_WorkSession.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Type.hpp>
#include <StepData_Plex.hpp>
#include <StepData_Simple.hpp>
#include <StepData_UndefinedEntity.hpp>
#include <StepSelect_Activator.hpp>
#include <StepSelect_FloatFormat.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepSelect_Activator, IFSelect_Activator)

static int THE_StepSelect_Activator_initActivator = 0;

StepSelect_Activator::StepSelect_Activator()
{
  if (THE_StepSelect_Activator_initActivator)
  {
    return;
  }

  THE_StepSelect_Activator_initActivator = 1;

  Add(1, "stepschema");
  AddSet(40, "floatformat");
}

IFSelect_ReturnStatus StepSelect_Activator::Do(const int                                 number,
                                               const occ::handle<IFSelect_SessionPilot>& pilot)
{
  int         argc = pilot->NbWords();
  const char* arg1 = pilot->Word(1).ToCString();
  const char* arg2 = pilot->Word(2).ToCString();

  switch (number)
  {

    case 1:
    {
      if (argc < 2)
      {
        std::cout << "Identify an entity" << std::endl;
        return IFSelect_RetError;
      }
      int num = pilot->Number(arg1);
      if (num <= 0)
      {
        std::cout << "Not an entity : " << arg2 << std::endl;
        return IFSelect_RetError;
      }
      occ::handle<Standard_Transient> ent = pilot->Session()->StartingEntity(num);
      DeclareAndCast(StepData_UndefinedEntity, und, ent);
      if (!und.IsNull())
      {
        std::cout << "Entity " << arg2 << " : No Binding known" << std::endl;
        return IFSelect_RetVoid;
      }
      DeclareAndCast(StepData_Simple, sim, ent);
      if (!sim.IsNull())
      {
        std::cout << "Entity " << arg2 << " : Late Binding" << std::endl;
        std::cout << "Simple Type : " << sim->StepType() << std::endl;
        return IFSelect_RetVoid;
      }
      DeclareAndCast(StepData_Plex, plx, ent);
      if (!plx.IsNull())
      {
        std::cout << "Entity " << arg2 << " : Late Binding" << std::endl;
        std::cout << "Complex Type" << std::endl;
      }

      std::cout << "Entity " << arg2 << " : Early Binding" << std::endl;
      std::cout << "CDL Type : " << ent->DynamicType()->Name() << std::endl;
      return IFSelect_RetVoid;
    }

    case 40:
    {
      char prem = ' ';
      if (argc < 2)
        prem = '?';
      else if (argc == 5)
      {
        std::cout << "floatformat tout court donne les formes admises" << std::endl;
        return IFSelect_RetError;
      }
      else
        prem = arg1[0];
      bool zerosup = false;
      int  digits  = 0;
      if (prem == 'N' || prem == 'n')
        zerosup = false;
      else if (prem == 'Z' || prem == 'z')
        zerosup = true;
      else if (prem >= 48 && prem <= 57)
        digits = atoi(arg1);
      else
      {
        std::cout << "floatformat digits, digits=nb de chiffres signifiants, ou\n"
                  << "floatformat NZ %mainformat [%rangeformat [Rmin Rmax]]\n"
                  << "  NZ : N ou n pour Non-zero-suppress, Z ou z pour zero-suppress\n"
                  << " %mainformat  : format principal type printf, ex,: %E\n"
                  << " + optionnel  : format secondaire (flottants autour de 1.) :\n"
                  << " %rangeformat Rmin Rmax : format type printf entre Rmin et Rmax\n"
                  << " %rangeformat tout seul : format type printf entre 0.1 et 1000.\n"
                  << std::flush;
        return (prem == '?' ? IFSelect_RetVoid : IFSelect_RetError);
      }
      double Rmin = 0., Rmax = 0.;
      if (argc > 4)
      {
        Rmin = Atof(pilot->Word(4).ToCString());
        Rmax = Atof(pilot->Word(5).ToCString());
        if (Rmin <= 0 || Rmax <= 0)
        {
          std::cout << "intervalle : donner reels > 0" << std::endl;
          return IFSelect_RetError;
        }
      }
      occ::handle<StepSelect_FloatFormat> fm = new StepSelect_FloatFormat;
      if (argc == 2)
        fm->SetDefault(digits);
      else
      {
        fm->SetZeroSuppress(zerosup);
        fm->SetFormat(arg2);
        if (argc == 4)
          fm->SetFormatForRange(pilot->Word(3).ToCString());
        else if (argc >= 6)
          fm->SetFormatForRange(pilot->Word(3).ToCString(), Rmin, Rmax);
        else
          fm->SetFormatForRange("");
      }
      return pilot->RecordItem(fm);
    }

    default:
      break;
  }
  return IFSelect_RetVoid;
}

const char* StepSelect_Activator::Help(const int number) const
{
  switch (number)
  {

    case 40:
      return "options... : cree FloatFormat ... floatformat tout court->help";
    default:
      break;
  }
  return "";
}
