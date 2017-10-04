.PHONY:all
all:math_cgi calcDAD calcDSD

calcDAD:calcDAD.cpp
	g++ -o $@ $^
calcDSD:calcDSD.cpp
	g++ -o $@ $^
math_cgi:mathcgi.c
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -f math_cgi calcDAD calcDSD
