# -------------------------------------------------
# Project created by QtCreator 2009-02-10T13:06:32
# QtNote - Simple note-taking application
# Copyright (C) 2010 Ili'nykh Sergey
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# Contacts:
# E-Mail: rion4ik@gmail.com XMPP: rion@jabber.ru
# -------------------------------------------------
TARGET = qtnote
TEMPLATE = app
CONFIG += tomboy # force tomboy
RESOURCES += main.qrc
QT += xml

include (src/src.pri)

TRANSLATIONS = langs/qtnote_ru.ts
unix { 
    target.path = $$PREFIX/bin
    INSTALLS += target
    
    # translations
    TRANSLATIONS_DIR = $$PREFIX/share/qtnote
    DEFINES += TRANSLATIONS_DIR=\\\"$$TRANSLATIONS_DIR\\\"
    
    # CTRANSLATIONS = langs/qtnote_ru.qm
    # DISTFILES += $$CTRANSLATIONS
    # for(t, CTRANSLATIONS):translations.files += "langs/$${t}"
    translations.files = "langs/qtnote_ru.qm"
    translations.path = $$TRANSLATIONS_DIR

	# Desktop file
	desktop.files = "qtnote.desktop"
	desktop.path = /usr/share/applications

	# Desktop pixmap
	pixmap.files = "images/qtnote.png"
	pixmap.path = /usr/share/pixmaps

	INSTALLS += translations desktop pixmap
}
RC_FILE = win/qtnote.rc

MOC_DIR = .moc
OBJECTS_DIR = .obj
RCC_DIR = .rcc
UI_DIR = .ui
