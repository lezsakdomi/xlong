CXXFLAGS:=--std=c++11

demo.out: xlong.o main.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^
