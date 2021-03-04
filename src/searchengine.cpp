#include "searchengine.hpp"
#include <QProcess>
#include <algorithm>
#include <cstdio>
#include <fmt/core.h>
#include <iostream>
#include <sstream>

SearchEngine::SearchEngine() {}

SearchEngine::~SearchEngine() {}

SearchProg::SearchProg(QString prog_name) : m_prog(prog_name) {}

QString SearchProg::search(QString querry) const {
  QProcess process;
  process.setProgram(m_prog);
  std::cerr << "starting " << m_prog.toStdString() << '\n';
  process.start();
  if (!process.waitForStarted())
    return QString("failed wait for started on program ") + m_prog;

  auto querry_array = querry.toLatin1();
  process.write(querry_array.data());
  process.closeWriteChannel();
  if (!process.waitForFinished())
    return QString("failed wait for finished on program ") + m_prog;

  auto output = QString(process.readAllStandardOutput());
  output.replace('\n', ' ');
  if (output.length() == 0)
    return output;
  else
    return m_prog + "\n" + output.trimmed();
}
