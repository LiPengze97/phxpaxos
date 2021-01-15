SRC_BASE_PATH=/root/lpz/phxpaxos

all:sub_dir

include $(SRC_BASE_PATH)/makefile.mk

SUBDIRS=phx_multism_echo phxecho phxelection phxkv

.PHONY:sub_dir
sub_dir:$(SUBDIRS)
	@for sub_dir in $^; do \
	make -C $$sub_dir; \
	done

.PHONY:clean
clean:$(SUBDIRS)
	@for sub_dir in $^; do \
	make -C $$sub_dir clean;\
	done
	rm -rf *.o *.pb.*  