CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -fpermissive -g -std=c++17 -Ilib/linuxptp-2.0/ 

SRCDIR := src
SRCS := $(wildcard $(SRCDIR)/*.cpp)
HPPS := $(wildcard $(SRCDIR)/*.hpp)
OBJDIR := obj
OBJS := $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.cpp=.o)))
BINDIR := bin

AR=/usr/bin/ar
ARFLAGS=-crs

LD=g++
LD_LIBS=
LDFLAGS=

LINUXPTP_LIB := lib/linuxptp-2.0/liblinuxptp.a

#ASTYLE := astyle
#ASTYLE_FLAGS := --options=astyle.cfg

DEPDIR := dep
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.cpp = $(CXX) $(DEPFLAGS) $(CXXFLAGS) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all :
	$(MAKE) -C lib/linuxptp-2.0
	$(AR) $(ARFLAGS) $(LINUXPTP_LIB) lib/linuxptp-2.0/*.o
	$(MAKE) $(BINDIR)/ptpphcshm

$(BINDIR)/ptpphcshm : $(OBJS) $(LINUXPTP_LIB) | $(BINDIR)
	$(LD) $(LDFLAGS) -o $@ $^ $(LD_LIBS)
	
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	$(COMPILE.cpp) $< -o $@
	$(POSTCOMPILE)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(DEPDIR) :
	mkdir -p $(DEPDIR)

$(BINDIR) :
	mkdir -p $(BINDIR)

clean :
	$(MAKE) -C lib/linuxptp-2.0 clean
	rm -f $(OBJS) $(BINDIR)/ptpphcshm

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(notdir $(basename $(SRCS))))
