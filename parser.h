
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

#line 87 "parser.x"

	void procedure_decl();

#line 167 "parser.x"

	int _level = 0;
	bool check_export();

#line 189 "parser.x"

	void expression();

#line 195 "parser.x"

	void type();

#line 201 "parser.x"

	void ident_list();

#line 262 "parser.x"

	void simple_expression();

#line 287 "parser.x"

	void term();

#line 314 "parser.x"

	void factor();

#line 333 "parser.x"

	void qualident();

#line 339 "parser.x"

	void param_list();

#line 345 "parser.x"

	void set();

#line 415 "parser.x"

	void array_type();

#line 421 "parser.x"

	void record_type();

#line 427 "parser.x"

	void procedure_type();

#line 548 "parser.x"

	void stat_sequence();

#line 596 "parser.x"

	void fp_section();

#line 630 "parser.x"

	void formal_type();

#line 667 "parser.x"

	void type_case();

#line 673 "parser.x"

	void selector();

#line 787 "parser.x"

	void parameter();

#line 832 "parser.x"

	void element();

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

#line 93 "parser.x"

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
			while (_symbol == Symbol::s_procedure) {
				procedure_decl();
				check(Symbol::s_semicolon, "no ;");
			}
			if (_symbol == Symbol::s_begin) {
				_symbol = _scanner.next();
				stat_sequence();
			}
			check(Symbol::s_end, "no END");
			if (_symbol == Symbol::s_ident) {
				if (_scanner.id() != _module) {
					std::cerr << "no match\n";
				}
				_symbol = _scanner.next();
			} else {
				std::cerr << "identifier missing\n";
			}
			if (_symbol != Symbol::s_period) {
				std::cerr << "period missing\n";
			}
		} else {
			std::cerr << "must start with MODULE\n";
		}
	}

#line 174 "parser.x"

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

#line 207 "parser.x"

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

#line 268 "parser.x"

	void Parser::expression() {
		simple_expression();
		if (_symbol >= Symbol::s_eql && _symbol <= Symbol::s_geq) {
			//Symbol rel { _symbol };
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

#line 293 "parser.x"

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
			//Symbol op { _symbol };
			_symbol = _scanner.next();
			term();
		}
	}

#line 320 "parser.x"

	void Parser::term() {
		factor();
		while (_symbol >= Symbol::s_times && _symbol <= Symbol::s_and) {
			//Symbol op { _symbol };
			_symbol = _scanner.next();
			factor();
		}
	}

#line 351 "parser.x"

	void Parser::factor() {
		if (_symbol < Symbol::s_char || _symbol > Symbol::s_ident) {
			std::cerr << "expression expected\n";
			do {
				_symbol = _scanner.next();
			} while (_symbol < Symbol::s_char || _symbol > Symbol::s_ident);
		}
		if (_symbol == Symbol::s_ident) {
			qualident();
			selector();
			if (_symbol == Symbol::s_lparen) {
				_symbol = _scanner.next();
				param_list();
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
			set();
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

#line 399 "parser.x"

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

#line 433 "parser.x"

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
			check(Symbol::s_to, "no TO");
			if (_symbol == Symbol::s_ident) {
				_symbol = _scanner.next();
			} else {
				type();
			}
		} else if (_symbol == Symbol::s_procedure) {
			_symbol = _scanner.next();
			procedure_type();
		} else {
			std::cerr << "illegal type\n";
		}
	}

#line 469 "parser.x"

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

#line 486 "parser.x"

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

#line 511 "parser.x"

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

#line 554 "parser.x"

	void Parser::procedure_decl() {
		_symbol = _scanner.next();
		if (_symbol == Symbol::s_times) {
			_symbol = _scanner.next();
		}
		if (_symbol == Symbol::s_ident) {
			std::string proc_id { _scanner.id() };
			_symbol = _scanner.next();
			check_export();
			procedure_type();
			check(Symbol::s_semicolon, "no ;");
			declarations();
			if (_symbol == Symbol::s_procedure) {
				do {
					procedure_decl();
					check(Symbol::s_semicolon, "no ;");
				} while (_symbol == Symbol::s_procedure);
			}
			if (_symbol == Symbol::s_begin) {
				_symbol = _scanner.next();
				stat_sequence();
			}
			if (_symbol == Symbol::s_return) {
				_symbol = _scanner.next();
				expression();
			}
			check(Symbol::s_end, "no END");
			if (_symbol == Symbol::s_ident) {
				if (_scanner.id() != proc_id) {
					std::cerr << "no match\n";
				}
				_symbol = _scanner.next();
			} else {
				std::cerr << "no proc id\n";
			}
		}
	}

#line 602 "parser.x"

	void Parser::procedure_type() {
		if (_symbol == Symbol::s_lparen) {
			_symbol = _scanner.next();
			if (_symbol == Symbol::s_rparen) {
				_symbol = _scanner.next();
			} else {
				fp_section();
				while (_symbol == Symbol::s_semicolon) {
					_symbol = _scanner.next();
					fp_section();
				}
				check(Symbol::s_rparen, "no )");
			}
			if (_symbol == Symbol::s_colon) {
				_symbol = _scanner.next();
				if (_symbol == Symbol::s_ident) {
					qualident();
				} else {
					std::cerr << "type identifier expected\n";
				}
			}
		}
	}

#line 636 "parser.x"

	void Parser::fp_section() {
		if (_symbol == Symbol::s_var) {
			_symbol = _scanner.next();
		}
		ident_list();
		formal_type();
	}

#line 648 "parser.x"

	void Parser::formal_type() {
		if (_symbol == Symbol::s_ident) {
			qualident();
		} else if (_symbol == Symbol::s_array) {
			_symbol = _scanner.next();
			check(Symbol::s_of, "OF ?");
			formal_type();
		} else if (_symbol == Symbol::s_procedure) {
			_symbol = _scanner.next();
			procedure_type();
		} else {
			std::cerr << "identifier expected\n";
		}
	}

#line 679 "parser.x"

	void Parser::stat_sequence() {
		do {
			if (!((_symbol >= Symbol::s_ident && (_symbol <= Symbol::s_for)) || (_symbol >= Symbol::s_semicolon))) {
				std::cerr << "statement expected\n";
				do {
					_symbol = _scanner.next();
				} while (!((_symbol >= Symbol::s_ident && (_symbol <= Symbol::s_for)) || (_symbol >= Symbol::s_semicolon)));
			}
			if (_symbol == Symbol::s_ident) {
				qualident();
				selector();
				if (_symbol == Symbol::s_becomes) {
					_symbol = _scanner.next();
					expression();
				} else if (_symbol == Symbol::s_eql) {
					std::cerr << "should be :=\n";
					_symbol = _scanner.next();
					expression();
				} else if (_symbol == Symbol::s_lparen) {
					_symbol = _scanner.next();
					param_list();
				}
			} else if (_symbol == Symbol::s_if) {
				_symbol = _scanner.next();
				expression();
				check(Symbol::s_then, "no THEN");
				stat_sequence();
				while (_symbol == Symbol::s_elsif) {
					_symbol = _scanner.next();
					expression();
					check(Symbol::s_then, "no THEN");
					stat_sequence();
				}
				if (_symbol == Symbol::s_else) {
					_symbol = _scanner.next();
					stat_sequence();
				}
				check(Symbol::s_end, "no END");
			} else if (_symbol == Symbol::s_while) {
				_symbol = _scanner.next();
				expression();
				check(Symbol::s_do, "no DO");
				stat_sequence();
				while (_symbol == Symbol::s_elsif) {
					_symbol = _scanner.next();
					expression();
					check(Symbol::s_do, "no DO");
					stat_sequence();
				}
				check(Symbol::s_end, "no END");
			} else if (_symbol == Symbol::s_repeat) {
				_symbol = _scanner.next();
				stat_sequence();
				if (_symbol == Symbol::s_until) {
					_symbol = _scanner.next();
					expression();
				} else {
					std::cerr << "missing UNTIL\n";
				}
			} else if (_symbol == Symbol::s_for) {
				_symbol = _scanner.next();
				if (_symbol == Symbol::s_ident) {
					qualident();
					if (_symbol == Symbol::s_becomes) {
						_symbol = _scanner.next();
						expression();
						check(Symbol::s_to, "no TO");
						expression();
						if (_symbol == Symbol::s_by) {
							_symbol = _scanner.next();
							expression();
						}
						check(Symbol::s_do, "no DO");
						stat_sequence();
						check(Symbol::s_end, "no END");
					} else {
						std::cerr << ":= expected\n";
					}
				} else {
					std::cerr << "identifier expected\n";
				}
			} else if (_symbol == Symbol::s_case) {
				_symbol = _scanner.next();
				if (_symbol == Symbol::s_ident) {
					qualident();
					check(Symbol::s_of, "OF expected");
					type_case();
					while (_symbol == Symbol::s_bar) {
						_symbol = _scanner.next();
						type_case();
					}
				} else {
					std::cerr << "ident expected\n";
				}
				check(Symbol::s_end, "no END");
			}
			if (_symbol == Symbol::s_semicolon) {
				_symbol = _scanner.next();
			} else if (_symbol < Symbol::s_semicolon) {
				std::cerr << "missing semicolon? " << (int) _symbol << "\n";
			}
		} while (_symbol <= Symbol::s_semicolon);
	}

#line 793 "parser.x"

	void Parser::param_list() {
		if (_symbol != Symbol::s_rparen) {
			parameter();
			while (_symbol <= Symbol::s_comma) {
				check(Symbol::s_comma, "comma?");
				parameter();
			}
			check(Symbol::s_rparen, ") missing");
		} else {
			_symbol = _scanner.next();
		}
	}

#line 810 "parser.x"

	void Parser::parameter() {
		expression();
	}

#line 818 "parser.x"

	void Parser::type_case() {
		if (_symbol == Symbol::s_ident) {
			qualident();
			check(Symbol::s_colon, ": expected");
			stat_sequence();
		} else {
			std::cerr << "type id expected\n";
		}
	}

#line 838 "parser.x"

	void Parser::set() {
		if (_symbol >= Symbol::s_if) {
			if (_symbol != Symbol::s_rbrace) {
				std::cerr << "} missing\n";
			}
		} else {
			element();
			while (_symbol < Symbol::s_rparen || _symbol > Symbol::s_rbrace) {
				if (_symbol == Symbol::s_comma) {
					_symbol = _scanner.next();
				} else if (_symbol != Symbol::s_rbrace) {
					std::cerr << "missing comma\n";
				}
				element();
			}
		}
	}

#line 860 "parser.x"

	void Parser::element() {
		expression();
		if (_symbol == Symbol::s_upto) {
			_symbol = _scanner.next();
			expression();
		}
	}

#line 872 "parser.x"

	void Parser::selector() {
		while (_symbol == Symbol::s_lbrak || _symbol == Symbol::s_period || _symbol == Symbol::s_arrow /* || _symbol == Symbol::s_lparen */) {
			if (_symbol == Symbol::s_lbrak) {
				do {
					_symbol = _scanner.next();
					expression();
				} while (_symbol == Symbol::s_comma);
				check(Symbol::s_rbrak, "no ]");
			} else if (_symbol == Symbol::s_period) {
				_symbol = _scanner.next();
				if (_symbol == Symbol::s_ident) {
					_symbol = _scanner.next();
				} else {
					std::cerr << "ident?\n";
				}
			} else if (_symbol == Symbol::s_arrow) {
				_symbol = _scanner.next();
/*			} else if (_symbol == Symbol::s_lparen) {
				_symbol = _scanner.next();
				if (_symbol == Symbol::s_ident) {
					qualident();
				} else {
					std::cerr << "not an identifier\n";
				}
				check(Symbol::s_rparen, ") missing 2");
*/			}
		}
	}

#line 14 "parser.x"
;
	#endif
