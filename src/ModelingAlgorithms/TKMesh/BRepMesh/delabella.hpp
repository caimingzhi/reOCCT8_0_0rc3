#pragma once

int DelaBella(int points, const double* xy, int* abc, int (*errlog)(const char* fmt, ...) = printf);

struct DelaBella_Vertex
{
  int               i;
  double            x, y;
  DelaBella_Vertex* next;
};

struct DelaBella_Triangle
{
  DelaBella_Vertex*   v[3];
  DelaBella_Triangle* f[3];
  DelaBella_Triangle* next;
};

#ifdef __cplusplus
struct IDelaBella
{
  static IDelaBella* Create();

  virtual void Destroy() = 0;

  virtual void SetErrLog(int (*proc)(void* stream, const char* fmt, ...), void* stream) = 0;

  virtual int Triangulate(int          points,
                          const float* x,
                          const float* y             = 0,
                          int          advance_bytes = 0) = 0;
  virtual int Triangulate(int           points,
                          const double* x,
                          const double* y             = 0,
                          int           advance_bytes = 0) = 0;

  virtual int GetNumInputPoints() const = 0;

  virtual int GetNumOutputVerts() const = 0;

  virtual const DelaBella_Triangle* GetFirstDelaunayTriangle() const = 0;
  virtual const DelaBella_Triangle* GetFirstHullTriangle() const     = 0;
  virtual const DelaBella_Vertex*   GetFirstHullVertex() const       = 0;
};
#else
void* DelaBella_Create();
void  DelaBella_Destroy(void* db);
void  DelaBella_SetErrLog(void* db, int (*proc)(void* stream, const char* fmt, ...), void* stream);
int DelaBella_TriangulateFloat(void* db, int points, float* x, float* y = 0, int advance_bytes = 0);
int DelaBella_TriangulateDouble(void*   db,
                                int     points,
                                double* x,
                                double* y             = 0,
                                int     advance_bytes = 0);
int DelaBella_GetNumInputPoints(void* db);
int DelaBella_GetNumOutputVerts(void* db);
const DelaBella_Triangle* GetFirstDelaunayTriangle(void* db);
const DelaBella_Triangle* GetFirstHullTriangle(void* db);
const DelaBella_Vertex*   GetFirstHullVertex(void* db);
#endif
