prebuild:
	mkdir -p ./build

build: prebuild
	clang++ \
	-std=c++17 \
	-o ./build/main \
	-I./event_queue.h \
	-I./button.h \
	./event_queue.cpp \
	./button.cpp \
	./main.cpp 

run: build
	./build/main

run-watch:
	reflex -r '\.cpp$$' -d none -s -- sh -c 'clear && make run'
