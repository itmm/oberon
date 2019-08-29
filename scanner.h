
#line 4 "scanner.x"

	#pragma once
	
#line 58 "scanner.x"

	#include <map>
	#include <string>

#line 118 "scanner.x"

	#include <iostream>

#line 328 "scanner.x"

	#include <limits>

#line 342 "scanner.x"

	#include <vector>

#line 6 "scanner.x"
;
	
#line 28 "scanner.x"

	enum class Symbol {
		s_null = 0,
		
#line 38 "scanner.x"

	s_times = 1, s_rdiv = 2, s_div = 3, s_mod = 4, s_and = 5,
	s_plus = 6, s_minus = 7, s_or = 8, s_eql = 9, s_neq = 10,
	s_lss = 11, s_leq = 12, s_gtr = 13, s_geq = 14, s_in = 15,
	s_is = 16, s_arrow = 17, s_period = 18, s_char = 20,
	s_int = 21, s_real = 22, s_false = 23, s_true = 24, s_nil = 25,
	s_string = 26, s_not = 27, s_lparen = 28, s_lbrak = 29,
	s_lbrace = 30, s_ident = 31, s_if = 32, s_while = 34,
	s_repeat = 35, s_case = 36, s_for = 37, s_comma = 40,
	s_colon = 41, s_becomes = 42, s_upto = 43, s_rparen = 44,
	s_rbrak = 45, s_rbrace = 46, s_then = 47, s_of = 48, s_do = 49,
	s_to = 50, s_by = 51, s_semicolon = 52, s_end = 53, s_bar = 54,
	s_else = 55, s_elsif = 56, s_until = 57, s_return = 58,
	s_array = 60, s_record = 61, s_pointer = 62, s_const = 63,
	s_type = 64, s_var = 65, s_procedure = 66, s_begin = 67,
	s_import = 68, s_module = 69,

#line 31 "scanner.x"

		s_eot = 70
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

#line 139 "scanner.x"

	void next_ch() {
		_ch = _in.get();
		// std::cout << (char) _ch;
	}

#line 154 "scanner.x"

	void comment();

#line 160 "scanner.x"

	Symbol number();

#line 334 "scanner.x"

	int _int_value;
	double _real_value;
	static double ten(int expo);

#line 488 "scanner.x"

	Symbol identifier();
	std::string _id;

#line 516 "scanner.x"

	void string();
	std::string _string;

#line 540 "scanner.x"

	void hex_string();

#line 10 "scanner.x"
;
		public:
			
#line 131 "scanner.x"

	Scanner(std::istream &in = std::cin):
		_in { in }, _ch{' '}
	{ }

#line 148 "scanner.x"

	Symbol next();

#line 578 "scanner.x"

	const std::string &id() const {
		return _id;
	}

#line 12 "scanner.x"
;
	};
	#if scanner_IMPL
		
#line 166 "scanner.x"

	Symbol Scanner::next() {
		Symbol s = Symbol::s_null;
		while (s == Symbol::s_null) {
			while (_ch != EOF && _ch <= ' ') {
				next_ch();
			}
			if (_ch == EOF) {
				s = Symbol::s_eot;
			} else if (_ch < 'A') {
				if (_ch < '0') {
					if (_ch == '"') {
						string();
						s = Symbol::s_string;
					} else if (_ch == '#') {
						next_ch();
						s = Symbol::s_neq;
					} else if (_ch == '$') {
						hex_string();
						s = Symbol::s_string;
					} else if (_ch == '&') {
						next_ch();
						s = Symbol::s_and;
					} else if (_ch == '(') {
						next_ch();
						if (_ch == '*') {
							comment();
						} else {
							s = Symbol::s_lparen;
						}
					} else if (_ch == ')') {
						next_ch();
						s = Symbol::s_rparen;
					} else if (_ch == '*') {
						next_ch();
						s = Symbol::s_times;
					} else if (_ch == '+') {
						next_ch();
						s = Symbol::s_plus;
					} else if (_ch == ',') {
						next_ch();
						s = Symbol::s_comma;
					} else if (_ch == '-') {
						next_ch();
						s = Symbol::s_minus;
					} else if (_ch == '.') {
						next_ch();
						if (_ch == '.') {
							next_ch();
							s = Symbol::s_upto;
						} else {
							s = Symbol::s_period;
						}
					} else if (_ch == '/') {
						next_ch();
						s = Symbol::s_rdiv;
					}
				} else if (_ch < ':') {
					s = number();
				} else if (_ch == ':') {
					next_ch();
					if (_ch == '=') {
						next_ch();
						s = Symbol::s_becomes;
					} else {
						s = Symbol::s_colon;
					}
				} else if (_ch == ';') {
					next_ch();
					s = Symbol::s_semicolon;
				} else if (_ch == '<') {
					next_ch();
					if (_ch == '=') {
						next_ch();
						s = Symbol::s_leq;
					} else {
						s = Symbol::s_lss;
					}
				} else if (_ch == '=') {
					next_ch();
					s = Symbol::s_eql;
				} else if (_ch == '>') {
					next_ch();
					if (_ch == '=') {
						next_ch();
						s = Symbol::s_geq;
					} else {
						s = Symbol::s_gtr;
					}
				} 
			} else if (_ch < '[') {
				s = identifier();
			} else if (_ch < 'a') {
				if (_ch == '[') {
					next_ch();
					s = Symbol::s_lbrak;
				} else if (_ch == ']') {
					next_ch();
					s = Symbol::s_rbrak;
				} else if (_ch == '^') {
					next_ch();
					s = Symbol::s_arrow;
				}
			} else if (_ch < '{') {
				s = identifier();
			} else {
				if (_ch == '{') {
					next_ch();
					s = Symbol::s_lbrace;
				} else if (_ch == '}') {
					next_ch();
					s = Symbol::s_rbrace;
				} else if (_ch == '|') {
					next_ch();
					s = Symbol::s_bar;
				} else if (_ch == '~') {
					next_ch();
					s = Symbol::s_not;
				} else if (_ch == '\x7f') {
					next_ch();
					s = Symbol::s_upto;
				}
			}
		}
		return s;
	}

#line 296 "scanner.x"

	void Scanner::comment() {
		
#line 304 "scanner.x"

	next_ch();
	do {
		while (_ch != EOF && _ch != '*') {
			if (_ch == '(') {
				next_ch();
				if (_ch == '*') {
					comment();
				}
			} else {
				next_ch();
			}
		}
		while (_ch == '*') { next_ch(); }
	} while (_ch != EOF && _ch != ')');
	if (_ch != EOF) {
		next_ch();
	} else {
		std::cerr << "unterminated comment\n";
	}

#line 298 "scanner.x"
;
	}

#line 348 "scanner.x"

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
			next_ch();
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
			next_ch();
		} else if (_ch == '.') {
			next_ch();
			if (_ch == '.') {
				_ch = '\x7f';
				int k = 0;
				for (const auto &d : digits) {
					if (d < 10) {
						if (k <= (std::numeric_limits<int>::max() - d) / 10) {
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
					next_ch();
				}
				if (_ch == 'E' || _ch == 'D') {
					next_ch();
					bool neg_expo { false };
					if (_ch == '-') {
						next_ch();
						neg_expo = true;
					} else if (_ch == '+') {
						next_ch();
					}
					if (_ch >= '0' && _ch <= '9') {
						int scale { 0 };
						while (_ch >= 0 && _ch <= '9') {
							scale = scale * 10 + (_ch - '0');
							next_ch();
						}
						if (neg_expo) {
							expo -= scale;
						} else {
							expo += scale;
						}

					} else {
						std::cerr << "digit?\n";
					}
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
		} else {
			int k = 0;
			for (const auto &d: digits) {
				if (d < 10) {
					if (k <= (std::numeric_limits<int>::max() - d) / 10) {
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

#line 495 "scanner.x"

	Symbol Scanner::identifier() {
		Symbol s { Symbol::s_null };
		std::string id;
		do {
			id += (char) _ch;
			next_ch();
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

#line 523 "scanner.x"

	void Scanner::string() {
		std::string str;
		next_ch();
		while (_ch != EOF && _ch != '"') {
			if (_ch >= ' ') {
				str += (char) _ch;
			}
			next_ch();
		}
		if (_ch != EOF) { next_ch(); }
		_string = str;
	}

#line 546 "scanner.x"

	void Scanner::hex_string() {
		std::string str;
		next_ch();
		int m, n;
		while (_ch != EOF && _ch != '$') {
			while (_ch != EOF && _ch <= ' ') {
				next_ch();
			}
			if (_ch >= '0' && _ch <= '9') {
				m = _ch - '0';
			} else if (_ch >= 'A' && _ch <= 'F') {
				m = _ch - 'A' + 10;
			} else {
				std::cerr << "hexdig expected\n";
			}
			next_ch();
			if (_ch >= '0' && _ch <= '9') {
				n = _ch - '0';
			} else if (_ch >= 'A' && _ch <= 'F') {
				n = _ch - 'A' + 10;
			} else {
				std::cerr << "hexdig expected\n";
			}
			str += (char) (m * 16 + n);
			next_ch();
		}
	}

#line 15 "scanner.x"
;
	#endif
