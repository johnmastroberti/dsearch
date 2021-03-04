#pragma once
#include <QString>

class SearchEngine {
public:
  SearchEngine();

  virtual ~SearchEngine();

  virtual QString search(QString) const = 0;
};

class SearchProg : public SearchEngine {
private:
  QString m_prog;

public:
  SearchProg(QString prog_name);

  QString search(QString) const;
};
