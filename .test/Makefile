UNA = sample.una

U4 = $(shell readlink /opt/ltx/ltx_os | grep U4)
# U4
ifneq ($(strip $(U4)),)
	UNA = sampleu4.una
endif

SRC = unison-util.cpp unison-util.h lib.uno
DOC = html

all : clean compile run

.PHONY: run clean lib compile doc tar

compile :
	MethodCompiler -f ${UNA}

lib :
	MethodCompiler -force -f ${UNA}

run :
	launcher -load ${UNA} -nodisplay -fast -run &

doc :
	doxygen .doxygen.cfg

tar : doc
	cd ..; tar czf unison-util.tar.gz $(SRC) $(DOC)

clean:
	unload &> /dev/null & pkill optool & sleep 1
