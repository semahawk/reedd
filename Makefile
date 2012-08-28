#
# reedd
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

CXX      = gcc
CXXFLAGS = -Wall -Werror -std=c99 -O2 -I./src
YACC     = bison
YFLAGS   = -d
LEX      = flex

OBJECTS = reedd.o installs.o config.y.tab.o config.lex.yy.o config.o

VERSION := ${shell cat VERSION}

all: reedd man clean

reedd: $(OBJECTS)
	$(CXX) $(OBJECTS) -o bin/$@

reedd.o: src/reedd.c src/reedd.h
	$(CXX) $(CXXFLAGS) -D'VERSION="$(VERSION)"' -c src/reedd.c

installs.o: src/cmd/installs.c src/cmd.h
	$(CXX) $(CXXFLAGS) -c src/cmd/installs.c

config.y.tab.o: src/config_grammar.y
	cd src; $(YACC) $(YFLAGS) config_grammar.y
	$(CXX) $(CXXFLAGS) -c src/config.y.tab.c

config.lex.yy.o: src/config_scanner.l
	cd src; $(LEX) config_scanner.l
	$(CXX) $(CXXFLAGS) -D_POSIX_SOURCE -c src/config.lex.yy.c

config.o: src/config.c src/config.h
	$(CXX) $(CXXFLAGS) -c src/config.c

man: reedd.8

%: man/%.in
	sed -e "s/##version##/$(VERSION)/" $< > man/$@

install: all
	install -D -m 0755 bin/reedd /usr/bin/reedd
	install -D -m 0644 man/reedd.8 /usr/man/man8/reedd.8

uninstall:
	rm -f /usr/bin/reedd
	rm -f /usr/man/man8/reedd.8

clean:
	rm -f *~ *.o *.8 *.tab.c *.tab.h *.yy.c
	rm -f src/*~ src/*.o man/*.8 src/*.tab.c src/*.tab.h src/*.yy.c

distclean: clean
	rm -f bin/reedd

# End of file
