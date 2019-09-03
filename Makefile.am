SUBDIRS = \
	quemath \
	test

html:
	doxygen

html-clean:
	rm -rf doc/html

html-release:
	rsync -rz --delete doc/html/ jaydolan.com:/var/www/projects/quemath
