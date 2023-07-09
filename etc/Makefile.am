MODULES = deffile/cm64.def deffile/sc55.def deffile/sc55mk2.def deffile/sc88.def
STED_DATAS = sted2.cnf sted2.fon

INSTALL_PATH = @sted_default_path@

EXTRA_DIST = sted2.cnf.in sted2.fon \
	     ${MODULES}
#             deffile/cm64.def \
#             deffile/sc55.def \
#             deffile/sc55mk2.def \
#             deffile/sc88.def

install-data-hook:
	sed -e 's%@''DEF_PATH''@%${INSTALL_PATH}/deffile%g' ./sted2.cnf.in > ./sted2.cnf ;
	$(mkinstalldirs) $(INSTALL_PATH)/deffile
	cp $(STED_DATAS) $(INSTALL_PATH)
	cp $(MODULES) $(INSTALL_PATH)/deffile
