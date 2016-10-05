//
// AComponent.hh for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/include
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Mon Feb  8 02:54:12 2016 Valerian Polizzi
// Last update Mon Feb 22 06:18:12 2016 Valerian Polizzi
//

#ifndef _COMPONENT_HH_
# define _COMPONENT_HH_
# include "IComponent.hpp"

class Component : public virtual nts::IComponent
{
  std::string		_name;
  std::string		_value;
  nts::IComponent	*link;
public:
  Component(const std::string &type, const std::string &value);
  ~Component(){};

  nts::Tristate		Compute(size_t pin_num_this = 1);
  void			SetLink(size_t pin_num_this,
				      nts::IComponent &component,
				      size_t pin_num_target);
  void			Dump(void);
};

#endif
