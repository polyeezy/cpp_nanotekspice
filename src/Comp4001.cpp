//
// Comp4001.cpp for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/src
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Mon Feb  8 05:04:35 2016 Valerian Polizzi
// Last update Mon Feb 22 06:19:06 2016 Valerian Polizzi
//

#include "Comp4001.hh"

Comp4001::Comp4001(const std::string &value) : Component("4001", value)
{
}

Comp4001::~Comp4001()
{
}

nts::Tristate       Comp4001::Compute()
{
  return nts::TRUE;
}

void                Comp4001::SetLink(size_t pin_num_this,
			    nts::IComponent &component,
			    size_t pin_num_target)
{
  pin_num_this += 0;
  pin_num_target += 0;
  (void)component;
}
