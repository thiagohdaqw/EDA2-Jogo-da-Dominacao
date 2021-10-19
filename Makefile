# Makefile apenas para os arquivos de teste em tests/

cxx = g++
cxxflags = -g -static -lm

exec = tests
build_dir ?= tests
bin_dir ?= bin

test_srcs := $(wildcard $(build_dir)/*.t.cpp)
test_objs := $(test_srcs:%=%.o)


all: $(bin_dir)/$(exec)
	@echo "done building tests"

$(bin_dir)/$(exec): $(test_objs)
	@$(cxx) $(cxxflags) $(test_objs) -o $@

$(build_dir)/%.t.cpp.o: $(build_dir)/%.t.cpp
	@$(cxx) $(cxxflags) -c $< -o $@
	
debug:
	@echo "test_srcs: $(test_srcs)"
	@echo "test_objs: $(test_objs)"

clean:
	@rm $(build_dir)/*.o

MKDIR_P ?= mkdir -p
