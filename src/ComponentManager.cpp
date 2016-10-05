//
// ComponentManager.cpp for  in /home/polizz_v/rendu/B4/CPP/cpp_nanotekspice/src
//
// Made by Valerian Polizzi
// Login   <polizz_v@epitech.net>
//
// Started on  Mon Feb  8 01:46:47 2016 Valerian Polizzi
// Last update Fri Feb 26 06:43:44 2016 Valerian Polizzi
//

#include "ComponentManager.hh"

int	g_sig = 0;

ComponentManager::ComponentManager(const std::string &file) : _loop(0)
{
  _fcn.push_back(&ComponentManager::display);
  _fcn.push_back(&ComponentManager::changeValue);
  _fcn.push_back(&ComponentManager::simulate);
  _fcn.push_back(&ComponentManager::loop);
  _fcn.push_back(&ComponentManager::dump);
  _fcn.push_back(&ComponentManager::do_nothing);
  _fcn.push_back(&ComponentManager::do_nothing);
  _fcn.push_back(&ComponentManager::create_input);
  _fcn.push_back(&ComponentManager::create_output);
  _fcn.push_back(&ComponentManager::newComponent);
  _fcn.push_back(&ComponentManager::link);
  _fcn.push_back(&ComponentManager::clock);
  _fcn.push_back(&ComponentManager::True);
  _fcn.push_back(&ComponentManager::False);
  this->_parser.createTree();
  this->open(file);
}

ComponentManager::~ComponentManager()
{
}

void			ComponentManager::open(const std::string &file)
{
  std::ifstream File(file);
  std::string   line;
  std::string   token;
  std::string   value;

  if (file.find(".nts") == std::string::npos)
    throw nts::Exception("[NTS] Parse Error : Can't open '" + file + "' : wrong extension (.nts required)");
  if (!File.is_open())
    throw nts::Exception("[NTS] Parse Error : Can't open '" + file + "'");
  while (std::getline(File, line))
    {
      if (line[0] != '#' && line.size() > 1)
	_parser.feed(line);
      _parser.incr_line();
    }
  File.close();
}

Parser			&ComponentManager::getParser()
{
  return (_parser);
}

void			ComponentManager::newComponent(const std::string &value)
{
  std::cout << value << std::endl;
}
/*
void			ComponentManager::tree_to_manager(const nts::t_ast_node *head)
{
  (void*)head;
}
*/
void			ComponentManager::create_input(const std::string &value)
{
  this->push_component("input", value);
 }

void			ComponentManager::create_output(const std::string &value)
{
  this->push_component("output", value);
}

void			ComponentManager::clock(const std::string &value)
{
  (void)value;
}


void			ComponentManager::True(const std::string &value)
{
  (void)value;
}


void			ComponentManager::False(const std::string &value)
{
  (void)value;
}



int			ComponentManager::read()
{
  static int		i = 0;

  std::string   input = "";
  int		id;

  if (i == 0)
    {
      this->simulate("");
      this->display("");
      i = 1;
    }
  while (input.compare("exit") != 0)
    {
      std::cout << ">";
      getline(std::cin, input);
      if (std::cin.eof())
	throw nts::Exception("[NTS] Signal killed by user (ctrl-d)");
      _parser.feed(input);
      std::stringstream	stream(input);
      std::string token;
      std::string value;
      stream >> token >> value;
      id = _parser.getLexer().lex_line(token);
      if (id != -1 && id <= (int)_fcn.size())
	(this->*_fcn[id])(value);
    }
  return (0);
}

void			ComponentManager::do_nothing(const std::string &input)
{
  (void)input;
}

void			ComponentManager::exit(const std::string &input)
{
  (void)input;
}

void			ComponentManager::push_component(const std::string &type, const std::string &name)
{
  this->_container[COMPONENT_NODE].push_back(new Component(type, name));
}

int                     ComponentManager::print_from_lex(const nts::t_ast_node *head, const std::string &lex)
{
  int                  i;

  i = 0;
  for (std::vector<nts::t_ast_node*>::iterator it = head->children->begin(); it != head->children->end(); it++)
    {
      if ((*it)->lexeme.compare(lex) == 0)
	std::cout << (*it)->value << std::endl;
      i++;
    }
  return (0);
}

void			ComponentManager::display(const std::string &input)
{
  nts::t_ast_node	*ptr = NULL;
   int                  i = 0;

   if (!(ptr = _parser.pile(_parser.getHead(), CHIPSETS_NODE)))
     throw nts::Exception("[NTS] Parse Error : chipsets section required" + input + "command aborted");
   if (!(ptr = _parser.pile(ptr, MANUAL_NODE)))
     throw nts::Exception("[NTS] Error : no chipsets");
   if (!(ptr = _parser.pile(ptr, OUTPUT_NODE)))
     throw nts::Exception("[NTS] Error : no outputs");
   for (std::vector<nts::t_ast_node*>::iterator it = ptr->children->begin(); it != ptr->children->end(); it++)
     {
       this->print(*it);
       i++;
     }
}

void			ComponentManager::print(nts::t_ast_node *node)
{
  std::cout << node->value << std::endl;
}

void			ComponentManager::changeValue(const std::string &input)
{
  std::cout << input << std::endl;
}

void			ComponentManager::simulate(const std::string&input)
{
  std::cout << "simulate" << input << std::endl;
}

void			ComponentManager::signal_handler(int sig)
{
  sig += 0;
  if (sig == SIGINT)
    {
      g_sig = 1;
    }
}

void			ComponentManager::loop(const std::string &input)
{
  signal(SIGINT, ComponentManager::signal_handler);
  while (g_sig != 1);
  std::cout << std::endl;
  (void)input;
}

void			ComponentManager::dump(const std::string &input)
{
  if (input.compare("--all") == 0)
    {
      nts::t_ast_node *tmp = this->_parser.getHead();
      this->_parser.parseTree(*tmp);
      tmp = _parser.pile(tmp, "chipsets");
      this->_parser.parseTree(*tmp);
      this->_parser.parseTree(*(_parser.pile(tmp, "manual_component")));
      this->_parser.parseTree(*(_parser.pile(tmp, "component")));
    }
}

void			ComponentManager::link(const std::string &input)
{
}

void				ComponentManager::addComponent(const std::string &type,
							       nts::IComponent* (ComponentManager::*to_add)(const std::string&)const)
{
  this->_pointers[type] = to_add;
}

nts::IComponent			*ComponentManager::CreateComponent(const std::string &type, const std::string &value)
{
  std::map<const std::string, nts::IComponent* (ComponentManager::*)(const std::string&)const>::iterator it = this->_pointers.find(type);

  if (it == this->_pointers.end())
    return (NULL);
  return ((this->*(_pointers)[type])(value));
}

nts::IComponent			*ComponentManager::Create4001(const std::string &value) const
{
  return (new Comp4001(value));
}
