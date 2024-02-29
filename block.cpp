#include "block.h"
#include <exception>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <boost/format.hpp>


Block::Block(unsigned N, std::function<time_t()> getTime)
  : m_N(N), m_getTime(std::move(getTime))
{}


void Block::parseLine(const std::string& line)
{
  m_lineno++;
  if(line == "{")
  {
    m_extendedModeLevel++;
    if(m_extendedModeLevel > 1) return;
    flush();
    return;
  }
  if(line == "}")
  {
    m_extendedModeLevel--;
    if(m_extendedModeLevel > 0) return;
    if(m_extendedModeLevel < 0) throw std::runtime_error("лишняя скобка } в строке " + std::to_string(m_lineno));
    flush();
    return;
  }
  if(m_cmdnum < m_N || m_extendedModeLevel > 0) append(line);
  if(m_cmdnum == m_N && m_extendedModeLevel == 0) flush();
}


void Block::append(const std::string &line)
{
  if(m_cmdnum == 0) {
    m_str = line;
    const time_t newts = m_getTime();
    if(newts == m_timestamp) { // same timestamp like in previous file
      suffix++; // add suffix
    }
    else { // no suffix
      suffix = 0;
    }
    m_timestamp = newts;
  }
  else {
    m_str += ", " + line;
  }
  m_cmdnum++;
}


void Block::flush()
{
  namespace fs = std::filesystem;
  if(m_cmdnum > 0) {
    std::string fname;
    if(suffix == 0) {
      fname = "bulk" + std::to_string(m_timestamp) +".log";
    }
    else {
      fname = str(boost::format("bulk%d-%03d.log") % m_timestamp % suffix);
    }
    if(fs::exists(fname)) throw std::runtime_error("невозможно создать файл '"+fname+"', потому что он уже существует");
    std::ofstream ofs(fname);
    std::cout << "bulk: "  << m_str << std::endl; // std::endl to flush the buffer
    ofs << "bulk: "  << m_str << "\n";
    m_cmdnum = 0;
    if(ofs.bad()) throw std::runtime_error("ошибка записи в файл " + fname);
  }
}

void Block::finalize()
{
  if(m_extendedModeLevel==0)
  {
    flush();
  }
}
