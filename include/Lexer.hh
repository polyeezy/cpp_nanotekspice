//
// Lexer.hh for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/include
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Mon Feb 15 05:38:32 2016 Valerian Polizzi
// Last update Mon Feb 22 08:01:56 2016 Valerian Polizzi
//

#ifndef _LEXER_HH_
# define _LEXER_HH_

# include <map>
# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# define LEX_INPUT	0
# define LEX_CMD	1

class Lexer
{
private:
  std::map<std::string , std::string>	_lex;
  std::map<std::string , std::string>	_cmd;
public:
  Lexer(const std::string &file, const std::string &);
  ~Lexer();
  bool	lex_check(const std::string &, const std::string&) const;
  int	lex_line(const std::string &) const;

};

int		match(std::string &s1, std::string &s2);

#endif
