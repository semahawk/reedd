#
# cara
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

# Please, do not mess with that
VERSION = 0.1.0

BINDIR = /usr/local/bin
MANDIR = /usr/local/man

CXX = gcc
CXXFLAGS += -Wall -Werror -std=c99 -DVERSION=\"$(VERSION)\"

OBJECTS = cara.o commands.o

all: cara man

cara: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

cara.o: cara.c cara.h
	$(CXX) $(CXXFLAGS) -c cara.c 

commands.o: commands.c commands.h
	$(CXX) $(CXXFLAGS) -c commands.c

man: cara.8

%: %.in
	sed -e "s/##version##/$(VERSION)/" $< > $@

install: all
	install -D -m 0755 cara $(BINDIR)/cara
	install -D -m 0644 cara.8 $(MANDIR)/man8/cara.8

clean:
	rm -f *~ *.o *.8

distclean: clean
	rm -f cara

uninstall: distclean
	rm -f $(BINDIR)/cara
	rm -f $(MANDIR)/man8/cara.8

# End of file
