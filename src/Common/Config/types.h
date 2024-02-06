#pragma once

// These classes exist to allow dynamic casting and checking of "primitive data types"
// Only a wrapper for config

#include <cstring>
#include <string>

class BaseType {
public:
  virtual ~BaseType() = default;
};

// Polymorphic copy of std::string
class CString : public BaseType {
public:
  CString(std::string value) { m_string = value; }
  std::string *ref() { return &m_string; }
  std::string get() { return m_string; }

  char *getC_str() { return &m_string[0]; }
  const char *c_str() { return m_string.c_str(); }

private:
  std::string m_string = "";
};

// Polymorphic copy of int
class CInt : public BaseType {
public:
  CInt(int value) { m_int = value; }
  int *ref() { return &m_int; }
  int get() { return m_int; }

private:
  int m_int;
};

// Polymorphic copy of float
class CFloat : public BaseType {
public:
  CFloat(float value) { m_float = value; }
  float *ref() { return &m_float; }
  float get() { return m_float; }

private:
  float m_float;
};

class CBool : public BaseType {
public:
  CBool(bool value) { m_bool = value; }
  bool *ref() { return &m_bool; }
  bool get() { return m_bool; }

private:
  bool m_bool;
};