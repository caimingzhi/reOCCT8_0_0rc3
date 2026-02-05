#include <Adaptor3d_HVertex.hpp>
#include <Contap_Point.hpp>
#include <gp_Pnt.hpp>

Contap_Point::Contap_Point()
    : uparam(0.0),
      vparam(0.0),
      paraline(0.0),
      onarc(false),
      prmarc(0.0),
      isvtx(false),
      ismult(false),
      myInternal(false)
{
}

Contap_Point::Contap_Point(const gp_Pnt& Pt, const double U, const double V)
    : pt(Pt),
      uparam(U),
      vparam(V),
      paraline(0.0),
      onarc(false),
      prmarc(0.0),
      isvtx(false),
      ismult(false),
      myInternal(false)
{
}
