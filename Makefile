all:
	docker build -t jsonsubst .
	docker run --rm -v "${PWD}":/host jsonsubst
	docker rmi jsonsubst

build:
	gcc -static -o jsonsubst jsonsubst.c -ljson-c

clean:
	rm jsonsubst
