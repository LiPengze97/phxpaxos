SRC_BASE_PATH=/root/lpz/phxpaxos

all:lib_node test_propose_batch_bin 

include $(SRC_BASE_PATH)/makefile.mk

include Makefile.define
NODE_SRC=$(NODE_OBJ)
NODE_INCS=$(sort $(SRC_BASE_PATH)/src/communicate/tcp $(SRC_BASE_PATH)/src/communicate $(SRC_BASE_PATH)/src/checkpoint $(SRC_BASE_PATH)/src/algorithm $(SRC_BASE_PATH)/src/sm-base $(SRC_BASE_PATH)/src/config $(SRC_BASE_PATH)/src/utils $(SRC_BASE_PATH)/src/comm $(PROTOBUF_INCLUDE_PATH) $(SRC_BASE_PATH)/include $(SRC_BASE_PATH)/src/logstorage $(LEVELDB_INCLUDE_PATH) $(SRC_BASE_PATH)/src/master $(SRC_BASE_PATH)/src/node)
NODE_FULL_LIB_PATH=$(SRC_BASE_PATH)/include $(SRC_BASE_PATH)/src/utils $(SRC_BASE_PATH)/src/comm $(SRC_BASE_PATH)/src/logstorage $(SRC_BASE_PATH)/src/sm-base $(SRC_BASE_PATH)/src/config $(SRC_BASE_PATH)/src/communicate/tcp $(SRC_BASE_PATH)/src/communicate $(SRC_BASE_PATH)/src/checkpoint $(SRC_BASE_PATH)/src/algorithm $(SRC_BASE_PATH)/src/master $(SRC_BASE_PATH)//src/node
NODE_EXTRA_CPPFLAGS=-Wall -Werror

CPPFLAGS+=$(patsubst %,-I%, $(NODE_INCS))
CPPFLAGS+=$(NODE_EXTRA_CPPFLAGS)

lib_node:$(SRC_BASE_PATH)/.lib/libnode.a

$(SRC_BASE_PATH)/.lib/libnode.a: $(NODE_SRC)
	ar -cvq $@ $(NODE_SRC)

TEST_PROPOSE_BATCH_SRC=$(TEST_PROPOSE_BATCH_OBJ)
TEST_PROPOSE_BATCH_INCS=$(sort $(SRC_BASE_PATH)/src/communicate/tcp $(SRC_BASE_PATH)/src/communicate $(SRC_BASE_PATH)/src/checkpoint $(SRC_BASE_PATH)/src/algorithm $(SRC_BASE_PATH)/src/sm-base $(SRC_BASE_PATH)/src/config $(SRC_BASE_PATH)/src/utils $(SRC_BASE_PATH)/src/comm $(PROTOBUF_INCLUDE_PATH) $(SRC_BASE_PATH)/include $(SRC_BASE_PATH)/src/logstorage $(LEVELDB_INCLUDE_PATH) $(SRC_BASE_PATH)/src/master $(SRC_BASE_PATH)/src/node)
TEST_PROPOSE_BATCH_FULL_LIB_PATH=$(SRC_BASE_PATH)/include $(SRC_BASE_PATH)/src/utils $(SRC_BASE_PATH)/src/comm $(SRC_BASE_PATH)/src/logstorage $(SRC_BASE_PATH)/src/sm-base $(SRC_BASE_PATH)/src/config $(SRC_BASE_PATH)/src/communicate/tcp $(SRC_BASE_PATH)/src/communicate $(SRC_BASE_PATH)/src/checkpoint $(SRC_BASE_PATH)/src/algorithm $(SRC_BASE_PATH)/src/master $(SRC_BASE_PATH)/src/node $(SRC_BASE_PATH)//src/node
TEST_PROPOSE_BATCH_EXTRA_CPPFLAGS=-Wall -Werror

CPPFLAGS+=$(patsubst %,-I%, $(TEST_PROPOSE_BATCH_INCS))
CPPFLAGS+=$(TEST_PROPOSE_BATCH_EXTRA_CPPFLAGS)

TEST_PROPOSE_BATCH_LINK=node communicate communicate_tcp algorithm checkpoint master config smbase logstorage comm utils
TEST_PROPOSE_BATCH_SYS_LIB=-lpthread $(PROTOBUF_LIB_PATH)/libprotobuf.a $(LEVELDB_LIB_PATH)/libleveldb.a
TEST_PROPOSE_BATCH_FLAGS+=$(LDFLAGS)

TEST_PROPOSE_BATCH_FLAGS+=$(patsubst %,-l%, $(TEST_PROPOSE_BATCH_LINK))
TEST_PROPOSE_BATCH_FLAGS+=$(TEST_PROPOSE_BATCH_SYS_LIB)
test_propose_batch_bin:test_propose_batch_dir test_propose_batch

test_propose_batch_dir:$(TEST_PROPOSE_BATCH_FULL_LIB_PATH)
	@for dir in $^;\
	do \
	current_dir=`readlink $$dir -m`;\
	pwd_dir=`pwd`;\
	pwd_dir=`readlink $$pwd_dir -m`;\
	if ([ "$$current_dir" != "$$pwd_dir" ]); then \
	make -C $$dir;\
	fi;\
	done

test_propose_batch:$(TEST_PROPOSE_BATCH_SRC)
	$(CXX) $^ -o $@ $(TEST_PROPOSE_BATCH_FLAGS)
	cp $@ $(SRC_BASE_PATH)/.sbin/

clean:
	rm -rf *.o *.pb.* $(SRC_BASE_PATH)/.lib/libnode.a test_propose_batch $(SRC_BASE_PATH)/.sbin/test_propose_batch test_propose_batch 

