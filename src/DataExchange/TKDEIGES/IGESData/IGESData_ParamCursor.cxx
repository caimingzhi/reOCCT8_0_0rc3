

#include <IGESData_ParamCursor.hpp>
#include <Interface_InterfaceError.hpp>

IGESData_ParamCursor::IGESData_ParamCursor(const int num)
{
  thestart = num;
  thelimit = thestart + 1;
  thecount = 1;
  theadv   = true;
  theisize = 1;
  theoffst = 0;
  thetsize = 1;
}

IGESData_ParamCursor::IGESData_ParamCursor(const int num, const int nb, const int size)
{
  thestart = num;
  thelimit = num + (nb * size);
  thecount = nb;
  theadv   = true;
  theisize = size;
  theoffst = 0;
  thetsize = size;
}

void IGESData_ParamCursor::SetTerm(const int size, const bool autoadv)
{
  theoffst += thetsize;
  thetsize = size;
  if (autoadv)
    theadv = (theoffst + thetsize == theisize);
  if (theoffst + thetsize > theisize)
    throw Interface_InterfaceError(
      "IGESDAta ParamCursor : required Term size overpass whole Item size");
}

void IGESData_ParamCursor::SetOne(const bool autoadv)
{
  SetTerm(1, autoadv);
}

void IGESData_ParamCursor::SetXY(const bool autoadv)
{
  SetTerm(2, autoadv);
}

void IGESData_ParamCursor::SetXYZ(const bool autoadv)
{
  SetTerm(3, autoadv);
}

void IGESData_ParamCursor::SetAdvance(const bool advance)
{
  theadv = advance;
}
