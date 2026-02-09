#include <BinTools.hpp>
#include <BinTools_Curve2dSet.hpp>
#include <BinTools_ShapeSet.hpp>
#include <BinTools_SurfaceSet.hpp>
#include <BRep_CurveOnClosedSurface.hpp>
#include <BRep_CurveOnSurface.hpp>
#include <BRep_CurveRepresentation.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_PointRepresentation.hpp>
#include <NCollection_List.hpp>
#include <BRep_PointOnCurve.hpp>
#include <BRep_PointOnCurveOnSurface.hpp>
#include <BRep_PointOnSurface.hpp>
#include <BRep_Polygon3D.hpp>
#include <BRep_PolygonOnTriangulation.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_TFace.hpp>
#include <BRep_Tool.hpp>
#include <BRep_TVertex.hpp>
#include <BRepTools.hpp>
#include <Poly_Polygon3D.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <Message_ProgressRange.hpp>

#include <cstring>

BinTools_ShapeSet::BinTools_ShapeSet()

  = default;

BinTools_ShapeSet::~BinTools_ShapeSet() = default;

void BinTools_ShapeSet::Clear()
{
  mySurfaces.Clear();
  myCurves.Clear();
  myCurves2d.Clear();
  myPolygons3D.Clear();
  myPolygons2D.Clear();
  myNodes.Clear();
  myTriangulations.Clear();
  myShapes.Clear();
  myLocations.Clear();
}

int BinTools_ShapeSet::Add(const TopoDS_Shape& theShape)
{
  if (theShape.IsNull())
    return 0;
  myLocations.Add(theShape.Location());
  TopoDS_Shape aS2 = theShape;
  aS2.Location(TopLoc_Location());
  int anIndex = myShapes.FindIndex(aS2);
  if (anIndex == 0)
  {
    AddShape(aS2);
    for (TopoDS_Iterator its(aS2, false, false); its.More(); its.Next())
      Add(its.Value());
    anIndex = myShapes.Add(aS2);
  }
  return anIndex;
}

const TopoDS_Shape& BinTools_ShapeSet::Shape(const int theIndx)
{
  return myShapes(theIndx);
}

int BinTools_ShapeSet::Index(const TopoDS_Shape& theShape) const
{
  return myShapes.FindIndex(theShape);
}

const BinTools_LocationSet& BinTools_ShapeSet::Locations() const
{
  return myLocations;
}

BinTools_LocationSet& BinTools_ShapeSet::ChangeLocations()
{
  return myLocations;
}

void BinTools_ShapeSet::AddShape(const TopoDS_Shape& S)
{

  if (S.ShapeType() == TopAbs_VERTEX)
  {

    occ::handle<BRep_TVertex> TV = occ::down_cast<BRep_TVertex>(S.TShape());
    NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itrp(TV->Points());

    while (itrp.More())
    {
      const occ::handle<BRep_PointRepresentation>& PR = itrp.Value();

      if (PR->IsPointOnCurve())
      {
        myCurves.Add(PR->Curve());
      }

      else if (PR->IsPointOnCurveOnSurface())
      {
        myCurves2d.Add(PR->PCurve());
        mySurfaces.Add(PR->Surface());
      }

      else if (PR->IsPointOnSurface())
      {
        mySurfaces.Add(PR->Surface());
      }

      ChangeLocations().Add(PR->Location());
      itrp.Next();
    }
  }
  else if (S.ShapeType() == TopAbs_EDGE)
  {

    occ::handle<BRep_TEdge> TE = occ::down_cast<BRep_TEdge>(S.TShape());
    NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itrc(TE->Curves());

    while (itrc.More())
    {
      const occ::handle<BRep_CurveRepresentation>& CR = itrc.Value();
      if (CR->IsCurve3D())
      {
        if (!CR->Curve3D().IsNull())
        {
          myCurves.Add(CR->Curve3D());
          ChangeLocations().Add(CR->Location());
        }
      }
      else if (CR->IsCurveOnSurface())
      {
        mySurfaces.Add(CR->Surface());
        myCurves2d.Add(CR->PCurve());
        ChangeLocations().Add(CR->Location());
        if (CR->IsCurveOnClosedSurface())
          myCurves2d.Add(CR->PCurve2());
      }
      else if (CR->IsRegularity())
      {
        mySurfaces.Add(CR->Surface());
        ChangeLocations().Add(CR->Location());
        mySurfaces.Add(CR->Surface2());
        ChangeLocations().Add(CR->Location2());
      }
      else if (IsWithTriangles())
      {
        if (CR->IsPolygon3D())
        {
          if (!CR->Polygon3D().IsNull())
          {
            myPolygons3D.Add(CR->Polygon3D());
            ChangeLocations().Add(CR->Location());
          }
        }
        else if (CR->IsPolygonOnTriangulation())
        {

          myTriangulations.Add(CR->Triangulation(), false);

          myNodes.Add(CR->PolygonOnTriangulation());
          ChangeLocations().Add(CR->Location());
          if (CR->IsPolygonOnClosedTriangulation())
            myNodes.Add(CR->PolygonOnTriangulation2());
        }
        else if (CR->IsPolygonOnSurface())
        {
          mySurfaces.Add(CR->Surface());
          myPolygons2D.Add(CR->Polygon());
          ChangeLocations().Add(CR->Location());
          if (CR->IsPolygonOnClosedSurface())
            myPolygons2D.Add(CR->Polygon2());
        }
      }
      itrc.Next();
    }
  }

  else if (S.ShapeType() == TopAbs_FACE)
  {

    bool                    needNormals(IsWithNormals());
    occ::handle<BRep_TFace> TF = occ::down_cast<BRep_TFace>(S.TShape());
    if (!TF->Surface().IsNull())
    {
      mySurfaces.Add(TF->Surface());
    }
    else
    {
      needNormals = true;
    }
    if (IsWithTriangles() || TF->Surface().IsNull())
    {
      occ::handle<Poly_Triangulation> Tr = TF->Triangulation();
      if (!Tr.IsNull())
        myTriangulations.Add(Tr, needNormals);
    }

    ChangeLocations().Add(TF->Location());
  }
}

void BinTools_ShapeSet::WriteGeometry(Standard_OStream&            OS,
                                      const Message_ProgressRange& theRange) const
{
  Message_ProgressScope aPS(theRange, "Writing geometry", 6);
  myCurves2d.Write(OS, aPS.Next());
  if (!aPS.More())
    return;
  myCurves.Write(OS, aPS.Next());
  if (!aPS.More())
    return;
  WritePolygon3D(OS, aPS.Next());
  if (!aPS.More())
    return;
  WritePolygonOnTriangulation(OS, aPS.Next());
  if (!aPS.More())
    return;
  mySurfaces.Write(OS, aPS.Next());
  if (!aPS.More())
    return;
  WriteTriangulation(OS, aPS.Next());
}

void BinTools_ShapeSet::Write(Standard_OStream& OS, const Message_ProgressRange& theRange)
{

  OS << "\n" << THE_ASCII_VERSIONS[FormatNb()] << "\n";

  myLocations.Write(OS);

  Message_ProgressScope aPS(theRange, "Writing geometry", 2);

  WriteGeometry(OS, aPS.Next());
  if (!aPS.More())
    return;

  int                   i, nbShapes = myShapes.Extent();
  Message_ProgressScope aPSinner(aPS.Next(), "Writing shapes", nbShapes);
  OS << "\nTShapes " << nbShapes << "\n";

  for (i = 1; i <= nbShapes && aPSinner.More(); i++, aPSinner.Next())
  {

    const TopoDS_Shape& S = myShapes(i);

    OS << (uint8_t)S.ShapeType();

    WriteShape(S, OS);

    BinTools::PutBool(OS, S.Free());
    BinTools::PutBool(OS, S.Modified());
    BinTools::PutBool(OS, S.Checked());
    BinTools::PutBool(OS, S.Orientable());
    BinTools::PutBool(OS, S.Closed());
    BinTools::PutBool(OS, S.Infinite());
    BinTools::PutBool(OS, S.Convex());

    TopoDS_Iterator its(S, false, false);
    while (its.More())
    {
      Write(its.Value(), OS);
      its.Next();
    }
    Write(TopoDS_Shape(), OS);
  }
}

void BinTools_ShapeSet::Read(Standard_IStream& IS, const Message_ProgressRange& theRange)
{
  Clear();

  char vers[101];
  bool anIsSetFormat = false;
  do
  {
    IS.getline(vers, 100, '\n');

    size_t lv = strlen(vers);
    if (lv > 0)
    {
      for (lv--; lv > 0 && (vers[lv] == '\r' || vers[lv] == '\n'); lv--)
        vers[lv] = '\0';
    }

    for (int i = BinTools_FormatVersion_LOWER; i <= BinTools_FormatVersion_UPPER; ++i)
    {
      if (!strcmp(vers, THE_ASCII_VERSIONS[i]))
      {
        SetFormatNb(i);
        anIsSetFormat = true;
        break;
      }
    }
    if (anIsSetFormat)
    {
      break;
    }
  } while (!IS.fail());
  if (IS.fail())
  {
    std::cout << "BinTools_ShapeSet::Read: File was not written with this version of the topology"
              << std::endl;
    return;
  }

  myLocations.Read(IS);

  Message_ProgressScope aPSouter(theRange, "Reading", 2);
  ReadGeometry(IS, aPSouter.Next());
  if (!aPSouter.More())
    return;

  char buffer[255];
  IS >> buffer;
  if (IS.fail() || strcmp(buffer, "TShapes"))
  {
    Standard_SStream aMsg;
    aMsg << "BinTools_ShapeSet::Read: Not a TShape table" << std::endl;
    throw Standard_Failure(aMsg.str().c_str());
    return;
  }
  int nbShapes = 0;
  IS >> nbShapes;
  IS.get();
  Message_ProgressScope aPSinner(aPSouter.Next(), "Reading Shapes", nbShapes);
  for (int i = 1; i <= nbShapes && aPSinner.More(); i++, aPSinner.Next())
  {
    TopoDS_Shape     S;
    TopAbs_ShapeEnum T = (TopAbs_ShapeEnum)IS.get();
    ReadShape(T, IS, S);
    ReadFlagsAndSubs(S, T, IS, nbShapes);
    myShapes.Add(S);
  }
}

void BinTools_ShapeSet::Write(const TopoDS_Shape& S, Standard_OStream& OS)
{
  if (S.IsNull())

    OS << '*';
  else
  {

    OS << (uint8_t)S.Orientation();
    BinTools::PutInteger(OS,
                         myShapes.Extent() - myShapes.FindIndex(S.Located(TopLoc_Location())) + 1);
    BinTools::PutInteger(OS, Locations().Index(S.Location()));
  }
}

void BinTools_ShapeSet::ReadFlagsAndSubs(TopoDS_Shape&          S,
                                         const TopAbs_ShapeEnum T,
                                         Standard_IStream&      IS,
                                         const int              nbShapes)
{

  bool aFree, aMod, aChecked, anOrient, aClosed, anInf, aConv;
  BinTools::GetBool(IS, aFree);
  BinTools::GetBool(IS, aMod);
  BinTools::GetBool(IS, aChecked);
  BinTools::GetBool(IS, anOrient);
  BinTools::GetBool(IS, aClosed);
  BinTools::GetBool(IS, anInf);
  BinTools::GetBool(IS, aConv);

  TopoDS_Shape SS;
  do
  {
    ReadSubs(SS, IS, nbShapes);
    if (!SS.IsNull())
      AddShapes(S, SS);
  } while (!SS.IsNull());

  S.Free(aFree);
  S.Modified(aMod);
  if (FormatNb() == BinTools_FormatVersion_VERSION_1)
  {
    aChecked = false;
  }
  S.Checked(aChecked);
  S.Orientable(anOrient);
  S.Closed(aClosed);
  S.Infinite(anInf);
  S.Convex(aConv);

  if (FormatNb() == BinTools_FormatVersion_VERSION_1)
    if (T == TopAbs_FACE)
    {
      const TopoDS_Face& F = TopoDS::Face(S);
      BRepTools::Update(F);
    }
}

void BinTools_ShapeSet::ReadSubs(TopoDS_Shape& S, Standard_IStream& IS, const int nbshapes)
{
  char aChar = '\0';
  IS >> aChar;
  if (aChar == '*')
    S = TopoDS_Shape();
  else
  {
    TopAbs_Orientation anOrient;
    anOrient = (TopAbs_Orientation)aChar;
    int anIndx;
    BinTools::GetInteger(IS, anIndx);
    S = Shape(nbshapes - anIndx + 1);
    S.Orientation(anOrient);

    int l;
    BinTools::GetInteger(IS, l);
    S.Location(myLocations.Location(l), false);
  }
}

void BinTools_ShapeSet::ReadGeometry(Standard_IStream& IS, const Message_ProgressRange& theRange)
{

  Message_ProgressScope aPS(theRange, "Reading geometry", 6);
  myCurves2d.Read(IS, aPS.Next());
  if (!aPS.More())
    return;

  myCurves.Read(IS, aPS.Next());
  if (!aPS.More())
    return;

  ReadPolygon3D(IS, aPS.Next());
  if (!aPS.More())
    return;

  ReadPolygonOnTriangulation(IS, aPS.Next());
  if (!aPS.More())
    return;

  mySurfaces.Read(IS, aPS.Next());
  if (!aPS.More())
    return;

  ReadTriangulation(IS, aPS.Next());
}

void BinTools_ShapeSet::WriteShape(const TopoDS_Shape& S, Standard_OStream& OS) const
{

  try
  {
    OCC_CATCH_SIGNALS
    if (S.ShapeType() == TopAbs_VERTEX)
    {

      TopoDS_Vertex V = TopoDS::Vertex(S);
      BinTools::PutReal(OS, BRep_Tool::Tolerance(V));
      gp_Pnt p = BRep_Tool::Pnt(V);
      OS << p;
#ifdef OCCT_DEBUG_POS
      std::streamoff aPos;
#endif
      occ::handle<BRep_TVertex> TV = occ::down_cast<BRep_TVertex>(S.TShape());
      NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itrp(TV->Points());
      while (itrp.More())
      {
        const occ::handle<BRep_PointRepresentation>& PR = itrp.Value();

        if (PR->IsPointOnCurve())
        {
#ifdef OCCT_DEBUG_POS
          aPos = OS.tellp();
#endif
          OS << (uint8_t)1;
          BinTools::PutReal(OS, PR->Parameter());
          BinTools::PutInteger(OS, myCurves.Index(PR->Curve()));
        }

        else if (PR->IsPointOnCurveOnSurface())
        {
#ifdef OCCT_DEBUG_POS
          aPos = OS.tellp();
#endif
          OS << (uint8_t)2;
          BinTools::PutReal(OS, PR->Parameter());
          BinTools::PutInteger(OS, myCurves2d.Index(PR->PCurve()));
          BinTools::PutInteger(OS, mySurfaces.Index(PR->Surface()));
        }

        else if (PR->IsPointOnSurface())
        {
#ifdef OCCT_DEBUG_POS
          aPos = OS.tellp();
#endif
          OS << (uint8_t)3;
          BinTools::PutReal(OS, PR->Parameter2());
          BinTools::PutReal(OS, PR->Parameter());
          BinTools::PutInteger(OS, mySurfaces.Index(PR->Surface()));
        }
        BinTools::PutInteger(OS, Locations().Index(PR->Location()));
        itrp.Next();
      }

      OS.put((uint8_t)0);
    }

    else if (S.ShapeType() == TopAbs_EDGE)
    {

      occ::handle<BRep_TEdge> TE = occ::down_cast<BRep_TEdge>(S.TShape());

      BinTools::PutReal(OS, TE->Tolerance());

      bool aVal = TE->SameParameter();
      BinTools::PutBool(OS, aVal);
      aVal = TE->SameRange();
      BinTools::PutBool(OS, aVal);
      aVal = TE->Degenerated();
      BinTools::PutBool(OS, aVal);

      double                                                            first, last;
      NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itrc = TE->Curves();
      while (itrc.More())
      {
        const occ::handle<BRep_CurveRepresentation>& CR = itrc.Value();
        if (CR->IsCurve3D())
        {
          if (!CR->Curve3D().IsNull())
          {
            occ::handle<BRep_GCurve> GC = occ::down_cast<BRep_GCurve>(itrc.Value());
            GC->Range(first, last);
            OS << (uint8_t)1;
            BinTools::PutInteger(OS, myCurves.Index(CR->Curve3D()));
            BinTools::PutInteger(OS, Locations().Index(CR->Location()));
            BinTools::PutReal(OS, first);
            BinTools::PutReal(OS, last);
          }
        }
        else if (CR->IsCurveOnSurface())
        {
          occ::handle<BRep_GCurve> GC = occ::down_cast<BRep_GCurve>(itrc.Value());
          GC->Range(first, last);
          if (!CR->IsCurveOnClosedSurface())

            OS << (uint8_t)2;
          else

            OS << (uint8_t)3;
          BinTools::PutInteger(OS, myCurves2d.Index(CR->PCurve()));
          if (CR->IsCurveOnClosedSurface())
          {
            BinTools::PutInteger(OS, myCurves2d.Index(CR->PCurve2()));
            OS << (uint8_t)CR->Continuity();
          }
          BinTools::PutInteger(OS, mySurfaces.Index(CR->Surface()));
          BinTools::PutInteger(OS, Locations().Index(CR->Location()));
          BinTools::PutReal(OS, first);
          BinTools::PutReal(OS, last);

          if (FormatNb() == BinTools_FormatVersion_VERSION_2
              || FormatNb() == BinTools_FormatVersion_VERSION_3)
          {
            gp_Pnt2d Pf, Pl;
            if (CR->IsCurveOnClosedSurface())
            {
              occ::handle<BRep_CurveOnClosedSurface> COCS =
                occ::down_cast<BRep_CurveOnClosedSurface>(CR);
              COCS->UVPoints2(Pf, Pl);
            }
            else
            {
              occ::handle<BRep_CurveOnSurface> COS = occ::down_cast<BRep_CurveOnSurface>(CR);
              COS->UVPoints(Pf, Pl);
            }
            BinTools::PutReal(OS, Pf.X());
            BinTools::PutReal(OS, Pf.Y());
            BinTools::PutReal(OS, Pl.X());
            BinTools::PutReal(OS, Pl.Y());
          }
        }
        else if (CR->IsRegularity())
        {

          OS << (uint8_t)4;
          OS << (uint8_t)CR->Continuity();
          BinTools::PutInteger(OS, mySurfaces.Index(CR->Surface()));
          BinTools::PutInteger(OS, Locations().Index(CR->Location()));
          BinTools::PutInteger(OS, mySurfaces.Index(CR->Surface2()));
          BinTools::PutInteger(OS, Locations().Index(CR->Location2()));
        }

        else if (IsWithTriangles())
        {
          if (CR->IsPolygon3D())
          {
            occ::handle<BRep_Polygon3D> GC = occ::down_cast<BRep_Polygon3D>(itrc.Value());
            if (!GC->Polygon3D().IsNull())
            {

              OS << (uint8_t)5;
              BinTools::PutInteger(OS, myPolygons3D.FindIndex(CR->Polygon3D()));
              BinTools::PutInteger(OS, Locations().Index(CR->Location()));
            }
          }
          else if (CR->IsPolygonOnTriangulation())
          {
            occ::handle<BRep_PolygonOnTriangulation> PT =
              occ::down_cast<BRep_PolygonOnTriangulation>(itrc.Value());
            if (!CR->IsPolygonOnClosedTriangulation())

              OS << (uint8_t)6;
            else

              OS << (uint8_t)7;
            BinTools::PutInteger(OS, myNodes.FindIndex(PT->PolygonOnTriangulation()));

            if (CR->IsPolygonOnClosedTriangulation())
            {
              BinTools::PutInteger(OS, myNodes.FindIndex(PT->PolygonOnTriangulation2()));
            }
            BinTools::PutInteger(OS, myTriangulations.FindIndex(PT->Triangulation()));
            BinTools::PutInteger(OS, Locations().Index(CR->Location()));
          }
        }

        itrc.Next();
      }

      OS << (uint8_t)0;
    }

    else if (S.ShapeType() == TopAbs_FACE)
    {

      occ::handle<BRep_TFace> TF = occ::down_cast<BRep_TFace>(S.TShape());
      const TopoDS_Face&      F  = TopoDS::Face(S);

      bool aNatRes = BRep_Tool::NaturalRestriction(F);
      BinTools::PutBool(OS, aNatRes);
      BinTools::PutReal(OS, TF->Tolerance());
      BinTools::PutInteger(OS, !TF->Surface().IsNull() ? mySurfaces.Index(TF->Surface()) : 0);
      BinTools::PutInteger(OS, Locations().Index(TF->Location()));

      if (IsWithTriangles() || TF->Surface().IsNull())
      {
        if (!(TF->Triangulation()).IsNull())
        {
          OS << (uint8_t)2;

          BinTools::PutInteger(OS, myTriangulations.FindIndex(TF->Triangulation()));
        }
        else
          OS << (uint8_t)1;
      }
      else
        OS << (uint8_t)0;
    }
  }
  catch (Standard_Failure const& anException)
  {
    Standard_SStream aMsg;
    aMsg << "EXCEPTION in BinTools_ShapeSet::WriteGeometry(S,OS)" << std::endl;
    aMsg << anException << std::endl;
    throw Standard_Failure(aMsg.str().c_str());
  }
}

void BinTools_ShapeSet::ReadShape(const TopAbs_ShapeEnum T, Standard_IStream& IS, TopoDS_Shape& S)
{

  int           val, c, pc, pc2 = 0, s, s2, l, l2, t, pt, pt2 = 0;
  double        tol, X, Y, Z, first, last, p1 = 0., p2;
  double        PfX, PfY, PlX, PlY;
  gp_Pnt2d      aPf, aPl;
  bool          closed, bval;
  GeomAbs_Shape reg = GeomAbs_C0;
  try
  {
    OCC_CATCH_SIGNALS
    switch (T)
    {

      case TopAbs_VERTEX:
      {
        TopoDS_Vertex& V = TopoDS::Vertex(S);

        BinTools::GetReal(IS, tol);
        BinTools::GetReal(IS, X);
        BinTools::GetReal(IS, Y);
        BinTools::GetReal(IS, Z);
        gp_Pnt aPnt(X, Y, Z);
        myBuilder.MakeVertex(V, aPnt, tol);
        occ::handle<BRep_TVertex> TV = occ::down_cast<BRep_TVertex>(V.TShape());

        NCollection_List<occ::handle<BRep_PointRepresentation>>& lpr = TV->ChangePoints();
        TopLoc_Location                                          L;
        do
        {
          if (FormatNb() == BinTools_FormatVersion_VERSION_3)
          {
            val = (int)IS.get();
            if (val > 0 && val <= 3)
              BinTools::GetReal(IS, p1);
          }
          else
          {
            std::streampos aPos = IS.tellg();
            BinTools::GetReal(IS, p1);
            val = (int)IS.get();
#ifdef OCCT_DEBUG
            std::cout << "\nVal = " << val << std::endl;
#endif
            if (val != 1 && val != 2 && val != 3)
            {
              IS.seekg(aPos);
              val = (int)IS.get();
              if (val > 0 && val <= 3)
                BinTools::GetReal(IS, p1);
            }
          }
          occ::handle<BRep_PointRepresentation> PR;
          switch (val)
          {
            case 0:
              break;

            case 1:
            {
              BinTools::GetInteger(IS, c);
              if (myCurves.Curve(c).IsNull())
                break;
              occ::handle<BRep_PointOnCurve> POC = new BRep_PointOnCurve(p1, myCurves.Curve(c), L);
              PR                                 = POC;
            }
            break;

            case 2:
            {
              BinTools::GetInteger(IS, pc);
              BinTools::GetInteger(IS, s);
              if (myCurves2d.Curve2d(pc).IsNull() || mySurfaces.Surface(s).IsNull())
                break;

              occ::handle<BRep_PointOnCurveOnSurface> POC =
                new BRep_PointOnCurveOnSurface(p1,
                                               myCurves2d.Curve2d(pc),
                                               mySurfaces.Surface(s),
                                               L);
              PR = POC;
            }
            break;

            case 3:
            {
              BinTools::GetReal(IS, p2);
              BinTools::GetInteger(IS, s);
              if (mySurfaces.Surface(s).IsNull())
                break;

              occ::handle<BRep_PointOnSurface> POC =
                new BRep_PointOnSurface(p1, p2, mySurfaces.Surface(s), L);
              PR = POC;
            }
            break;

            default:
            {
              Standard_SStream aMsg;
              aMsg << "BinTools_SurfaceSet::ReadGeometry: UnExpected BRep_PointRepresentation = "
                   << val << std::endl;
              throw Standard_Failure(aMsg.str().c_str());
            }
          }

          if (val > 0)
          {
            BinTools::GetInteger(IS, l);

            if (!PR.IsNull())
            {
              PR->Location(Locations().Location(l));
              lpr.Append(PR);
            }
          }
        } while (val > 0);
      }
      break;

      case TopAbs_EDGE:

      {
        TopoDS_Edge& E = TopoDS::Edge(S);

        myBuilder.MakeEdge(E);

        BinTools::GetReal(IS, tol);
        BinTools::GetBool(IS, bval);
        myBuilder.SameParameter(E, bval);

        BinTools::GetBool(IS, bval);
        myBuilder.SameRange(E, bval);

        BinTools::GetBool(IS, bval);
        myBuilder.Degenerated(E, bval);

        do
        {
          val = (int)IS.get();

          switch (val)
          {
            case 0:
              break;

            case 1:
              BinTools::GetInteger(IS, c);
              BinTools::GetInteger(IS, l);
              if (!myCurves.Curve(c).IsNull())
              {
                myBuilder.UpdateEdge(E, myCurves.Curve(c), Locations().Location(l), tol);
              }
              BinTools::GetReal(IS, first);
              BinTools::GetReal(IS, last);
              if (!myCurves.Curve(c).IsNull())
              {
                bool Only3d = true;
                myBuilder.Range(E, first, last, Only3d);
              }
              break;

            case 2:
            case 3:
              closed = (val == 3);
              BinTools::GetInteger(IS, pc);
              if (closed)
              {
                BinTools::GetInteger(IS, pc2);
                reg = (GeomAbs_Shape)IS.get();
              }

              BinTools::GetInteger(IS, s);
              BinTools::GetInteger(IS, l);

              BinTools::GetReal(IS, first);
              BinTools::GetReal(IS, last);

              if (FormatNb() == BinTools_FormatVersion_VERSION_2
                  || FormatNb() == BinTools_FormatVersion_VERSION_3)
              {
                BinTools::GetReal(IS, PfX);
                BinTools::GetReal(IS, PfY);
                BinTools::GetReal(IS, PlX);
                BinTools::GetReal(IS, PlY);
                aPf = gp_Pnt2d(PfX, PfY);
                aPl = gp_Pnt2d(PlX, PlY);
              }

              if (myCurves2d.Curve2d(pc).IsNull() || (closed && myCurves2d.Curve2d(pc2).IsNull())
                  || mySurfaces.Surface(s).IsNull())
                break;

              if (closed)
              {
                if (FormatNb() == BinTools_FormatVersion_VERSION_2
                    || FormatNb() == BinTools_FormatVersion_VERSION_3)
                {
                  myBuilder.UpdateEdge(E,
                                       myCurves2d.Curve2d(pc),
                                       myCurves2d.Curve2d(pc2),
                                       mySurfaces.Surface(s),
                                       Locations().Location(l),
                                       tol,
                                       aPf,
                                       aPl);
                }
                else
                {
                  myBuilder.UpdateEdge(E,
                                       myCurves2d.Curve2d(pc),
                                       myCurves2d.Curve2d(pc2),
                                       mySurfaces.Surface(s),
                                       Locations().Location(l),
                                       tol);
                }

                myBuilder.Continuity(E,
                                     mySurfaces.Surface(s),
                                     mySurfaces.Surface(s),
                                     Locations().Location(l),
                                     Locations().Location(l),
                                     reg);
              }
              else
              {
                if (FormatNb() == BinTools_FormatVersion_VERSION_2
                    || FormatNb() == BinTools_FormatVersion_VERSION_3)
                {
                  myBuilder.UpdateEdge(E,
                                       myCurves2d.Curve2d(pc),
                                       mySurfaces.Surface(s),
                                       Locations().Location(l),
                                       tol,
                                       aPf,
                                       aPl);
                }
                else
                {
                  myBuilder.UpdateEdge(E,
                                       myCurves2d.Curve2d(pc),
                                       mySurfaces.Surface(s),
                                       Locations().Location(l),
                                       tol);
                }
              }
              myBuilder.Range(E, mySurfaces.Surface(s), Locations().Location(l), first, last);
              break;

            case 4:
              reg = (GeomAbs_Shape)IS.get();
              BinTools::GetInteger(IS, s);
              BinTools::GetInteger(IS, l);
              BinTools::GetInteger(IS, s2);
              BinTools::GetInteger(IS, l2);
              if (mySurfaces.Surface(s).IsNull() || mySurfaces.Surface(s2).IsNull())
                break;
              myBuilder.Continuity(E,
                                   mySurfaces.Surface(s),
                                   mySurfaces.Surface(s2),
                                   Locations().Location(l),
                                   Locations().Location(l2),
                                   reg);
              break;

            case 5:
              BinTools::GetInteger(IS, c);
              BinTools::GetInteger(IS, l);

              myBuilder.UpdateEdge(E, myPolygons3D(c), Locations().Location(l));
              break;

            case 6:
            case 7:
              closed = (val == 7);
              BinTools::GetInteger(IS, pt);
              if (closed)
                BinTools::GetInteger(IS, pt2);

              BinTools::GetInteger(IS, t);
              BinTools::GetInteger(IS, l);
              if (closed)
              {
                myBuilder.UpdateEdge(E,
                                     myNodes(pt),
                                     myNodes(pt2),
                                     myTriangulations.FindKey(t),
                                     Locations().Location(l));
              }
              else
              {
                myBuilder.UpdateEdge(E,
                                     myNodes(pt),
                                     myTriangulations.FindKey(t),
                                     Locations().Location(l));
              }

              break;
            default:
            {
              Standard_SStream aMsg;
              aMsg << "Unexpected Curve Representation =" << val << std::endl;
              throw Standard_Failure(aMsg.str().c_str());
            }
          }
        } while (val > 0);
      }
      break;

      case TopAbs_WIRE:
        myBuilder.MakeWire(TopoDS::Wire(S));
        break;

      case TopAbs_FACE:
      {

        TopoDS_Face& F = TopoDS::Face(S);
        myBuilder.MakeFace(F);
        BinTools::GetBool(IS, bval);
        BinTools::GetReal(IS, tol);
        BinTools::GetInteger(IS, s);
        BinTools::GetInteger(IS, l);
        myBuilder.UpdateFace(F,
                             s > 0 ? mySurfaces.Surface(s) : occ::handle<Geom_Surface>(),
                             Locations().Location(l),
                             tol);
        myBuilder.NaturalRestriction(F, bval);

        uint8_t aByte = (uint8_t)IS.get();

        if (aByte == 2)
        {
          BinTools::GetInteger(IS, s);
          myBuilder.UpdateFace(TopoDS::Face(S), myTriangulations.FindKey(s));
        }
      }
      break;

      case TopAbs_SHELL:
        myBuilder.MakeShell(TopoDS::Shell(S));
        break;

      case TopAbs_SOLID:
        myBuilder.MakeSolid(TopoDS::Solid(S));
        break;

      case TopAbs_COMPSOLID:
        myBuilder.MakeCompSolid(TopoDS::CompSolid(S));
        break;

      case TopAbs_COMPOUND:
        myBuilder.MakeCompound(TopoDS::Compound(S));
        break;

      default:
      {
        Standard_SStream aMsg;
        aMsg << "Unexpected topology type = " << T << std::endl;
        throw Standard_Failure(aMsg.str().c_str());
        break;
      }
    }
  }
  catch (Standard_Failure const& anException)
  {
    Standard_SStream aMsg;
    aMsg << "EXCEPTION in BinTools_ShapeSet::ReadGeometry(S,OS)" << std::endl;
    aMsg << anException << std::endl;
    throw Standard_Failure(aMsg.str().c_str());
  }
}

void BinTools_ShapeSet::AddShapes(TopoDS_Shape& S1, const TopoDS_Shape& S2)
{
  myBuilder.Add(S1, S2);
}

void BinTools_ShapeSet::WritePolygonOnTriangulation(Standard_OStream&            OS,
                                                    const Message_ProgressRange& theRange) const
{
  const int aNbPol = myNodes.Extent();
  OS << "PolygonOnTriangulations " << aNbPol << "\n";
  try
  {
    OCC_CATCH_SIGNALS
    Message_ProgressScope aPS(theRange, "Writing polygons on triangulation", aNbPol);
    for (int aPolIter = 1; aPolIter <= aNbPol && aPS.More(); ++aPolIter, aPS.Next())
    {
      const occ::handle<Poly_PolygonOnTriangulation>& aPoly  = myNodes.FindKey(aPolIter);
      const NCollection_Array1<int>&                  aNodes = aPoly->Nodes();
      BinTools::PutInteger(OS, aNodes.Length());
      for (int aNodeIter = 1; aNodeIter <= aNodes.Length(); ++aNodeIter)
      {
        BinTools::PutInteger(OS, aNodes.Value(aNodeIter));
      }

      BinTools::PutReal(OS, aPoly->Deflection());

      if (const occ::handle<NCollection_HArray1<double>>& aParam = aPoly->Parameters())
      {
        BinTools::PutBool(OS, true);
        for (int aNodeIter = 1; aNodeIter <= aParam->Length(); ++aNodeIter)
        {
          BinTools::PutReal(OS, aParam->Value(aNodeIter));
        }
      }
      else
      {
        BinTools::PutBool(OS, false);
      }
    }
  }
  catch (Standard_Failure const& anException)
  {
    Standard_SStream aMsg;
    aMsg << "EXCEPTION in BinTools_ShapeSet::WritePolygonOnTriangulation(..)\n"
         << anException << "\n";
    throw Standard_Failure(aMsg.str().c_str());
  }
}

void BinTools_ShapeSet::ReadPolygonOnTriangulation(Standard_IStream&            IS,
                                                   const Message_ProgressRange& theRange)
{
  char aHeader[255];
  IS >> aHeader;
  if (IS.fail() || (strstr(aHeader, "PolygonOnTriangulations") == nullptr))
  {
    throw Standard_Failure(
      "BinTools_ShapeSet::ReadPolygonOnTriangulation: Not a PolygonOnTriangulation section");
  }

  int aNbPol = 0;
  IS >> aNbPol;
  IS.get();
  try
  {
    OCC_CATCH_SIGNALS
    Message_ProgressScope aPS(theRange, "Reading Polygones on triangulation", aNbPol);
    for (int aPolIter = 1; aPolIter <= aNbPol && aPS.More(); ++aPolIter, aPS.Next())
    {
      int aNbNodes = 0;
      BinTools::GetInteger(IS, aNbNodes);
      occ::handle<Poly_PolygonOnTriangulation> aPoly =
        new Poly_PolygonOnTriangulation(aNbNodes, false);
      for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
      {
        int aNode = 0;
        BinTools::GetInteger(IS, aNode);
        aPoly->SetNode(aNodeIter, aNode);
      }

      double aDefl = 0.0;
      BinTools::GetReal(IS, aDefl);
      aPoly->Deflection(aDefl);

      bool hasParameters = false;
      BinTools::GetBool(IS, hasParameters);
      if (hasParameters)
      {
        occ::handle<NCollection_HArray1<double>> aParams =
          new NCollection_HArray1<double>(1, aNbNodes);
        for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
        {
          BinTools::GetReal(IS, aParams->ChangeValue(aNodeIter));
        }
        aPoly->SetParameters(aParams);
      }
      myNodes.Add(aPoly);
    }
  }
  catch (Standard_Failure const& anException)
  {
    Standard_SStream aMsg;
    aMsg << "EXCEPTION in BinTools_ShapeSet::ReadPolygonOnTriangulation(..)\n"
         << anException << "\n";
    throw Standard_Failure(aMsg.str().c_str());
  }
}

void BinTools_ShapeSet::WritePolygon3D(Standard_OStream&            OS,
                                       const Message_ProgressRange& theRange) const
{
  const int aNbPol = myPolygons3D.Extent();
  OS << "Polygon3D " << aNbPol << "\n";
  try
  {
    OCC_CATCH_SIGNALS
    Message_ProgressScope aPS(theRange, "Writing polygons 3D", aNbPol);
    for (int aPolIter = 1; aPolIter <= aNbPol && aPS.More(); ++aPolIter, aPS.Next())
    {
      const occ::handle<Poly_Polygon3D>& aPoly = myPolygons3D.FindKey(aPolIter);
      BinTools::PutInteger(OS, aPoly->NbNodes());
      BinTools::PutBool(OS, aPoly->HasParameters());

      BinTools::PutReal(OS, aPoly->Deflection());

      const int                         aNbNodes = aPoly->NbNodes();
      const NCollection_Array1<gp_Pnt>& aNodes   = aPoly->Nodes();
      for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
      {
        const gp_Pnt& aPnt = aNodes.Value(aNodeIter);
        BinTools::PutReal(OS, aPnt.X());
        BinTools::PutReal(OS, aPnt.Y());
        BinTools::PutReal(OS, aPnt.Z());
      }
      if (aPoly->HasParameters())
      {
        const NCollection_Array1<double>& aParam = aPoly->Parameters();
        for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
        {
          BinTools::PutReal(OS, aParam.Value(aNodeIter));
        }
      }
    }
  }
  catch (Standard_Failure const& anException)
  {
    Standard_SStream aMsg;
    aMsg << "EXCEPTION in BinTools_ShapeSet::WritePolygon3D(..)\n" << anException << "\n";
    throw Standard_Failure(aMsg.str().c_str());
  }
}

void BinTools_ShapeSet::ReadPolygon3D(Standard_IStream& IS, const Message_ProgressRange& theRange)
{
  char aHeader[255];
  IS >> aHeader;

  if (IS.fail() || strstr(aHeader, "Polygon3D") == nullptr)
  {
#ifdef OCCT_DEBUG
    std::cout << "Buffer: " << aHeader << std::endl;
#endif
    throw Standard_Failure("BinTools_ShapeSet::ReadPolygon3D: Not a Polygon3D section");
  }

  int aNbPol = 0;
  IS >> aNbPol;
  IS.get();
  try
  {
    OCC_CATCH_SIGNALS
    Message_ProgressScope aPS(theRange, "Reading polygones 3D", aNbPol);
    for (int aPolIter = 1; aPolIter <= aNbPol && aPS.More(); ++aPolIter, aPS.Next())
    {
      int    aNbNodes      = 0;
      bool   hasParameters = false;
      double aDefl         = 0.0;
      BinTools::GetInteger(IS, aNbNodes);
      BinTools::GetBool(IS, hasParameters);
      BinTools::GetReal(IS, aDefl);

      occ::handle<Poly_Polygon3D> aPoly = new Poly_Polygon3D(aNbNodes, hasParameters);
      aPoly->Deflection(aDefl);

      NCollection_Array1<gp_Pnt>& aNodes = aPoly->ChangeNodes();
      for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
      {
        gp_XYZ& aPnt = aNodes.ChangeValue(aNodeIter).ChangeCoord();
        BinTools::GetReal(IS, aPnt.ChangeCoord(1));
        BinTools::GetReal(IS, aPnt.ChangeCoord(2));
        BinTools::GetReal(IS, aPnt.ChangeCoord(3));
      }
      if (hasParameters)
      {
        NCollection_Array1<double>& aParam = aPoly->ChangeParameters();
        for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
        {
          BinTools::GetReal(IS, aParam.ChangeValue(aNodeIter));
        }
      }

      myPolygons3D.Add(aPoly);
    }
  }
  catch (Standard_Failure const& anException)
  {
    Standard_SStream aMsg;
    aMsg << "EXCEPTION in BinTools_ShapeSet::ReadPolygon3D(..)\n" << anException << "\n";
    throw Standard_Failure(aMsg.str().c_str());
  }
}

void BinTools_ShapeSet::WriteTriangulation(Standard_OStream&            OS,
                                           const Message_ProgressRange& theRange) const
{
  const int aNbTriangulations = myTriangulations.Extent();
  OS << "Triangulations " << aNbTriangulations << "\n";

  try
  {
    OCC_CATCH_SIGNALS
    Message_ProgressScope aPS(theRange, "Writing triangulation", aNbTriangulations);
    for (int aTriangulationIter = 1; aTriangulationIter <= aNbTriangulations && aPS.More();
         ++aTriangulationIter, aPS.Next())
    {
      const occ::handle<Poly_Triangulation>& aTriangulation =
        myTriangulations.FindKey(aTriangulationIter);
      bool      NeedToWriteNormals = myTriangulations.FindFromIndex(aTriangulationIter);
      const int aNbNodes           = aTriangulation->NbNodes();
      const int aNbTriangles       = aTriangulation->NbTriangles();
      BinTools::PutInteger(OS, aNbNodes);
      BinTools::PutInteger(OS, aNbTriangles);
      BinTools::PutBool(OS, aTriangulation->HasUVNodes());
      if (FormatNb() >= BinTools_FormatVersion_VERSION_4)
      {
        BinTools::PutBool(OS, aTriangulation->HasNormals() && NeedToWriteNormals);
      }
      BinTools::PutReal(OS, aTriangulation->Deflection());

      for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
      {
        const gp_Pnt aPnt = aTriangulation->Node(aNodeIter);
        BinTools::PutReal(OS, aPnt.X());
        BinTools::PutReal(OS, aPnt.Y());
        BinTools::PutReal(OS, aPnt.Z());
      }

      if (aTriangulation->HasUVNodes())
      {
        for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
        {
          const gp_Pnt2d aUV = aTriangulation->UVNode(aNodeIter);
          BinTools::PutReal(OS, aUV.X());
          BinTools::PutReal(OS, aUV.Y());
        }
      }

      for (int aTriIter = 1; aTriIter <= aNbTriangles; ++aTriIter)
      {
        const Poly_Triangle aTri = aTriangulation->Triangle(aTriIter);
        BinTools::PutInteger(OS, aTri.Value(1));
        BinTools::PutInteger(OS, aTri.Value(2));
        BinTools::PutInteger(OS, aTri.Value(3));
      }

      if (FormatNb() >= BinTools_FormatVersion_VERSION_4)
      {
        if (aTriangulation->HasNormals() && NeedToWriteNormals)
        {
          NCollection_Vec3<float> aNormal;
          for (int aNormalIter = 1; aNormalIter <= aNbNodes; ++aNormalIter)
          {
            aTriangulation->Normal(aNormalIter, aNormal);
            BinTools::PutShortReal(OS, aNormal.x());
            BinTools::PutShortReal(OS, aNormal.y());
            BinTools::PutShortReal(OS, aNormal.z());
          }
        }
      }
    }
  }
  catch (Standard_Failure const& anException)
  {
    Standard_SStream aMsg;
    aMsg << "EXCEPTION in BinTools_ShapeSet::WriteTriangulation(..)\n" << anException << "\n";
    throw Standard_Failure(aMsg.str().c_str());
  }
}

void BinTools_ShapeSet::ReadTriangulation(Standard_IStream&            IS,
                                          const Message_ProgressRange& theRange)
{
  char aHeader[255];
  IS >> aHeader;
  if (IS.fail() || (strstr(aHeader, "Triangulations") == nullptr))
  {
    throw Standard_Failure("BinTools_ShapeSet::Triangulation: Not a Triangulation section");
  }

  int aNbTriangulations = 0;
  IS >> aNbTriangulations;
  IS.get();

  try
  {
    OCC_CATCH_SIGNALS
    Message_ProgressScope aPS(theRange, "Reading triangulation", aNbTriangulations);
    for (int aTriangulationIter = 1; aTriangulationIter <= aNbTriangulations && aPS.More();
         ++aTriangulationIter, aPS.Next())
    {
      int    aNbNodes = 0, aNbTriangles = 0;
      bool   hasUV      = false;
      bool   hasNormals = false;
      double aDefl      = 0.0;
      BinTools::GetInteger(IS, aNbNodes);
      BinTools::GetInteger(IS, aNbTriangles);
      BinTools::GetBool(IS, hasUV);
      if (FormatNb() >= BinTools_FormatVersion_VERSION_4)
      {
        BinTools::GetBool(IS, hasNormals);
      }
      BinTools::GetReal(IS, aDefl);
      occ::handle<Poly_Triangulation> aTriangulation =
        new Poly_Triangulation(aNbNodes, aNbTriangles, hasUV, hasNormals);
      aTriangulation->Deflection(aDefl);

      gp_Pnt aNode;
      for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
      {
        BinTools::GetReal(IS, aNode.ChangeCoord().ChangeCoord(1));
        BinTools::GetReal(IS, aNode.ChangeCoord().ChangeCoord(2));
        BinTools::GetReal(IS, aNode.ChangeCoord().ChangeCoord(3));
        aTriangulation->SetNode(aNodeIter, aNode);
      }

      if (hasUV)
      {
        gp_Pnt2d aNode2d;
        for (int aNodeIter = 1; aNodeIter <= aNbNodes; ++aNodeIter)
        {
          BinTools::GetReal(IS, aNode2d.ChangeCoord().ChangeCoord(1));
          BinTools::GetReal(IS, aNode2d.ChangeCoord().ChangeCoord(2));
          aTriangulation->SetUVNode(aNodeIter, aNode2d);
        }
      }

      int aTriNodes[3] = {};
      for (int aTriIter = 1; aTriIter <= aNbTriangles; ++aTriIter)
      {
        BinTools::GetInteger(IS, aTriNodes[0]);
        BinTools::GetInteger(IS, aTriNodes[1]);
        BinTools::GetInteger(IS, aTriNodes[2]);
        aTriangulation->SetTriangle(aTriIter,
                                    Poly_Triangle(aTriNodes[0], aTriNodes[1], aTriNodes[2]));
      }

      if (hasNormals)
      {
        NCollection_Vec3<float> aNormal;
        for (int aNormalIter = 1; aNormalIter <= aNbNodes; ++aNormalIter)
        {
          BinTools::GetShortReal(IS, aNormal.x());
          BinTools::GetShortReal(IS, aNormal.y());
          BinTools::GetShortReal(IS, aNormal.z());
          aTriangulation->SetNormal(aNormalIter, aNormal);
        }
      }

      myTriangulations.Add(aTriangulation, hasNormals);
    }
  }
  catch (Standard_Failure const& anException)
  {
    Standard_SStream aMsg;
    aMsg << "EXCEPTION in BinTools_ShapeSet::ReadTriangulation(..)\n" << anException << "\n";
    throw Standard_Failure(aMsg.str().c_str());
  }
}

int BinTools_ShapeSet::NbShapes() const
{
  return myShapes.Extent();
}
