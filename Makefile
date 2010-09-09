all: libi2cio.so i2c-ctl

PREFIX:=/usr

i2c-io.o : i2c-io.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -fPIC -g -c -Wall $^

libi2cio.so: i2c-io.o
	$(CROSS_COMPILE)gcc -shared $(CFLAGS) \
		-Wl,-soname,$@.1 -o $@.1.0.1 $^ -lc
	ln -s $@.1.0.1 $@

# test app
i2c-ctl: i2c-ctl.c
	$(CROSS_COMPILE)gcc -L./ -I./ $(CFLAGS) -o $@ $^ -li2cio

install: all
	install -m 0755 i2c-ctl $(PREFIX)/bin/
	install -m 0755 libi2cio.so.1.0.1 $(PREFIX)/lib/
	ln -sf $(PREFIX)/lib/libi2cio.so.1.0.1 $(PREFIX)/lib/libi2cio.so.1
	ln -sf $(PREFIX)/lib/libi2cio.so.1 $(PREFIX)/lib/libi2cio.so

clean:
	rm -f i2c-ctl *.o *.so *.so.*

.PHONY: clean install
