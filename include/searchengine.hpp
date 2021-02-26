#pragma once
#include <string>

class SearchEngine {
public:
  SearchEngine();

  virtual ~SearchEngine();

  virtual std::string search(std::string) const = 0;
};

class SearchProg : public SearchEngine {
private:
  std::string m_prog;

public:
  SearchProg(std::string prog_name);

  std::string search(std::string) const;
};
