MODULES = text_utils

PG_CONFIG = pg_config
PGXS = $(shell $(PG_CONFIG) --pgxs)
INCLUDEDIR = $(shell $(PG_CONFIG) --includedir-server)

COPY_FILES = text_utils.so
DESTINATION = $(shell $(PG_CONFIG) --pkglibdir)
include $(PGXS)
text_utils.o: 
	cc -fpic -c src/text_utils.c $(CFLAGS) -I$(INCLUDEDIR)
text_utils.so: text_utils.o
	cc -shared -o text_utils.so text_utils.o 
copy:
	cp -f $(COPY_FILES) $(DESTINATION)
install: copy
