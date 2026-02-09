#include <QADNaming.hpp>
#include <TDF_Label.hpp>
#include <Draw_Interpretor.hpp>
#include <TNaming_Builder.hpp>
#include <TopoDS_Shape.hpp>
#include <DBRep.hpp>

static int BuildNamedShape(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb >= 4)
  {
    TDF_Label aLabel;
    if (!QADNaming::Entry(arg, aLabel))
      return 1;
    char anEvolution = arg[3][0];
    int  a, anInc = (anEvolution == 'P' || anEvolution == 'D') ? 1 : 2;

    TNaming_Builder aBuilder(aLabel);
    TopoDS_Shape    aShape1, aShape2;

    for (a = 4; a < nb; a += anInc)
    {
      aShape1 = DBRep::Get(arg[a]);
      if (anInc == 2)
      {
        if (a == nb - 1)
        {
          di << "For this type of evolution number of shapes must be even\n";
          return 1;
        }
        aShape2 = DBRep::Get(arg[a + 1]);
      }

      switch (anEvolution)
      {
        case 'P':
          aBuilder.Generated(aShape1);
          break;
        case 'G':
          aBuilder.Generated(aShape1, aShape2);
          break;
        case 'M':
          aBuilder.Modify(aShape1, aShape2);
          break;
        case 'D':
          aBuilder.Delete(aShape1);
          break;
        case 'R':

          aBuilder.Modify(aShape1, aShape2);
          break;
        case 'S':
          aBuilder.Select(aShape1, aShape2);
          break;
        default:
          di << "Unknown evolution type\n";
          return 1;
      }
    }
  }
  else
  {
    di << "Usage: BuildName df entry evolution(P[RIMITIVE] G[ENERATED] M[ODIFY] D[ELETE] R[EPLACE] "
          "S[ELECTED]) [shape1 shape2 ...]\n";
    return 1;
  }
  return 0;
}

void QADNaming::BuilderCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "Naming builder commands";

  theCommands.Add("BuildNamedShape",
                  "BuildNamedShape df entry evolution(P[RIMITIVE] G[ENERATED] M[ODIFY] D[ELETE] "
                  "R[EPLACE] S[ELECTED]) [shape1 shape2 ...]",
                  __FILE__,
                  BuildNamedShape,
                  g);
}
