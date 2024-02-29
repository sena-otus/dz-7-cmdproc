#pragma once

#include <string>

class Block
{
public:
  explicit Block(unsigned N) : m_N(N) {}

  void parseLine(const std::string& line);
  void append(const std::string &line);
  void print();
  void finalize();
private:
  std::string m_str;
  unsigned m_cmdnum{0};
  time_t m_timestamp{};
  int m_lineno{0};
  int m_extendedModeLevel{0};
  unsigned m_N;
  int suffix{0};
};
