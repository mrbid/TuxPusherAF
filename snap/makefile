all:
	gcc -DBUILD_GLFW ../main.c ../glad_gl.c -I ../inc -Ofast -lglfw -lm -o tuxpusheraf

install:
	cp tuxpusheraf $(DESTDIR)

uninstall:
	rm $(DESTDIR)/tuxpusheraf

clean:
	rm tuxpusheraf