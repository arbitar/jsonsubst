all:
	docker build -t jsonsubst .
	docker run --rm -v "${PWD}":/host jsonsubst
	docker rmi jsonsubst

clean:
	rm jsonsubst
