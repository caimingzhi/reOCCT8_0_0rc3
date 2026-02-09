#include <QABugs.hpp>

#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <DBRep.hpp>
#include <AIS_InteractiveContext.hpp>
#include <AIS_Shape.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

#include <TopExp_Explorer.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS.hpp>
#include <BRepBndLib.hpp>
#include <gp_Pln.hpp>
#include <BRep_Tool.hpp>
#include <BRepAlgoAPI_Section.hpp>
#include <Standard_ErrorHandler.hpp>

#include <cstdio>

static int OCC527(Draw_Interpretor& di, int argc, const char** argv)
{
  try
  {
    OCC_CATCH_SIGNALS

    if (argc != 2)
    {
      di << "Usage : " << argv[0] << "OCC527 shape\n";
      return 1;
    }

    TopoDS_Shape aShape = DBRep::Get(argv[1]);
    if (aShape.IsNull())
    {
      di << "OCC527 FAULTY. Entry shape is NULL";
      return 0;
    }

    const double Zmin = -40.228173882121, Zmax = 96.408126285268, aStep = 1.0;
    char         str[100];
    str[0] = 0;
    Sprintf(str, "Test range: [%f, %f] with step %f\n", Zmin, Zmax, aStep);
    di << str;
    int             nbf = 0;
    TopExp_Explorer aExp1;
    for (aExp1.Init(aShape, TopAbs_FACE); aExp1.More(); aExp1.Next())
    {

      str[0] = 0;
      Sprintf(str, "Face #%d: \t", nbf++);
      di << str;
      TopoDS_Face aFace = TopoDS::Face(aExp1.Current());

      Bnd_Box aFaceBox;
      BRepBndLib::Add(aFace, aFaceBox);
      double X1, X2, Y1, Y2, Z1, Z2;
      aFaceBox.Get(X1, Y1, Z1, X2, Y2, Z2);

      double gmaxdist = 0.0, gzmax = Zmax;
      for (double zcur = Zmax; zcur > Zmin; zcur -= aStep)
      {

        if (zcur < Z1 || zcur > Z2)
          continue;

        gp_Pln pl(0, 0, 1, -zcur);

        di << "BRepAlgoAPI_Section aSection(aFace,pl,false)\n";
        BRepAlgoAPI_Section aSection(aFace, pl, false);
        aSection.Approximation(true);
        aSection.Build();
        bool IsDone = aSection.IsDone();

        if (IsDone)
        {
          const TopoDS_Shape& aResult = aSection.Shape();
          if (!aResult.IsNull())
          {
            double          lmaxdist = 0.0;
            TopExp_Explorer aExp2;
            for (aExp2.Init(aResult, TopAbs_VERTEX); aExp2.More(); aExp2.Next())
            {
              TopoDS_Vertex aV    = TopoDS::Vertex(aExp2.Current());
              double        toler = BRep_Tool::Tolerance(aV);
              double        dist  = pl.Distance(BRep_Tool::Pnt(aV));
              if (dist > lmaxdist)
                lmaxdist = dist;

              str[0] = 0;
              if (dist > toler)
                Sprintf(str, "Dist=%f, Toler=%f, Param=%f FAULTY\n", dist, toler, gzmax);
              else
                Sprintf(str, "Dist=%f, Toler=%f, Param=%f\n", dist, toler, gzmax);
              di << str;
            }
            if (lmaxdist > gmaxdist)
            {
              gmaxdist = lmaxdist;
              gzmax    = zcur;
            }
          }
        }
      }
    }
  }
  catch (Standard_Failure const&)
  {
    di << "OCC527 Exception \n";
    return 0;
  }

  return 0;
}

void QABugs::Commands_2(Draw_Interpretor& theCommands)
{
  const char* group = "QABugs";

  theCommands.Add("OCC527", "OCC527 shape", __FILE__, OCC527, group);
  return;
}
