#!/bin/bash

BASEDIR=$(cd $(dirname $0) && pwd)
FILENAME=$(basename $BASEDIR)
TESTFLAGS="+map map01"

function usage_and_exit
{
    BASENAME=$(basename $0)
    echo "USAGE: $BASENAME [ make | package <version> | test [ gzdoom | skulltag ] [wad] ]" >&2
    exit
}

function makepk3
{
    if (("x$1" != "x"))
    then
        compressionlevel=0
    else
        compressionlevel=$1
    fi

    if [ -e acc ]
    then
        ACCDIR="."
    else
        ACCDIR="${HOME}/.bin"
    fi

    cd $BASEDIR

    for i in `find $PWD -iname '*.svn'`
    do
        rm -rf $i 2>/dev/null
    done

    EXITCODE=0

    if [ -e pk3/acs ]
    then

        rm pk3/acs/*.o 2> /dev/null

        for file in pk3/acs/*.c
        do

            fileBase=$(basename $file)
            cpwd=$(pwd)
            (cd $ACCDIR && ./acc ${cpwd}/pk3/acs/${fileBase})
            EXITCODE=$(( EXITCODE + $? ))

            if ((EXITCODE != 0))
            then
                break
            fi

        done
    fi

    if ((EXITCODE == 0))
    then
        rm -f $FILENAME.pk3
        cd pk3
        zip -9r ../$FILENAME.pk3 *
    fi

    return $EXITCODE
}

function testpk3
{
    ( makepk3 )

    exitcode=$?

    if (( exitcode != 0 ))
    then
        exit
    fi

    if [ "x${1}" == "xgzdoom" ]
    then
        shift
        gzdoom -file $PWD/${FILENAME}.pk3 $@ ${TESTFLAGS}
        return 0
    fi

    if [ "x${1}" == "xskulltag" ]
    then
        shift
        skulltag -file $PWD/${FILENAME}.pk3 $@ ${TESTFLAGS}
        return 0
    fi

    echo "Invalid test source port $1"
    usage_and_exit
    return 1
}

function packagepk3
{
    pk3version=$1

    grep "[0-9]$" <<< ${FILENAME} 2> /dev/null >&2
    exitcode=$?

    if ((exitcode == 0))
    then
        newname="${FILENAME}_${pk3version}"
    else
        newname="${FILENAME}${pk3version}"
    fi

    newpk3="${newname}.pk3"
    newzip="${newname}.zip"

    cd $BASEDIR

    ( makepk3 9 > /dev/null 2> /dev/null )

    mv ${FILENAME}.pk3 $newpk3
    cp $newpk3 ~/.skulltag/

    zip $newzip $newpk3

    zip -9 $newzip README.txt
    zip -9 $newzip CHANGELOG.txt

    ( makepk3 9 > /dev/null 2> /dev/null )
}




if [ "x$1" == "x" ]
then
    usage_and_exit

elif [ "x$1" == "xpackage" -a "x$2" != "x" ]
then
    packagepk3 $2

elif [ "x$1" == "xtest" -a "x$2" != "x" ]
then
    shift
    testpk3 $@

elif [ "x$1" == "xmake" ]
then
    makepk3
fi
