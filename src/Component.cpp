//
// AComponent.cpp for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/src
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Mon Feb  8 03:37:03 2016 Valerian Polizzi
// Last update Mon Feb 22 06:20:11 2016 Valerian Polizzi
//

#include "Component.hh"

Component::Component(const std::string &name, const std::string &value) :  _name(name), _value(value)
{
}

nts::Tristate       Component::Compute(size_t pin)
{
  pin += 0;
  return (nts::TRUE);
}

void                Component::SetLink(size_t pin_num_this,
				    nts::IComponent &component,
				    size_t pin_num_target)
{
  pin_num_this += 0;
  pin_num_target += 0;
  (void)component;
}

void			Component::Dump(void)
{

}
