SRCs := $(shell hx-srcs.sh)
FILEs := $(shell hx-files.sh $(SRCs))
CPPs := $(filter %.cpp,$(FILEs))
HTMLs := $(SRCs:.x=.html)
Ds := $(CPPs:.cpp=.d)
Os := $(CPPs:.cpp=.o)

.PHONY: all clean

all: oberon $(HTMLs)

-include $(Ds)

CXXFLAGS += -Wall -MMD -std=c++17

oberon: $(Os)
	$(CXX) $^ -o $@

hx-run: $(SRCs)
	hx
	date > hx-run

$(FILEs) $(HTMLs): hx-run

clean:
	rm -f $(FILEs) $(HTMLs) $(Ds) oberon hx-run
