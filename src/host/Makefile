CC = gcc
PROGRAM = tddlight

$(PROGRAM): $(PROGRAM).c
	${CC} $< -o $@

install: $(PROGRAM)
	install -m 0755 $(PROGRAM) $(prefix)/bin

clean:
	rm $(PROGRAM)
