//
// Parser.cpp for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/src
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Fri Feb 12 03:01:42 2016 Valerian Polizzi
// Last update Fri Feb 26 05:50:14 2016 Valerian Polizzi
//

#include "Parser.hh"
# include <fstream>

Parser::Parser() : _line("0"), _lex("misc/lex/nts.lex", "misc/lex/cmd.lex"), _head(this->createTree())
{
  this->_fcn.push_back(&Parser::createSection);
  this->_fcn.push_back(&Parser::createInput);
  this->_fcn.push_back(&Parser::createOutput);
  this->_fcn.push_back(&Parser::createComponent);
  this->_fcn.push_back(&Parser::createLink);
  this->_fcn.push_back(&Parser::createClock);
  this->_fcn.push_back(&Parser::createFalse);
  this->_fcn.push_back(&Parser::createTrue);
}

Parser::~Parser()
{
}

void		Parser::feed(const std::string &input)
{
  std::stringstream	content(input);
  std::string		token("");
  std::string		value("");
  int			token_id(0);

  content >> token >> value;
  if (input.size() == 0)
    throw nts::Exception("[NTS] Syntax error : Empty input (line " + this->_line + ")");
  if ((token_id = this->_lex.lex_line(token)) == -1)
      throw nts::Exception("[NTS] Syntax error : Implicit input '" + input + "' (line " + this->_line + ")");
  if (token_id >= 6)
    (this->*_fcn[token_id - 6])(token, value);
}

nts::t_ast_node		*Parser::create_node(const std::string &lexeme, const std::string &value, const nts::ASTNodeType &type)
{
  nts::t_ast_node	*data = new nts::t_ast_node(new std::vector<nts::t_ast_node*>);

  data->lexeme = lexeme;
  data->type = type;
  data->value = value;
  return (data);
}

int			Parser::print_from_lex(const nts::t_ast_node *head, const std::string &lex)
{
   int			i;

  i = 0;
  for (std::vector<nts::t_ast_node*>::iterator it = head->children->begin(); it != head->children->end(); it++)
    {
      if ((*it)->lexeme.compare(lex) == 0)
	std::cout << (*it)->value << std::endl;
      i++;
    }
  return (0);
}

std::string	epur_alpha(std::string str)
{
  size_t i = 0;
  size_t len = str.length();
  while(i < len)
    {
      if (!isalnum(str[i]))
	{
	str.erase(i,1);
	len--;
      }
      else
	i++;
    }
  return (str);
}

const Lexer		&Parser::getLexer()
{
  return (_lex);
}

int			Parser::children_exists(const nts::t_ast_node *head, const std::string &to_find) const
{
  int			i;

  i = 0;
  for (std::vector<nts::t_ast_node*>::iterator it = head->children->begin(); it != head->children->end(); it++)
    {
      if ((*it)->value.compare(to_find) == 0)
	return (i);
      i++;
    }
  return (-1);
}

nts::t_ast_node		*Parser::pile(const nts::t_ast_node *head, const std::string &value)
{
  int       		children_id = 0;

  if ((children_id = children_exists(head, value)) != -1)
    return (head->children->at(children_id));
  return (NULL);
}


nts::t_ast_node		*Parser::pile_or_create(const nts::t_ast_node *ptr, const std::string &to_go, const std::string &lex, const nts::ASTNodeType ast)
{
  if (!pile(ptr, to_go))
    ptr->children->push_back(this->create_node(lex, to_go, ast));
  return (pile(ptr, to_go));
}

int		Parser::check_cmd(const std::string &line)
{
  int		token_id = this->_lex.lex_line(line);

  if (token_id == -1)
    throw nts::Exception("[NTS] Parse Error : unknown command : '" + line + "' (line " + this->_line + ")");
  return (token_id);
}

void		Parser::createSection(const std::string &token, const std::string &value)
 {
   if (children_exists(_head, std::string(token).erase(0, 1).erase(token.size() - 2, 1)) != -1)
     throw nts::Exception("[NTS] Parse Error : multiple definition of section '" + token + "' line "+ _line);
   _head->children->push_back(create_node(SECTION_LEX,std::string(token).erase(0, 1).erase(token.size() - 2, 1),nts::ASTNodeType::SECTION));
   (void)value;
 }

void		Parser::createInput(const std::string &token, const std::string &value)
{
  nts::t_ast_node	*ptr = NULL;

  if ((ptr = pile(_head, CHIPSETS_NODE)))
    {
      ptr = pile_or_create(ptr, "manual_component", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr = pile_or_create(ptr, "inputs", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr->children->push_back(create_node(INPUT_LEX, value, nts::ASTNodeType::COMPONENT));
    }
  else
    throw nts::Exception("[NTS] Parse Error : can't access to  '" + std::string(CHIPSETS_NODE) + "' line "+ _line);
}

void		Parser::createOutput(const std::string &token, const std::string &value)
{
  nts::t_ast_node	*ptr = NULL;

  if ((ptr = pile(_head, CHIPSETS_NODE)))
    {
      ptr = pile_or_create(ptr, "manual_component", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr = pile_or_create(ptr, "outputs", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr->children->push_back(create_node(OUTPUT_LEX, std::string(value).append("=0"), nts::ASTNodeType::COMPONENT));
    }
  else
      throw nts::Exception("[NTS] Parse Error : can't access to  '" + std::string(CHIPSETS_NODE) + "' line "+ _line);
}

void		Parser::createComponent(const std::string &token, const std::string &value)
{
  nts::t_ast_node	*ptr = NULL;

  if ((ptr = pile(_head, CHIPSETS_NODE)))
    {
      ptr = pile_or_create(ptr, "component", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr->children->push_back(create_node(COMPONENT_LEX ,std::string(token).append(":").append(value),nts::ASTNodeType::COMPONENT));
    }
  else
    throw nts::Exception("[NTS] Parse Error : can't access to  '" + std::string(CHIPSETS_NODE) + "' line "+ _line);
}

void		Parser::createLink(const std::string &token, const std::string &value)
{
  nts::t_ast_node	*ptr = NULL;
  nts::t_ast_node	*link = NULL;

  if ((ptr = pile(_head, LINKS_NODE)))
    {
      link = create_node(LINK_LEX, epur_alpha(std::string(token)).append("-").append(epur_alpha(std::string(value))), nts::ASTNodeType::LINK);
      link->children->push_back(create_node(LINK_LEX, std::string(token), nts::ASTNodeType::LINK));
      link->children->push_back(create_node(LINK_LEX, std::string(value), nts::ASTNodeType::LINK));
      ptr->children->push_back(link);
    }
  else
    throw nts::Exception("[NTS] Parse Error : can't access to  '" + std::string(LINKS_NODE) + "' line "+ _line);
}

void		Parser::createClock(const std::string &token, const std::string &value)
{
  nts::t_ast_node	*ptr = NULL;

  if ((ptr = pile(_head, CHIPSETS_NODE)))
    {
      ptr = pile_or_create(ptr, "manual_component", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr = pile_or_create(ptr, "clocks", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr->children->push_back(create_node(OUTPUT_LEX, std::string(value).append("=0"), nts::ASTNodeType::COMPONENT));
    }
}

void		Parser::createTrue(const std::string &token, const std::string &value)
{
  nts::t_ast_node	*ptr = NULL;

  if ((ptr = pile(_head, CHIPSETS_NODE)))
    {
      ptr = pile_or_create(ptr, "manual_component", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr = pile_or_create(ptr, "trues", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr->children->push_back(create_node(OUTPUT_LEX, std::string(value).append("=0"), nts::ASTNodeType::COMPONENT));
    }
}

void		Parser::createFalse(const std::string &token, const std::string &value)
{
  nts::t_ast_node	*ptr = NULL;

  if ((ptr = pile(_head, CHIPSETS_NODE)))
    {
      ptr = pile_or_create(ptr, "manual_component", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr = pile_or_create(ptr, "falses", INPUT_LEX, nts::ASTNodeType::COMPONENT);
      ptr->children->push_back(create_node(OUTPUT_LEX, std::string(value).append("=0"), nts::ASTNodeType::COMPONENT));
    }
}

void		Parser::parseTree(nts::t_ast_node &root)
{
  std::cout << "In " << root.value << std::endl;
  for (std::vector<nts::t_ast_node*>::iterator it = root.children->begin(); it != root.children->end(); it++)
    {
      std::cout << "----" <<  (*it)->value << std::endl;
    }
}

nts::t_ast_node	*Parser::getHead() const
{
  return (_head);
}

nts::t_ast_node	*Parser::createTree()
{
  return (create_node("head", "head", nts::ASTNodeType::SECTION));
}

nts::t_ast_node	*Parser::newNode()
{
  return (new nts::t_ast_node(new std::vector<nts::t_ast_node*>));
}

void		Parser::incr_line(void)
{
  this->_line = std::to_string(atoi(this->_line.c_str()) + 1);
}
