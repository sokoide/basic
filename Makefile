TARGET = bas
TESTTARGET = bastest
OUTDIR = ~/tmp/hoge

COMMONFILES =
SRCS = main.c \
	   basic.c
TESTSRCS = testmain.c \
		   basic.c
HEADERS :=  $(shell find . -type f -name '*.h')
OBJS = $(SRCS:.c=.o)
TESTOBJS = $(TESTSRCS:.c=.o)

OUTOBJS = $(addprefix $(OUTDIR)/,$(OBJS))
TESTOUTOBJS = $(addprefix $(OUTDIR)/,$(TESTOBJS))

CXX = clang
CXXFLAGS = -std=c17 -Wall -g -O0 -I. -I/opt/homebrew/include

.PHONY:	default build run diag clean itest itest2 test

default: $(TARGET)

$(TARGET): build

$(TESTTARGET): testbuild

build: $(OUTOBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(OUTDIR)/$(TARGET) $(LDFLAGS)

testbuild: $(TESTOUTOBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(OUTDIR)/$(TESTTARGET) $(LDFLAGS) -L/opt/homebrew/lib -lcheck

$(OUTDIR)/%.o: %.c $(OUTDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTDIR):
	mkdir -p $(OUTDIR)

run: $(TARGET)
	$(OUTDIR)/$(TARGET)

test: $(TESTTARGET)
	$(OUTDIR)/$(TESTTARGET)

itest: $(TARGET)
	$(OUTDIR)/$(TARGET) < test.bas

itest2: $(TARGET)
	$(OUTDIR)/$(TARGET) < test2.bas

diag: $(TARGET)
	#readelf -d $(OUTDIR)/$(TARGET)
	objdump -p $(OUTDIR)/$(TARGET)

clean:
	rm -rf $(OUTDIR)
