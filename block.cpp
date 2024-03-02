#include "block.h"
#include <algorithm>

Block::Block(
  std::list<writer_t> &&wlist,
  std::function<time_t()> getTime)
  : m_wlist(std::move(wlist)), m_getTime(std::move(getTime)) {}

void Block::append(const std::string &line) {
  if (m_cmdnum == 0) {
    m_str = line;
    const time_t newts = m_getTime();
    if (newts == m_timestamp) { // same timestamp like in previous file
      m_suffix++;                 // add suffix
    } else {                    // no suffix
      m_suffix = 0;
    }
    m_timestamp = newts;
  } else {
    m_str += ", " + line;
  }
  m_cmdnum++;
}

[[nodiscard]] unsigned Block::cmdnum() const { return m_cmdnum; }

void Block::flush() {
  if (m_cmdnum > 0) {
    std::for_each(m_wlist.begin(), m_wlist.end(),
                  [&](writer_t &f){f(m_str, m_timestamp, m_suffix);});
    m_cmdnum = 0;
  }
}
