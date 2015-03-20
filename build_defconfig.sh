#!/bin/bash
#This script will build every defconfig files found in the board directory.

#=======================================
buildConfig(){
configName=$1
echo -e "========================\n Testing the $configName\n ========================"
make $configName
  if [ "$?" -ne "0" ] ; then
    echo "make Error on defconfig : $configName=> $?"
    exit 1
  fi
  
  make all
  if [ "$?" -ne "0" ] ; then
    echo -e "!!!!!!!!!!!!!!!!\n make Error build all : $configName => $?"
    exit 1
  fi
  
  make mrproper
  return 0;
}
#=======================================
printFlags(){
  configName=$1
  echo -e "========================\n Flags of $configName\n ========================"
  make PrintFlags
  if [ "$?" -ne "0" ] ; then
    echo "make Error on defconfig : $configName=> $?"
    exit 1
  fi
}
#=============== MAIN ====================
#If an argument : the last failed config : the restart point
if [ "$#" -eq "1" ]
then
  startConfig="$1"
else
  startConfig=""
fi

configFiles=$(find board -name "*defconfig")

for configFile in $configFiles;
do
  configName=$(basename $configFile)
  echo "$configName - $startConfig"
  if [ ! -z "$startConfig" ] && [ "$configName" != "$startConfig" ]; then echo "Skipping $configName" ; continue; fi
  #Forget the startConfig
  startConfig=""
  buildConfig $configName
  #printFlags $configName
  
done

echo "ALL BUILDS PASSED !!"