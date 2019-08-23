AM_TESTS_ENVIRONMENT = \
	AM_TESTS=1; export AM_TESTS;

TESTS = \
	vec

CFLAGS += \
	-I$(top_srcdir)/quemath \
	@HOST_CFLAGS@ \
	@CHECK_CFLAGS@

LDADD = \
	@CHECK_LIBS@

check_PROGRAMS = \
	$(TESTS)
