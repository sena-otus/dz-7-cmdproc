#include "block.h"
#include "parser.h"
#include "stdoutwriter.h"
#include "filewriter.h"
#include <iostream>
#include <stdexcept>


const int generic_errorcode = 101;

int main(int argc, char const *argv[] )
{
  try {
    unsigned N{0};

    if(argc != 2)
    {
      std::cout << "Запуск:\n bulk <N>\n\n где <N> это количество команд в блоке для обработки\n";
      return 0;
    }

    try {
      N = std::stoul(argv[1]);
    }
    catch(...) {
      throw std::runtime_error("Единственный аргумент командной строки дожен быть положительным числом");
    }

    Block block({stdoutwriter, filewriter});
    Parser parser(N, block);
    for(std::string line; std::getline(std::cin, line);) {
      parser.parse(line);
    }
    parser.finalize();
    return 0;
  }
  catch(const std::exception &e)
  {
    std::cerr << "Ошибка\n" << e.what() << std::endl;
    return generic_errorcode;
  }
}
