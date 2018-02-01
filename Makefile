CXXFLAGS:=--std=c++11

demo.out: xlong.o main.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^

.PHONY: run
run: demo.out
	@echo Program started.
	@./$< && echo && echo Returned status $$?
