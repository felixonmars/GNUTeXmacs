
###############################################################################
# MODULE     : Make file for shell plugin
# COPYRIGHT  : (C) 1999-2008  Joris van der Hoeven
###############################################################################
# This software falls under the GNU general public license version 3 or later.
# It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
# in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
###############################################################################

CXX = g++
RM = rm -f

all: bin/tm_shell

bin/tm_shell: src/tm_shell.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I../../src/System src/tm_shell.cpp -o bin/tm_shell -lutil

clean:
	$(RM) bin/tm_shell
