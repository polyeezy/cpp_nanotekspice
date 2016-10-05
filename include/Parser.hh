//
// Parser.hh for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/src
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Fri Feb 12 02:58:34 2016 Valerian Polizzi
// Last update Fri Feb 26 04:42:54 2016 Valerian Polizzi
//

#ifndef _PARSER_HH_
# define _PARSER_HH_

# include <map>
# include <iostream>
# include "Cpp_NanoTekSpice_Parser.hpp"
# include "NTSException.hh"
# include "Lexer.hh"

# define CHIPSETS_NODE		"chipsets"
# define LINKS_NODE		"links"
# define MANUAL_NODE		"manual_component"
# define COMPONENT_NODE		"component"
# define INPUT_NODE		"inputs"
# define OUTPUT_NODE		"outputs"

# define SECTION_TOKEN		6
# define SECTION_LEX		".*:"
# define INPUT_TOKEN		7
# define INPUT_LEX		"input"
# define OUTPUT_TOKEN		8
# define OUTPUT_LEX		"output"
# define COMPONENT_TOKEN	9
# define COMPONENT_LEX		"%"
# define LINK_TOKEN		10
# define LINK_LEX		"#%:%"
# define CLOCK_TOKEN		11
# define CLOCK_LEX		"clock"
# define TRUE_TOKEN		12
# define TRUE_LEX		"true"
# define FALSE_TOKEN		13
# define FALSE_LEX		"false"

# define CMD_DISPLAY		0
# define CMD_NEW_VALUE		1
# define CMD_SIMULATE		2
# define CMD_LOOP		3
# define CMD_DUMP		4
# define CMD_EXIT		5

class Parser : public nts::IParser
{
  std::vector<void (Parser::*)(const std::string&, const std::string&)>	_fcn;
  std::string						_line;
  Lexer							_lex;
  nts::t_ast_node					*_head;
  std::string						_input;
public:
  Parser();
  ~Parser();
  const Lexer		&getLexer();
  void			createSection(const std::string &, const std::string&);
  void			createInput(const std::string &, const std::string&);
  void			createOutput(const std::string &, const std::string&);
  void			createComponent(const std::string &, const std::string&);
  void			createLink(const std::string &, const std::string&);
  void			createClock(const std::string &, const std::string&);
  void			createTrue(const std::string &, const std::string&);
  void			createFalse(const std::string &, const std::string&);
  void			dump_node(const nts::t_ast_node*);
  int			check_cmd(const std::string&);
  void			read();
  int			print_from_lex(const nts::t_ast_node*, const std::string &);
  nts::t_ast_node	*create_node(const std::string &, const std::string&, const nts::ASTNodeType&);
  nts::t_ast_node	*newNode();
  nts::t_ast_node	*pile(const nts::t_ast_node *, const std::string&);
  nts::t_ast_node	*pile_or_create(const nts::t_ast_node*, const std::string &, const std::string&, const nts::ASTNodeType);
  void			save_data(int, const std::string &, const std::string &);
  void			feed_lex(const std::string &file);
  void			feed(const std::string & input);
void			open(const std::string & input);
  void			parseTree(nts::t_ast_node& root);
  int		       	children_exists(const nts::t_ast_node *, const std::string &) const;
  nts::t_ast_node	*createTree();
  void			incr_line();
  nts::t_ast_node	*getHead() const;
};

#endif
