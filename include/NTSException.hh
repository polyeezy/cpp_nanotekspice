//
// NTSExeption.hh for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/include
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Fri Feb 12 03:39:53 2016 Valerian Polizzi
// Last update Fri Feb 12 04:55:09 2016 Valerian Polizzi
//

#ifndef _NTSEXEPTION_HH_
# define _NTSEXEPTION_HH_

# include <exception>
# include <string>

namespace nts
{
  class Exception : public std::exception
  {
  private:
    std::string		_msg;
    std::string		_line;
  public:
    Exception(const std::string& message);
    virtual ~Exception() throw (){}

    virtual const char* what() const throw ()
    {
      return _msg.c_str();
    }
  };
}
#endif
