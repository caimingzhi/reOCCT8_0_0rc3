#include <HLRTopoBRep_VData.hpp>
#include <TopoDS_Shape.hpp>

HLRTopoBRep_VData::HLRTopoBRep_VData(const double P, const TopoDS_Shape& V)
    : myParameter(P),
      myVertex(V)
{
}
