SRC_BASE_PATH=/root/lpz/phxpaxos

all:phx_multism_echo_bin 

include $(SRC_BASE_PATH)/makefile.mk

include Makefile.define
PHX_MULTISM_ECHO_SRC=$(PHX_MULTISM_ECHO_OBJ)
PHX_MULTISM_ECHO_INCS=$(sort $(SRC_BASE_PATH)/sample/phx_multism_echo $(PHXPAXOS_PLUGIN_PATH) $(PHXPAXOS_INCLUDE_PATH) $(LEVELDB_INCLUDE_PATH) $(PROTOBUF_INCLUDE_PATH))
PHX_MULTISM_ECHO_FULL_LIB_PATH=$(SRC_BASE_PATH)//sample/phx_multism_echo
PHX_MULTISM_ECHO_EXTRA_CPPFLAGS=-Wall -Werror

CPPFLAGS+=$(patsubst %,-I%, $(PHX_MULTISM_ECHO_INCS))
CPPFLAGS+=$(PHX_MULTISM_ECHO_EXTRA_CPPFLAGS)
LDFLAGS+=-lsnappy
PHX_MULTISM_ECHO_LINK=
PHX_MULTISM_ECHO_SYS_LIB=$(PHXPAXOS_LIB_PATH)/libphxpaxos_plugin.a $(PHXPAXOS_LIB_PATH)/libphxpaxos.a $(LEVELDB_LIB_PATH)/libleveldb.a $(PROTOBUF_LIB_PATH)/libprotobuf.a $(GLOG_LIB_PATH)/libglog.a $(GFLAGS_LIB_PATH)/libgflags.a -lpthread
PHX_MULTISM_ECHO_FLAGS+=$(LDFLAGS)

PHX_MULTISM_ECHO_FLAGS+=$(patsubst %,-l%, $(PHX_MULTISM_ECHO_LINK))
PHX_MULTISM_ECHO_FLAGS+=$(PHX_MULTISM_ECHO_SYS_LIB)
phx_multism_echo_bin:phx_multism_echo_dir phx_multism_echo

phx_multism_echo_dir:$(PHX_MULTISM_ECHO_FULL_LIB_PATH)
	@for dir in $^;\
	do \
	current_dir=`readlink $$dir -m`;\
	pwd_dir=`pwd`;\
	pwd_dir=`readlink $$pwd_dir -m`;\
	if ([ "$$current_dir" != "$$pwd_dir" ]); then \
	make -C $$dir;\
	fi;\
	done

phx_multism_echo:$(PHX_MULTISM_ECHO_SRC)
	$(CXX) $^ -o $@ $(PHX_MULTISM_ECHO_FLAGS)
	cp $@ $(SRC_BASE_PATH)/.sbin/

clean:
	rm -rf *.o *.pb.* phx_multism_echo $(SRC_BASE_PATH)/.sbin/phx_multism_echo phx_multism_echo 

