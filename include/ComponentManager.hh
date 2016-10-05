//
// ComponentManager.hh for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/include
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Mon Feb  8 01:43:42 2016 Valerian Polizzi
// Last update Fri Feb 26 06:43:33 2016 Valerian Polizzi
//

#ifndef _COMPONENTMANAGER_HH_
# define _COMPONENTMANAGER_HH_

# include <signal.h>
# include <utility>
# include <string>
# include <iostream>
# include <map>
# include "IComponent.hpp"
# include "Components.hh"
# include "Parser.hh"
# include "NTSException.hh"

# define VALUE_SEP	"="

extern int		g_sig;

class ComponentManager
{
private:
  std::map<const std::string, nts::IComponent* (ComponentManager::*)(const std::string&)const>				_pointers;
  std::vector<void (ComponentManager::*)(const std::string&)>								_fcn;
  std::map<const std::string, std::vector<nts::IComponent*>>	       				_container;
  Parser	_parser;
  int		_loop;
public:
  ComponentManager(const std::string &file);
  ~ComponentManager();
  static void				signal_handler(int);
  int				read();
  void				open(const std::string&);
  Parser			&getParser();
  void				display(const std::string&);
  void				print(nts::t_ast_node*);
  void				changeValue(const std::string&);
  void				simulate(const std::string&);
  void				loop(const std::string&);
  void				dump(const std::string&);
  void				exit(const std::string&);
  void				link(const std::string &);
  void				clock(const std::string &);
  void				True(const std::string &);
  void				False(const std::string &);
  void				newComponent(const std::string &);
  void				create_input(const std::string &input);
  void				create_output(const std::string &input);
  void				do_nothing(const std::string&);
  int				print_from_lex(const nts::t_ast_node*, const std::string&);
  void				addComponent(const std::string &, nts::IComponent* (ComponentManager::*ComponentPtr)(const std::string&)const);
  void				push_component(const std::string&, const std::string&);
  nts::IComponent		*CreateComponent(const std::string &type, const std::string &value);
private:
  nts::IComponent		*Create4001(const std::string &value) const;
};

#endif
