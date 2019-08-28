
#line 4 "scanner.x"

	#pragma once
	
#line 58 "scanner.x"

	#include <map>
	#include <string>

#line 118 "scanner.x"

	#include <iostream>

#line 321 "scanner.x"

	#include <limits>

#line 335 "scanner.x"

	#include <vector>

#line 6 "scanner.x"
;
	
#line 28 "scanner.x"

	enum class Symbol {
		s_null,
		
#line 38 "scanner.x"

	s_times, s_rdiv, s_div, s_mod, s_and,
	s_plus, s_minus, s_or, s_eql, s_neq,
	s_lss, s_leq, s_gtr, s_geq, s_in,
	s_is, s_arrow, s_period, s_char,
	s_int, s_real, s_false, s_true, s_nil,
	s_string, s_not, s_lparen, s_lbrak,
	s_lbrace, s_ident, s_if, s_while,
	s_repeat, s_case, s_for, s_comma,
	s_colon, s_becomes, s_upto, s_rparen,
	s_rbrak, s_rbrace, s_then, s_of, s_do,
	s_to, s_by, s_semicolon, s_end, s_bar,
	s_else, s_elsif, s_until, s_return,
	s_array, s_record, s_pointer, s_const,
	s_type, s_var, s_procedure, s_begin,
	s_import, s_module,

#line 31 "scanner.x"

		s_eot
	};

#line 65 "scanner.x"

	#if scanner_IMPL
		std::map<std::string, Symbol> keywords;
		struct Keyword_Init {
			Keyword_Init() {
				
#line 80 "scanner.x"

	keywords["IF"] = Symbol::s_if;
	keywords["DO"] = Symbol::s_do;
	keywords["OF"] = Symbol::s_of;
	keywords["OR"] = Symbol::s_or;
	keywords["TO"] = Symbol::s_to;
	keywords["IN"] = Symbol::s_in;
	keywords["IS"] = Symbol::s_is;
	keywords["BY"] = Symbol::s_by;
	keywords["END"] = Symbol::s_end;
	keywords["NIL"] = Symbol::s_nil;
	keywords["VAR"] = Symbol::s_var;
	keywords["DIV"] = Symbol::s_div;
	keywords["MOD"] = Symbol::s_mod;
	keywords["FOR"] = Symbol::s_for;
	keywords["ELSE"] = Symbol::s_else;
	keywords["THEN"] = Symbol::s_then;
	keywords["TRUE"] = Symbol::s_true;
	keywords["TYPE"] = Symbol::s_type;
	keywords["CASE"] = Symbol::s_case;
	keywords["ELSIF"] = Symbol::s_elsif;
	keywords["FALSE"] = Symbol::s_false;
	keywords["ARRAY"] = Symbol::s_array;
	keywords["BEGIN"] = Symbol::s_begin;
	keywords["CONST"] = Symbol::s_const;
	keywords["UNTIL"] = Symbol::s_until;
	keywords["WHILE"] = Symbol::s_while;
	keywords["RECORD"] = Symbol::s_record;
	keywords["REPEAT"] = Symbol::s_repeat;
	keywords["RETURN"] = Symbol::s_return;
	keywords["IMPORT"] = Symbol::s_import;
	keywords["MODULE"] = Symbol::s_module;
	keywords["POINTER"] = Symbol::s_pointer;
	keywords["PROCEDURE"] = Symbol::s_procedure;

#line 70 "scanner.x"
;
			}
		} keyword_init;
	#else
		extern std::map<std::string, Symbol> keywords;
	#endif

#line 7 "scanner.x"
;
	class Scanner {
		private:
			
#line 124 "scanner.x"

	std::istream &_in = std::cin;
	int _ch;

#line 145 "scanner.x"

	void comment();

#line 151 "scanner.x"

	Symbol number();

#line 327 "scanner.x"

	int _int_value;
	double _real_value;
	static double ten(int expo);

#line 480 "scanner.x"

	Symbol identifier();
	std::string _id;

#line 508 "scanner.x"

	void string();
	std::string _string;

#line 532 "scanner.x"

	void hex_string();

#line 10 "scanner.x"
;
		public:
			
#line 131 "scanner.x"

	Scanner(std::istream &in = std::cin):
		_in { in }, _ch{' '}
	{ }

#line 139 "scanner.x"

	Symbol next();

#line 12 "scanner.x"
;
	};
	#if scanner_IMPL
		
#line 157 "scanner.x"

	Symbol Scanner::next() {
		Symbol s = Symbol::s_null;
		while (s == Symbol::s_null) {
			while (_ch != EOF && _ch <= ' ') {
				_ch = _in.get();
			}
			if (_ch == EOF) {
				s = Symbol::s_eot;
			} else if (_ch < 'A') {
				if (_ch < '0') {
					if (_ch == '"') {
						string();
						s = Symbol::s_string;
					} else if (_ch == '#') {
						_ch = _in.get();
						s = Symbol::s_neq;
					} else if (_ch == '$') {
						hex_string();
						s = Symbol::s_string;
					} else if (_ch == '&') {
						_ch = _in.get();
						s = Symbol::s_and;
					} else if (_ch == '(') {
						_ch = _in.get();
						if (_ch == '*') {
							comment();
						} else {
							s = Symbol::s_lparen;
						}
					} else if (_ch == ')') {
						_ch = _in.get();
						s = Symbol::s_rparen;
					} else if (_ch == '*') {
						_ch = _in.get();
						s = Symbol::s_times;
					} else if (_ch == '+') {
						_ch = _in.get();
						s = Symbol::s_plus;
					} else if (_ch == ',') {
						_ch = _in.get();
						s = Symbol::s_comma;
					} else if (_ch == '-') {
						_ch = _in.get();
						s = Symbol::s_minus;
					} else if (_ch == '.') {
						_ch = _in.get();
						if (_ch == '.') {
							_ch = _in.get();
							s = Symbol::s_upto;
						} else {
							s = Symbol::s_period;
						}
					} else if (_ch == '/') {
						_ch = _in.get();
						s = Symbol::s_rdiv;
					}
				} else if (_ch < ':') {
					s = number();
				} else if (_ch == ':') {
					_ch = _in.get();
					if (_ch == '=') {
						_ch = _in.get();
						s = Symbol::s_becomes;
					} else {
						s = Symbol::s_colon;
					}
				} else if (_ch == ';') {
					_ch = _in.get();
					s = Symbol::s_semicolon;
				} else if (_ch == '<') {
					_ch = _in.get();
					if (_ch == '=') {
						_ch = _in.get();
						s = Symbol::s_leq;
					} else {
						s = Symbol::s_lss;
					}
				} else if (_ch == '=') {
					_ch = _in.get();
					s = Symbol::s_eql;
				} else if (_ch == '>') {
					_ch = _in.get();
					if (_ch == '=') {
						_ch = _in.get();
						s = Symbol::s_geq;
					} else {
						s = Symbol::s_gtr;
					}
				} 
			} else if (_ch < '[') {
				s = identifier();
			} else if (_ch < 'a') {
				if (_ch == '[') {
					_ch = _in.get();
					s = Symbol::s_lbrak;
				} else if (_ch == ']') {
					_ch = _in.get();
					s = Symbol::s_rbrak;
				} else if (_ch == '^') {
					_ch = _in.get();
					s = Symbol::s_arrow;
				}
			} else if (_ch < '{') {
				s = identifier();
			} else {
				if (_ch == '{') {
					_ch = _in.get();
					s = Symbol::s_lbrace;
				} else if (_ch == '}') {
					_ch = _in.get();
					s = Symbol::s_rbrace;
				} else if (_ch == '|') {
					_ch = _in.get();
					s = Symbol::s_bar;
				} else if (_ch == '~') {
					_ch = _in.get();
					s = Symbol::s_not;
				} else if (_ch == '\x7f') {
					_ch = _in.get();
					s = Symbol::s_upto;
				}
			}

			_ch = _in.get();
		}
		return s;
	}

#line 289 "scanner.x"

	void Scanner::comment() {
		
#line 297 "scanner.x"

	_ch = _in.get();
	do {
		while (_ch != EOF && _ch != '*') {
			if (_ch == '(') {
				_ch = _in.get();
				if (_ch == '*') {
					comment();
				}
			} else {
				_ch = _in.get();
			}
		}
		while (_ch == '*') { _ch = _in.get(); }
	} while (_ch != EOF && _ch != ')');
	if (_ch != EOF) {
		_ch = _in.get();
	} else {
		std::cerr << "unterminated comment\n";
	}

#line 291 "scanner.x"
;
	}

#line 341 "scanner.x"

	double Scanner::ten(int expo) {
		double x { 1.0 };
		double t { 10.0 };
		while (expo > 0) {
			if (expo & 1) { x *= t; }
			t *= t;
			expo /= 2;
		}
		return x;
	}

	Symbol Scanner::number() {
		std::vector<char> digits;
		Symbol s { Symbol::s_null };
		do {
			digits.push_back(_ch - '0');
			_ch = _in.get();
		} while ((_ch >= '0' && _ch <= '9') || (_ch >= 'A' && _ch <= 'F'));
		if (_ch == 'H' || _ch == 'R' || _ch == 'X') {
			int k { 0 };
			for (char h : digits) {
				if (h >= 10) { h -= 7; }
				k = k * 16 + h;
			}
			if (_ch == 'X') {
				s = Symbol::s_char;
				if (k < 0x100) {
					_int_value = k;
				} else {
					_int_value = 0;
					std::cerr << "illegal value\n";
				}
			} else if (_ch == 'R') {
				s = Symbol::s_real;
				_real_value = k;
			} else {
				s = Symbol::s_int;
				_int_value = k;
			}
		} else if (_ch == '.') {
			_ch = _in.get();
			if (_ch == '.') {
				_ch = '\x7f';
				int k = 0;
				for (const auto &d : digits) {
					if (d < 10) {
						if (k < (std::numeric_limits<int>::max() - d) / 10) {
							k = k * 10 + d;
						} else {
							std::cerr << "too large\n";
							break;
						}
					} else {
						std::cerr << "bad integer\n";
						break;
					}
				}
				_int_value = k;
				s = Symbol::s_int;
			} else {
				double x { 0.0 };
				int expo { 0 };
				for (const auto &d : digits) {
					x = x * 10.0 + d;
				}
				while (_ch >= '0' && _ch <= '9') {
					x = x * 10.0 + (_ch - '0');
					++expo;
					_ch = _in.get();
				}
				if (_ch == 'E' || _ch == 'D') {
					_ch = _in.get();
					bool neg_expo { false };
					if (_ch == '-') {
						_ch = _in.get();
						neg_expo = true;
					} else if (_ch == '+') {
						_ch = _in.get();
					}
					if (_ch >= '0' && _ch <= '9') {
						int scale { 0 };
						while (_ch >= 0 && _ch <= '9') {
							scale = scale * 10 + (_ch - '0');
							_ch = _in.get();
						}
						if (neg_expo) {
							expo -= scale;
						} else {
							expo += scale;
						}

					} else {
						std::cerr << "digit?\n";
					}
					
					if (expo < 0) {
						if (expo >= std::numeric_limits<double>::min_exponent10) {
							x = x / ten(-expo);
						} else {
							x = 0.0;
						}
					} else if (expo > 0) {
						if (expo <= std::numeric_limits<double>::max_exponent10) {
							x = x * ten(expo);
						} else {
							x = 0.0;
							std::cerr << "too large\n";
						}
					}

					s = Symbol::s_real;
					_real_value = x;
				}
			}
		} else {
			int k = 0;
			for (const auto &d: digits) {
				if (d < 10) {
					if (k < (std::numeric_limits<int>::max() - d) / 10) {
						k = k * 10 + d;
					} else {
						std::cerr << "too large\n";
						break;
					}
				} else {
					std::cerr << "bad integer\n";
					break;
				}
			}
			_int_value = k;
			s = Symbol::s_int;
		}
		return s;
	}

#line 487 "scanner.x"

	Symbol Scanner::identifier() {
		Symbol s { Symbol::s_null };
		std::string id;
		do {
			id += (char) _ch;
			_ch = _in.get();
		} while ((_ch >= '0' && _ch <= '9') || (_ch >= 'A' && _ch <= 'Z') || (_ch >= 'a' && _ch <= 'z'));
		auto found = keywords.find(id);
		if (found != keywords.end()) {
			s = found->second;
		} else {
			s = Symbol::s_ident;
		}
		_id = id;
		return s;
	}

#line 515 "scanner.x"

	void Scanner::string() {
		std::string str;
		_ch = _in.get();
		while (_ch != EOF && _ch != '"') {
			if (_ch >= ' ') {
				str += (char) _ch;
			}
			_ch = _in.get();
		}
		if (_ch != EOF) { _ch = _in.get(); }
		_string = str;
	}

#line 538 "scanner.x"

	void Scanner::hex_string() {
		std::string str;
		_ch = _in.get();
		int m, n;
		while (_ch != EOF && _ch != '$') {
			while (_ch != EOF && _ch <= ' ') {
				_ch = _in.get();
			}
			if (_ch >= '0' && _ch <= '9') {
				m = _ch - '0';
			} else if (_ch >= 'A' && _ch <= 'F') {
				m = _ch - 'A' + 10;
			} else {
				std::cerr << "hexdig expected\n";
			}
			_ch = _in.get();
			if (_ch >= '0' && _ch <= '9') {
				n = _ch - '0';
			} else if (_ch >= 'A' && _ch <= 'F') {
				n = _ch - 'A' + 10;
			} else {
				std::cerr << "hexdig expected\n";
			}
			str += (char) (m * 16 + n);
			_ch = _in.get();
		}
	}

#line 15 "scanner.x"
;
	#endif
