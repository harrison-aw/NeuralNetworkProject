DIRS = src src/frequency src/retriever

.PHONY: all clean

all:
	for dir in $(DIRS); do \
		$(MAKE) -C $$dir; \
	done
