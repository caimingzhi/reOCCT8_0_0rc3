#pragma once

#include <gp_XY.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XYZ.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>
#include <gp_GTrsf.hpp>
#include <Interface_MSG.hpp>

#define IGESData_DumpString(S, str)                                                                \
  if (str.IsNull())                                                                                \
    S << "(undefined)";                                                                            \
  else                                                                                             \
  {                                                                                                \
    S << '"' << str->String() << '"';                                                              \
  }

#define IGESData_DumpXY(S, XYval) S << " (" << XYval.X() << "," << XYval.Y() << ")"

#define IGESData_DumpXYZ(S, XYZval)                                                                \
  S << " (" << XYZval.X() << "," << XYZval.Y() << "," << XYZval.Z() << ")"

#define IGESData_DumpXYT(S, XYval, Trsf)                                                           \
  {                                                                                                \
    gp_XYZ XYZval(XYval.X(), XYval.Y(), 0.);                                                       \
    Trsf.Transforms(XYZval);                                                                       \
    IGESData_DumpXY(S, XYZval);                                                                    \
  }

#define IGESData_DumpXYTZ(S, XYval, Trsf, Z)                                                       \
  {                                                                                                \
    gp_XYZ XYZval(XYval.X(), XYval.Y(), Z);                                                        \
    Trsf.Transforms(XYZval);                                                                       \
    IGESData_DumpXYZ(S, XYZval);                                                                   \
  }

#define IGESData_DumpXYZT(S, XYZval, Trsf)                                                         \
  {                                                                                                \
    gp_XYZ XYZTval(XYZval.X(), XYZval.Y(), XYZval.Z());                                            \
    Trsf.Transforms(XYZTval);                                                                      \
    IGESData_DumpXYZ(S, XYZTval);                                                                  \
  }

#define IGESData_DumpXYL(S, Level, XYval, Trsf)                                                    \
  {                                                                                                \
    IGESData_DumpXY(S, XYval);                                                                     \
    if (Level > 5 && Trsf.Form() != gp_Identity)                                                   \
    {                                                                                              \
      S << "  Transformed :";                                                                      \
      IGESData_DumpXYT(S, XYval, Trsf);                                                            \
    }                                                                                              \
  }

#define IGESData_DumpXYLZ(S, Level, XYval, Trsf, Z)                                                \
  {                                                                                                \
    IGESData_DumpXY(S, XYval);                                                                     \
    if (Level > 5 && Trsf.Form() != gp_Identity)                                                   \
    {                                                                                              \
      S << "  Transformed :";                                                                      \
      IGESData_DumpXYTZ(S, XYval, Trsf, Z);                                                        \
    }                                                                                              \
  }

#define IGESData_DumpXYZL(S, Level, XYZval, Trsf)                                                  \
  {                                                                                                \
    IGESData_DumpXYZ(S, XYZval);                                                                   \
    if (Level > 5 && Trsf.Form() != gp_Identity)                                                   \
    {                                                                                              \
      S << "  Transformed :";                                                                      \
      IGESData_DumpXYZT(S, XYZval, Trsf);                                                          \
    }                                                                                              \
  }

#define IGESData_DumpListHeader(S, lower, upper)                                                   \
  {                                                                                                \
    if (lower > upper)                                                                             \
      S << " (Empty List)";                                                                        \
    else if (lower == 1)                                                                           \
      S << " (Count : " << upper << ")";                                                           \
    else                                                                                           \
      S << " (" << lower << " - " << upper << ")";                                                 \
  }

#define IGESData_DumpListVal(S, lower, upper, item)                                                \
  {                                                                                                \
    int lo = lower;                                                                                \
    int up = upper;                                                                                \
    IGESData_DumpListHeader(S, lo, up);                                                            \
    S << " :";                                                                                     \
    for (int iopa = lo; iopa <= up; iopa++)                                                        \
      S << " " << item(iopa);                                                                      \
  }

#define IGESData_DumpListXY(S, lower, upper, item)                                                 \
  {                                                                                                \
    int lo = lower;                                                                                \
    int up = upper;                                                                                \
    IGESData_DumpListHeader(S, lo, up);                                                            \
    S << " :";                                                                                     \
    for (int iopa = lo; iopa <= up; iopa++)                                                        \
      IGESData_DumpXY(S, item(iopa));                                                              \
  }

#define IGESData_DumpListXYZ(S, lower, upper, item)                                                \
  {                                                                                                \
    int lo = lower;                                                                                \
    int up = upper;                                                                                \
    IGESData_DumpListHeader(S, lo, up);                                                            \
    S << " :";                                                                                     \
    for (int iopa = lo; iopa <= up; iopa++)                                                        \
      IGESData_DumpXYZ(S, item(iopa));                                                             \
  }

#define IGESData_DumpVals(S, Level, lower, upper, item)                                            \
  {                                                                                                \
    int lo = lower;                                                                                \
    int up = upper;                                                                                \
    IGESData_DumpListHeader(S, lo, up);                                                            \
    if (lo > up)                                                                                   \
    {                                                                                              \
    }                                                                                              \
    else if (Level == 4 || Level == -4)                                                            \
      S << " [content : ask level > 4]";                                                           \
    else if (Level > 0)                                                                            \
    {                                                                                              \
      S << " :";                                                                                   \
      for (int iopa = lo; iopa <= up; iopa++)                                                      \
        S << " " << item(iopa);                                                                    \
    }                                                                                              \
  }

#define IGESData_DumpListXYL(S, Level, lower, upper, item, Trsf)                                   \
  {                                                                                                \
    int lo = lower;                                                                                \
    int up = upper;                                                                                \
    IGESData_DumpListHeader(S, lo, up);                                                            \
    if (lo > up)                                                                                   \
    {                                                                                              \
    }                                                                                              \
    else if (Level == 4 || Level == -4)                                                            \
      S << " [content : ask level > 4, transformed : level > 5]";                                  \
    else if (Level > 0)                                                                            \
    {                                                                                              \
      S << " :";                                                                                   \
      for (int iopa = lo; iopa <= up; iopa++)                                                      \
        IGESData_DumpXY(S, item(iopa));                                                            \
      if (Trsf.Form() != gp_Identity)                                                              \
      {                                                                                            \
        S << "\n Transformed :";                                                                   \
        if (Level == 5)                                                                            \
          S << " [ask level > 5]";                                                                 \
        else                                                                                       \
          for (int jopa = lo; jopa <= up; jopa++)                                                  \
            IGESData_DumpXYT(S, item(jopa), Trsf);                                                 \
      }                                                                                            \
    }                                                                                              \
  }

#define IGESData_DumpListXYLZ(S, Level, lower, upper, item, Trsf, Z)                               \
  {                                                                                                \
    int lo = lower;                                                                                \
    int up = upper;                                                                                \
    IGESData_DumpListHeader(S, lo, up);                                                            \
    if (lo > up)                                                                                   \
    {                                                                                              \
    }                                                                                              \
    else if (Level == 4 || Level == -4)                                                            \
      S << " [content : ask level > 4, transformed : level > 5]";                                  \
    else if (Level > 0)                                                                            \
    {                                                                                              \
      S << " :";                                                                                   \
      for (int iopa = lo; iopa <= up; iopa++)                                                      \
        IGESData_DumpXY(S, item(iopa));                                                            \
      if (Trsf.Form() != gp_Identity)                                                              \
      {                                                                                            \
        S << "\n Transformed :";                                                                   \
        if (Level == 5)                                                                            \
          S << " [ask level > 5]";                                                                 \
        else                                                                                       \
          for (int jopa = lo; jopa <= up; jopa++)                                                  \
            IGESData_DumpXYTZ(S, item(jopa), Trsf, Z);                                             \
      }                                                                                            \
    }                                                                                              \
  }

#define IGESData_DumpListXYZL(S, Level, lower, upper, item, Trsf)                                  \
  {                                                                                                \
    int lo = lower;                                                                                \
    int up = upper;                                                                                \
    IGESData_DumpListHeader(S, lo, up);                                                            \
    if (lo > up)                                                                                   \
    {                                                                                              \
    }                                                                                              \
    else if (Level == 4 || Level == -4)                                                            \
      S << " [content : ask level > 4, transformed : level > 5]";                                  \
    else if (Level > 0)                                                                            \
    {                                                                                              \
      S << " :";                                                                                   \
      for (int iopa = lo; iopa <= up; iopa++)                                                      \
        IGESData_DumpXYZ(S, item(iopa));                                                           \
      if (Trsf.Form() != gp_Identity)                                                              \
      {                                                                                            \
        S << "\n Transformed :";                                                                   \
        if (Level == 5)                                                                            \
          S << " [ask level > 5]";                                                                 \
        else                                                                                       \
          for (int jopa = lo; jopa <= up; jopa++)                                                  \
            IGESData_DumpXYZT(S, item(jopa), Trsf);                                                \
      }                                                                                            \
    }                                                                                              \
  }

#define IGESData_DumpStrings(S, Level, lower, upper, item)                                         \
  {                                                                                                \
    int lo = lower;                                                                                \
    int up = upper;                                                                                \
    IGESData_DumpListHeader(S, lo, up);                                                            \
    if (lo > up)                                                                                   \
    {                                                                                              \
    }                                                                                              \
    else if (Level == 4 || Level == -4)                                                            \
      S << " [content : ask level > 4]";                                                           \
    else if (Level > 0)                                                                            \
    {                                                                                              \
      S << " :";                                                                                   \
      for (int iopa = lo; iopa <= up; iopa++)                                                      \
      {                                                                                            \
        S << "\n[" << Interface_MSG::Blanks(iopa, 3) << iopa << "]:\"" << item(iopa)->String()     \
          << '"';                                                                                  \
      }                                                                                            \
      S << "\n";                                                                                   \
    }                                                                                              \
  }

#define IGESData_DumpEntities(S, dumper, Level, lower, upper, item)                                \
  {                                                                                                \
    int lo = lower;                                                                                \
    int up = upper;                                                                                \
    IGESData_DumpListHeader(S, lo, up);                                                            \
    if (lo > up)                                                                                   \
    {                                                                                              \
    }                                                                                              \
    else if (Level == 4 || Level == -4)                                                            \
      S << " [content : ask level > 4]";                                                           \
    else if (Level > 0)                                                                            \
    {                                                                                              \
      S << " :";                                                                                   \
      for (int iopa = lo; iopa <= up; iopa++)                                                      \
      {                                                                                            \
        if (Level == 5)                                                                            \
        {                                                                                          \
          S << " ";                                                                                \
          dumper.PrintDNum(item(iopa), S);                                                         \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
          S << "\n[" << Interface_MSG::Blanks(iopa, 3) << iopa << "]:";                            \
          dumper.PrintShort(item(iopa), S);                                                        \
        }                                                                                          \
      }                                                                                            \
    }                                                                                              \
  }

#define IGESData_DumpRectVals(S, Level, LowCol, UpCol, LowRow, UpRow, Item)                        \
  {                                                                                                \
    int loco = LowCol;                                                                             \
    int upc  = UpCol;                                                                              \
    int lor  = LowRow;                                                                             \
    int upr  = UpRow;                                                                              \
    S << " (Row :" << lor << " - " << upr << " ; Col :" << loco << " - " << upc << ")";            \
    if (loco > upc || lor > upr)                                                                   \
    {                                                                                              \
    }                                                                                              \
    else if (Level == 4 || Level == -4)                                                            \
      S << " [content : ask level > 4]";                                                           \
    else if (Level > 0)                                                                            \
    {                                                                                              \
      S << "\n";                                                                                   \
      for (int ir = lor; ir <= upr; ir++)                                                          \
      {                                                                                            \
        S << "Row " << ir << ":[";                                                                 \
        for (int ic = loco; ic <= upc; ic++)                                                       \
          S << " " << Item(ic, ir);                                                                \
        S << " ]\n";                                                                               \
      }                                                                                            \
    }                                                                                              \
  }
