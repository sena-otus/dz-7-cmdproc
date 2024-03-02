#pragma once

#include <string>

/**
 * @brief bulk вывод в файл
 * @see Block::writer_t
 * @see Block::m_wlist
 * @param outstr строка с командами для вывода
 * @param ts  метка времени
 * @param suffix суффикс
 * */
extern void filewriter(const std::string &outstr, time_t ts, int suffix);
