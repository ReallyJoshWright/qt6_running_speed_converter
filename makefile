all:
	@$(MAKE) -C src -f src.mk
.PHONY: clean
clean:
	@$(MAKE) -C src -f src.mk clean
