#include "filewriter.h"

#include <boost/format.hpp>
#include <filesystem>
#include <fstream>


void filewriter(const std::string &outstr, time_t ts, int suffix)
{
  namespace fs = std::filesystem;
  std::string fname;
  if (suffix == 0) {
    fname = "bulk" + std::to_string(ts) + ".log";
  } else {
    fname = str(boost::format("bulk%d-%03d.log") % ts % suffix);
  }
  if (fs::exists(fname))
    throw std::runtime_error("невозможно создать файл '" + fname +
                             "', потому что он уже существует");
  std::ofstream ofs(fname);
  ofs << "bulk: " << outstr << "\n";
  if (ofs.bad())
    throw std::runtime_error("ошибка записи в файл " + fname);
}
