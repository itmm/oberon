# Oberon Parser

```
@Def(file: parser.h)
	#pragma once
	@put(includes)
	class Parser {
		private:
			@put(privates);
		public:
			@put(publics);
	};
	#if parser_IMPL
		@put(impl);
	#endif
@End(file: parser.h)
```

```
@Def(file: parser.cpp)
	#define parser_IMPL 1
	#include "parser.h"
@End(file: parser.cpp)
```

```
@inc(scanner.x)
```

```
@def(includes)
	#include "scanner.h"
@end(includes)
```

```
@def(privates)
	Scanner &_scanner;
	Symbol _symbol;
@end(privates)
```

```
@def(publics)
	Parser(Scanner &sc): _scanner { sc }, _symbol { sc.next() } { }
@end(publics)
```

```
@add(publics)
	void module();
@end(publics)
```

```
@add(privates)
	int _version;
	std::string _module;
@end(privates)
```

```
@add(privates)
	void check(Symbol s, const std::string &msg);
@end(privates)
```

```
@def(impl)
	void Parser::check(Symbol s, const std::string &msg) {
		if (_symbol == s) {
			_symbol = _scanner.next();
		} else {
			std::cerr << msg << " " << (int) _symbol << '\n';
		}
	}
@end(impl)
```

```
@add(impl)
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
@end(impl)
```
