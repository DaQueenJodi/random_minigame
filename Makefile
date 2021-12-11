program_NAME	:=	bin/main
program_CXX_SRCS	:=	$(wildcard src/*.cpp)
program_CXX_OBJS	:=	${program_CXX_SRCS:.cpp=.o}
program_OBJS	:=	$(program_CXX_OBJS)
program_INCLUDE_DIRS	:=  include/ /usr/include
program_LIBRARY_DIRS	:=
program_LIBRARIES	:=	SDL2 SDL2_image SDL2main SDL2_ttf

CPPFLAGS	+=	$(foreach includedir, $(program_INCLUDE_DIRS), -I$(includedir)) -std=c++20 -Wall -Wextra -g
LDFLAGS		+=	$(foreach libarydir, $(program_LIBRARY_DIRS), -L$(librarydir))
LDLLIBS		+=	$(foreach library, $(program_LIBRARIES), -l$(library))

.PHONY: all clean distclean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME) $(LDLLIBS) 

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_CXX_OBJS)

distclean: clean