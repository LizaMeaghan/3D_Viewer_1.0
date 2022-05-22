CC:=gcc
BD=../build/
SV=Saves/default_settings_3d_view.conf
SV_2=Saves/settings_3d_view.conf
CFLAGS=-c -Wall -Wextra
TEST_NAME=test.out
OS=$(shell uname)
TST_LBS=$(shell pkg-config --cflags --libs check) -lm

# ifeq ($(OS), Darwin)
# 	TST_LBS=$(shell pkg-config --cflags --libs check) -lm
# else
# ifeq ($(OS), Linux)
# 	TST_LBS=$(shell pkg-config --cflags --libs check) -lm
# endif
# endif

.PHONY: all clean rebuild

all: translocation install

install: translocation $(BD)3D_Viewer_1_0.pro
	cd $(BD); qmake 3D_Viewer_1_0.pro
	make -C $(BD)

uninstall:
	cd $(BD); rm -f *
	rm -f ../3D_Viewer_1_0.tar.gz

translocation:
	cp $(SV) $(BD)
	cp $(SV_2) $(BD)
	cp 3D_Viewer_1_0/opengl.h $(BD)

./$(BD)3D_Viewer_1_0.pro:
	cp 3D_Viewer_1_0.pro $(BD)

./$(BD)%.o: */%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

rebuild: clean all

test:
	gcc test.c parse.c transformations.c -o $(TEST_NAME) -lm $(TST_LBS)

clean:
	rm -rf report
	rm -f *.o
	rm -f *.a
	rm -f *.gcda
	rm -f *.gcno
	rm -f test.info
	rm -f a.out
	rm -f $(TEST_NAME)
	rm -f valgrind-out.txt
	cd $(BD); rm -f *


ifeq ($(OS), Darwin)
dvi:
	@open manual.html
install_qt:
	brew install qt6
else
dvi:
	xdg-open manual.html
install_qt:
	sudo pacman -S qt6
endif

dist:
	tar -cvf $(BD)../3D_Viewer_1_0.tar $(BD)
	gzip $(BD)../3D_Viewer_1_0.tar

gcov_report: lcov test_ lcov_

lcov:
	$(CC) --coverage -c test.c parse.c transformations.c $(TST_LBS)
	$(CC) --coverage test.o parse.o transformations.o -o $(TEST_NAME) $(TST_LBS)

lcov_:
	lcov -t "Test_3DViewer" -o test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o report test.info --rc lcov_branch_coverage=1

test_:
	-./$(TEST_NAME)

check:
	cppcheck —enable=all —suppress=missingIncludeSystem *.c *.h
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -f CPPLINT.cfg

