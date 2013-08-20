
ifeq ($(platform),osx)
   fpic := -fPIC
   TARGET := libretro.dylib
else ifeq ($(platform),win)
   fpic :=
   TARGET := libretro.dll
   CC = gcc
   CXX = g++
else
   fpic := -fPIC
   TARGET := libretro.so
endif

lynx = lynx
retro = libretro

handy_objs = Cart Memmap Mikie Ram Rom Susie System
retro_objs = libretro
libs = -lz

objects += $(handy_objs) $(retro_objs)

liblynx_objects := $(patsubst %,obj/%.o,$(objects))

includes = -I$(lynx)/ -I$(retro)/

c := $(CC) -std=gnu99
cpp := $(CXX) -std=gnu++0x
flags := -O3 -fomit-frame-pointer -fno-tree-vectorize -I. $(fpic) $(libs) $(includes)

compile = \
  $(strip \
    $(if $(filter %.c,$<), \
      $(c) $(flags) $1 -c $< -o $@, \
      $(if $(filter %.cpp,$<), \
        $(cpp) $(flags) $1 -c $< -o $@ \
      ) \
    ) \
  )

obj/Cart.o: $(lynx)/Cart.cpp
obj/Memmap.o: $(lynx)/Memmap.cpp
obj/Mikie.o: $(lynx)/Mikie.cpp
obj/Ram.o: $(lynx)/Ram.cpp
obj/Rom.o: $(lynx)/Rom.cpp
obj/Susie.o: $(lynx)/Susie.cpp
obj/System.o: $(lynx)/System.cpp
obj/libretro.o: $(retro)/libretro.cpp

%.o: $<; $(call compile)

$(TARGET): $(liblynx_objects)
ifeq ($(platform),x)
	$(cpp) -o $@ -shared $(liblynx_objects) -Wl,--no-undefined -Wl,--version-script=link.T $(libs)
else ifeq ($(platform),win)
	$(cpp) -o $@ -shared $(liblynx_objects) -Wl,--no-undefined -static-libgcc -static-libstdc++ -Wl,--version-script=link.T $(libs)
else
	$(cpp) -o $@ -shared $(liblynx_objects) -Wl,--no-undefined $(libs)
endif

all: $(TARGET)

.PHONY: clean all

clean:
	rm -f $(liblynx_objects) $(TARGET)
