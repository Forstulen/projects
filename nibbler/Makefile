##
## Makefile for  in /home/tholim_r//nibbler-2014-benram_s
## 
## Made by romain tholimet
## Login   <tholim_r@epitech.net>
## 
## Started on  Sun Mar 20 16:06:45 2011 romain tholimet
## Last update Sun Mar 20 19:55:02 2011 romain tholimet
##

EXEC			=	nibbler

PREFIX			=	lib_nibbler_

QT			=	Qt

SFML			=	SFML

GTKMM			=	Gtkmm

RM			=	rm -f

CP			=	cp -f

all			:	$(EXEC) $(QT) $(SFML) $(GTKMM)

$(EXEC)			:
			@($(MAKE) -C Core)
			@($(RM) nibbler)
			@($(CP) Core/nibbler .)

$(QT)			:
			@(cd $(QT) ; qmake-qt4 ; $(MAKE))
			@($(RM) $(PREFIX)$(QT).so)
			@($(CP) $(QT)/$(PREFIX)$(QT).so .)

$(SFML)			:
			@($(MAKE) -C $(SFML))
			@($(RM) $(PREFIX)$(SFML).so)
			@($(CP) $(SFML)/$(PREFIX)$(SFML).so .)

$(GTKMM)		:
			@($(MAKE) -C $(GTKMM))
			@($(RM) $(PREFIX)$(GTKMM).so)
			@($(CP) $(GTKMM)/$(PREFIX)$(GTKMM).so .)

clean			:
			@(cd Core ; $(MAKE) $@)
			@(cd Qt ; $(MAKE) $@)
			@(cd SFML ; $(MAKE) $@)
			@(cd Gtkmm ; $(MAKE) $@)

fclean			:
			@(cd Core ; $(MAKE) $@)
			@(cd Qt ; $(RM) lib_nibbler_Qt.so)
			@(cd Qt ; $(MAKE) clean)
			@(cd SFML ; $(MAKE) $@)
			@(cd Gtkmm ; $(MAKE) $@)
			@($(RM) nibbler $(PREFIX)$(QT).so $(PREFIX)$(SFML).so $(PREFIX)$(GTKMM).so)

re			:	recopy
			@(cd Core ; $(MAKE) $@)
			@(cd Qt ; $(MAKE) clean ; $(MAKE); cd -)
			@(cd SFML ; $(MAKE) $@)
			@(cd Gtkmm ; $(MAKE) $@)
			@($(CP) Core/nibbler .)
			@($(CP) $(QT)/$(PREFIX)$(QT).so .)
			@($(CP) $(SFML)/$(PREFIX)$(SFML).so .)
			@($(CP) $(GTKMM)/$(PREFIX)$(GTKMM).so .)

recopy			:
			@($(RM) nibbler)
			@($(RM) $(PREFIX)$(QT).so)
			@($(RM) $(PREFIX)$(SFML).so)
			@($(RM) $(PREFIX)$(GTKMM).so)

.PHONY			:	all clean fclean re $(EXEC) $(QT) $(SFML) $(GTKMM)
