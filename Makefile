FILES=CMakeLists.txt AUTHORS ChangeLog Makefile configure README TODO src/ sample/
TARBALL=berson_r-PrPa.tar.bz2

ERROR="<It seems that the build/ directory is missing\nMaybe you forgot to execute the configure ?>"

.PHONY: check pit track


all:
	@make -j 4 -C build

clean:
	@echo -e "\033[33m< ---------------------- >\033[37m"
	@echo -e "\033[33m< Cleaning PrPa Project  >\033[37m"
	@echo -e "\033[33m< ---------------------- >\033[37m"
	@rm -f *.dot
	@if [ -e build/ ] ; then make -C build/ clean ; fi 1>/dev/null

distclean: clean
	@echo -e "\033[34m< Preparing directory for dist >\033[37m"
	@if [ -e build/ ] ; then rm -fr build/ ; fi 1>/dev/null
	@rm -frv track pit
	@if test -e $(TARBALL) ; then rm -fr $(TARBALL) ; fi 1>/dev/null

dist: distclean
	@mkdir berson_r
	@cp -r $(FILES) berson_r/
	@tar cjvf $(TARBALL) berson_r/
	@rm -fr berson_r
