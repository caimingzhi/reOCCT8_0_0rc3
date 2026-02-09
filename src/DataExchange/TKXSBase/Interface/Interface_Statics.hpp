#pragma once

#define StaticHandle(type, var)                                                                    \
  static struct type##_struc                                                                       \
  {                                                                                                \
    Handle(type) H;                                                                                \
  }* var##_s = NULL

#define StaticHandleA(type, var) static struct type##_struc* var##_s = NULL

#define UseHandle(type, var) Handle(type)& var = var##_s->H

#define InitHandle(type, var)                                                                      \
  if (!var##_s)                                                                                    \
  {                                                                                                \
    var##_s = new type##_struc;                                                                    \
  }                                                                                                \
  Handle(type)& var = var##_s->H;

#define InitHandleVoid(type, var)                                                                  \
  if (!var##_s)                                                                                    \
  {                                                                                                \
    var##_s    = new type##_struc;                                                                 \
    var##_s->H = new type;                                                                         \
  }                                                                                                \
  Handle(type)& var = var##_s->H;

#define InitHandleArgs(type, var, args)                                                            \
  if (!var##_s)                                                                                    \
  {                                                                                                \
    var##_s    = new type##_struc;                                                                 \
    var##_s->H = new type args;                                                                    \
  }                                                                                                \
  Handle(type)& var = var##_s->H;

#define InitHandleVal(type, var, value)                                                            \
  if (!var##_s)                                                                                    \
  {                                                                                                \
    var##_s    = new type##_struc;                                                                 \
    var##_s->H = value;                                                                            \
  }                                                                                                \
  Handle(type)& var = var##_s->H;
