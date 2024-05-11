VERSION = v0.2.0

OBJECTS = \
	src/hash.o	\
	src/util.o	\
	src/arraylist.o	\
	src/buffer.o	\
	src/error.o	\
	src/hashmap.o	\
	src/slice.o	\
	src/test.o	\
	# end

OBJECTS += \
	src/test/main.o	\
	src/test/buffer.o	\
	src/test/slice.o	\
	src/test/arraylist.o	\
	src/test/hashmap.o	\
	# end

CFLAGS = \
	-ftrivial-auto-var-init=pattern	\
	-DUSERVE_VERSION=\"$(VERSION)\" \
	-D_POSIX_C_SOURCE=200112L

INCLUDES = -Iinclude/

LDFLAGS =

WARNINGS = -Wall -Wextra -Wmissing-prototypes -Wvla

EXE = tests

include deps/c-build/build.mk
