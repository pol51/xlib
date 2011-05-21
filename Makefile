test: main.cpp
	g++ main.cpp -o test -lX11

clean:
	rm -f test