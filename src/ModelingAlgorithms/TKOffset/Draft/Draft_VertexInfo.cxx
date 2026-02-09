#include <Draft_VertexInfo.hpp>
#include <Standard_DomainError.hpp>
#include <NCollection_List.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>

Draft_VertexInfo::Draft_VertexInfo() = default;

void Draft_VertexInfo::Add(const TopoDS_Edge& E)
{
  for (myItEd.Initialize(myEdges); myItEd.More(); myItEd.Next())
  {
    if (E.IsSame(myItEd.Value()))
    {
      break;
    }
  }
  if (!myItEd.More())
  {
    myEdges.Append(E);
    myParams.Append(RealLast());
  }
}

const gp_Pnt& Draft_VertexInfo::Geometry() const
{
  return myGeom;
}

gp_Pnt& Draft_VertexInfo::ChangeGeometry()
{
  return myGeom;
}

double Draft_VertexInfo::Parameter(const TopoDS_Edge& E)
{
  NCollection_List<double>::Iterator itp(myParams);
  myItEd.Initialize(myEdges);
  for (; myItEd.More(); myItEd.Next(), itp.Next())
  {
    if (myItEd.Value().IsSame(E))
    {
      return itp.Value();
    }
  }
  throw Standard_DomainError();
}

double& Draft_VertexInfo::ChangeParameter(const TopoDS_Edge& E)
{
  NCollection_List<double>::Iterator itp(myParams);
  myItEd.Initialize(myEdges);
  for (; myItEd.More(); myItEd.Next(), itp.Next())
  {
    if (myItEd.Value().IsSame(E))
    {
      return itp.ChangeValue();
    }
  }
  throw Standard_DomainError();
}

void Draft_VertexInfo::InitEdgeIterator()
{
  myItEd.Initialize(myEdges);
}

const TopoDS_Edge& Draft_VertexInfo::Edge() const
{
  return TopoDS::Edge(myItEd.Value());
}

bool Draft_VertexInfo::MoreEdge() const
{
  return myItEd.More();
}

void Draft_VertexInfo::NextEdge()
{
  myItEd.Next();
}
