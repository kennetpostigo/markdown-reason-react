test:
	dune runtest 

run: 
	./_build/install/default/bin/Index

.PHONY: coverage
coverage: clean
	BISECT_ENABLE=YES dune build
	dune runtest
	bisect-ppx-report -ignore-missing-files -I _build/default/ -html coverage/ \
	    _build/default/tests/bisect*.out
	@echo See ./coverage/index.html

clean:
	rm -f _build/default/tests/bisect*.out
	rm -rf _build *.install
