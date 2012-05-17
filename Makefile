#
# griff
#
# Copyright: (c) 2012 by Szymon Urbaś <urbas@hush.ai>
#
# License: (the MIT license)
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

BINDIR = /usr/local/bin
MANDIR = /usr/local/man

CXX = gcc
CXXFLAGS += -Wall -Werror -std=c99 -I./src

OBJECTS = griff.o installs.o

VERSION := ${shell cat VERSION}

all: griff man

griff: $(OBJECTS)
	$(CXX) $(OBJECTS) -o bin/$@

griff.o: src/griff.c src/griff.h
	$(CXX) $(CXXFLAGS) -D'VERSION="$(VERSION)"' -c src/griff.c

installs.o: src/cmd/installs.c src/cmd.h
	$(CXX) $(CXXFLAGS) -c src/cmd/installs.c

man: griff.8

%: man/%.in
	sed -e "s/##version##/$(VERSION)/" $< > man/$@

install: all
	install -D -m 0755 bin/griff $(BINDIR)/griff
	install -D -m 0644 man/griff.8 $(MANDIR)/man8/griff.8

uninstall:
	rm -f $(BINDIR)/griff
	rm -f $(MANDIR)/man8/griff.8

clean:
	rm -f *~ *.o *.8
	rm -f src/*~ src/*.o man/*.8

distclean: clean
	rm -f bin/griff

# End of file
