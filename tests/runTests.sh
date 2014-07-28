#!/bin/bash

krakenPath="../build/kraken"
testDir=${1:-"../tests"}
ext=${2:-"krak"}

fileList=""
for dir in `find ${testDir} -type f -name "*.${ext}"`; do
	filename=$(basename ${dir})
	filename="${filename%.*}"
	fileList+=\ $testDir\/$filename
done

${krakenPath} "--test" ${fileList}