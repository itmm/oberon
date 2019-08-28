
#line 4 "parser.x"

	#pragma once
	
#line 31 "parser.x"

	#include "scanner.h"

#line 6 "parser.x"

	class Parser {
		private:
			
#line 37 "parser.x"

	Scanner &_scanner;
	Symbol _symbol;

#line 56 "parser.x"

	int _version;
	std::string _module;

#line 63 "parser.x"

	void check(Symbol s, const std::string &msg);

#line 9 "parser.x"
;
		public:
			
#line 44 "parser.x"

	Parser(Scanner &sc): _scanner { sc }, _symbol { sc.next() } { }

#line 50 "parser.x"

	void module();

#line 11 "parser.x"
;
	};
	#if parser_IMPL
		
#line 69 "parser.x"

	void Parser::check(Symbol s, const std::string &msg) {
		if (_symbol == s) {
			_symbol = _scanner.next();
		} else {
			std::cerr << msg << " " << (int) _symbol << '\n';
		}
	}

#line 81 "parser.x"

	void Parser::module() {
		std::cout << "  compiling ";
		if (_symbol == Symbol::s_module) {
			_symbol = _scanner.next();
			if (_symbol == Symbol::s_times) {
				_version = 0;
				std::cout << '*';
				_symbol = _scanner.next();
			} else {
				_version = 1;
			}
			// ORB.Init; ORB.OpenScope
			if (_symbol == Symbol::s_ident) {
				_module = _scanner.id();
				_symbol = _scanner.next();
				std::cout << _module << '\n';
			} else {
				std::cerr << "identifier expected\n";
			}
			check(Symbol::s_semicolon, "no ;");
			if (_symbol == Symbol::s_import) {
				_symbol = _scanner.next();
				while (_symbol == Symbol::s_ident) {
					std::string imp_name { _scanner.id() };
					std::string imp_name_2;
					_symbol = _scanner.next();
					if (_symbol == Symbol::s_becomes) {
						_symbol = _scanner.next();
						if (_symbol == Symbol::s_ident) {
							imp_name_2 = _scanner.id();
							_symbol = _scanner.next();
						} else {
							std::cerr << "id expected\n";
						}
					} else {
						imp_name_2 = imp_name;
					}
					// ORB.Import(_imp_name, _imp_name_2)
					std::cout << "import " << imp_name << " := " << imp_name_2 << "\n";
					if (_symbol == Symbol::s_comma) {
						_symbol = _scanner.next();
					} else if (_symbol == Symbol::s_ident) {
						std::cerr << "comma missing\n";
					}
				}
				check(Symbol::s_semicolon, "no ;");
			}
			// ORG.Open(version)
			// Declarations(dc);
			// ORG.SetDataSize ..
		} else {
			std::cerr << "must start with MODULE\n";
		}
	}

#line 14 "parser.x"
;
	#endif
