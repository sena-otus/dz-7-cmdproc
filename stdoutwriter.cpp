#include "stdoutwriter.h"
#include <iostream>

void stdoutwriter(
  const std::string &outstr,
  time_t ts  [[maybe_unused]],
  int suffix [[maybe_unused]])
{
  std::cout << "bulk: " << outstr
            << std::endl; // std::endl to flush the buffer
}
