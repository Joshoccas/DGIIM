###############################################################################
# makefile
###############################################################################

SHELL = /bin/bash # for ubuntu

###############################################################################

SRC = $(sort $(wildcard *.cc))
EXE = $(basename $(SRC))
DAT = $(EXE:=.dat)
PNG = $(EXE:=.png)
SVG = $(EXE:=.svg)
PER = $(EXE:=.perf)
REP = $(EXE:=.rep)

###############################################################################

CXXFLAGS = -march=native -Ofast -std=c++11 -Wall
PLT =  "set terminal svg enhanced; \
		set output '$@'; \
		set nokey; \
		set grid; \
		set xlabel 'size (B)'; \
		set ylabel 'time (µs)'; \
		set logscale x 2; \
		set logscale y 2; \
		set xtics rotate; \
		set xtics (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, '1K' 1024, '2K' 2048, '4K' 4096, '8K' 8192, '16K' 16384, '32K' 32768, '64K' 65526, '128K' 131072, '256K' 262144, '512K' 524288, '1M' 1048576, '2M' 2097152, '4M' 4194304, '8M' 8388608, '16M' 16777216, '32M' 33554432, '64M' 67108864, '128M' 134217728, '256M' 268435456, '512M' 536870912, '1G' 1073741824); \
		plot '$<' u 1:2 w lp lc 1 pt 7"

###############################################################################

all: tools $(EXE) $(PNG) $(SVG)

clean:
	$(RM) -rfv $(DAT) $(EXE) $(PER) $(PNG) $(SVG) core.* *~

info:
	@echo "line size = $$(cat /sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size)B"; \
	echo "cache size = $$(cat /sys/devices/system/cpu/cpu0/cache/index*/size | tr '\n' '/')"; \
	echo "cache level = $$(cat /sys/devices/system/cpu/cpu0/cache/index*/level | tr '\n' '/')"; \
	echo "cache type = $$(cat /sys/devices/system/cpu/cpu0/cache/index*/type | tr '\n' '/')"

tools:
	@for i in gnuplot g++; do \
		if [ -z $$(which $$i 2> /dev/null) ]; then \
			echo necesito que instales $$i!!!; \
			exit 1; \
		fi \
	done

###############################################################################

%.dat: %
	./$< | tee $@
#	sudo nice -n -20 su -c './$< | tee $@' $USER # better ;)

%.png: %.dat makefile
	@gnuplot <<< $(PLT:svg=pngcairo)

%.svg: %.dat makefile
	gnuplot <<< $(PLT)

###############################################################################

%.perf: %
	perf record --call-graph dwarf -o $@ -- ./$<

%.report: %.perf
	perf report -g --no-children -i $<

###############################################################################

.PHONY: all clean info tools
.PRECIOUS: $(DAT)
.NOEXPORT:

###############################################################################

