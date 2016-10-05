//
// Comp4001.hh for NTS in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/include
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Mon Feb  8 05:02:35 2016 Valerian Polizzi
// Last update Mon Feb 22 06:19:20 2016 Valerian Polizzi
//

#ifndef _COMP4001_HH_
# define _COMP4001
# include "Component.hh"

class Comp4001 : public Component
{
public:
  Comp4001(const std::string &value);
  ~Comp4001();

  nts::Tristate       Compute();
  void                SetLink(size_t pin_num_this,
			      nts::IComponent &component,
			      size_t pin_num_target);
};


#endif
