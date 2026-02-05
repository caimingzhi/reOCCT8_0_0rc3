#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAlgo.hpp>
#include <BRepCheck.hpp>
#include <BRepCheck_Analyzer.hpp>
#include <BRepCheck_Status.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <BRepCheck_Result.hpp>
#include <BRepCheck_Shell.hpp>
#include <BRepLib.hpp>
#include <BRepTools.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

//=================================================================================================

bool BRepAlgo::IsValid(const TopoDS_Shape& S)
{
  BRepCheck_Analyzer ana(S);
  return ana.IsValid();
}

//=================================================================================================

bool BRepAlgo::IsValid(const NCollection_List<TopoDS_Shape>& theArgs,
                       const TopoDS_Shape&                   theResult,
                       const bool                            closedSolid,
                       const bool                            GeomCtrl)
{
  if (theResult.IsNull())
    return true;
  bool validate = false;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> allFaces;
  TopExp_Explorer                                        tEx;
  NCollection_List<TopoDS_Shape>::Iterator               itLOS;
  for (itLOS.Initialize(theArgs); itLOS.More(); itLOS.Next())
  {
    if (itLOS.Value().IsSame(theResult))
    {
      validate = true;
      break;
    }
    for (tEx.Init(itLOS.Value(), TopAbs_FACE); tEx.More(); tEx.Next())
    {
      allFaces.Add(tEx.Current());
    }
  }

  TopoDS_Compound toCheck;

  if (allFaces.IsEmpty())
  {
    if (validate)
      return true;
    BRepCheck_Analyzer ana(theResult, GeomCtrl);
    if (!ana.IsValid())
      return false;
  }
  else if (!validate)
  {
    BRep_Builder bB;
    TopoDS_Face  curf;
    for (tEx.Init(theResult, TopAbs_FACE); tEx.More(); tEx.Next())
    {
      curf = TopoDS::Face(tEx.Current());
      if (!allFaces.Contains(curf))
      {
        if (toCheck.IsNull())
          bB.MakeCompound(toCheck);
        BRepTools::Update(curf);
        bB.Add(toCheck, curf);
      }
    }
    if (toCheck.IsNull())
    {
      validate = true;
    }
    else
    {
      BRepCheck_Analyzer ana(toCheck, true);
      if (!ana.IsValid())
      {

        // Check if the problem is not just BRepCheck_InvalidSameParameterFlag
        NCollection_List<BRepCheck_Status>::Iterator itl;
        BRepCheck_Status                             sta;
        for (tEx.Init(toCheck, TopAbs_FACE); tEx.More(); tEx.Next())
        {
          if (!ana.Result(tEx.Current()).IsNull())
          {
            for (itl.Initialize(ana.Result(tEx.Current())->Status()); itl.More(); itl.Next())
            {
              sta = itl.Value();
              // If a face is incorrect
              if (sta != BRepCheck_NoError)
              {
                NCollection_List<BRepCheck_Status>::Iterator ilt;
                TopExp_Explorer                              exp;
                for (exp.Init(tEx.Current(), TopAbs_EDGE); exp.More(); exp.Next())
                {
                  const occ::handle<BRepCheck_Result>& res = ana.Result(exp.Current());
                  for (res->InitContextIterator(); res->MoreShapeInContext();
                       res->NextShapeInContext())
                  {
                    if (res->ContextualShape().IsSame(tEx.Current()))
                    {
                      for (ilt.Initialize(res->StatusOnShape()); ilt.More(); ilt.Next())
                      {
                        sta = ilt.Value();
                        // If an edge is BRepCheck_InvalidSameParameterFlag or
                        // BRepCheck_InvalidSameRangeFlag, it is forced
                        if (sta == BRepCheck_InvalidSameParameterFlag
                            || sta == BRepCheck_InvalidSameRangeFlag)
                        {
                          bB.SameRange(TopoDS::Edge(exp.Current()), false);
                          bB.SameParameter(TopoDS::Edge(exp.Current()), false);
                          BRepLib::SameParameter(TopoDS::Edge(exp.Current()),
                                                 BRep_Tool::Tolerance(TopoDS::Edge(exp.Current())));
                          break;
                        }
                      }
                    }
                  }
                }
                break;
              }
            }
          }
        }
        // Remake control (there can be a problem of another type orb the one that cannot be
        // corrected
        ana.Init(toCheck, true);
        if (!ana.IsValid())
          return false;
      }
    }
  }

  occ::handle<BRepCheck_Shell> HR;
  for (tEx.Init(theResult, TopAbs_SHELL); tEx.More(); tEx.Next())
  {
    if (HR.IsNull())
      HR = new BRepCheck_Shell(TopoDS::Shell(tEx.Current()));
    else
      HR->Init(tEx.Current());
    if (HR->Status().First() != BRepCheck_NoError)
      return false;
    if (HR->Orientation(false) != BRepCheck_NoError)
      return false;
    if (closedSolid)
    {
      if (HR->Closed() != BRepCheck_NoError)
        return false;
    }
  }

  return true;
}

//=================================================================================================

bool BRepAlgo::IsTopologicallyValid(const TopoDS_Shape& S)
{
  //

  // if (getenv("DONT_SWITCH_IS_VALID") != NULL) {
  //   return true ;
  // }
  // else {
  BRepCheck_Analyzer ana(S, false);
  return ana.IsValid();

  // }
}
