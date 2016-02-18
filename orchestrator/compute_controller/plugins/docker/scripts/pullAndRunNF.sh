#!/bin/bash

#Author: Ivano Cerrato
#Date: June 16th 2014
#Brief: pull a NF from a docker repository, and run it.

#command line: sudo ./pullAndRunNF.sh $1 $2 $3 $4 [$5 ...]

#$1 LSI ID				(e.g., 2)
#$2 NF name				(e.g., firewall)
#$3 registry/nf[:tag] 	(e.g., localhost:5000/pcap:latest)
#$4 number_of_ports		(e.g., 2)
#The next $4 parameters are port names to be provided to the container (e.g., vEth0 vEth1)
#The next parameter is a number indicating how many port forwarding must be setup. If not
#zero, the next N*2 elements are: TCP port of the host - TCP port in the container. Note that
#the request for port forwardings cause the creation of a further NIC connected to the docker0
#bridge

tmp_file="$1_$2_tmp"

if (( $EUID != 0 ))
then
    echo "[$0] This script must be executed with ROOT privileges"
    exit 0
fi

#Check if some port forwarding must be set up
num_ports=$4
position_num_forwarding=`expr 4 + $num_ports + 1`
num_forwarding=${!position_num_forwarding}

echo -ne "sudo docker run -d --name $1_$2 "   > $tmp_file

if [ $num_forwarding != 0 ]
then
	echo [`date`]"[$0] Port remapping required. A furter NIC ('eth0' in the container) is created and connected to 'docker0'"
	
	position_host_port=`expr $position_num_forwarding + 1`
	position_docker_port=`expr $position_num_forwarding + 2`
	
	for (( c=0; c<$num_forwarding; c++ ))
	do	
		host_port=${!position_host_port}
		docker_port=${!position_docker_port}
		
		echo [`date`]"[$0] Port remapping between host TCP port $host_port and VNF TCP port $docker_port"
		
		echo -ne "-p 127.0.0.1:$host_port:$docker_port " >> $tmp_file
		
		position_host_port=`expr $position_host_port + 2`
		position_docker_port=`expr $position_docker_port + 2`
	done
	
	firstnicname=1
	lastnicname=`expr $4 + 1`
else
	# The NIC connected to the docker0 is not needed
	echo -ne "--net=\"none\" " >> $tmp_file
	
	firstnicname=0
	lastnicname=$4
fi

echo "--privileged=true  $3 " >> $tmp_file

echo [`date`]"[$0] Executing command: '"`cat $tmp_file`"'"

ID=`bash $tmp_file`

#docker run returns 0 in case of success
ret=`echo $?`

if [ $ret -eq 0 ]
then
	echo [`date`]"[$0] Container $2 started with ID: '"$ID"'"
else
	echo "[$0] An error occurred while starting the container"
	rm $tmp_file
	exit 0
fi

#Save the binding lsi-nf-docker id on a file
file="$1_$2"
echo $ID >> $file

rm $tmp_file

#The following code configures the network for the container just created.
#It is based on the description provided at
#	http://docs.docker.com/articles/networking/#container-networking

PID=`docker inspect --format '{{ .State.Pid }}' $ID`

sudo mkdir -p /var/run/netns
sudo ln -s /proc/$PID/ns/net /var/run/netns/$PID
	
current=5

for (( c=$firstnicname; c<$lastnicname; c++ ))
do	
	ip link set ${!current} netns $PID
	
	echo "[$0] Inserting port ${!current} inside a container. It will have name eth$c"
	
	ip netns exec $PID ip link set dev ${!current} name eth$c
				
 	ip netns exec $PID ip link set eth$c up
	
	current=`expr $current + 1`
done

exit 1
