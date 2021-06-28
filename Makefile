lib.name = phase_shaper
class.sources = phase_shaper~.c
phase_shaper~.class.sources = biquad_allpass.c
phase_shaper~.class.sources += vas_mem.c



PDDIR=C:/Program Files/Pd

include pd-lib-builder/Makefile.pdlibbuilder
