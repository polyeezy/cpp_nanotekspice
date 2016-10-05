//
// IComponent.hpp for nanotekspice in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/include
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Mon Feb  8 01:09:45 2016 Valerian Polizzi
// Last update Fri Feb 12 02:53:19 2016 Valerian Polizzi
//

#ifndef _ICOMPONENT_HPP
# define _ICOMPONENT_HPP
# include <string>
# include <iostream>

namespace nts
{
  enum Tristate
    {
      UNDEFINED = (-true),
      TRUE = true,
      FALSE = false
    };
  class IComponent
  {
  public:
    virtual ~IComponent(void){}
    virtual nts::Tristate	Compute(size_t pin_num_this = 1) =0;
    virtual void		SetLink(size_t pin_num_this,
					nts::IComponent &component,
					size_t pin_num_target) = 0;
    virtual void Dump(void){}
  };
}

#endif
