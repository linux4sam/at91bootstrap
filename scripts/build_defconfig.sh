#!/bin/bash
#This script will build every defconfig files found in the board directory.

#=======================================
buildConfig(){
configName=$1
echo -e "========================\n Testing the $configName\n ========================"
make $configName
  if [ "$?" -ne "0" ] ; then
    echo "make Error on defconfig : $configName=> $?"
    return 1
  fi
  
  make all
  if [ "$?" -ne "0" ] ; then
    echo -e "!!!!!!!!!!!!!!!!\n make Error build all : $configName => $?"
    return 2
  fi
  
  make mrproper
}
#=======================================
printFlags(){
  configName=$1
  echo -e "========================\n Flags of $configName\n ========================"
  make PrintFlags
  if [ "$?" -ne "0" ] ; then
    echo "make Error on defconfig : $configName=> $?"
    return 1
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
  if [ ! -z "$startConfig" ] && [ "$configName" != "$startConfig" ]; then echo "Skipping $configName" ; continue; fi
  #Forget the startConfig
  startConfig=""
  buildConfig $configName
  [ "$?" -ne "0" ] && echo "Build failed for $configName" && exit $?
  #printFlags $configName
done

echo "startConfig: $startConfig"
if [ -z "$startConfig" ]
then
 echo "ALL BUILDS PASSED !!"
else
 echo "$startConfig : not a known configuration"
 exit 3
fi


