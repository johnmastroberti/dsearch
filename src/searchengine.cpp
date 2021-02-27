#include "searchengine.hpp"
#include <QProcess>
#include <algorithm>
#include <cstdio>
#include <fmt/core.h>
#include <iostream>
#include <sstream>

SearchEngine::SearchEngine() {}

SearchEngine::~SearchEngine() {}

SearchProg::SearchProg(std::string prog_name) : m_prog(prog_name) {}

std::string SearchProg::search(std::string querry) const {
  QProcess process;
  process.setProgram(QString::fromStdString(m_prog));
  std::cerr << "starting " << m_prog << '\n';
  process.start();
  if (!process.waitForStarted())
    return std::string("failed wait for started on program ") + m_prog;

  process.write(querry.c_str());
  process.closeWriteChannel();
  if (!process.waitForFinished())
    return std::string("failed wait for finished on program ") + m_prog;

  auto output = process.readAllStandardOutput();
  return output.toStdString();
}
//  auto cmd = fmt::format("{} '{}'", m_prog, querry);
//  std::cerr << cmd << '\n';
//  FILE *process = popen(cmd.c_str(), "r");
//  std::stringstream process_output;
//  char buf[1024];
//  while (fgets(buf, sizeof(buf), process))
//    process_output << buf;

//  if (pclose(process))
//    return "Search failed";
//  else
//    return fmt::format("{}\n{}", m_prog, process_output.str());
