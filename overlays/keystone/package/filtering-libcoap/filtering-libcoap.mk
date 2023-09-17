################################################################################
#
# libcoap
#
################################################################################

ifeq ($(FILTERING_LIBCOAP),)
$(error FILTERING_LIBCOAP directory not defined)
else
include $(KEYSTONE)/mkutils/pkg-keystone.mk
endif

FILTERING_LIBCOAP_LICENSE = BSD-2-Clause
FILTERING_LIBCOAP_LICENSE_FILES = COPYING LICENSE
FILTERING_LIBCOAP_INSTALL_STAGING = YES
FILTERING_LIBCOAP_CONF_OPTS = \
    -DCMAKE_INSTALL_PREFIX=/usr/local \
	-DENABLE_DOCS=OFF \
    -DENABLE_DTLS=OFF \
    -DWITH_EPOLL=ON \
    -DENABLE_EXAMPLES=OFF \
    -DENABLE_TCP=OFF \
    -DENABLE_OSCORE=OFF \
    -DENABLE_OSCORE_NG=ON \
    -DENABLE_RAP=ON \
    -DENABLE_Q_BLOCK=OFF \
    -DWITH_OBSERVE_PERSIST=OFF

$(eval $(keystone-package))
$(eval $(cmake-package))
