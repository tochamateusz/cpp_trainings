prebuild:
	mkdir -p ./build

build: prebuild
	clang++ \
	-std=c++17 \
	-pthread \
	-o ./build/main \
	-I./include \
	./src/main.cpp 

run: build
	./build/main

run-watch:
	reflex -r '\.cpp|\.h$$' -d none -s -- sh -c 'clear && make run'
