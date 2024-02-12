#include <iostream>
#include <stdexcept>

const int parsing_errorcode = 101;

  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  // NOLINTNEXTLINE(hicpp-named-parameter,readability-named-parameter)
int main(int argc, char const *argv[] )
{
  int errorcode = 0;
  int N{0};

  if(argc == 2)
  {
    try {
      N = std::stoi(argv[1]);
    }
    catch(const std::exception &e)
    {
      std::cerr << "Единственные параметр должен быть целым числом\n" << std::endl;
      errorcode = parsing_errorcode;
    }
  }
  if(argc != 2 || errorcode != 0)
  {
    std::cout << "Запуск:\n"
              << argv[0] << " <N>\n\n"
              << " где <N> это количество команд в блоке для обработки\n";
    exit(errorcode);
  }

  int lineno{0};
  int cmdnum{0};
  std::string blockoutput;
  int extendedModeLevel{0};
  for(std::string line; std::getline(std::cin, line);++lineno)
  {
    try {
      if(line == "{")
      {
        extendedModeLevel++;
        if(extendedModeLevel > 1)
        {
          continue;
        }
        if(!blockoutput.empty())
        {
          std::cout << "bulk: "  << blockoutput << "\n";
          blockoutput.clear();
        }
        cmdnum = 0;
        continue;
      }

      if(line == "}")
      {
        extendedModeLevel--;
        if(extendedModeLevel > 0)
        {
          continue;
        }
        if(extendedModeLevel < 0)
        {
          throw std::runtime_error("нарушен баланс скобок");
        }
        if(!blockoutput.empty())
        {
          std::cout << "bulk: "  << blockoutput << "\n";
          blockoutput.clear();
        }
        cmdnum = 0;
        continue;
      }

      if(cmdnum < N || extendedModeLevel > 0)
      {
        blockoutput += (cmdnum == 0) ? line : (", " + line);
        cmdnum++;
      }
      if(cmdnum == N && extendedModeLevel == 0) {
        std::cout << "bulk: "  << blockoutput << "\n";
        blockoutput.clear();
        cmdnum = 0;
      }
    }
    catch(const std::exception &e)
    {
      std::cerr << "Error in line " << lineno << ": " << e.what() << std::endl;
      return parsing_errorcode;
    }
  }
  if(!blockoutput.empty())
  {
    std::cout << "bulk: "  << blockoutput << "\n";
  }
  return 0;
}
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
