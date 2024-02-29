#include <iostream>
#include <stdexcept>
#include <ctime>

const int generic_errorcode = 101;

class Block
{
public:
  // void parseLine(std::string && line)
  // {
  // }


  void append(const std::string &line)
  {
    if(m_cmdnum == 0) {
      m_str = line;
      m_timestamp = std::time(nullptr);
    }
    else {
       m_str += ", " + line;
    }
    m_cmdnum++;
  }

  void print()
  {
    if(m_cmdnum > 0) {
      std::cout << "bulk: "  << m_str << std::endl; // std::endl to flush the buffer
      m_cmdnum = 0;
    }
  }

  [[nodiscard]] unsigned cmdnum() const { return m_cmdnum;}

private:
  std::string m_str;
  unsigned m_cmdnum{0};
  time_t m_timestamp{};
};



  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  // NOLINTBEGIN(readability-braces-around-statements,hicpp-braces-around-statements)
  // NOLINTNEXTLINE(hicpp-named-parameter,readability-named-parameter)
int main(int argc, char const *argv[] )
{
  try {
    unsigned N{0};

    if(argc != 2)
    {
      std::cout << "Запуск:\n bulk <N>\n\n"
                << " где <N> это количество команд в блоке для обработки\n";
      return 0;
    }

    try {
      N = std::stoul(argv[1]);
    }
    catch(...) {
      throw std::runtime_error("Единственный аргумент командной строки дожен быть положительным числом");
    }

    int lineno{0};
    Block block;
    int extendedModeLevel{0};
    for(std::string line; std::getline(std::cin, line);++lineno)
    {
      if(line == "{")
      {
        extendedModeLevel++;
        if(extendedModeLevel > 1) continue;
        block.print();
        continue;
      }

      if(line == "}")
      {
        extendedModeLevel--;
        if(extendedModeLevel > 0) continue;
        if(extendedModeLevel < 0) throw std::runtime_error("нарушен баланс скобок в строке " + std::to_string(lineno));
        block.print();
        continue;
      }

      if(block.cmdnum() < N || extendedModeLevel > 0) block.append(line);

      if(block.cmdnum() == N && extendedModeLevel == 0) block.print();
    }
    block.print();
    return 0;
  }
  catch(const std::exception &e)
  {
    std::cerr << "Ошибка\n" << e.what() << std::endl;
    return generic_errorcode;
  }
}
  // NOLINTEND(readability-braces-around-statements,hicpp-braces-around-statements)
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
