
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

#line 81 "parser.x"

	int declarations();

#line 141 "parser.x"

	int _level = 0;
	bool check_export();

#line 163 "parser.x"

	void expression();

#line 169 "parser.x"

	void type();

#line 175 "parser.x"

	void ident_list();

#line 236 "parser.x"

	void simple_expression();

#line 261 "parser.x"

	void term();

#line 288 "parser.x"

	void factor();

#line 307 "parser.x"

	void qualident();

#line 376 "parser.x"

	void array_type();

#line 382 "parser.x"

	void record_type();

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

#line 87 "parser.x"

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
					if (_symbol == Symbol::s_comma) {
						_symbol = _scanner.next();
					} else if (_symbol == Symbol::s_ident) {
						std::cerr << "comma missing\n";
					}
				}
				check(Symbol::s_semicolon, "no ;");
			}
			declarations();
		} else {
			std::cerr << "must start with MODULE\n";
		}
	}

#line 148 "parser.x"

	bool Parser::check_export() {
		if (_symbol == Symbol::s_times) {
			_symbol = _scanner.next();
			if (_level != 0) {
				std::cerr << "remove asterisk\n";
			}
			return true;
		}
		return false;
	}

#line 181 "parser.x"

	int Parser::declarations() {
		if (_symbol < Symbol::s_const && _symbol != Symbol::s_end && _symbol != Symbol::s_return) {
			std::cerr << "declaration?\n";
			do {
				_symbol = _scanner.next();
			} while (_symbol < Symbol::s_const && _symbol != Symbol::s_end && _symbol != Symbol::s_return);
		}
		if (_symbol == Symbol::s_const) {
			_symbol = _scanner.next();
			while (_symbol == Symbol::s_ident) {
				std::string id { _scanner.id() };
				_symbol = _scanner.next();
				check_export();
				if (_symbol == Symbol::s_eql) {
					_symbol = _scanner.next();
				} else {
					std::cerr << "= ?\n";
				}
				expression();
				check(Symbol::s_semicolon, "; missing");
			}
		}
		if (_symbol == Symbol::s_type) {
			_symbol = _scanner.next();
			while (_symbol == Symbol::s_ident) {
				std::string id { _scanner.id() };
				_symbol = _scanner.next();
				check_export();
				if (_symbol == Symbol::s_eql) {
					_symbol = _scanner.next();
				} else {
					std::cerr << "= ?\n";
				}
				type();
				check(Symbol::s_semicolon, "; missing");
			}
		}
		if (_symbol == Symbol::s_var) {
			_symbol = _scanner.next();
			while (_symbol == Symbol::s_ident) {
				ident_list();
				type();
				check(Symbol::s_semicolon, "; missing");
			}
		}
		if (_symbol >= Symbol::s_const && _symbol <= Symbol::s_var) {
			std::cerr << "declaration in bad order\n";
		}
		return 0;
	}

#line 242 "parser.x"

	void Parser::expression() {
		simple_expression();
		if (_symbol >= Symbol::s_eql && _symbol <= Symbol::s_geq) {
			// Symbol rel { _symbol };
			_symbol = _scanner.next();
			simple_expression();
		} else if (_symbol == Symbol::s_in) {
			_symbol = _scanner.next();
			simple_expression();
		} else if (_symbol == Symbol::s_is) {
			_symbol = _scanner.next();
			qualident();
		}
	}

#line 267 "parser.x"

	void Parser::simple_expression() {
		if (_symbol == Symbol::s_minus) {
			_symbol = _scanner.next();
			term();
		} else if (_symbol == Symbol::s_plus) {
			_symbol = _scanner.next();
			term();
		} else {
			term();
		}
		while (_symbol >= Symbol::s_plus && _symbol <= Symbol::s_or) {
			// Symbol op { _symbol };
			_symbol = _scanner.next();
			term();
		}
	}

#line 294 "parser.x"

	void Parser::term() {
		factor();
		while (_symbol >= Symbol::s_times && _symbol <= Symbol::s_and) {
			//Symbol op { _symbol };
			_symbol = _scanner.next();
			factor();
		}
	}

#line 313 "parser.x"

	void Parser::factor() {
		if (_symbol < Symbol::s_char || _symbol > Symbol::s_ident) {
			std::cerr << "expression expected\n";
			do {
				_symbol = _scanner.next();
			} while (_symbol < Symbol::s_char || _symbol > Symbol::s_ident);
		}
		if (_symbol == Symbol::s_ident) {
			qualident();
			if (_symbol == Symbol::s_lparen) {
				_symbol = _scanner.next();
				// param_list();
			}
		} else if (_symbol == Symbol::s_int) {
			_symbol = _scanner.next();
		} else if (_symbol == Symbol::s_real) {
			_symbol = _scanner.next();
		} else if (_symbol == Symbol::s_char) {
			_symbol = _scanner.next();
		} else if (_symbol == Symbol::s_nil) {
			_symbol = _scanner.next();
		} else if (_symbol == Symbol::s_string) {
			_symbol = _scanner.next();
		} else if (_symbol == Symbol::s_lparen) {
			_symbol = _scanner.next();
			expression();
			check(Symbol::s_rparen, "no )");
		} else if (_symbol == Symbol::s_lbrace) {
			_symbol = _scanner.next();
			// set();
			check(Symbol::s_rbrace, "no }");
		} else if (_symbol == Symbol::s_not) {
			_symbol = _scanner.next();
			factor();
		} else if (_symbol == Symbol::s_false) {
			_symbol = _scanner.next();
		} else if (_symbol == Symbol::s_true) {
			_symbol = _scanner.next();
		} else {
			std::cerr << "not a factor\n";
		}
	}

#line 360 "parser.x"

	void Parser::qualident() {
		_symbol = _scanner.next();
		if (_symbol == Symbol::s_period) {
			_symbol = _scanner.next();
			if (_symbol == Symbol::s_ident) {
				_symbol = _scanner.next();
			} else {
				std::cerr << "identifier expected\n";
			}
		}
	}

#line 388 "parser.x"

	void Parser::type() {
		if (_symbol != Symbol::s_ident && _symbol < Symbol::s_array) {
			std::cerr << "not a type " << (int) _symbol << "\n";
			do {
				_symbol = _scanner.next();
			} while (_symbol != Symbol::s_ident && _symbol < Symbol::s_array);
		}
		if (_symbol == Symbol::s_ident) {
			qualident();
		} else if (_symbol == Symbol::s_array) {
			_symbol = _scanner.next();
			array_type();
		} else if (_symbol == Symbol::s_record) {
			_symbol = _scanner.next();
			record_type();
			check(Symbol::s_end, "no END");
		} else if (_symbol == Symbol::s_pointer) {
			_symbol = _scanner.next();
			if (_symbol == Symbol::s_ident) {
				_symbol = _scanner.next();
			} else {
				type();
			}
		} else if (_symbol == Symbol::s_procedure) {
			_symbol = _scanner.next();
			// procedure_type();
		} else {
			std::cerr << "illegal type\n";
		}
	}

#line 423 "parser.x"

	void Parser::array_type() {
		expression();
		if (_symbol == Symbol::s_of) {
			_symbol = _scanner.next();
			type();
		} else if (_symbol == Symbol::s_comma) {
			_symbol = _scanner.next();
			array_type();
		} else {
			std::cerr << "missing OF\n";
		}
	}

#line 440 "parser.x"

	void Parser::ident_list() {
		if (_symbol == Symbol::s_ident) {
			_symbol = _scanner.next();
			check_export();
			while (_symbol == Symbol::s_comma) {
				_symbol = _scanner.next();
				if (_symbol == Symbol::s_ident) {
					_symbol = _scanner.next();
					check_export();
				} else {
					std::cerr << "ident?\n";
				}
			}
			if (_symbol == Symbol::s_colon) {
				_symbol = _scanner.next();
			} else {
				std::cerr << ":?\n";
			}
		}
	}

#line 465 "parser.x"

	void Parser::record_type() {
		if (_symbol == Symbol::s_lparen) {
			_symbol = _scanner.next();
			if (_level != 0) {
				std::cerr << "extension of local types not implemented\n";
			}
			if (_symbol == Symbol::s_ident) {
				qualident();
			} else {
				std::cerr << "ident expected\n";
			}
			check(Symbol::s_rparen, "no )");
		}
		while (_symbol == Symbol::s_ident) {
			while (_symbol == Symbol::s_ident) {
				_symbol = _scanner.next();
				check_export();
				if (_symbol != Symbol::s_comma && _symbol != Symbol::s_colon) {
					std::cerr << "comma expected\n";
				} else if (_symbol == Symbol::s_comma) {
					_symbol = _scanner.next();
				}
			}
			check(Symbol::s_colon, "colon expected\n");
			type();
			if (_symbol == Symbol::s_semicolon) {
				_symbol = _scanner.next();
			} else if (_symbol != Symbol::s_end) {
				std::cerr << "; or END\n";
			}
		}
	}

#line 14 "parser.x"
;
	#endif
