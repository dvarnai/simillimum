SUBDIRS_SIM = core
SUBDIRS_CORE = core/logic loader sourcepawn/jit lua
SUBDIRS_EXTENSIONS = extensions/bintools extensions/clientprefs extensions/curl extensions/geoip extensions/mysql extensions/regex extensions/sqlite extensions/tf2 extensions/topmenus extensions/updater
SUBDIRS_EXTENSIONS_META = extensions/sdkhooks extensions/sdktools
SUBDIRS_EXTENSIONS_CSTRIKE = extensions/cstrike

all: $(SUBDIRS_CORE) $(SUBDIRS_SIM) $(SUBDIRS_EXTENSIONS) $(SUBDIRS_EXTENSIONS_META) $(SUBDIRS_EXTENSIONS_CSTRIKE)

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
	
$(SUBDIRS_EXTENSIONS):
	$(MAKE) -C $@
	
$(SUBDIRS_EXTENSIONS_META):
	$(MAKE) -C $@ ENGINE=original
	$(MAKE) -C $@ ENGINE=orangebox
	$(MAKE) -C $@ ENGINE=orangeboxvalve
	$(MAKE) -C $@ ENGINE=left4dead
	$(MAKE) -C $@ ENGINE=left4dead2
	$(MAKE) -C $@ ENGINE=csgo
	$(MAKE) -C $@ ENGINE=css
	
$(SUBDIRS_EXTENSIONS_CSTRIKE):
	$(MAKE) -C $@ ENGINE=csgo
	$(MAKE) -C $@ ENGINE=css
	
.PHONY: $(SUBDIRS_CORE) $(SUBDIRS_SIM) $(SUBDIRS_EXTENSIONS) $(SUBDIRS_EXTENSIONS_META) $(SUBDIRS_EXTENSIONS_CSTRIKE)