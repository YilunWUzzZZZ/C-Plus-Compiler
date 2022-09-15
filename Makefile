#CXX = clang++
CXX = g++
MCXXFLAGS := -g -Wall -O2 -I util/ -std=c++11 $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH)

HOSTSRCS = ParserUtil.C Value.C Type.C SymTabEntry.C SymTab.C STEClasses.C SymTabMgr.C Ast.C Error.C C+_parser.C C+_lexer.C IR.C IRGen.C MemAlloc.C RegAlloc.C ICodeGen.C Optimization.C
TESTSRCS = driveParse.C

SRCS = $(HOSTSRCS) $(TESTSRCS)
HOSTOBJS = $(HOSTSRCS:%.C=%.o)

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.C = $(CXX) $(DEPFLAGS) $(MCXXFLAGS) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

# Disable default rules. It seems hard to ensure that our patterns rules
# fire, instead of the default rules.
.SUFFIXES:

%.o : %.cpp $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

%.o: %.C cxx_flags $(DEPDIR)/%.d
	$(COMPILE.C) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

%.o: test/%.C cxx_flags $(DEPDIR)/%.d
	$(COMPILE.C) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

.PHONY: force

cxx_flags: force
	@echo '$(MCXXFLAGS)' | tr " " '\n' | grep -v '^$$' | sort -u | diff -q $@ - || echo '$(MCXXFLAGS)' | tr " " '\n' | grep -v '^$$' | sort -u  > $@

all: demo

demo: $(HOSTOBJS) driveParse.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

C+_parser.C: C+_parser.y++
	bison -t -d -v -o C+_parser.C C+_parser.y++
#    mv E--_parser.H E--.tab.h


#C+_lexer.C: C+_lexer.l++
#	flex -p -8 -Ce -o C+_lexer.C C+_lexer.l++

#tags: ${SRCS}
#	etags --c++ *.[Chly]

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))

clean:
	rm -f demo *.o *parser.C *parser.H *.output .d/*.d
