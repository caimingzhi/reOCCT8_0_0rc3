#pragma once


#ifdef OCCT_DEBUG

  #include <TopAbs_ShapeEnum.hpp>

  #include <TopAbs_Orientation.hpp>

  #include <TopAbs_State.hpp>

  #include <TopoDS_Shape.hpp>

  #include <TopTools_ShapeMapHasher.hpp>

  #include <NCollection_Map.hpp>

  #include <NCollection_List.hpp>

  #include <NCollection_IndexedMap.hpp>

  #include <NCollection_DataMap.hpp>

  #include <Standard_Integer.hpp>

  #include <NCollection_IndexedDataMap.hpp>

  #include <TopoDS_Face.hpp>

  #include <TopoDS_Edge.hpp>

  #include <TopoDS_Vertex.hpp>

  #include <TCollection_AsciiString.hpp>
  #include <Standard_OStream.hpp>

class TopOpeBRep_traceSIFF
{
public:
  TopOpeBRep_traceSIFF();

  void Reset();

  void Set(const bool b, int n, char** a);

  void Set(const TCollection_AsciiString& brep1,
           const TCollection_AsciiString& brep2,
           const TCollection_AsciiString& n);

  TCollection_AsciiString Name1(const int I) const;
  TCollection_AsciiString Name2(const int I) const;

  const TCollection_AsciiString& File() const;

  bool Start(const TCollection_AsciiString& s, Standard_OStream& OS);
  void Add(const int I1, const int I2);
  void End(const TCollection_AsciiString& s, Standard_OStream& OS);

private:
  TCollection_AsciiString mybrep1, mybrep2, myfilename;
  std::filebuf            myfilebuf;
  bool                    myopen;
};

// #ifdef OCCT_DEBUG
#endif
// #define _TopOpeBRep_traceSIFF_HeaderFile
