
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

#line 59 "parser.x"

	int _version;
	std::string _module;

#line 66 "parser.x"

	void check(
		Symbol s, const std::string &msg
	);

#line 74 "parser.x"

	void err(
		int src, const std::string &msg
	) {
		std::cerr << "\n:";
		std::cerr << _scanner.line();
		std::cerr << " (" << src << ") ";
		std::cerr << msg << " [";
		std::cerr << (int) _symbol;
		std::cerr << "]\n";
	}
	#define ERR(MSG) err(__LINE__, (MSG))

#line 105 "parser.x"

	int declarations();

#line 111 "parser.x"

	void procedure_decl();

#line 191 "parser.x"

	int _level = 0;
	bool check_export();

#line 213 "parser.x"

	void expression();

#line 219 "parser.x"

	void type();

#line 225 "parser.x"

	void ident_list();

#line 372 "parser.x"

	void simple_expression();

#line 397 "parser.x"

	void term();

#line 424 "parser.x"

	void factor();

#line 443 "parser.x"

	void qualident();

#line 449 "parser.x"

	void param_list();

#line 455 "parser.x"

	void set();

#line 525 "parser.x"

	void array_type();

#line 531 "parser.x"

	void record_type();

#line 537 "parser.x"

	void procedure_type();

#line 658 "parser.x"

	void stat_sequence();

#line 706 "parser.x"

	void fp_section();

#line 740 "parser.x"

	void formal_type();

#line 777 "parser.x"

	void type_case();

#line 783 "parser.x"

	void selector();

#line 897 "parser.x"

	void parameter();

#line 945 "parser.x"

	void element();

#line 9 "parser.x"
;
		public:
			
#line 44 "parser.x"

	Parser(Scanner &sc):
		_scanner { sc },
		_symbol { sc.next() }
	{ }

#line 53 "parser.x"

	void module();

#line 11 "parser.x"
;
	};
	#if parser_IMPL
		
#line 90 "parser.x"

	void Parser::check(
		Symbol s,
		const std::string &msg
	) {
		if (_symbol == s) {
			_symbol = _scanner.next();
		} else {
			ERR(msg);
		}
	}

#line 117 "parser.x"

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
				ERR("identifier expected");
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
							ERR("id expected");
						}
					} else {
						imp_name_2 = imp_name;
					}
					if (_symbol == Symbol::s_comma) {
						_symbol = _scanner.next();
					} else if (_symbol == Symbol::s_ident) {
						ERR("comma missing");
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
					ERR("no match");
				}
				_symbol = _scanner.next();
			} else {
				ERR("identifier missing");
			}
			if (_symbol != Symbol::s_period) {
				ERR("period missing");
			}
		} else {
			ERR("must start with MODULE");
		}
	}

#line 198 "parser.x"

	bool Parser::check_export() {
		if (_symbol == Symbol::s_times) {
			_symbol = _scanner.next();
			if (_level != 0) {
				ERR("remove asterisk");
			}
			return true;
		}
		return false;
	}

#line 231 "parser.x"

	int Parser::declarations() {
		
#line 287 "parser.x"

	if (
		_symbol < Symbol::s_const &&
		_symbol != Symbol::s_end &&
		_symbol != Symbol::s_return
	) {
		ERR("declaration?");
		do {
			_symbol = _scanner.next();
		} while (
			_symbol < Symbol::s_const &&
			_symbol != Symbol::s_end &&
			_symbol != Symbol::s_return
		);
	}

#line 306 "parser.x"

	if (_symbol == Symbol::s_const) {
		_symbol = _scanner.next();
		
#line 315 "parser.x"

	while (_symbol == Symbol::s_ident) {
		std::string id { _scanner.id() };
		_symbol = _scanner.next();
		check_export();
		if (_symbol == Symbol::s_eql) {
			_symbol = _scanner.next();
		} else {
			ERR("= ?");
		}
		expression();
		check(
			Symbol::s_semicolon,
			"; missing"
		);
	}

#line 309 "parser.x"
;
	}

#line 335 "parser.x"

	if (_symbol == Symbol::s_type) {
		_symbol = _scanner.next();
		while (_symbol == Symbol::s_ident) {
			std::string id { _scanner.id() };
			_symbol = _scanner.next();
			check_export();
			if (_symbol == Symbol::s_eql) {
				_symbol = _scanner.next();
			} else {
				ERR("= ?");
			}
			type();
			check(Symbol::s_semicolon, "; missing");
		}
	}

#line 355 "parser.x"

	if (_symbol == Symbol::s_var) {
		_symbol = _scanner.next();
		while (_symbol == Symbol::s_ident) {
			ident_list();
			type();
			check(Symbol::s_semicolon, "; missing");
		}
	}
	if (_symbol >= Symbol::s_const && _symbol <= Symbol::s_var) {
		ERR("declaration in bad order");
	}
	return 0;

#line 233 "parser.x"
;
		if (_symbol < Symbol::s_const && _symbol != Symbol::s_end && _symbol != Symbol::s_return) {
			ERR("declaration?");
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
					ERR("= ?");
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
					ERR("= ?");
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
			ERR("declaration in bad order");
		}
		return 0;
	}

#line 378 "parser.x"

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

#line 403 "parser.x"

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

#line 430 "parser.x"

	void Parser::term() {
		factor();
		while (_symbol >= Symbol::s_times && _symbol <= Symbol::s_and) {
			//Symbol op { _symbol };
			_symbol = _scanner.next();
			factor();
		}
	}

#line 461 "parser.x"

	void Parser::factor() {
		if (_symbol < Symbol::s_char || _symbol > Symbol::s_ident) {
			ERR("expression expected");
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
			ERR("not a factor");
		}
	}

#line 509 "parser.x"

	void Parser::qualident() {
		_symbol = _scanner.next();
		if (_symbol == Symbol::s_period) {
			_symbol = _scanner.next();
			if (_symbol == Symbol::s_ident) {
				_symbol = _scanner.next();
			} else {
				ERR("identifier expected");
			}
		}
	}

#line 543 "parser.x"

	void Parser::type() {
		if (_symbol != Symbol::s_ident && _symbol < Symbol::s_array) {
			ERR("not a type");
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
			ERR("illegal type");
		}
	}

#line 579 "parser.x"

	void Parser::array_type() {
		expression();
		if (_symbol == Symbol::s_of) {
			_symbol = _scanner.next();
			type();
		} else if (_symbol == Symbol::s_comma) {
			_symbol = _scanner.next();
			array_type();
		} else {
			ERR("missing OF");
		}
	}

#line 596 "parser.x"

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
					ERR("ident?");
				}
			}
			if (_symbol == Symbol::s_colon) {
				_symbol = _scanner.next();
			} else {
				ERR(":?\n");
			}
		}
	}

#line 621 "parser.x"

	void Parser::record_type() {
		if (_symbol == Symbol::s_lparen) {
			_symbol = _scanner.next();
			if (_level != 0) {
				ERR("extension of local types not implemented");
			}
			if (_symbol == Symbol::s_ident) {
				qualident();
			} else {
				ERR("ident expected");
			}
			check(Symbol::s_rparen, "no )");
		}
		while (_symbol == Symbol::s_ident) {
			while (_symbol == Symbol::s_ident) {
				_symbol = _scanner.next();
				check_export();
				if (_symbol != Symbol::s_comma && _symbol != Symbol::s_colon) {
					ERR("comma expected");
				} else if (_symbol == Symbol::s_comma) {
					_symbol = _scanner.next();
				}
			}
			check(Symbol::s_colon, "colon expected\n");
			type();
			if (_symbol == Symbol::s_semicolon) {
				_symbol = _scanner.next();
			} else if (_symbol != Symbol::s_end) {
				ERR("; or END");
			}
		}
	}

#line 664 "parser.x"

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
					ERR("no match");
				}
				_symbol = _scanner.next();
			} else {
				ERR("no proc id");
			}
		}
	}

#line 712 "parser.x"

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
					ERR("type identifier expected");
				}
			}
		}
	}

#line 746 "parser.x"

	void Parser::fp_section() {
		if (_symbol == Symbol::s_var) {
			_symbol = _scanner.next();
		}
		ident_list();
		formal_type();
	}

#line 758 "parser.x"

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
			ERR("identifier expected");
		}
	}

#line 789 "parser.x"

	void Parser::stat_sequence() {
		do {
			if (!((_symbol >= Symbol::s_ident && (_symbol <= Symbol::s_for)) || (_symbol >= Symbol::s_semicolon))) {
				ERR("statement expected");
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
					ERR("should be :=");
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
					ERR("missing UNTIL");
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
						ERR(":= expected");
					}
				} else {
					ERR("identifier expected");
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
					ERR("ident expected");
				}
				check(Symbol::s_end, "no END");
			}
			if (_symbol == Symbol::s_semicolon) {
				_symbol = _scanner.next();
			} else if (_symbol < Symbol::s_semicolon) {
				ERR("missing semicolon?");
			}
		} while (_symbol <= Symbol::s_semicolon);
	}

#line 903 "parser.x"

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

#line 920 "parser.x"

	void Parser::parameter() {
		expression();
	}

#line 928 "parser.x"

	void Parser::type_case() {
		if (_symbol == Symbol::s_ident) {
			qualident();
			check(
				Symbol::s_colon,
				": expected"
			);
			stat_sequence();
		} else {
			ERR("type id expected");
		}
	}

#line 951 "parser.x"

	void Parser::set() {
		
#line 959 "parser.x"

	if (_symbol >= Symbol::s_if) {
		if (_symbol != Symbol::s_rbrace) {
			ERR("} missing");
		}
	} else {
		element();
		
#line 972 "parser.x"

	while (
		_symbol < Symbol::s_rparen ||
		_symbol > Symbol::s_rbrace
	) {
		if (_symbol == Symbol::s_comma) {
			_symbol = _scanner.next();
		} else if (
			_symbol != Symbol::s_rbrace
		) {
			ERR("missing comma");
		}
		element();
	}

#line 966 "parser.x"
;
	}

#line 953 "parser.x"
;
	}

#line 990 "parser.x"

	void Parser::element() {
		expression();
		if (_symbol == Symbol::s_upto) {
			_symbol = _scanner.next();
			expression();
		}
	}

#line 1002 "parser.x"

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
					ERR("ident?");
				}
			} else if (_symbol == Symbol::s_arrow) {
				_symbol = _scanner.next();
/*			} else if (_symbol == Symbol::s_lparen) {
				_symbol = _scanner.next();
				if (_symbol == Symbol::s_ident) {
					qualident();
				} else {
					ERR("not an identifier");
				}
				check(Symbol::s_rparen, ") missing 2");
*/			}
		}
	}

#line 14 "parser.x"
;
	#endif
