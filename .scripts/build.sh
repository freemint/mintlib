#!/bin/bash -eux
# -e: Exit immediately if a command exits with a non-zero status.
# -u: Treat unset variables as an error when substituting.
# -x: Display expanded script commands

make SHELL=/bin/bash
make SHELL=/bin/bash DESTDIR="${INSTALL_DIR}" install

ARCHIVE_NAME="${PROJECT_NAME}-${PROJECT_VERSION}-${SHORT_ID}"
BINFILES="sbin/tzinit usr/sbin/tzselect usr/sbin/zdump usr/sbin/zic"

mkdir -p "${DEPLOY_DIR}"

rm -f tz/*.o
make -C tz DESTDIR="${INSTALL_DIR}" type=m68020 install
cd "${INSTALL_DIR}"
: ${CROSS_TOOL}-strip $BINFILES
tar cjf "${DEPLOY_DIR}/${ARCHIVE_NAME}-020.${DEPLOY_ARCHIVE}" $BINFILES usr/share/zoneinfo
rm -f $BINFILES
cd -

rm -f tz/*.o
make -C tz DESTDIR="${INSTALL_DIR}" type=coldfire install
cd "${INSTALL_DIR}"
: ${CROSS_TOOL}-strip $BINFILES
tar cjf "${DEPLOY_DIR}/${ARCHIVE_NAME}-v4e.${DEPLOY_ARCHIVE}" $BINFILES usr/share/zoneinfo
rm -f $BINFILES
cd -

rm -f tz/*.o
make -C tz DESTDIR="${INSTALL_DIR}" type=m68000 install
cd "${INSTALL_DIR}"
:  ${CROSS_TOOL}-strip $BINFILES
tar cjf "${DEPLOY_DIR}/${ARCHIVE_NAME}-000.${DEPLOY_ARCHIVE}" $BINFILES usr/share/zoneinfo
rm -f $BINFILES
rmdir sbin usr/sbin
cd -
