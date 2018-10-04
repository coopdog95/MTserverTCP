#!/bin/bash

COUNTER=0
while [ $COUNTER -lt 10 ]; do
	(./client 127.0.1.1 8080 "This is a long message that shouldn't fit into a single buffer. Count: $COUNTER")
	let COUNTER=COUNTER+1
done