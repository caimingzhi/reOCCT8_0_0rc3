#include <MAT2d_Mat2d.hpp>
#include <MAT2d_Tool2d.hpp>
#include <MAT_Bisector.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <MAT_Edge.hpp>
#include <MAT_ListOfBisector.hpp>
#include <MAT_ListOfEdge.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>

MAT2d_Mat2d::MAT2d_Mat2d(const bool IsOpenResult)
    : semiInfinite(false),
      isDone(false)
{
  myIsOpenResult       = IsOpenResult;
  thenumberofbisectors = 0;
  thenumberofedges     = 0;
}

void MAT2d_Mat2d::CreateMatOpen(MAT2d_Tool2d& atool)
{

#ifdef ICONTINUE
  bool Icontinue;
#endif

  bool interrupt = false;

  occ::handle<MAT_Edge> edgetoremove;
  occ::handle<MAT_Edge> previousedge, currentedge;

  int                       noofbisectorstoremove;
  occ::handle<MAT_Bisector> firstbisector, secondbisector;
  occ::handle<MAT_Edge>     edge;
  int                       intersectionpoint;
  int                       beginbisector;
  int                       noofbisectors;

  int                     NbIterBis     = 0;
  int                     EvenNbIterBis = 10;
  NCollection_Array1<int> EdgeNumbers(1, EvenNbIterBis + 1);
  EdgeNumbers.Init(-1);
  bool ToNullifyNoofbisectorstoremove = false;

  occ::handle<MAT_ListOfBisector> currentbisectorlist;

  occ::handle<MAT_Bisector> bisectortoremove, lastbisector, currentbisector;
  occ::handle<MAT_Bisector> previousbisector;

  int    i, j, k, narea, shift, compact, all;
  int    noofedges;
  int    NumberMaxOfIte;
  double toleranceofconfusion;

  noofedges            = atool.NumberOfItems();
  toleranceofconfusion = atool.ToleranceOfConfusion();
  NumberMaxOfIte       = noofedges * noofedges;

  NCollection_Array1<int> firstarea(0, noofedges);
  NCollection_Array1<int> lastarea(0, noofedges);
  NCollection_Array1<int> noofarea(0, noofedges);

  int parama[2];
  int paramb[2];

  bisectoronetoremove.Clear();
  bisectortwotoremove.Clear();
  typeofbisectortoremove.Clear();
  bisectormap.Clear();

  isDone        = true;
  noofbisectors = noofedges - 1;
  beginbisector = 0;

  theedgelist      = new MAT_ListOfEdge();
  RemovedEdgesList = new MAT_ListOfEdge();

  for (i = 0; i < noofedges; i++)
  {
    edge = new MAT_Edge();
    edge->EdgeNumber(i + 1);
    edge->Distance(-1);
    theedgelist->BackAdd(edge);
  }

  theedgelist->Loop();

  double Dist;
  theedgelist->First();

  for (i = 0; i < theedgelist->Number() - 1; i++)
  {
    bisectormap.Bind(i, new MAT_Bisector());
    bisectormap(i)->IndexNumber(i);
    bisectormap(i)->FirstEdge(theedgelist->Current());
    bisectormap(i)->FirstVector(
      atool.TangentBefore(theedgelist->Current()->EdgeNumber(), myIsOpenResult));
    theedgelist->Next();
    bisectormap(i)->SecondEdge(theedgelist->Current());
    bisectormap(i)->IssuePoint(atool.FirstPoint(theedgelist->Current()->EdgeNumber(), Dist));
    bisectormap(i)->DistIssuePoint(Dist);
    bisectormap(i)->SecondVector(
      atool.TangentAfter(theedgelist->Current()->EdgeNumber(), myIsOpenResult));
  }

  theedgelist->First();
  theedgelist->Current()->FirstBisector(bisectormap(0));
  theedgelist->Current()->SecondBisector(bisectormap(0));
  theedgelist->Next();

  for (i = 1; i < theedgelist->Number() - 1; i++)
  {
    theedgelist->Current()->FirstBisector(bisectormap(i - 1));
    theedgelist->Current()->SecondBisector(bisectormap(i));
    theedgelist->Next();
  }

  theedgelist->Current()->FirstBisector(bisectormap(theedgelist->Number() - 2));
  theedgelist->Current()->SecondBisector(bisectormap(theedgelist->Number() - 2));

  int NumberOfIte = 0;

  while (theedgelist->Number() > 1)
  {

    for (i = beginbisector; i < noofbisectors; i++)
    {

      atool.CreateBisector(bisectormap(i));
      thenumberofbisectors++;

#ifdef OCCT_DEBUG_Mat
      atool.Dump(bisectormap(i)->BisectorNumber(), 1);
  #ifdef ICONTINUE
      std::cin >> Icontinue;
  #endif
#endif
    }

    if (theedgelist->Number() < 3)
      break;

    for (;;)
    {
      NbIterBis++;

      noofbisectorstoremove = 0;
      theedgelist->First();
      theedgelist->Next();

      if (NbIterBis <= EvenNbIterBis + 1)
        EdgeNumbers(NbIterBis) = theedgelist->Number();
      else
      {
        for (k = 1; k <= EvenNbIterBis; k++)
          EdgeNumbers(k) = EdgeNumbers(k + 1);
        EdgeNumbers(EvenNbIterBis + 1) = theedgelist->Number();
      }
      if (EdgeNumbers(EvenNbIterBis + 1) == EdgeNumbers(1))
        ToNullifyNoofbisectorstoremove = true;

      for (i = 1; i < theedgelist->Number() - 1; i++)
      {
        edge = theedgelist->Current();
        if (edge->Distance() == -1.)
        {
          firstbisector  = edge->FirstBisector();
          secondbisector = edge->SecondBisector();
          edge->Distance(atool.IntersectBisector(firstbisector, secondbisector, intersectionpoint));
          edge->IntersectionPoint(intersectionpoint);

          if (edge->Distance() == Precision::Infinite())
          {
            if (firstbisector->IndexNumber() >= beginbisector
                || secondbisector->IndexNumber() >= beginbisector)
              Intersect(atool, 0, noofbisectorstoremove, firstbisector, secondbisector);
          }
          else
          {
            if (firstbisector->IndexNumber() >= beginbisector)
            {
              Intersect(atool, 1, noofbisectorstoremove, firstbisector, secondbisector);
            }
            if (secondbisector->IndexNumber() >= beginbisector)
            {
              Intersect(atool, 2, noofbisectorstoremove, firstbisector, secondbisector);
            }
          }
        }
        theedgelist->Next();
      }

      if (ToNullifyNoofbisectorstoremove)
        noofbisectorstoremove = 0;
      if (noofbisectorstoremove == 0)
        break;

      for (i = 0; i < noofbisectorstoremove; i++)
      {

        bisectortoremove = bisectoronetoremove(i);

        for (;;)
        {

#ifdef OCCT_DEBUG_Mat
          atool.Dump(bisectortoremove->BisectorNumber(), 0);
#endif

          thenumberofbisectors--;
          currentbisectorlist = bisectortoremove->List();
          currentbisectorlist->First();
          currentbisector = currentbisectorlist->FirstItem();
          previousedge    = currentbisector->FirstEdge();
          theedgelist->Init(previousedge);
          previousedge->Distance(-1.);
          previousedge->FirstBisector()->SecondParameter(Precision::Infinite());
          previousedge->SecondBisector()->FirstParameter(Precision::Infinite());

          while (currentbisectorlist->More())
          {
            currentbisector = currentbisectorlist->Current();
            currentedge     = currentbisector->SecondEdge();

            theedgelist->LinkAfter(currentedge);
            theedgelist->Next();

            currentedge->FirstBisector(currentbisector);
            previousedge->SecondBisector(currentbisector);
#ifdef OCCT_DEBUG_Mat
            atool.Dump(currentbisector->BisectorNumber(), 0);
#endif

            currentbisector->FirstParameter(Precision::Infinite());
            currentbisector->SecondParameter(Precision::Infinite());

            atool.TrimBisector(currentbisector);

#ifdef OCCT_DEBUG_Mat
            atool.Dump(currentbisector->BisectorNumber(), 1);
#endif
            currentedge->Distance(-1.);
            currentedge->FirstBisector()->SecondParameter(Precision::Infinite());
            currentedge->SecondBisector()->FirstParameter(Precision::Infinite());

            previousedge = currentedge;
            currentbisectorlist->Next();
          }

          RemovedEdgesList->BackAdd(theedgelist->Current());
          theedgelist->Unlink();

          if (bisectortoremove->BisectorNumber() == bisectortwotoremove(i)->BisectorNumber())
            break;

          if (typeofbisectortoremove(i) == 1)
            bisectortoremove = bisectortoremove->FirstBisector();
          else
            bisectortoremove = bisectortoremove->LastBisector();
        }
      }

#ifdef ICONTINUE
      std::cin >> Icontinue;
#endif
    }

    theedgelist->First();
    theedgelist->Next();

    currentbisector = theedgelist->Current()->FirstBisector();
    if (currentbisector->FirstParameter() == Precision::Infinite()
        && currentbisector->SecondParameter() == Precision::Infinite())
    {
      parama[0] = -1;
      paramb[0] = -1;
    }
    else if (currentbisector->FirstParameter() == Precision::Infinite())
    {
      parama[0] = -1;
      paramb[0] = 1;
    }
    else if (currentbisector->SecondParameter() == Precision::Infinite())
    {
      paramb[0] = -1;
      parama[0] = 1;
    }
    else if (atool.Distance(currentbisector,
                            currentbisector->FirstParameter(),
                            currentbisector->SecondParameter())
             > toleranceofconfusion)
    {
      if ((currentbisector->FirstParameter() - currentbisector->SecondParameter())
            * currentbisector->Sense()
          > 0.)
      {
        parama[0] = -1;
        paramb[0] = 1;
      }
      else
      {
        paramb[0] = -1;
        parama[0] = 1;
      }
    }
    else
    {
      parama[0] = 1;
      paramb[0] = 1;
    }

    narea = -1;

    for (i = 1; i < theedgelist->Number() - 1; i++)
    {
      currentbisector = theedgelist->Current()->SecondBisector();
      if (currentbisector->FirstParameter() == Precision::Infinite()
          && currentbisector->SecondParameter() == Precision::Infinite())
      {
        parama[1] = -1;
        paramb[1] = -1;
      }
      else if (currentbisector->FirstParameter() == Precision::Infinite())
      {
        parama[1] = -1;
        paramb[1] = 1;
      }
      else if (currentbisector->SecondParameter() == Precision::Infinite())
      {
        paramb[1] = -1;
        parama[1] = 1;
      }
      else if (atool.Distance(currentbisector,
                              currentbisector->FirstParameter(),
                              currentbisector->SecondParameter())
               > toleranceofconfusion)
      {
        if ((currentbisector->FirstParameter() - currentbisector->SecondParameter())
              * currentbisector->Sense()
            > 0.)
        {
          parama[1] = -1;
          paramb[1] = 1;
        }
        else
        {
          paramb[1] = -1;
          parama[1] = 1;
        }
      }
      else
      {
        parama[1] = 1;
        paramb[1] = 1;
      }

#ifdef OCCT_DEBUG_Mat
      std::cout << " Test sur les parametres pour elimination" << std::endl;
      std::cout << " Edge number :" << theedgelist->Current()->EdgeNumber() << std::endl;
#endif

      if (paramb[0] > 0 && parama[1] > 0)
      {

#ifdef OCCT_DEBUG_Mat
        std::cout << " A ELIMINER " << std::endl;
#endif
        if (narea < 0)
        {
          firstarea(++narea) = theedgelist->Index();
          lastarea(narea)    = firstarea(narea);
          noofarea(narea)    = 1;
        }
        else
        {
          if (theedgelist->Index() == lastarea(narea) + 1)
          {
            lastarea(narea)++;
            noofarea(narea)++;
          }
          else
          {
            firstarea(++narea) = theedgelist->Index();
            lastarea(narea)    = firstarea(narea);
            noofarea(narea)    = 1;
          }
        }
      }
      parama[0] = parama[1];
      paramb[0] = paramb[1];
      theedgelist->Next();
    }

    compact = 0;
    if (narea > 0)
    {
      if (lastarea(narea) == theedgelist->Number() && firstarea(0) == 1)
      {
        firstarea(0) = firstarea(narea);
        noofarea(0)  = noofarea(0) + noofarea(narea);
        compact      = noofarea(narea);
        narea--;
      }
    }

    narea++;

    if (narea == 0)
    {
      interrupt = true;
      break;
    }

    beginbisector = noofbisectors;
    shift         = 0;
    all           = 0;
    if (narea == 1 && noofarea(0) == theedgelist->Number())
      all = 1;

    for (i = 0; i < narea; i++)
    {
      if (i == 1)
        shift = shift - compact;
      theedgelist->First();
      theedgelist->Next();
      edgetoremove = theedgelist->Brackets(firstarea(i) - shift);

      edgetoremove->FirstBisector()->EndPoint(edgetoremove->IntersectionPoint());

#ifdef OCCT_DEBUG_Mat
      atool.Dump(edgetoremove->FirstBisector()->BisectorNumber(), 0);
#endif

      edgetoremove->FirstBisector()->FirstParameter(
        edgetoremove->FirstBisector()->SecondParameter());

#ifdef OCCT_DEBUG_Mat
      if (atool.TrimBisector(edgetoremove->FirstBisector()))
        atool.Dump(edgetoremove->FirstBisector()->BisectorNumber(), 1);
#else
      atool.TrimBisector(edgetoremove->FirstBisector());
#endif

      bisectormap.Bind(noofbisectors, new MAT_Bisector());
      bisectormap(noofbisectors)->IndexNumber(noofbisectors);
      bisectormap(noofbisectors)->DistIssuePoint(edgetoremove->Distance());
      bisectormap(noofbisectors)->IssuePoint(edgetoremove->IntersectionPoint());
      bisectormap(noofbisectors)->FirstEdge(theedgelist->PreviousItem());
      bisectormap(noofbisectors)->AddBisector(edgetoremove->FirstBisector());

      for (j = 0; j < noofarea(i); j++)
      {
        RemovedEdgesList->BackAdd(theedgelist->Current());
        theedgelist->Unlink();
        theedgelist->Next();
        shift++;

#ifdef OCCT_DEBUG_Mat
        std::cout << " Suppression de l'arete : " << edgetoremove->EdgeNumber() << std::endl;
#endif

        if (all == 0 || j + 1 != noofarea(i))
        {
          bisectormap(noofbisectors)->AddBisector(edgetoremove->SecondBisector());
        }
        edgetoremove->SecondBisector()->EndPoint(edgetoremove->IntersectionPoint());

#ifdef OCCT_DEBUG_Mat
        atool.Dump(edgetoremove->SecondBisector()->BisectorNumber(), 0);
#endif

        edgetoremove->SecondBisector()->SecondParameter(
          edgetoremove->SecondBisector()->FirstParameter());
#ifdef OCCT_DEBUG_Mat
        if (atool.TrimBisector(edgetoremove->SecondBisector()))
          atool.Dump(edgetoremove->SecondBisector()->BisectorNumber(), 1);
#else
        atool.TrimBisector(edgetoremove->SecondBisector());
#endif
        edgetoremove = theedgelist->Current();
      }
      bisectormap(noofbisectors)->SecondEdge(theedgelist->Current());

      theedgelist->PreviousItem()->SecondBisector(bisectormap(noofbisectors));
      theedgelist->Current()->FirstBisector(bisectormap(noofbisectors));

      bisectormap(noofbisectors)
        ->FirstVector(atool.Tangent(bisectormap(noofbisectors)->FirstBisector()->BisectorNumber()));

      bisectormap(noofbisectors)
        ->SecondVector(atool.Tangent(bisectormap(noofbisectors)->LastBisector()->BisectorNumber()));

      noofbisectors++;

      theedgelist->PreviousItem()->Distance(-1);
      theedgelist->Current()->Distance(-1);

      theedgelist->PreviousItem()->FirstBisector()->SecondParameter(Precision::Infinite());
      theedgelist->Current()->SecondBisector()->FirstParameter(Precision::Infinite());
    }

    if (NumberOfIte > NumberMaxOfIte)
    {
      isDone = false;
      break;
    }
    NumberOfIte++;
  }

  if (interrupt)
    semiInfinite = true;
  else
  {
    semiInfinite = false;

    if (theedgelist->Number() > 1)
    {

      theedgelist->First();
      edge = theedgelist->Current();
      if (edge->FirstBisector()->IndexNumber() == noofbisectors - 1)
      {

        if (atool.TrimBisector(edge->SecondBisector(), edge->FirstBisector()->IssuePoint()))
        {
          if (edge->SecondBisector()->EndPoint() == 0)
            edge->SecondBisector()->EndPoint(edge->FirstBisector()->IssuePoint());
          bisectormap(noofbisectors - 1)->AddBisector(edge->SecondBisector());
        }
        else
          semiInfinite = true;
      }
      else
      {

        if (atool.TrimBisector(edge->FirstBisector(), edge->SecondBisector()->IssuePoint()))
        {
          if (edge->FirstBisector()->EndPoint() == 0)
            edge->FirstBisector()->EndPoint(edge->SecondBisector()->IssuePoint());
          bisectormap(noofbisectors - 1)->AddBisector(edge->FirstBisector());
        }
        else
          semiInfinite = true;
      }
      if (!semiInfinite)
      {
        thenumberofbisectors--;
        bisectormap(noofbisectors - 1)->SecondEdge(edge);
        bisectormap(noofbisectors - 1)->BisectorNumber(-1);
      }
    }
  }

  if (semiInfinite)
  {
    beginbisector = noofbisectors;
    theedgelist->First();
    for (i = 1; i < theedgelist->Number(); i++)
    {
      edge = theedgelist->Current();
      bisectormap.Bind(noofbisectors, edge->SecondBisector());
      noofbisectors++;
      theedgelist->Next();
    }
  }

  roots = new MAT_ListOfBisector;

  if (bisectormap(noofbisectors - 1)->BisectorNumber() == -1)
  {
    roots = bisectormap(noofbisectors - 1)->List();
    roots->First();
    roots->Current()->FirstEdge()->Distance(bisectormap(noofbisectors - 1)->DistIssuePoint());
  }
  else
  {
    for (i = beginbisector; i < noofbisectors; i++)
    {
      roots->BackAdd(bisectormap(i));
    }
  }
}

void MAT2d_Mat2d::CreateMat(MAT2d_Tool2d& atool)
{

#ifdef ICONTINUE
  bool Icontinue;
#endif

  bool interrupt = false;

  occ::handle<MAT_Edge> edgetoremove;
  occ::handle<MAT_Edge> previousedge, currentedge;

  int                       noofbisectorstoremove;
  occ::handle<MAT_Bisector> firstbisector, secondbisector;
  occ::handle<MAT_Edge>     edge;
  int                       intersectionpoint;
  int                       beginbisector;
  int                       noofbisectors;

  int                     NbIterBis     = 0;
  int                     EvenNbIterBis = 10;
  NCollection_Array1<int> EdgeNumbers(1, EvenNbIterBis + 1);
  EdgeNumbers.Init(-1);
  bool ToNullifyNoofbisectorstoremove = false;

  occ::handle<MAT_ListOfBisector> currentbisectorlist;

  occ::handle<MAT_Bisector> bisectortoremove, lastbisector, currentbisector;
  occ::handle<MAT_Bisector> previousbisector;

  int    i, j, k, narea, shift, compact, all;
  int    noofedges;
  int    NumberMaxOfIte;
  double toleranceofconfusion;

  noofedges            = atool.NumberOfItems();
  toleranceofconfusion = atool.ToleranceOfConfusion();
  NumberMaxOfIte       = noofedges * noofedges;

  NCollection_Array1<int> firstarea(0, noofedges);
  NCollection_Array1<int> lastarea(0, noofedges);
  NCollection_Array1<int> noofarea(0, noofedges);

  int parama[2];
  int paramb[2];

  int  aNbOfNarea1 = 0, aPrefNarea = 0, aNbMaxNarea1 = 10;
  int  aNbElts[2] = {0, 0}, aCountElts[2] = {0, 0};
  bool isBreak = false;

  bisectoronetoremove.Clear();
  bisectortwotoremove.Clear();
  typeofbisectortoremove.Clear();
  bisectormap.Clear();

  isDone        = true;
  noofbisectors = noofedges;
  beginbisector = 0;

  theedgelist      = new MAT_ListOfEdge();
  RemovedEdgesList = new MAT_ListOfEdge();

  for (i = 0; i < noofedges; i++)
  {
    edge = new MAT_Edge();
    edge->EdgeNumber(i + 1);
    edge->Distance(-1);
    theedgelist->BackAdd(edge);
  }

  theedgelist->Loop();

  double Dist;
  theedgelist->First();

  for (i = 0; i < theedgelist->Number(); i++)
  {
    bisectormap.Bind(i, new MAT_Bisector());
    bisectormap(i)->IndexNumber(i);
    bisectormap(i)->FirstEdge(theedgelist->Current());
    bisectormap(i)->FirstVector(
      atool.TangentBefore(theedgelist->Current()->EdgeNumber(), myIsOpenResult));
    theedgelist->Next();
    bisectormap(i)->SecondEdge(theedgelist->Current());
    bisectormap(i)->IssuePoint(atool.FirstPoint(theedgelist->Current()->EdgeNumber(), Dist));
    bisectormap(i)->DistIssuePoint(Dist);
    bisectormap(i)->SecondVector(
      atool.TangentAfter(theedgelist->Current()->EdgeNumber(), myIsOpenResult));
  }

  theedgelist->First();

  for (i = 0; i < theedgelist->Number(); i++)
  {
    theedgelist->Current()->FirstBisector(bisectormap((i - 1 + noofbisectors) % noofbisectors));
    theedgelist->Current()->SecondBisector(bisectormap(i));
    theedgelist->Next();
  }

  int NumberOfIte = 0;

  while (theedgelist->Number() > 1)
  {

    int aNbBis = noofbisectors - beginbisector;
    for (i = beginbisector; i < noofbisectors; i++)
    {

      atool.CreateBisector(bisectormap(i));
      thenumberofbisectors++;

#ifdef OCCT_DEBUG_Mat
      atool.Dump(bisectormap(i)->BisectorNumber(), 1);
  #ifdef ICONTINUE
      std::cin >> Icontinue;
  #endif
#endif
    }

    if (aNbBis == 1)
    {
      if (aPrefNarea == 1)
      {
        aNbOfNarea1++;
        int edge1number = bisectormap(beginbisector)->FirstEdge()->EdgeNumber();
        int edge2number = bisectormap(beginbisector)->SecondEdge()->EdgeNumber();
        if (aNbElts[0] == edge1number)
        {
          aCountElts[0]++;
        }
        else
        {
          aCountElts[0] = 0;
          aNbElts[0]    = edge1number;
        }
        if (aNbElts[1] == edge2number)
        {
          aCountElts[1]++;
        }
        else
        {
          aCountElts[1] = 0;
          aNbElts[1]    = edge2number;
        }
        if (aNbOfNarea1 >= aNbMaxNarea1
            && (aCountElts[0] >= aNbMaxNarea1 || aCountElts[1] >= aNbMaxNarea1))
        {
          isBreak = true;
        }
      }
      else
      {
        aNbOfNarea1   = 0;
        aCountElts[0] = 0;
        aCountElts[1] = 0;
      }
    }
    aPrefNarea = aNbBis;

    if (theedgelist->Number() < 3)
      break;

    for (;;)
    {
      NbIterBis++;

      noofbisectorstoremove = 0;
      theedgelist->First();

      if (NbIterBis <= EvenNbIterBis + 1)
        EdgeNumbers(NbIterBis) = theedgelist->Number();
      else
      {
        for (k = 1; k <= EvenNbIterBis; k++)
          EdgeNumbers(k) = EdgeNumbers(k + 1);
        EdgeNumbers(EvenNbIterBis + 1) = theedgelist->Number();
      }
      if (EdgeNumbers(EvenNbIterBis + 1) == EdgeNumbers(1))
        ToNullifyNoofbisectorstoremove = true;

      for (i = 0; i < theedgelist->Number(); i++)
      {
        edge = theedgelist->Current();
        if (edge->Distance() == -1.)
        {
          firstbisector  = edge->FirstBisector();
          secondbisector = edge->SecondBisector();
          edge->Distance(atool.IntersectBisector(firstbisector, secondbisector, intersectionpoint));
          edge->IntersectionPoint(intersectionpoint);

          if (edge->Distance() == Precision::Infinite())
          {
            if (firstbisector->IndexNumber() >= beginbisector
                || secondbisector->IndexNumber() >= beginbisector)
              Intersect(atool, 0, noofbisectorstoremove, firstbisector, secondbisector);
          }
          else
          {
            if (firstbisector->IndexNumber() >= beginbisector)
            {
              Intersect(atool, 1, noofbisectorstoremove, firstbisector, secondbisector);
            }
            if (secondbisector->IndexNumber() >= beginbisector)
            {
              Intersect(atool, 2, noofbisectorstoremove, firstbisector, secondbisector);
            }
          }
        }
        theedgelist->Next();
      }

      if (ToNullifyNoofbisectorstoremove)
        noofbisectorstoremove = 0;
      if (noofbisectorstoremove == 0)
        break;

      for (i = 0; i < noofbisectorstoremove; i++)
      {

        bisectortoremove = bisectoronetoremove(i);

        for (;;)
        {

#ifdef OCCT_DEBUG_Mat
          atool.Dump(bisectortoremove->BisectorNumber(), 0);
#endif

          thenumberofbisectors--;
          currentbisectorlist = bisectortoremove->List();
          currentbisectorlist->First();
          currentbisector = currentbisectorlist->FirstItem();
          previousedge    = currentbisector->FirstEdge();
          theedgelist->Init(previousedge);
          previousedge->Distance(-1.);
          previousedge->FirstBisector()->SecondParameter(Precision::Infinite());
          previousedge->SecondBisector()->FirstParameter(Precision::Infinite());

          while (currentbisectorlist->More())
          {
            currentbisector = currentbisectorlist->Current();
            currentedge     = currentbisector->SecondEdge();

            theedgelist->LinkAfter(currentedge);
            theedgelist->Next();

            currentedge->FirstBisector(currentbisector);
            previousedge->SecondBisector(currentbisector);
#ifdef OCCT_DEBUG_Mat
            atool.Dump(currentbisector->BisectorNumber(), 0);
#endif

            currentbisector->FirstParameter(Precision::Infinite());
            currentbisector->SecondParameter(Precision::Infinite());

            atool.TrimBisector(currentbisector);

#ifdef OCCT_DEBUG_Mat
            atool.Dump(currentbisector->BisectorNumber(), 1);
#endif
            currentedge->Distance(-1.);
            currentedge->FirstBisector()->SecondParameter(Precision::Infinite());
            currentedge->SecondBisector()->FirstParameter(Precision::Infinite());

            previousedge = currentedge;
            currentbisectorlist->Next();
          }

          RemovedEdgesList->BackAdd(theedgelist->Current());
          theedgelist->Unlink();

          if (bisectortoremove->BisectorNumber() == bisectortwotoremove(i)->BisectorNumber())
            break;

          if (typeofbisectortoremove(i) == 1)
            bisectortoremove = bisectortoremove->FirstBisector();
          else
            bisectortoremove = bisectortoremove->LastBisector();
        }
      }

#ifdef ICONTINUE
      std::cin >> Icontinue;
#endif
    }

    theedgelist->First();

    currentbisector = theedgelist->Current()->FirstBisector();
    if (currentbisector->FirstParameter() == Precision::Infinite()
        && currentbisector->SecondParameter() == Precision::Infinite())
    {
      parama[0] = -1;
      paramb[0] = -1;
    }
    else if (currentbisector->FirstParameter() == Precision::Infinite())
    {
      parama[0] = -1;
      paramb[0] = 1;
    }
    else if (currentbisector->SecondParameter() == Precision::Infinite())
    {
      paramb[0] = -1;
      parama[0] = 1;
    }
    else if (atool.Distance(currentbisector,
                            currentbisector->FirstParameter(),
                            currentbisector->SecondParameter())
             > toleranceofconfusion)
    {
      if ((currentbisector->FirstParameter() - currentbisector->SecondParameter())
            * currentbisector->Sense()
          > 0.)
      {
        parama[0] = -1;
        paramb[0] = 1;
      }
      else
      {
        paramb[0] = -1;
        parama[0] = 1;
      }
    }
    else
    {
      parama[0] = 1;
      paramb[0] = 1;
    }

    narea = -1;

    for (i = 0; i < theedgelist->Number(); i++)
    {
      currentbisector = theedgelist->Current()->SecondBisector();
      if (currentbisector->FirstParameter() == Precision::Infinite()
          && currentbisector->SecondParameter() == Precision::Infinite())
      {
        parama[1] = -1;
        paramb[1] = -1;
      }
      else if (currentbisector->FirstParameter() == Precision::Infinite())
      {
        parama[1] = -1;
        paramb[1] = 1;
      }
      else if (currentbisector->SecondParameter() == Precision::Infinite())
      {
        paramb[1] = -1;
        parama[1] = 1;
      }
      else if (atool.Distance(currentbisector,
                              currentbisector->FirstParameter(),
                              currentbisector->SecondParameter())
               > toleranceofconfusion)
      {
        if ((currentbisector->FirstParameter() - currentbisector->SecondParameter())
              * currentbisector->Sense()
            > 0.)
        {
          parama[1] = -1;
          paramb[1] = 1;
        }
        else
        {
          paramb[1] = -1;
          parama[1] = 1;
        }
      }
      else
      {
        parama[1] = 1;
        paramb[1] = 1;
      }

#ifdef OCCT_DEBUG_Mat
      std::cout << " Test sur les parametres pour elimination" << std::endl;
      std::cout << " Edge number :" << theedgelist->Current()->EdgeNumber() << std::endl;
#endif

      if (paramb[0] > 0 && parama[1] > 0)
      {

#ifdef OCCT_DEBUG_Mat
        std::cout << " A ELIMINER " << std::endl;
#endif
        if (narea < 0)
        {
          firstarea(++narea) = theedgelist->Index();
          lastarea(narea)    = firstarea(narea);
          noofarea(narea)    = 1;
        }
        else
        {
          if (theedgelist->Index() == lastarea(narea) + 1)
          {
            lastarea(narea)++;
            noofarea(narea)++;
          }
          else
          {
            firstarea(++narea) = theedgelist->Index();
            lastarea(narea)    = firstarea(narea);
            noofarea(narea)    = 1;
          }
        }
      }
      parama[0] = parama[1];
      paramb[0] = paramb[1];
      theedgelist->Next();
    }

    compact = 0;
    if (narea > 0)
    {
      if (lastarea(narea) == theedgelist->Number() && firstarea(0) == 1)
      {
        firstarea(0) = firstarea(narea);
        noofarea(0)  = noofarea(0) + noofarea(narea);
        compact      = noofarea(narea);
        narea--;
      }
    }

    narea++;

    if (narea == 1 && isBreak)
    {
      narea = 0;
    }

    if (narea == 0)
    {
      interrupt = true;
      break;
    }

    beginbisector = noofbisectors;
    shift         = 0;
    all           = 0;
    if (narea == 1 && noofarea(0) == theedgelist->Number())
      all = 1;

    for (i = 0; i < narea; i++)
    {
      if (i == 1)
        shift = shift - compact;
      theedgelist->First();
      edgetoremove = theedgelist->Brackets(firstarea(i) - shift);

      edgetoremove->FirstBisector()->EndPoint(edgetoremove->IntersectionPoint());

#ifdef OCCT_DEBUG_Mat
      atool.Dump(edgetoremove->FirstBisector()->BisectorNumber(), 0);
#endif

      edgetoremove->FirstBisector()->FirstParameter(
        edgetoremove->FirstBisector()->SecondParameter());

#ifdef OCCT_DEBUG_Mat
      if (atool.TrimBisector(edgetoremove->FirstBisector()))
        atool.Dump(edgetoremove->FirstBisector()->BisectorNumber(), 1);
#else
      atool.TrimBisector(edgetoremove->FirstBisector());
#endif

      bisectormap.Bind(noofbisectors, new MAT_Bisector());
      bisectormap(noofbisectors)->IndexNumber(noofbisectors);
      bisectormap(noofbisectors)->DistIssuePoint(edgetoremove->Distance());
      bisectormap(noofbisectors)->IssuePoint(edgetoremove->IntersectionPoint());
      bisectormap(noofbisectors)->FirstEdge(theedgelist->PreviousItem());
      bisectormap(noofbisectors)->AddBisector(edgetoremove->FirstBisector());

      for (j = 0; j < noofarea(i); j++)
      {
        RemovedEdgesList->BackAdd(theedgelist->Current());
        theedgelist->Unlink();
        theedgelist->Next();
        shift++;

#ifdef OCCT_DEBUG_Mat
        std::cout << " Suppression de l'arete : " << edgetoremove->EdgeNumber() << std::endl;
#endif

        if (all == 0 || j + 1 != noofarea(i))
        {
          bisectormap(noofbisectors)->AddBisector(edgetoremove->SecondBisector());
        }
        edgetoremove->SecondBisector()->EndPoint(edgetoremove->IntersectionPoint());

#ifdef OCCT_DEBUG_Mat
        atool.Dump(edgetoremove->SecondBisector()->BisectorNumber(), 0);
#endif

        edgetoremove->SecondBisector()->SecondParameter(
          edgetoremove->SecondBisector()->FirstParameter());
#ifdef OCCT_DEBUG_Mat
        if (atool.TrimBisector(edgetoremove->SecondBisector()))
          atool.Dump(edgetoremove->SecondBisector()->BisectorNumber(), 1);
#else
        atool.TrimBisector(edgetoremove->SecondBisector());
#endif
        edgetoremove = theedgelist->Current();
      }
      bisectormap(noofbisectors)->SecondEdge(theedgelist->Current());

      theedgelist->PreviousItem()->SecondBisector(bisectormap(noofbisectors));
      theedgelist->Current()->FirstBisector(bisectormap(noofbisectors));

      bisectormap(noofbisectors)
        ->FirstVector(atool.Tangent(bisectormap(noofbisectors)->FirstBisector()->BisectorNumber()));

      bisectormap(noofbisectors)
        ->SecondVector(atool.Tangent(bisectormap(noofbisectors)->LastBisector()->BisectorNumber()));

      noofbisectors++;

      theedgelist->PreviousItem()->Distance(-1);
      theedgelist->Current()->Distance(-1);

      theedgelist->PreviousItem()->FirstBisector()->SecondParameter(Precision::Infinite());
      theedgelist->Current()->SecondBisector()->FirstParameter(Precision::Infinite());
    }

    if (NumberOfIte > NumberMaxOfIte)
    {
      isDone = false;
      break;
    }
    NumberOfIte++;
  }

  if (interrupt)
    semiInfinite = true;
  else
  {
    semiInfinite = false;

    if (theedgelist->Number() > 1)
    {

      theedgelist->First();
      edge = theedgelist->Current();
      if (edge->FirstBisector()->IndexNumber() == noofbisectors - 1)
      {

        if (atool.TrimBisector(edge->SecondBisector(), edge->FirstBisector()->IssuePoint()))
        {
          if (edge->SecondBisector()->EndPoint() == 0)
            edge->SecondBisector()->EndPoint(edge->FirstBisector()->IssuePoint());
          bisectormap(noofbisectors - 1)->AddBisector(edge->SecondBisector());
        }
        else
          semiInfinite = true;
      }
      else
      {

        if (atool.TrimBisector(edge->FirstBisector(), edge->SecondBisector()->IssuePoint()))
        {
          if (edge->FirstBisector()->EndPoint() == 0)
            edge->FirstBisector()->EndPoint(edge->SecondBisector()->IssuePoint());
          bisectormap(noofbisectors - 1)->AddBisector(edge->FirstBisector());
        }
        else
          semiInfinite = true;
      }
      if (!semiInfinite)
      {
        thenumberofbisectors--;
        bisectormap(noofbisectors - 1)->SecondEdge(edge);
        bisectormap(noofbisectors - 1)->BisectorNumber(-1);
      }
    }
  }
  if (semiInfinite)
  {
    beginbisector = noofbisectors;
    theedgelist->First();
    for (i = 0; i < theedgelist->Number(); i++)
    {
      edge = theedgelist->Current();
      bisectormap.Bind(noofbisectors, edge->SecondBisector());
      noofbisectors++;
      theedgelist->Next();
    }
  }

  roots = new MAT_ListOfBisector;

  if (bisectormap(noofbisectors - 1)->BisectorNumber() == -1)
  {
    roots = bisectormap(noofbisectors - 1)->List();
    roots->First();
    roots->Current()->FirstEdge()->Distance(bisectormap(noofbisectors - 1)->DistIssuePoint());
  }
  else
  {
    for (i = beginbisector; i < noofbisectors; i++)
    {
      roots->BackAdd(bisectormap(i));
    }
  }
}

void MAT2d_Mat2d::LoadBisectorsToRemove(int&                             noofbisectorstoremove,
                                        const double                     distance1,
                                        const double                     distance2,
                                        const occ::handle<MAT_Bisector>& firstbisectortoremove1,
                                        const occ::handle<MAT_Bisector>& firstbisectortoremove2,
                                        const occ::handle<MAT_Bisector>& lastbisectortoremove1,
                                        const occ::handle<MAT_Bisector>& lastbisectortoremove2)
{

  int                       found, index;
  occ::handle<MAT_Bisector> firstbisectortoremove[2];
  occ::handle<MAT_Bisector> lastbisectortoremove[2];

  firstbisectortoremove[0] = firstbisectortoremove1;
  firstbisectortoremove[1] = firstbisectortoremove2;
  lastbisectortoremove[0]  = lastbisectortoremove1;
  lastbisectortoremove[1]  = lastbisectortoremove2;

  if (distance1 < Precision::Infinite() && distance2 == Precision::Infinite())
    index = 0;
  else if (distance2 < Precision::Infinite() && distance1 == Precision::Infinite())
    index = 1;
  else
    index = -1;

  if (index != -1)
  {
    found = noofbisectorstoremove;
    for (int j = 0; j < noofbisectorstoremove; j++)
    {
      if (bisectoronetoremove(j)->BisectorNumber()
          == firstbisectortoremove[index]->BisectorNumber())
      {
        found = j;
        if (bisectortwotoremove(j)->BisectorNumber()
            < lastbisectortoremove[index]->BisectorNumber())
          found = -1;
        break;
      }
    }

    if (found != -1)
    {
#ifdef OCCT_DEBUG_Mat
      std::cout << " first last bisector to remove :"
                << firstbisectortoremove[index]->BisectorNumber() << " "
                << lastbisectortoremove[index]->BisectorNumber() << std::endl;
#endif
      bisectoronetoremove.Bind(found, firstbisectortoremove[index]);
      bisectortwotoremove.Bind(found, lastbisectortoremove[index]);
      typeofbisectortoremove.Bind(found, index + 1);

      if (found == noofbisectorstoremove)
        noofbisectorstoremove++;
    }
  }
}

void MAT2d_Mat2d::Intersect(MAT2d_Tool2d&                    atool,
                            const int                        aside,
                            int&                             noofbisectortoremove,
                            const occ::handle<MAT_Bisector>& firstbisector,
                            const occ::handle<MAT_Bisector>& secondbisector)
{
  int                       bisectornumber;
  double                    distant, saveparameter;
  double                    distance[2];
  int                       intersectionpoint;
  occ::handle<MAT_Bisector> lastbisector, previousbisector;
  occ::handle<MAT_Bisector> firstbisectortoremove[2];
  occ::handle<MAT_Bisector> lastbisectortoremove[2];

  distance[0] = Precision::Infinite();
  distance[1] = Precision::Infinite();

  for (bisectornumber = 0; bisectornumber < 2; bisectornumber++)
  {
    if (aside == 0)
    {
      if (bisectornumber == 0)
        firstbisectortoremove[bisectornumber] = secondbisector;
      else
        firstbisectortoremove[bisectornumber] = firstbisector;
    }
    else if (aside == 1)
    {
      firstbisectortoremove[bisectornumber] = firstbisector;
    }
    else
    {
      firstbisectortoremove[bisectornumber] = secondbisector;
    }

    lastbisector = firstbisectortoremove[bisectornumber];

    if (aside == 0)
    {
      previousbisector = firstbisectortoremove[bisectornumber];
    }
    else
    {
      if (firstbisectortoremove[bisectornumber]->List()->IsEmpty())
        continue;

      if (bisectornumber == 0)
        previousbisector = firstbisectortoremove[bisectornumber]->FirstBisector();
      else
        previousbisector = firstbisectortoremove[bisectornumber]->LastBisector();
    }

    distant = distance[bisectornumber];
    while (!previousbisector->List()->IsEmpty())
    {

      if (bisectornumber == 0)
        previousbisector = previousbisector->FirstBisector();
      else
        previousbisector = previousbisector->LastBisector();

      if (aside == 1 || (aside == 0 && bisectornumber == 0))
      {
        saveparameter = previousbisector->FirstParameter();
        distant       = atool.IntersectBisector(firstbisector, previousbisector, intersectionpoint);
        previousbisector->FirstParameter(saveparameter);
      }
      else
      {
        saveparameter = previousbisector->SecondParameter();
        distant = atool.IntersectBisector(previousbisector, secondbisector, intersectionpoint);
        previousbisector->SecondParameter(saveparameter);
      }

      if (distant < Precision::Infinite())
      {
        distance[bisectornumber]             = distant;
        lastbisectortoremove[bisectornumber] = lastbisector;
      }

      lastbisector = previousbisector;
    }
  }

  LoadBisectorsToRemove(noofbisectortoremove,
                        distance[0],
                        distance[1],
                        firstbisectortoremove[0],
                        firstbisectortoremove[1],
                        lastbisectortoremove[0],
                        lastbisectortoremove[1]);
}

void MAT2d_Mat2d::Init()
{
  roots->First();
}

bool MAT2d_Mat2d::More() const
{
  return roots->More();
}

void MAT2d_Mat2d::Next()
{
  roots->Next();
}

occ::handle<MAT_Bisector> MAT2d_Mat2d::Bisector() const
{
  return roots->Current();
}

int MAT2d_Mat2d::NumberOfBisectors() const
{
  return thenumberofbisectors;
}

bool MAT2d_Mat2d::SemiInfinite() const
{
  return semiInfinite;
}

bool MAT2d_Mat2d::IsDone() const
{
  return isDone;
}

MAT2d_Mat2d::~MAT2d_Mat2d()
{
  NCollection_DataMap<int, occ::handle<MAT_Bisector>>::Iterator itmap(bisectormap);
  for (; itmap.More(); itmap.Next())
  {
    const occ::handle<MAT_Bisector>& aBisector = itmap.Value();
    aBisector->FirstEdge(nullptr);
    aBisector->SecondEdge(nullptr);
  }

  if (!theedgelist.IsNull())
  {
    theedgelist->First();
    for (int i = 1; i <= theedgelist->Number(); i++)
    {
      occ::handle<MAT_Edge> anEdge = theedgelist->Current();
      anEdge->FirstBisector(nullptr);
      anEdge->SecondBisector(nullptr);
      theedgelist->Next();
    }
  }
  if (!RemovedEdgesList.IsNull())
  {
    RemovedEdgesList->First();
    for (int i = 1; i <= RemovedEdgesList->Number(); i++)
    {
      occ::handle<MAT_Edge> anEdge = RemovedEdgesList->Current();
      anEdge->FirstBisector(nullptr);
      anEdge->SecondBisector(nullptr);
      RemovedEdgesList->Next();
    }
  }
}
