#include <TopOpeBRepTool_2d.hpp>
#include <BRep_Tool.hpp>

#define M_FORWARD(sta) (sta == TopAbs_FORWARD)
#define M_REVERSED(sta) (sta == TopAbs_REVERSED)
#define M_INTERNAL(sta) (sta == TopAbs_INTERNAL)
#define M_EXTERNAL(sta) (sta == TopAbs_EXTERNAL)

#ifdef OCCT_DEBUG
extern NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> STATIC_PURGE_mapv;
extern NCollection_IndexedMap<TopoDS_Shape>                          STATIC_PURGE_mapeds;
extern bool                                                          TopOpeBRepTool_GettracePURGE();

void FUN_REINIT()
{
  STATIC_PURGE_mapv.Clear();
  STATIC_PURGE_mapeds.Clear();
}

Standard_EXPORT void FUN_tool_tori(const TopAbs_Orientation Or)
{
  switch (Or)
  {
    case TopAbs_FORWARD:
      std::cout << "FOR";
      break;
    case TopAbs_REVERSED:
      std::cout << "REV";
      break;
    case TopAbs_INTERNAL:
      std::cout << "INT";
      break;
    case TopAbs_EXTERNAL:
      std::cout << "EXT";
      break;
  }
}
#endif

Standard_EXPORT void FUN_tool_trace(const int Index)
{
  if (Index == 1)
    std::cout << "FORWARD ";
  if (Index == 2)
    std::cout << "REVERSED ";
}

Standard_EXPORT void FUN_tool_trace(const gp_Pnt2d p2d)
{
  std::cout << " = (" << p2d.X() << " " << p2d.Y() << ")" << std::endl;
}
