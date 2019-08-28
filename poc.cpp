
#line 8 "index.x"

	#include "parser.h"
	int main() {
		Scanner sc { std::cin };
		Parser prs { sc };
		prs.module();
	}
