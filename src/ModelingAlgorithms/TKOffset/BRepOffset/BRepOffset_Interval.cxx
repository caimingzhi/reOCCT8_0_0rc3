#include <BRepOffset_Interval.hpp>

BRepOffset_Interval::BRepOffset_Interval() = default;

BRepOffset_Interval::BRepOffset_Interval(const double                 U1,
                                         const double                 U2,
                                         const ChFiDS_TypeOfConcavity Type)
    : f(U1),
      l(U2),
      type(Type)
{
}
