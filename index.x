# Oberon-Compiler in C++

```
@inc(parser.x)
```

```
@Def(file: poc.cpp)
	#include "parser.h"
	int main() {
		Scanner sc { std::cin };
		Parser prs { sc };
		prs.module();
	}
@End(file: poc.cpp)
```
