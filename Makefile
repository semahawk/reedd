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

CXX = gcc
CXXFLAGS += -Wall -Werror -std=c99 -I./src

OBJECTS = reedd.o installs.o

VERSION := ${shell cat VERSION}

all: reedd man

reedd: $(OBJECTS)
	$(CXX) $(OBJECTS) -o bin/$@

reedd.o: src/reedd.c src/reedd.h
	$(CXX) $(CXXFLAGS) -D'VERSION="$(VERSION)"' -c src/reedd.c

installs.o: src/cmd/installs.c src/cmd.h
	$(CXX) $(CXXFLAGS) -c src/cmd/installs.c

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
	rm -f *~ *.o *.8
	rm -f src/*~ src/*.o man/*.8

distclean: clean
	rm -f bin/reedd

# End of file
