//
// main.cpp for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/src
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Mon Feb  8 01:51:03 2016 Valerian Polizzi
// Last update Thu Feb 25 06:53:33 2016 Valerian Polizzi
//

# include "ComponentManager.hh"
#include "NTSException.hh"
#include "Parser.hh"

int		main(int ac, char **av)
{
  int		i;

  if (ac <= 1)
    throw nts::Exception("[NTS] Error : Required parameter : file");
  ComponentManager	CM(av[1]);
  i = 2;
  while (av[i])
    CM.getParser().feed(av[i++]);
  CM.read();
  return (0);
}
