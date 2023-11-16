.PHONY: all run run-profile clean lint list

all: run

venv/bin/activate: requirements.txt
	python3 -m venv venv
	./venv/bin/pip install -r requirements.txt

run: venv/bin/activate
	./venv/bin/python3 main.py

run-profile: venv/bin/activate
	./venv/bin/python3 -m cProfile main.py

clean:
	rm -rf venv
	rm -f *.json
	find . -type f -name ‘*.pyc’ -delete

lint: venv/bin/activate
	./venv/bin/pylint main.py generator

list:
	find . -type f -not -path "*/venv/*" -name "*.py" -not -name "__init__.py" | sort
