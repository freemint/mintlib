#!/bin/sh -x

SERVER=web196@server43.webgo24.de
UPLOAD_DIR=$SERVER:/home/www/snapshots

if [ -z "${DEPLOY_ARCHIVE+x}" ]
then
	# zip is default
	DEPLOY_ARCHIVE="zip"
fi

ARCHIVE_NAME="${PROJECT_NAME}-${PROJECT_VERSION}-${SHORT_ID}"
ARCHIVE_PATH="${DEPLOY_DIR}/${ARCHIVE_NAME}.${DEPLOY_ARCHIVE}"

mkdir -p "${DEPLOY_DIR}"

if [ "${DEPLOY_ARCHIVE}" = "tar.bz2" ]
then
	cd ${INSTALL_DIR} && tar cjf ${ARCHIVE_PATH} *
elif [ "${DEPLOY_ARCHIVE}" = "tar.xz" ]
then
	cd ${INSTALL_DIR} && tar cJf ${ARCHIVE_PATH} *
elif [ "${DEPLOY_ARCHIVE}" = "tar.gz" ]
then
	cd ${INSTALL_DIR} && tar czf ${ARCHIVE_PATH} *
else
	cd $(dirname ${INSTALL_DIR}) && zip -r -9 ${ARCHIVE_PATH} $(basename ${INSTALL_DIR})
fi

cd -


eval "$(ssh-agent -s)"

PROJECT_DIR="$PROJECT_NAME"
case $PROJECT_DIR in
	m68k-atari-mint-gcc) PROJECT_DIR=gcc ;;
	m68k-atari-mint-binutils-gdb) PROJECT_DIR=binutils ;;
esac

upload_file() {
	local from="$1"
	local to="$2"
	for i in 1 2 3
	do
		scp -o "StrictHostKeyChecking no" "$from" "$to"
		[ $? = 0 ] && return 0
		sleep 1
	done
	exit 1
}

link_file() {
	local from="$1"
	local to="$2"
	for i in 1 2 3
	do
		ssh -o "StrictHostKeyChecking no" $SERVER -- "cd www/snapshots/${PROJECT_DIR}; ln -sf $from $to"
		[ $? = 0 ] && return 0
		sleep 1
	done
	exit 1
}

for f in "" -000 -020 -v4e; do
	upload_file "${DEPLOY_DIR}/${ARCHIVE_NAME}${f}.${DEPLOY_ARCHIVE}" "${UPLOAD_DIR}/${PROJECT_DIR}/${ARCHIVE_NAME}${f}.${DEPLOY_ARCHIVE}"
done
if test -z "${CPU_TARGET}"
then
	link_file "${ARCHIVE_NAME}.${DEPLOY_ARCHIVE}" "${PROJECT_DIR}-latest.${DEPLOY_ARCHIVE}"
fi

echo ${PROJECT_NAME}-${PROJECT_VERSION}-${SHORT_ID} > .latest_version
upload_file .latest_version "${UPLOAD_DIR}/${PROJECT_DIR}/.latest_version"
