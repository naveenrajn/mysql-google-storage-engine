# Copyright (c) 2006, 2010, Oracle and/or its affiliates. All rights reserved.
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

find_package(LibXML++ REQUIRED)
include_directories("/usr/local/include/libxml++-2.6;/usr/local/lib/libxml++-2.6/include;/usr/include/libxml2;/usr/include/glibmm-2.4;/usr/lib/x86_64-linux-gnu/glibmm-2.4/include;/usr/include/sigc++-2.0;/usr/lib/x86_64-linux-gnu/sigc++-2.0/include;/usr/include/glib-2.0;/usr/lib/x86_64-linux-gnu/glib-2.0/include")
set(LIBS ${LIBS} ${LIBXMLPP_LIBRARY})

find_package(Curlpp REQUIRED)
include_directories(${CURLPP_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CURLPP_LIBRARIES})

SET(GSTORAGE_PLUGIN_DYNAMIC "ha_gstorage")
SET(GSTORAGE_SOURCES ha_gstorage.cc lib/doclist_service.cc lib/spreadsheets_service.cc lib/util/service.cc lib/util/atom_helper.cc lib/util/string_utils.cc)
MYSQL_ADD_PLUGIN(gstorage ${GSTORAGE_SOURCES} STORAGE_ENGINE MODULE_ONLY LINK_LIBRARIES ${LIBS})
