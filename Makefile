SUBDIRS_SIM = core
SUBDIRS_CORE = core/logic loader sourcepawn/jit

all: $(SUBDIRS_CORE) $(SUBDIRS_SIM)

$(SUBDIRS_SIM):
	$(MAKE) -C $@ ENGINE=original
	$(MAKE) -C $@ ENGINE=orangebox
	$(MAKE) -C $@ ENGINE=orangeboxvalve
	$(MAKE) -C $@ ENGINE=left4dead
	$(MAKE) -C $@ ENGINE=left4dead2
	$(MAKE) -C $@ ENGINE=csgo
	$(MAKE) -C $@ ENGINE=css
	
$(SUBDIRS_CORE):
	$(MAKE) -C $@
	
.PHONY: $(SUBDIRS_CORE) $(SUBDIRS_SIM)