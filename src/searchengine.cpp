#include "searchengine.hpp"
#include <algorithm>
#include <cstdio>
#include <fmt/core.h>
#include <iostream>
#include <sstream>

SearchEngine::SearchEngine() {}

SearchEngine::~SearchEngine() {}

SearchProg::SearchProg(std::string prog_name) : m_prog(prog_name) {}

std::string SearchProg::search(std::string querry) const {
  auto cmd = fmt::format("{} '{}'", m_prog, querry);
  std::cerr << cmd << '\n';
  FILE *process = popen(cmd.c_str(), "r");
  std::stringstream process_output;
  char buf[1024];
  while (fgets(buf, sizeof(buf), process))
    process_output << buf;

  if (pclose(process))
    return "Search failed";
  else
    return fmt::format("{}\n{}", m_prog, process_output.str());
}
