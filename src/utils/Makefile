SRC_BASE_PATH=/root/lpz/phxpaxos

all:lib_utils test_notifier_pool_bin 

include $(SRC_BASE_PATH)/makefile.mk

include Makefile.define
UTILS_SRC=$(UTILS_OBJ)
UTILS_INCS=$(sort $(SRC_BASE_PATH)/src/utils)
UTILS_FULL_LIB_PATH=$(SRC_BASE_PATH)//src/utils
UTILS_EXTRA_CPPFLAGS=-Wall -Werror

CPPFLAGS+=$(patsubst %,-I%, $(UTILS_INCS))
CPPFLAGS+=$(UTILS_EXTRA_CPPFLAGS)

lib_utils:$(SRC_BASE_PATH)/.lib/libutils.a

$(SRC_BASE_PATH)/.lib/libutils.a: $(UTILS_SRC)
	ar -cvq $@ $(UTILS_SRC)

TEST_NOTIFIER_POOL_SRC=$(TEST_NOTIFIER_POOL_OBJ)
TEST_NOTIFIER_POOL_INCS=$(sort $(SRC_BASE_PATH)/src/utils)
TEST_NOTIFIER_POOL_FULL_LIB_PATH=$(SRC_BASE_PATH)/src/utils $(SRC_BASE_PATH)//src/utils
TEST_NOTIFIER_POOL_EXTRA_CPPFLAGS=-Wall -Werror

CPPFLAGS+=$(patsubst %,-I%, $(TEST_NOTIFIER_POOL_INCS))
CPPFLAGS+=$(TEST_NOTIFIER_POOL_EXTRA_CPPFLAGS)

TEST_NOTIFIER_POOL_LINK=utils
TEST_NOTIFIER_POOL_SYS_LIB=-lpthread
TEST_NOTIFIER_POOL_FLAGS+=$(LDFLAGS)

TEST_NOTIFIER_POOL_FLAGS+=$(patsubst %,-l%, $(TEST_NOTIFIER_POOL_LINK))
TEST_NOTIFIER_POOL_FLAGS+=$(TEST_NOTIFIER_POOL_SYS_LIB)
test_notifier_pool_bin:test_notifier_pool_dir test_notifier_pool

test_notifier_pool_dir:$(TEST_NOTIFIER_POOL_FULL_LIB_PATH)
	@for dir in $^;\
	do \
	current_dir=`readlink $$dir -m`;\
	pwd_dir=`pwd`;\
	pwd_dir=`readlink $$pwd_dir -m`;\
	if ([ "$$current_dir" != "$$pwd_dir" ]); then \
	make -C $$dir;\
	fi;\
	done

test_notifier_pool:$(TEST_NOTIFIER_POOL_SRC)
	$(CXX) $^ -o $@ $(TEST_NOTIFIER_POOL_FLAGS)
	cp $@ $(SRC_BASE_PATH)/.sbin/

clean:
	rm -rf *.o *.pb.* $(SRC_BASE_PATH)/.lib/libutils.a test_notifier_pool $(SRC_BASE_PATH)/.sbin/test_notifier_pool test_notifier_pool 

