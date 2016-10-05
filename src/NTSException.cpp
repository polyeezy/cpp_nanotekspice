//
// NTSExeption.cpp for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/src
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Fri Feb 12 03:46:35 2016 Valerian Polizzi
// Last update Fri Feb 12 04:54:46 2016 Valerian Polizzi
//

#include "NTSException.hh"

nts::Exception::Exception(const std::string &msg) : _msg(msg), _line("0")
{
}
