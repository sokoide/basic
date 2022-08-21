TARGET = bas
OUTDIR = ~/tmp/hoge

COMMONFILES =
SRCS = main.c \
	   basic.c
HEADERS :=  $(shell find . -type f -name '*.h')
OBJS = $(SRCS:.c=.o)

OUTOBJS = $(addprefix $(OUTDIR)/,$(OBJS))

CXX = clang
CXXFLAGS = -std=c17 -Wall -g -O0 -I.

.PHONY:	default build run diag clean test test2

default: $(TARGET)

$(TARGET): build

build: $(OUTOBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(OUTDIR)/$(TARGET) $(LDFLAGS)

$(OUTDIR)/%.o: %.c $(OUTDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTDIR):
	mkdir -p $(OUTDIR)

run: $(TARGET)
	$(OUTDIR)/$(TARGET)

test: $(TARGET)
	$(OUTDIR)/$(TARGET) < test.bas

test2: $(TARGET)
	$(OUTDIR)/$(TARGET) < test2.bas

diag: $(TARGET)
	#readelf -d $(OUTDIR)/$(TARGET)
	objdump -p $(OUTDIR)/$(TARGET)

clean:
	rm -rf $(OUTDIR)
