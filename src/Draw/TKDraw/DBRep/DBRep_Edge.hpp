#pragma once

#include <Standard.hpp>

#include <TopoDS_Edge.hpp>
#include <Draw_Color.hpp>
#include <Standard_Transient.hpp>

class DBRep_Edge : public Standard_Transient
{

public:
  Standard_EXPORT DBRep_Edge(const TopoDS_Edge& E, const Draw_Color& C);

  const TopoDS_Edge& Edge() const;

  void Edge(const TopoDS_Edge& E);

  const Draw_Color& Color() const;

  void Color(const Draw_Color& C);

  DEFINE_STANDARD_RTTIEXT(DBRep_Edge, Standard_Transient)

private:
  TopoDS_Edge myEdge;
  Draw_Color  myColor;
};

inline const TopoDS_Edge& DBRep_Edge::Edge() const
{
  return myEdge;
}

inline void DBRep_Edge::Edge(const TopoDS_Edge& E)
{
  myEdge = E;
}

inline const Draw_Color& DBRep_Edge::Color() const
{
  return myColor;
}

inline void DBRep_Edge::Color(const Draw_Color& C)
{
  myColor = C;
}
