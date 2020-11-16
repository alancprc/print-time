UNA = sample.una

NAME = print-time
DATE = $(shell date +%Y%m%d)
TARBALL = $(NAME)_$(DATE).tar.gz

RELEASE = /net/shfs1/vol/training/training/PAx/Libraries/$(NAME)
ARCHIVED = archived-release/

U4 = $(shell readlink /opt/ltx/ltx_os | grep U4)
# U4
ifneq ($(strip $(U4)),)
	UNA = sampleu4.una
endif

SRC = lib.uno $(NAME).cpp $(NAME).h
DOC = html

all : clean compile run

.PHONY: run clean lib compile doc tar release

compile :
	MethodCompiler -f $(UNA)

lib :
	MethodCompiler -force -f $(UNA)

run :
	launcher -load $(UNA) -nodisplay -fast -run &

doc :
	doxygen .doxygen.cfg

tar :
	mkdir ../$(NAME)
	cd ..; cp -at $(NAME) $(SRC)
	cd ..; tar czf $(TARBALL) $(NAME); tar tzf $(TARBALL)
	rm -rf ../$(NAME)

release :
	mkdir $(RELEASE)
	rm -f $(RELEASE)/$(NAME)_*.tar.gz;
	cp -at $(RELEASE) ../$(TARBALL)

clean:
	unload &> /dev/null & pkill optool & sleep 1
	rm -rf ../$(NAME) ../$(NAME)_*.tar.gz

