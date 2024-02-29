#pragma once

#include <ctime>
#include <string>
#include <functional>
#include <utility>

/**
 * Block разбирает входные строки на блоки и выводит их
 * */
class Block
{
public:
    /**
     * Конструктор принимает указатель на функцию для полученияв времени
     * Это используется только для тестирования
     * @param N размер блока
     * @param getTime функция возвращающая time_t
     * */
  explicit Block(unsigned N, std::function<time_t()> getTime = [](){ return std::time(nullptr);});

    /**
     *  Разобрать строку и вывести блок по готовности
     *  @param line строка для разбора
     *  */
  void parseLine(const std::string& line);

    /**
     * Вывести накопленные данные (вызывается по получению EOF)
     * */
    void finalize();

private:
    /**
     * Добвавить строку в буфер
     * @param line строка для обновления
     * */
  void append(const std::string &line);
    /**
     * Вывести накопленные данные и очистить буфер
     * */
  void flush();

private:
  std::string m_str;
  unsigned m_cmdnum{0};
  time_t m_timestamp{};
  int m_lineno{0};
  int m_extendedModeLevel{0};
  unsigned m_N;
  int suffix{0};
  std::function<time_t()> m_getTime;
};
