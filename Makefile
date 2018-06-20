ifeq ($(OS),Windows_NT)
    CPPFLAGS += -DWINDOWS
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CPPFLAGS += -DAMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CPPFLAGS += -DAMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CPPFLAGS += -DIA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    UNAME_O := $(shell uname -o)
    ifeq ($(UNAME_S),Linux)
        CPPFLAGS += -DLINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        CPPFLAGS += -DOSX
    endif
    ifeq ($(UNAME_O),Cygwin)
        CPPFLAGS += -DCYGWIN
    endif
endif

CXX := g++
CXXFLAGS := -Wall -Werror -O3

SOURCEDIR := $(shell pwd)
BUILDDIR := $(SOURCEDIR)/build
ENGINE := $(BUILDDIR)/engine

CXXSRCS := $(shell find $(SOURCEDIR) -type d \( -name '.git' -o -name 'win_32' \) -prune -o -name "*.cpp" -type f) 

CXXOBJS := $(addprefix $(BUILDDIR)/,$(CXXSRCS:%.cpp=%.o))

$(BUILDDIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -I$(HEADERDIR) -I$(dir $<) -c $< -o $@

$(ENGINE): $(CXXOBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: all check clean dist install
all: $(ENGINE)
check:
clean:
	@rm -f $(CXXOBJS) $(ENGINE)
install:
dist:
