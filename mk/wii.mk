#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	libflixel++
BUILD		:=	obj
SOURCES		:=	source
DATA		:=	data  
INCLUDES	:=  include

#---------------------------------------------------------------------------------
# version for release generation
#---------------------------------------------------------------------------------
MAJOR	 = 0
MINOR	 = 3
REVISION = 0f

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

CFLAGS	= -g -O2 -Wall $(MACHDEP) $(INCLUDE) `freetype-config --cflags` -D__WII__
CXXFLAGS	=	$(CFLAGS)

LDFLAGS	=	-g $(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:=	`freetype-config --libs` -lpng -lz -logc -lm

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES))
export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(sFILES:.s=.o) $(SFILES:.S=.o)
export OFILES := $(OFILES_BIN) $(OFILES_SOURCES)

export HFILES := $(addsuffix .h,$(subst .,_,$(BINFILES)))

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES), -iquote $(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/include \
					-I$(CURDIR)/$(BUILD) \
					-I$(LIBOGC_INC)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
					-L$(LIBOGC_LIB)

export OUTPUT	:=	$(CURDIR)/build/$(TARGET)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@[ -d $(CURDIR)/build ] || mkdir -p $(CURDIR)/build
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/mk/wii.mk

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT).a $(OUTPUT) $(CURDIR)/lib $(TARGET)-*.tgz
#---------------------------------------------------------------------------------
install:
	@[ -d $(PORTLIBS_PATH)/wii/lib ] || mkdir -p $(PORTLIBS_PATH)/wii/lib
	cp $(OUTPUT).a $(PORTLIBS_PATH)/wii/lib/$(TARGET).a
	@[ -d $(PORTLIBS_PATH)/wii/include ] || mkdir -p $(PORTLIBS_PATH)/wii/include
	cp -fr include/* $(PORTLIBS_PATH)/wii/include/.

#---------------------------------------------------------------------------------
uninstall:
	rm $(PORTLIBS_PATH)/wii/lib/$(TARGET).a
	rm -fr $(PORTLIBS_PATH)/wii/include/flixel++* 


#---------------------------------------------------------------------------------
tgz:
	tar -C $(CURDIR) -czf $(TARGET)-$(MAJOR).$(MINOR).$(REVISION).tgz lib include

#---------------------------------------------------------------------------------
src:
	make clean
	tar -C $(CURDIR) --exclude=*.tgz -czf $(TARGET)-$(MAJOR).$(MINOR).$(REVISION)_src.tgz *

#---------------------------------------------------------------------------------
run:
	wiiload $(TARGET).dol

#---------------------------------------------------------------------------------
%.a:
	@echo linking to lib ... $(notdir $@)
	@$(AR) -rc $@ $^
#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).a: $(OFILES)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .jpg extension
#---------------------------------------------------------------------------------
%.jpg.o	:	%.jpg
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------