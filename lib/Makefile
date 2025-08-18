########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   Simon Barrette & Jerome Collin pour  #####
#####           INF1900 - 2016               #####
#####                                        #####
#####         Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################

# Ce Makefile vous permet de compiler des projets
# pour les microcontrôleurs Atmel AVR sur 
# Linux ou Unix, en utilisant l'outil AVR-GCC. 
# Ce Makefile supporte C & C++

###### Includes ######

#####      Détails spécifiques à la cible       #####
#####  Vous devez les adapter à votre projet   #####

# Nom du microcontrôleur cible
MCU=atmega324pa

# Nom de votre bibliothèque
LIBNAME=liblibrairie

# Niveau d'optimisation
OPTLEVEL=s

# Vérification de la présence des outils
CC=avr-gcc
AR ?= $(shell which avr-ar 2>/dev/null)
REMOVE ?= rm -f

ifeq ($(CC),)
    $(error "avr-gcc n'est pas installé ou introuvable")
endif
ifeq ($(AR),)
    $(error "avr-ar n'est pas installé ou introuvable")
endif

# Fichiers sources
SRCDIR=CAN DEL INTERRUPT_BUTTON MEMOIRE_24 PWM TIMER UART WHEELS DEBUG SOUND INTERPRETER LINE_DETECTOR IR_SENSOR LINE_TRACKER LOCATION ROBOT EDGE_CASE LINE_FOLLOWER CAN_MANAGER
PRJSRC=$(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.cpp))

# Génération des fichiers objets
EXEC=$(PRJSRC:.cpp=.o)

####################################################
#####         Configuration terminée           #####
#####                                          #####
#####  Le reste de cette section contient les  #####
##### détails d'implémentation vous permettant #####
##### de mieux comprendre le fonctionnement de #####
#####   ce Makefile en vue de sa modification  #####
####################################################

####### Cible (Target) #######

LIBRAIRIE=$(LIBNAME).a

####### Création des commandes du Makefile ####### 

.PHONY: all clean

# Compilation complète
all: $(LIBRAIRIE)

# Création de la bibliothèque
$(LIBRAIRIE): $(EXEC)
	$(AR) -crs $(LIBRAIRIE) $(EXEC)

# Compilation des fichiers source
%.o: %.cpp
	$(CC) -mmcu=$(MCU) -O$(OPTLEVEL) -std=c++11 -c $< -o $@

# Vérification des dépendances
-include $(EXEC:.o=.d)

# Nettoyage des fichiers générés
clean:
	$(REMOVE) $(LIBRAIRIE) $(EXEC) *.d
