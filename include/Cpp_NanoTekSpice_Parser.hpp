//
// Cpp_NanoTekSpice_Paser.hpp for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/include
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Fri Feb 12 02:54:23 2016 Valerian Polizzi
// Last update Mon Feb 22 01:36:37 2016 Valerian Polizzi
//

#ifndef _CPP_NANOTEKSPICE_PARSER_HPP_
# define _CPP_NANOTEKSPICE_PARSER_HPP_

# include <string>
# include <vector>
# include <fstream>

namespace nts
{
  enum class ASTNodeType : int
  {
    DEFAULT = -1,
      NEWLINE = 0,
      SECTION = 1,
      COMPONENT = 2,
      LINK = 3,
      LINK_END = 4,
      STRING = 5
      };

  typedef struct s_ast_node
  {
    s_ast_node(std::vector<struct s_ast_node*> *children) : children(children) { }
    std::string lexeme;
    ASTNodeType type;
    std::string value;
    std::vector<struct s_ast_node*> *children;
  }		t_ast_node;

  class IParser
  {
  public:
    IParser(){}
    virtual void feed(const std::string & input) = 0;
    virtual void parseTree(t_ast_node& root) = 0;
    virtual t_ast_node *createTree() = 0;
    virtual ~IParser(){}
  };
}

#endif
