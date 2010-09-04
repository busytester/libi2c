libi2c.so: i2c.c
	gcc -shared -Wl,-soname,$@ -Wall -pedantic -o $@ -lc

i2c-ctl: i2c-ctl.c libi2c.so
	gcc -L./ -Wall -pedantic -o $@ $^ -li2c

install: libi2c.so
	cp ./libi2c.so /usr/local/lib

clean:
	rm -f i2c-ctl libi2c.so
