all: start

start:
	docker run --rm -v ${LOCAL_WORKSPACE_FOLDER}/:/src emscripten/emsdk ls
	mkdir -p build
	npm install
	npm run start

node_test:
	./node-test.sh

test:
	./make-test.sh

clean:
	rm -f dist/*
	rm -f build/*

