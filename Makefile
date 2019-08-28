SRCs := $(shell hx-srcs.sh)
FILEs := $(shell hx-files.sh $(SRCs))
CPPs := $(filter %.cpp,$(FILEs))
HTMLs := $(SRCs:.x=.html)
Ds := $(CPPs:.cpp=.d)
Os := $(CPPs:.cpp=.o)

.PHONY: all clean

all: poc $(HTMLs)

-include $(Ds)

CXXFLAGS += -Wall -MMD -std=c++17 -g

poc: $(Os)
	$(CXX) $^ -o $@

hx-run: $(SRCs)
	hx
	date > hx-run

$(FILEs) $(HTMLs): hx-run

clean:
	rm -f $(FILEs) $(HTMLs) $(Ds) poc hx-run
