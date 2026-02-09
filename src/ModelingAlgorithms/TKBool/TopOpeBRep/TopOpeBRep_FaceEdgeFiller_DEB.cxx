#ifdef OCCT_DEBUG

  #include <TCollection_AsciiString.hpp>
  #include <TopOpeBRep_FaceEdgeIntersector.hpp>
  #include <TopOpeBRepDS_DataStructure.hpp>
  #include <TopOpeBRepDS.hpp>
  #include <TopOpeBRepDS_Transition.hpp>
  #include <TopoDS_Shape.hpp>
  #include <TopAbs.hpp>
  #include <TopAbs_State.hpp>
  #include <TopAbs_Orientation.hpp>
  #include <gp_Pnt.hpp>
  #include <gp_Pnt2d.hpp>

void FEINT_DUMPPOINTS(TopOpeBRep_FaceEdgeIntersector& FEINT, const TopOpeBRepDS_DataStructure& BDS)
{
  FEINT.InitPoint();
  if (!FEINT.MorePoint())
    return;

  std::cout << std::endl;
  std::cout << "---------- F/E : " << FEINT.NbPoints() << " p ";
  std::cout << std::endl;

  const TopoDS_Shape& FF = FEINT.Shape(1);
  const TopoDS_Shape& EE = FEINT.Shape(2);

  int FFindex = BDS.Shape(FF);
  int EEindex = BDS.Shape(EE);

  TopAbs_Orientation FFori = FF.Orientation();
  TopAbs_Orientation EEori = EE.Orientation();
  std::cout << "FF = " << FFindex << " ";
  TopAbs::Print(FFori, std::cout);
  std::cout << ", ";
  std::cout << "EE = " << EEindex << " ";
  TopAbs::Print(EEori, std::cout);
  std::cout << std::endl;

  int ip = 1;
  for (; FEINT.MorePoint(); FEINT.NextPoint(), ip++)
  {
    gp_Pnt2d pUV;
    FEINT.UVPoint(pUV);
    TopAbs_State sta  = FEINT.State();
    double       parE = FEINT.Parameter();

    TopOpeBRepDS_Transition T1, T2;
    T1 = FEINT.Transition(1, EEori);
    T2 = FEINT.Transition(2, FFori);

    TopoDS_Vertex V1;
    bool          isvertexF = FEINT.IsVertex(1, V1);
    TopoDS_Vertex V2;
    bool          isvertexE = FEINT.IsVertex(2, V2);

    std::cout << std::endl;
    std::cout << "P" << ip << " : ";
    gp_Pnt P3D = FEINT.Value();
    std::cout << "\t" << P3D.X() << " " << P3D.Y() << " " << P3D.Z() << std::endl;

    std::cout << "\t";
    if (isvertexF)
      std::cout << "IS VERTEX, ";
    std::cout << " pUV = " << pUV.X() << " " << pUV.Y() << std::endl;
    std::cout << " sta = ";
    TopAbs::Print(sta, std::cout);
    std::cout << std::endl;

    std::cout << "\t";
    if (isvertexE)
      std::cout << "IS VERTEX, ";
    std::cout << " parE = " << parE << std::endl;
  }
}

#endif
